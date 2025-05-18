 #include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Grid {
    int size;
    vector<vector<int>> value;
    vector<vector<bool>> painted;
};

class HitoriSolver {
private:
    Grid grid;
    int rows, cols;

    bool isConnected() {
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));
        int startX = -1, startY = -1;
        int count = 0;

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (!grid.painted[i][j]) {
                    startX = i;
                    startY = j;
                    count++;
                }
            }
        }

        if (count == 0) return false;

        queue<pair<int, int>> q;
        q.push({startX, startY});
        visited[startX][startY] = true;
        int connectedCount = 1;

        const int dx[4] = {-1, 1, 0, 0};
        const int dy[4] = {0, 0, -1, 1};

        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();

            for (int i = 0; i < 4; i++) {
                int nx = x + dx[i];
                int ny = y + dy[i];

                if (nx >= 0 && nx < rows && ny >= 0 && ny < cols) {
                    if (!grid.painted[nx][ny] && !visited[nx][ny]) {
                        visited[nx][ny] = true;
                        connectedCount++;
                        q.push({nx, ny});
                    }
                }
            }
        }

        return connectedCount == count;
    }

    bool noAdjacentPainted() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (grid.painted[i][j]) {
                    if (i > 0 && grid.painted[i-1][j]) return false;
                    if (j > 0 && grid.painted[i][j-1]) return false;
                    if (i < rows-1 && grid.painted[i+1][j]) return false;
                    if (j < cols-1 && grid.painted[i][j+1]) return false;
                }
            }
        }
        return true;
    }
    
    bool checkUniqueness() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (!grid.painted[i][j]) {
                    for (int k = j+1; k < cols; k++) {
                        if (!grid.painted[i][k] && grid.value[i][j] == grid.value[i][k]) {
                            return false;
                        }
                    }
                }
            }
        }

        for (int j = 0; j < cols; j++) {
            for (int i = 0; i < rows; i++) {
                if (!grid.painted[i][j]) {
                    for (int k = i+1; k < rows; k++) {
                        if (!grid.painted[k][j] && grid.value[i][j] == grid.value[k][j]) {
                            return false;
                        }
                    }
                }
            }
        }

        return true;
    }

    bool solve(int row, int col) {
        if (row == rows) {
            return checkUniqueness() && isConnected() && noAdjacentPainted();
        }

        int nextRow = col == cols-1 ? row+1 : row;
        int nextCol = col == cols-1 ? 0 : col+1;

        if (solve(nextRow, nextCol)) {
            return true;
        }

        grid.painted[row][col] = true;
        if (noAdjacentPainted() && solve(nextRow, nextCol)) {
            return true;
        }
        grid.painted[row][col] = false;

        return false;
    }


public:
    HitoriSolver(const Grid& g) : grid(g), rows(g.size), cols(g.size) {
        grid.painted.resize(rows, vector<bool>(cols, false));
    }

    bool solvePuzzle() {
        return solve(0, 0);
    }

    void printSolution() {
        cout << "Solution:\n";
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (grid.painted[i][j]) {
                    cout << "[" << grid.value[i][j] << "] ";
                } else {
                    cout << " " << grid.value[i][j] << "  ";
                }
            }
            cout << endl;
        }
    }
};

Grid GridSwitch(const int num){
    switch (num){
        case 1:
            return {
                10,
                {{5, 7, 2, 1, 8, 5, 3, 10, 5, 9},
                {9, 3, 7, 6, 10, 8, 5, 4, 2, 6},
                {7, 1, 10, 4, 8, 6, 7, 7, 5, 10},
                {1, 3, 4, 9, 7, 8, 3, 5, 8, 10},
                {7, 2, 6, 8, 6, 3, 10, 1, 4, 5},
                {8, 3, 3, 5, 9, 5, 6, 5, 7, 5},
                {1, 8, 1, 10, 6, 9, 4, 6, 1, 7},
                {3, 10, 1, 5, 6, 4, 1, 9, 6, 2},
                {4, 5, 10, 7, 3, 8, 1, 8, 9, 4},
                {10, 10, 8, 7, 1, 2, 1, 3, 6, 4}},
                {}};
        case 2:
            return {
                10,
                {{6, 6, 9, 7, 3, 1, 8, 1, 3, 6},
                {2, 3, 7, 6, 9, 7, 1, 8, 4, 1},
                {5, 4, 2, 3, 4, 6, 9, 5, 8, 5},
                {7, 8, 4, 4, 2, 10, 10, 9, 10, 6},
                {6, 10, 7, 8, 9, 4, 7, 10, 9, 3},
                {8, 9, 8, 5, 7, 8, 1, 5, 10, 4},
                {4, 10, 3, 9, 4, 5, 7, 1, 9, 8},
                {8, 2, 4, 8, 3, 6, 6, 4, 1, 5},
                {5, 9, 8, 2, 4, 10, 3, 6, 10, 9},
                {4, 7, 5, 6, 8, 7, 4, 3, 6, 3}},
                {}};
        case 3:
            return {
                10,
                {{6, 2, 8, 9, 4, 6, 8, 6, 4, 10},
                {1, 5, 6, 10, 3, 4, 2, 9, 2, 8},
                {3, 4, 1, 8, 1, 3, 1, 10, 5, 7},
                {5, 9, 10, 4, 9, 6, 2, 5, 4, 10},
                {4, 6, 8, 1, 10, 9, 1, 7, 3, 2},
                {3, 9, 6, 2, 8, 4, 4, 1, 6, 3},
                {6, 5, 1, 5, 4, 8, 1, 2, 5, 4},
                {3, 8, 2, 10, 1, 7, 6, 5, 10, 3},
                {10, 7, 10, 3, 8, 1, 9, 7, 8, 10},
                {8, 6, 4, 6, 5, 2, 4, 3, 7, 9}},
                {}};
        case 4:
            return {
                12,
                {{6, 10, 5, 5, 11, 3, 10, 4, 10, 1, 2, 8},
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
                {10, 1, 2, 3, 7, 6, 11, 10, 4, 1, 9, 5}},
                {}};
        return {0, {}, {}};
    }
}

int main() {
    int num = 0;
    Grid grid = GridSwitch(num);
    HitoriSolver solver(grid);
    if (solver.solvePuzzle()) {
        solver.printSolution();
    } else {
        cout << "No solution found.\n";
    }

    return 0;
}
