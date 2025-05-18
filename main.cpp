#include <iostream>
using namespace std;

#define MAP_WIDTH 6
#define MAP_HEIGHT 6

struct Map
{
    int map_number[MAP_HEIGHT][MAP_WIDTH];
    bool map_check[MAP_HEIGHT][MAP_WIDTH];
};

void Filling_An_Map_Check(Map *map, const int *height, const int *width)
{
    for (int i = 0; i < *height; i++)
    {
        for (int j = 0; j < *width; j++)
        {
            map->map_check[i][j] = false;
        }
    }
}

void Check_Columns_Down(Map *map, const int *height, const int *width)
{
    for (int j = 0; j < *width; j++)
    {
        for (int i = *height - 1; i >= 0; i--)
        {
            for (int k = i - 1; k >= 0; k--)
            {
                if (map->map_number[i][j] == map->map_number[k][j] && !map->map_check[k][j])
                {
                    map->map_check[i][j] = true;
                    break;
                }
            }
        }
    }
}

void Check_Columns_Up(Map *map, const int *height, const int *width)
{
    for (int j = 0; j < *width; j++)
    {
        for (int i = 0; i < *height; i++)
        {
            for (int k = i + 1; k < *height; k++)
            {
                if (map->map_number[i][j] == map->map_number[k][j] && !map->map_check[k][j])
                {
                    map->map_check[i][j] = true;
                    break;
                }
            }
        }
    }
}

void Check_Rows(Map *map, const int *height, const int *width)
{
    for (int i = 0; i < *height; i++)
    {
        for (int j = 0; j < *width; j++)
        {
            for (int k = 0; k < *width; k++)
            {
                if (map->map_number[i][j] == map->map_number[i][k] && (j != k) && (!map->map_check[i][k]))
                {
                    map->map_check[i][j] = true;
                    break;
                }
            }
        }
    }
}

void Check_Map(Map *map, const int *height, const int *width)
{
    for (int i = 0; i < *height; i++)
    {
        for (int j = 0; j < *width-1; j++)
        {
            if (map->map_check[i][j] == map->map_check[i][j + 1])
            {
                map->map_check[i][j] = false;
            }
        }
    }

    for (int j = 0; j < *width; j++)
    {
        for (int i = *height - 1; i >= 0; i--)
        {
            if (map->map_check[j][i] == map->map_check[j-1][i])
            {   
                map->map_check[j-1][i] = false;
                for (int k = *height -1; k >= 0; k-- )
                {
                    if ( map->map_number[j-1][i] == map->map_number[k][i] && (k != (j-1)))
                    {
                        map->map_check[k][i] = true;
                    }
                }
            }
        }
    }
}

void printMap(const Map &m)
{
    cout << "map_number:" << endl;
    for (int i = 0; i < MAP_HEIGHT; ++i)
    {
        for (int j = 0; j < MAP_WIDTH; ++j)
        {
            cout << m.map_number[i][j] << " ";
        }
        cout << endl;
    }

    cout << "\nmap_check:" << endl;
    for (int i = 0; i < MAP_HEIGHT; ++i)
    {
        for (int j = 0; j < MAP_WIDTH; ++j)
        {
            cout << m.map_check[i][j] << " ";
        }
        cout << endl;
    }
}

int main()
{
    Map map = {
        {{6, 6, 3, 2, 1, 5},
         {1, 2, 6, 3, 5, 4},
         {5, 1, 4, 2, 3, 4},
         {3, 3, 3, 5, 2, 1},
         {4, 2, 1, 6, 5, 3},
         {6, 1, 5, 4, 4, 4}},
        {}};

    int height = MAP_HEIGHT, width = MAP_WIDTH;

    Filling_An_Map_Check(&map, &height, &width);
    Check_Columns_Down(&map, &height, &width);
    Check_Rows(&map, &height, &width);
    Check_Map(&map, &height, &width);

    printMap(map);

    return 0;
}
