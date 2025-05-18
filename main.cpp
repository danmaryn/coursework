 #include <iostream>
using namespace std;

#define MAP_WIDTH 6
#define MAP_HEIGHT 6

struct Map
{
    int map_number[MAP_HEIGHT][MAP_WIDTH];
    bool map_check[MAP_HEIGHT][MAP_WIDTH];
};

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

    return 0;
}
