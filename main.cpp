#include <iostream>
using namespace std;

#define SIZE 6

struct Grid {
    int value[SIZE][SIZE];
    bool painted[SIZE][SIZE];
};

class HitoriSolver {
private:
    Grid grid;
    int rows, cols;

    bool isConnected() {
        bool visited[SIZE][SIZE] = {false};
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

        int queue[SIZE*SIZE][2];
        int front = 0, rear = 0;
        queue[rear][0] = startX;
        queue[rear][1] = startY;
        rear++;
        visited[startX][startY] = true;
        int connectedCount = 1;

        const int dx[4] = {-1, 1, 0, 0};
        const int dy[4] = {0, 0, -1, 1};

        while (front < rear) {
            int x = queue[front][0];
            int y = queue[front][1];
            front++;

            for (int i = 0; i < 4; i++) {
                int nx = x + dx[i];
                int ny = y + dy[i];

                if (nx >= 0 && nx < rows && ny >= 0 && ny < cols) {
                    if (!grid.painted[nx][ny] && !visited[nx][ny]) {
                        visited[nx][ny] = true;
                        connectedCount++;
                        queue[rear][0] = nx;
                        queue[rear][1] = ny;
                        rear++;
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
    HitoriSolver(const Grid& g) : grid(g), rows(SIZE), cols(SIZE) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                grid.painted[i][j] = false;
            }
        }
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

int main() {
    Grid grid = {
        {{6, 6, 3, 2, 1, 5},
         {1, 2, 6, 3, 5, 4},
         {5, 1, 4, 2, 3, 4},
         {3, 3, 3, 5, 2, 1},
         {4, 2, 1, 6, 5, 3},
         {6, 1, 5, 4, 4, 4}},
        {}};

    HitoriSolver solver(grid);
    if (solver.solvePuzzle()) {
        solver.printSolution();
    } else {
        cout << "No solution found.\n";
    }

    return 0;
}