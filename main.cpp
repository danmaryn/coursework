#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

struct Map{
    int height;
    int width;
    vector<vector<int>> map_number;
    vector<vector<bool>> map_check;

    Map(int h, int w, const vector<vector<int>> &numbers)
        : height(h), width(w), map_number(numbers), map_check(h, vector<bool>(w, false)) {}
};

class HitoriSolver{
private:
    void Filling_An_Map_Check(Map &map){
        for (int i = 0; i < map.height; ++i){
            for (int j = 0; j < map.width; ++j){
                map.map_check[i][j] = false;
            }
        }
    }

    void Check_Columns_Down(Map &map){
        for (int j = 0; j < map.width; ++j){
            for (int i = map.height - 1; i >= 0; --i){
                for (int k = i - 1; k >= 0; --k){
                    if (map.map_number[i][j] == map.map_number[k][j] && !map.map_check[k][j]){
                        map.map_check[i][j] = true;
                        break;
                    }
                }
            }
        }                
    }

    void Check_Rows(Map &map){
        for (int i = 0; i < map.height; ++i){
            for (int j = 0; j < map.width; ++j){
                for (int k = 0; k < map.width; ++k){
                    if (j != k && map.map_number[i][j] == map.map_number[i][k] && !map.map_check[i][k]){
                        map.map_check[i][j] = true;
                        break;
                    }
                }
            }
        }                
    }

    bool Search_Row(Map &map, int y, int x){
        for (int j = 0; j < map.width; ++j){
            if (j != x && map.map_number[y][x] == map.map_number[y][j] && !map.map_check[y][j]){
                map.map_check[y][x] = false;
                map.map_check[y][j] = true;
                return true;
            }
        }
        return false;
    }

    bool Search_Columns(Map &map, int y, int x){
        for (int i = 0; i < map.height; ++i){
            if (i != y && map.map_number[y][x] == map.map_number[i][x] && !map.map_check[i][x]){
                map.map_check[y][x] = false;
                map.map_check[i][x] = true;
                return true;
            }
        }
        return false;
    }

    void Joint_Check(Map &map)
    {
        int h = map.height;
        int w = map.width;

        for (int i = 0; i < h; ++i)
        {
            for (int j = 0; j < w; ++j)
            {
                if (!map.map_check[i][j])
                {
                    if (i == 0 && j == 0)
                    {
                        if (map.map_check[0][1] && map.map_check[1][0])
                        {
                            if (!Search_Row(map, 0, 1))
                                if (!Search_Columns(map, 0, 1))
                                    break;
                            if (!Search_Row(map, 1, 0))
                                if (!Search_Columns(map, 1, 0))
                                    break;
                        }
                    }
                    else if (i == 0 && j == w - 1)
                    {
                        if (map.map_check[0][j - 1] && map.map_check[1][j])
                        {
                            if (!Search_Row(map, 0, j))
                                if (!Search_Columns(map, 0, j))
                                    break;
                            if (!Search_Row(map, 1, j))
                                if (!Search_Columns(map, 1, j))
                                    break;
                        }
                    }
                    else if (i == h - 1 && j == 0)
                    {
                        if (map.map_check[i - 1][0] && map.map_check[i][1])
                        {
                            if (!Search_Columns(map, i, 0))
                                if (!Search_Row(map, i, 0))
                                    break;
                            if (!Search_Row(map, i, 1))
                                if (!Search_Columns(map, i, 1))
                                    break;
                        }
                    }
                    else if (i == h - 1 && j == w - 1)
                    {
                        if (map.map_check[i][j - 1] && map.map_check[i - 1][j])
                        {
                            if (!Search_Row(map, i, j))
                                Search_Columns(map, i, j);
                            if (!Search_Columns(map, i, j))
                                Search_Row(map, i, j);
                        }
                    }
                    else
                    {
                        int count = 0;
                        if (i > 0 && map.map_check[i - 1][j])
                            ++count;
                        if (j > 0 && map.map_check[i][j - 1])
                            ++count;
                        if (i < h - 1 && map.map_check[i + 1][j])
                            ++count;
                        if (j < w - 1 && map.map_check[i][j + 1])
                            ++count;

                        if (count == 4)
                        {
                            if (!Search_Row(map, i, j))
                                Search_Columns(map, i, j);
                        }
                    }
                }
            }
        }
    }

    void Check_Map(Map &map)
    {
        for (int i = 0; i < map.height; ++i)
            for (int j = 0; j + 1 < map.width; ++j)
                if (map.map_check[i][j] == map.map_check[i][j + 1])
                    map.map_check[i][j] = false;

        for (int j = 0; j < map.width; ++j)
            for (int i = map.height - 1; i > 0; --i)
                if (map.map_check[i][j] == map.map_check[i - 1][j])
                {
                    map.map_check[i - 1][j] = false;
                    for (int k = map.height - 1; k >= 0; --k)
                        if (k != i - 1 && map.map_number[i - 1][j] == map.map_number[k][j])
                            map.map_check[k][j] = true;
                }

        Joint_Check(map);

        for (int i = 0; i < map.height; ++i)
            for (int j = 0; j < map.width - 1; ++j)
                if (map.map_check[i][j] && map.map_check[i][j] == map.map_check[i][j + 1])
                    if (!Search_Columns(map, i, j))
                        Search_Columns(map, i, j + 1);

        for (int j = 0; j < map.width; ++j)
            for (int i = 0; i < map.height - 1; ++i)
                if (map.map_check[i][j] && map.map_check[i][j] == map.map_check[i + 1][j])
                    if (!Search_Row(map, i, j))
                        Search_Row(map, i + 1, j);
    }

public:
    HitoriSolver(Map &map){
        Filling_An_Map_Check(map);
        Check_Columns_Down(map);
        Check_Rows(map);
        Check_Map(map);
    }

    void printMap(const Map &m){
        const int cellWidth = 3;
        const string separator = "+";

        for (int i = 0; i < m.height; ++i){
            for (int j = 0; j < m.width; ++j){
                cout << separator << string(cellWidth, '-');
            }            
            cout << "+" << endl;

            for (int j = 0; j < m.width; ++j){
                cout << "|";
                if (m.map_check[i][j]){
                    cout << setw(cellWidth) << "#";
                } else {
                    cout << setw(cellWidth) << m.map_number[i][j];
                }
            }
            cout << "|" << endl;
        }

        for (int j = 0; j < m.width; ++j){
            cout << separator << string(cellWidth, '-');
        }
        cout << "+" << endl;
    }
};

Map SwitchMap(int number)
{
    vector<vector<int>> data1 = {
        {5, 7, 2, 1, 8, 5, 3, 10, 5, 9},
        {9, 3, 7, 6, 10, 8, 5, 4, 2, 6},
        {7, 1, 10, 4, 8, 6, 7, 7, 5, 10},
        {1, 3, 4, 9, 7, 8, 3, 5, 8, 10},
        {7, 2, 6, 8, 6, 3, 10, 1, 4, 5},
        {8, 3, 3, 5, 9, 5, 6, 5, 7, 5},
        {1, 8, 1, 10, 6, 9, 4, 6, 1, 7},
        {3, 10, 1, 5, 6, 4, 1, 9, 6, 2},
        {4, 5, 10, 7, 3, 8, 1, 8, 9, 4},
        {10, 10, 8, 7, 1, 2, 1, 3, 6, 4}
    };

    vector<vector<int>> data2 = {
        {6, 6, 9, 7, 3, 1, 8, 1, 3, 6},
        {2, 3, 7, 6, 9, 7, 1, 8, 4, 1},
        {5, 4, 2, 3, 4, 6, 9, 5, 8, 5},
        {7, 8, 4, 4, 2, 10, 10, 9, 10, 6},
        {6, 10, 7, 8, 9, 4, 7, 10, 9, 3},
        {8, 9, 8, 5, 7, 8, 1, 5, 10, 4},
        {4, 10, 3, 9, 4, 5, 7, 1, 9, 8},
        {8, 2, 4, 8, 3, 6, 6, 4, 1, 5},
        {5, 9, 8, 2, 4, 10, 3, 6, 10, 9},
        {4, 7, 5, 6, 8, 7, 4, 3, 6, 3}
    };

    vector<vector<int>> data3 = {
        {6, 2, 8, 9, 4, 6, 8, 6, 4, 10},
        {1, 5, 6, 10, 3, 4, 2, 9, 2, 8},
        {3, 4, 1, 8, 1, 3, 1, 10, 5, 7},
        {5, 9, 10, 4, 9, 6, 2, 5, 4, 10},
        {4, 6, 8, 1, 10, 9, 1, 7, 3, 2},
        {3, 9, 6, 2, 8, 4, 4, 1, 6, 3},
        {6, 5, 1, 5, 4, 8, 1, 2, 5, 4},
        {3, 8, 2, 10, 1, 7, 6, 5, 10, 3},
        {10, 7, 10, 3, 8, 1, 9, 7, 8, 10},
        {8, 6, 4, 6, 5, 2, 4, 3, 7, 9}
    };

    vector<vector<int>> data4 = {
        {6, 10, 5, 5, 11, 3, 10, 4, 10, 1, 2, 8},
        {8, 6, 1, 9, 10, 5, 7, 2, 11, 4, 8, 3},
        {4, 9, 7, 12, 6, 2, 9, 3, 8, 12, 7, 4},
        {11, 5, 12, 1, 4, 9, 5, 11, 6, 7, 3, 2},
        {3, 11, 6, 2, 5, 1, 3, 5, 10, 8, 12, 4},
        {7, 1, 10, 11, 2, 7, 3, 6, 9, 2, 5, 11},
        {12, 7, 11, 4, 9, 10, 1, 9, 12, 6, 5, 11},
        {5, 4, 6, 1, 3, 12, 2, 12, 7, 7, 11, 10},
        {4, 5, 12, 10, 6, 8, 9, 8, 2, 11, 6, 1},
        {2, 3, 9, 7, 12, 5, 6, 1, 3, 3, 4, 7},
        {4, 8, 3, 5, 5, 11, 6, 2, 1, 10, 8, 6},
        {10, 1, 2, 3, 7, 6, 11, 10, 4, 1, 9, 5}
    };

    switch (number){
    case 1:
        return Map(10, 10, data1);
    case 2:
        return Map(10, 10, data2);
    case 3:
        return Map(10, 10, data3);
    case 4:
        return Map(12, 12, data4);
    default:
        return Map(0, 0, {});
    }
}

int main(){
    int number = 0;
    while (true){
        cout << "Switch:\n"
             << "\t1. Map 1\n"
             << "\t2. Map 2\n"
             << "\t3. Map 3\n"
             << "\t4. Map 4\n"
             << "\t5. Exit\n"
             << "Set Number: ";
        cin >> number;
        if (number == 5)
            break;
        Map map = SwitchMap(number);
        if (map.height == 0 || map.width == 0)
            break;
        HitoriSolver hitori(map);
        hitori.printMap(map);
    }
    return 0;
}
