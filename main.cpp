/* ----------------------------------------------------------------<Header>-
 Name: main.cpp
 Title: Hitori Solver

 Group: TV-41
 Student: Marynenko D.A.
 Written: 2025-05-18
 Revised: 2025-05-19

 Description:   Fill in some cells so that there are no repeating 
                numbers in each row or column. Filled cells must 
                not touch each other. All unfilled cells must be 
                connected to each other by their sides horizontally 
                or vertically so that there is a single continuous 
                space of unfilled cells.
 ------------------------------------------------------------------</Header>-*/
#include <iostream>
#include <vector>
#include <iomanip>
#include <string>

using namespace std;

/* ---------------------------------------------------------------------[<]-
 Function: new_array
 Synopsis: Copies content from original grid to a new array.
 ---------------------------------------------------------------------[>]-*/
void new_array(int row, int col, const vector<vector<int>> &grid, vector<vector<int>> &new_arr);

/* ---------------------------------------------------------------------[<]-
 Function: final_print
 Synopsis: Updates the original grid with shaded cells marked as '#'.
 ---------------------------------------------------------------------[>]-*/
void final_print(int row, int col, vector<vector<int>> &grid, const vector<vector<int>> &new_arr);

/* ---------------------------------------------------------------------[<]-
 Function: print_final
 Synopsis: Prints the grid with '#' characters and numbers in bordered format.
 ---------------------------------------------------------------------[>]-*/
void print_final(int row, int col, const vector<vector<int>> &grid);

/* ---------------------------------------------------------------------[<]-
 Function: print_grid
 Synopsis: Prints the grid in plain format with leading zeros.
 ---------------------------------------------------------------------[>]-*/
void print_grid(int row, int col, const vector<vector<int>> &grid);

/* ---------------------------------------------------------------------[<]-
 Function: is_safe
 Synopsis: Checks if shading a cell is safe (i.e., it will not violate adjacency rule).
 ---------------------------------------------------------------------[>]-*/
bool is_safe(int row, int col, const vector<vector<int>> &grid, int i, int j);

/* ---------------------------------------------------------------------[<]-
 Function: col_count_paubos
 Synopsis: Counts duplicate values downward in the same column.
 ---------------------------------------------------------------------[>]-*/
int col_count_paubos(int row_len, const vector<vector<int>> &grid, int val, int i, int j);

/* ---------------------------------------------------------------------[<]-
 Function: col_count_pataas
 Synopsis: Counts duplicate values upward in the same column.
 ---------------------------------------------------------------------[>]-*/
int col_count_pataas(const vector<vector<int>> &grid, int val, int i, int j);

/* ---------------------------------------------------------------------[<]-
 Function: col_count
 Synopsis: Counts duplicates in both upward and downward column directions.
 ---------------------------------------------------------------------[>]-*/
int col_count(int row_len, const vector<vector<int>> &grid, int val, int i, int j);

/* ---------------------------------------------------------------------[<]-
 Function: row_count_right
 Synopsis: Counts duplicate values to the right in the same row.
 ---------------------------------------------------------------------[>]-*/
int row_count_right(int col_len, const vector<vector<int>> &grid, int val, int i, int j);

/* ---------------------------------------------------------------------[<]-
 Function: row_ount_left
 Synopsis: Counts duplicate values to the left in the same row.
 ---------------------------------------------------------------------[>]-*/
int row_ount_left(const vector<vector<int>> &grid, int val, int i, int j);

/* ---------------------------------------------------------------------[<]-
 Function: row_count
 Synopsis: Counts duplicates in both left and right row directions.
 ---------------------------------------------------------------------[>]-*/
int row_count(int row_len, int colLen, const vector<vector<int>> &grid, int val, int i, int j);

/* ---------------------------------------------------------------------[<]-
 Function: is_neither_shaded_or_unshaded
 Synopsis: Checks if a cell is neither shaded (111) nor unshaded (0).
 ---------------------------------------------------------------------[>]-*/
bool is_neither_shaded_or_unshaded(const vector<vector<int>> &grid, int i, int j);

/* ---------------------------------------------------------------------[<]-
 Function: blacken_sa_column
 Synopsis: Shades all matching values in a column if safe.
 ---------------------------------------------------------------------[>]-*/
void blacken_sa_column(int row_len, int colLen, vector<vector<int>> &grid, int val, int j);

/* ---------------------------------------------------------------------[<]-
 Function: blacken_sa_row
 Synopsis: Shades all matching values in a row if safe.
 ---------------------------------------------------------------------[>]-*/
void blacken_sa_row(int row_len, int colLen, vector<vector<int>> &grid, int val, int i);

/* ---------------------------------------------------------------------[<]-
 Function: whiten
 Synopsis: Marks a cell as unshaded (0) and applies shading rules to row/column.
 ---------------------------------------------------------------------[>]-*/
void whiten(int row_len, int col_len, vector<vector<int>> &grid, int val, int i, int j);

/* ---------------------------------------------------------------------[<]-
 Function: is_corner
 Synopsis: Checks if the cell is at one of the four corners.
 ---------------------------------------------------------------------[>]-*/
int is_corner(int row_len, int col_len, int i, int j);

/* ---------------------------------------------------------------------[<]-
 Function: is_edge
 Synopsis: Checks if the cell is on an edge of the grid.
 ---------------------------------------------------------------------[>]-*/
int is_edge(int row_len, int col_len, int i, int j);

/* ---------------------------------------------------------------------[<]-
 Function: eliminate_around_non_edges
 Synopsis: Applies whitening to all adjacent cells (not on edges).
 ---------------------------------------------------------------------[>]-*/
void eliminate_around_non_edges(int row_len, int col_len, vector<vector<int>> &grid, int i, int j);

/* ---------------------------------------------------------------------[<]-
 Function: eliminate_around_corner
 Synopsis: Applies whitening to two adjacent cells of a corner cell.
 ---------------------------------------------------------------------[>]-*/
void eliminate_around_corner(int row_len, int col_len, vector<vector<int>> &grid, int i, int j);

/* ---------------------------------------------------------------------[<]-
 Function: eliminate_around_edges
 Synopsis: Applies whitening to three adjacent cells of an edge cell.
 ---------------------------------------------------------------------[>]-*/
void eliminate_around_edges(int row_len, int col_len, vector<vector<int>> &grid, int i, int j);

/* ---------------------------------------------------------------------[<]-
 Function: eliminate_around_shaded_parts
 Synopsis: Applies elimination rules to all shaded cells in the grid.
 ---------------------------------------------------------------------[>]-*/
void eliminate_around_shaded_parts(int row_len, int col_len, vector<vector<int>> &grid);

/* ---------------------------------------------------------------------[<]-
 Function: three_adjacent_num_eliminate
 Synopsis: Detects and processes three consecutive duplicates in a row/column.
 ---------------------------------------------------------------------[>]-*/
void three_adjacent_num_eliminate(int row_len, int col_len, vector<vector<int>> &grid);

/* ---------------------------------------------------------------------[<]-
 Function: between_pair_eliminate
 Synopsis: Eliminates the middle cell between two equal numbers if applicable.
 ---------------------------------------------------------------------[>]-*/
void between_pair_eliminate(int row_len, int col_len, vector<vector<int>> &grid);

/* ---------------------------------------------------------------------[<]-
 Function: solve_hitori
 Synopsis: Core solving logic that applies Hitori puzzle rules.
 ---------------------------------------------------------------------[>]-*/
void solve_hitori(int row, int col, vector<vector<int>> &grid);

/* ---------------------------------------------------------------------[<]-
 Function: switch_map
 Synopsis: Loads and solves predefined Hitori puzzle fields.
 ---------------------------------------------------------------------[>]-*/
void switch_map(int number);


int main(){
  int number = 0;
    cout << endl << "Welcome to the Hitori crossword puzzle solver!" << endl;
    while (true){
        cout << endl << "Select:" << endl
             << "1. Field #1" << endl
             << "2. Field #2" << endl
             << "3. Field #3" << endl
             << "4. Field #4" << endl
             << "5. EXIT" << endl
             << "Enter value: ";
        cin >> number;
        if (number == 5){
            break;
        } else if(number == 1 || number == 2 || number == 3 || number == 4){
            switch_map(number);
        } else {
            cout << "Invalid item entered, please try again." << endl << endl;
        }
    }
    return 0;
}

void new_array(int row, int col, const vector<vector<int>> &grid, vector<vector<int>> &new_arr){
  for (int i = 0; i < row; i++){
    for (int j = 0; j < col; j++){
      new_arr[i][j] = grid[i][j];
    }
  }
}

void final_print(int row, int col, vector<vector<int>> &grid, const vector<vector<int>> &new_arr)
{
  for (int i = 0; i < row; i++){
    for (int j = 0; j < col; j++){
      if (new_arr[i][j] == 111){
        grid[i][j] = '#';
      }
    }
  }
}

void print_final(int row, int col, const vector<vector<int>> &grid)
{
  const string separator = "+---";
  const string end_line = "+\n";

  for (int i = 0; i < row; i++){
    for (int j = 0; j < col; j++){
      cout << separator;
    }
    cout << end_line;

    for (int j = 0; j < col; j++){
      cout << "|";
      if (grid[i][j] == '#'){
        cout << setw(3) << '#';
      } else {
        cout << setw(3) << grid[i][j];
      }
    }
    cout << "|" << endl;
  }

  for (int j = 0; j < col; j++){
    cout << separator;
  }
  cout << end_line;
}

void print_grid(int row, int col, const vector<vector<int>> &grid){
  for (int i = 0; i < row; i++){
    for (int j = 0; j < col; j++){
      cout << setw(3) << setfill('0') << grid[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl;
}

bool is_safe(int row, int col, const vector<vector<int>> &grid, int i, int j){
  if (i == 0 && j == 0){
    if (grid[i + 1][j] == 111 || grid[i][j + 1] == 111){
      return false;
    }
    else{
      return true;
    }
  }
  else if (i == 0 && j == col - 1){
    if (grid[i + 1][j] == 111 || grid[i][j - 1] == 111){
      return false;
    }
    else
    {
      return true;
    }
  }
  else if (i == row - 1 && j == 0){
    if (grid[i - 1][j] == 111 || grid[i][j + 1] == 111){
      return false;
    } else {
      return true;
    }
  }
  else if (i == row - 1 && j == col - 1){
    if (grid[i - 1][j] == 111 || grid[i][j - 1] == 111){
      return false;
    } else {
      return true;
    }
  }
  else if (i == 0){
    if (grid[i + 1][j] == 111 || grid[i][j + 1] == 111 || grid[i][j - 1] == 111){
      return false;
    } else {
      return true;
    }
  }
  else if (i == row - 1){
    if (grid[i - 1][j] == 111 || grid[i][j + 1] == 111 || grid[i][j - 1] == 111){
      return false;
    } else {
      return true;
    }
  }
  else if (j == 0){
    if (grid[i - 1][j] == 111 || grid[i + 1][j] == 111 || grid[i][j + 1] == 111){
      return false;
    } else {
      return true;
    }
  }
  else if (j == col - 1){
    if (grid[i - 1][j] == 111 || grid[i + 1][j] == 111 || grid[i][j - 1] == 111){
      return false;
    } else {
      return true;
    }
  }
  else{
    if (grid[i - 1][j] == 111 || grid[i + 1][j] == 111 || grid[i][j - 1] == 111 || grid[i][j + 1] == 111){
      return false;
    } else {
      return true;
    }
  }
}

int col_count_paubos(int row_len, const vector<vector<int>> &grid, int val, int i, int j){
  int col_count_result = 0;
  for (int row_index = i + 1; row_index < row_len; row_index++){
    if (grid[row_index][j] == val){
      col_count_result++;
    }
  }
  return col_count_result;
}

int col_count_pataas(const vector<vector<int>> &grid, int val, int i, int j){
  int col_count_result = 0;
  for (int row_index = i - 1; row_index >= 0; row_index--){
    if (grid[row_index][j] == val){
      col_count_result++;
    }
  }
  return col_count_result;
}

int col_count(int row_len, const vector<vector<int>> &grid, int val, int i, int j){
  if (i == 0){
    return col_count_paubos(row_len, grid, val, i, j);
  }
  else if (i > 0 && i < (row_len - 1)){
    return col_count_paubos(row_len, grid, val, i, j) + col_count_pataas(grid, val, i, j);
  }
  return col_count_pataas(grid, val, i, j);
}

int row_count_right(int col_len, const vector<vector<int>> &grid, int val, int i, int j){
  int row_count_result = 0;
  for (int col_index = j + 1; col_index < col_len; col_index++){
    if (grid[i][col_index] == val){
      row_count_result++;
    }
  }
  return row_count_result;
}

int row_ount_left(const vector<vector<int>> &grid, int val, int i, int j){
  int row_count_result = 0;
  for (int col_index = j - 1; col_index >= 0; col_index--){
    if (grid[i][col_index] == val){
      row_count_result++;
    }
  }
  return row_count_result;
}

int row_count(int row_len, int colLen, const vector<vector<int>> &grid, int val, int i, int j){
  if (j == 0){
    return row_count_right(colLen, grid, val, i, j);
  }
  else if (j > 0 && j < (row_len - 1)){
    return row_ount_left(grid, val, i, j) + row_count_right(colLen, grid, val, i, j);
  }
  return row_ount_left(grid, val, i, j);
}

bool is_neither_shaded_or_unshaded(const vector<vector<int>> &grid, int i, int j){
  return ((grid[i][j] != 0) && (grid[i][j] != 111));
}

void blacken_sa_column(int row_len, int colLen, vector<vector<int>> &grid, int val, int j){
  for (int ii = 0; ii < row_len; ii++){
    if ((grid[ii][j] == val) && is_neither_shaded_or_unshaded(grid, ii, j)){
      if (is_safe(row_len, colLen, grid, ii, j)){
        grid[ii][j] = 111;
      }
    }
  }
}

void blacken_sa_row(int row_len, int colLen, vector<vector<int>> &grid, int val, int i){
  for (int jj = 0; jj < colLen; jj++){
    if ((grid[i][jj] == val) && is_neither_shaded_or_unshaded(grid, i, jj)){
      if (is_safe(row_len, colLen, grid, i, jj)){
        grid[i][jj] = 111;
      }
    }
  }
}

void whiten(int row_len, int col_len, vector<vector<int>> &grid, int val, int i, int j){
  int current_val = grid[i][j];
  if (((row_count(row_len, col_len, grid, val, i, j) == 0) || (col_count(row_len, grid, val, i, j) == 0)) && is_neither_shaded_or_unshaded(grid, i, j)){
    if (col_count(row_len, grid, val, i, j) == 0){
      grid[i][j] = 0;
      blacken_sa_row(row_len, col_len, grid, current_val, i);
    }
    if (row_count(row_len, col_len, grid, val, i, j) == 0){
      grid[i][j] = 0;
      blacken_sa_column(row_len, col_len, grid, current_val, j);
    }
  }
  else if ((row_count(row_len, col_len, grid, current_val, i, j) > 0) && (col_count(row_len, grid, current_val, i, j) > 0)){
    grid[i][j] = 0;
    blacken_sa_row(row_len, col_len, grid, current_val, i);
    blacken_sa_column(row_len, col_len, grid, current_val, j);
  }
}

int is_corner(int row_len, int col_len, int i, int j){
  return ((i == 0 && j == 0) || (i == 0 && j == (col_len - 1)) ||
       (i == (row_len - 1) && j == 0) || (i == (row_len - 1) && j == (col_len - 1)));
}

int is_edge(int row_len, int col_len, int i, int j){
  return ((i == 0) || (j == 0) || (i == (row_len - 1)) || (j == (col_len - 1)));
}

void eliminate_around_non_edges(int row_len, int col_len, vector<vector<int>> &grid, int i, int j){
  whiten(row_len, col_len, grid, grid[i][j + 1], i, j + 1);
  whiten(row_len, col_len, grid, grid[i][j - 1], i, j - 1);
  whiten(row_len, col_len, grid, grid[i + 1][j], i + 1, j);
  whiten(row_len, col_len, grid, grid[i - 1][j], i - 1, j);
}

void eliminate_around_corner(int row_len, int col_len, vector<vector<int>> &grid, int i, int j){
  if (i == 0 && j == 0){
    whiten(row_len, col_len, grid, grid[i + 1][j], i + 1, j);
    whiten(row_len, col_len, grid, grid[i][j + 1], i, j + 1);
  }
  else if (i == 0 && j == (col_len - 1)){
    whiten(row_len, col_len, grid, grid[i][j - 1], i, j - 1);
    whiten(row_len, col_len, grid, grid[i + 1][j], i + 1, j);
  }
  else if (i == (row_len - 1) && j == 0){
    whiten(row_len, col_len, grid, grid[i - 1][j], i - 1, j);
    whiten(row_len, col_len, grid, grid[i][j + 1], i, j + 1);
  }
  else{
    whiten(row_len, col_len, grid, grid[i][j - 1], i, j - 1);
    whiten(row_len, col_len, grid, grid[i - 1][j], i - 1, j);
  }
}

void eliminate_around_edges(int row_len, int col_len, vector<vector<int>> &grid, int i, int j){
  if (i == 0){
    whiten(row_len, col_len, grid, grid[i][j + 1], i, j + 1);
    whiten(row_len, col_len, grid, grid[i][j - 1], i, j - 1);
    whiten(row_len, col_len, grid, grid[i + 1][j], i + 1, j);
  }
  else if (j == 0){
    whiten(row_len, col_len, grid, grid[i - 1][j], i - 1, j);
    whiten(row_len, col_len, grid, grid[i][j + 1], i, j + 1);
    whiten(row_len, col_len, grid, grid[i + 1][j], i + 1, j);
  }
  else if (j == (col_len - 1)){
    whiten(row_len, col_len, grid, grid[i - 1][j], i - 1, j);
    whiten(row_len, col_len, grid, grid[i][j - 1], i, j - 1);
    whiten(row_len, col_len, grid, grid[i + 1][j], i + 1, j);
  }
  else{
    whiten(row_len, col_len, grid, grid[i - 1][j], i - 1, j);
    whiten(row_len, col_len, grid, grid[i][j + 1], i, j + 1);
    whiten(row_len, col_len, grid, grid[i][j - 1], i, j - 1);
  }
}

void eliminate_around_shaded_parts(int row_len, int col_len, vector<vector<int>> &grid){
  for (int i = 0; i < row_len; i++){
    for (int j = 0; j < col_len; j++){
      if (grid[i][j] == 111){
        if (is_edge(row_len, col_len, i, j)){
          if (is_corner(row_len, col_len, i, j))
            eliminate_around_corner(row_len, col_len, grid, i, j);
          else
            eliminate_around_edges(row_len, col_len, grid, i, j);
        }
        else{
          eliminate_around_non_edges(row_len, col_len, grid, i, j);
        }
      }
    }
  }
}

void three_adjacent_num_eliminate(int row_len, int col_len, vector<vector<int>> &grid){
  for (int i = 0; i < row_len; i++){
    for (int j = 0; j < col_len; j++){
      if ((grid[i][j] != 111) && (grid[i][j] != 0)){
        if ((j + 2 < col_len) && (grid[i][j] == grid[i][j + 1]) && (grid[i][j] == grid[i][j + 2])){
          grid[i][j] = 111;
          grid[i][j + 2] = 111;
          whiten(row_len, col_len, grid, grid[i][j + 1], i, j + 1);
        }
        else if ((i + 2 < row_len) && (grid[i][j] == grid[i + 1][j]) && (grid[i][j] == grid[i + 2][j])){
          grid[i][j] = 111;
          grid[i + 2][j] = 111;
          whiten(row_len, col_len, grid, grid[i + 1][j], i + 1, j);
        }
        eliminate_around_shaded_parts(row_len, col_len, grid);
      }
    }
  }
}

void between_pair_eliminate(int row_len, int col_len, vector<vector<int>> &grid){
  for (int i = 0; i < row_len; i++){
    for (int j = 0; j < col_len; j++){
      if (grid[i][j] != 111 && grid[i][j] != 0){
        if ((i == 0) || (i == (row_len - 1))){
          if ((grid[i][j - 1] == grid[i][j + 1]) &&
              is_neither_shaded_or_unshaded(grid, i, j - 1) &&
              is_neither_shaded_or_unshaded(grid, i, j + 1))
          {
            whiten(row_len, col_len, grid, grid[i][j], i, j);
          }
        }
        else if ((j == 0) || (j == (col_len - 1)))
        {
          if ((grid[i - 1][j] == grid[i + 1][j]) &&
              is_neither_shaded_or_unshaded(grid, i - 1, j) &&
              is_neither_shaded_or_unshaded(grid, i + 1, j))
          {
            whiten(row_len, col_len, grid, grid[i][j], i, j);
          }
        }
        else
        {
          if ((is_neither_shaded_or_unshaded(grid, i, j - 1) &&
            is_neither_shaded_or_unshaded(grid, i, j + 1)) ||
              (is_neither_shaded_or_unshaded(grid, i - 1, j) &&
            is_neither_shaded_or_unshaded(grid, i + 1, j)))
          {
            if ((grid[i][j - 1] == grid[i][j + 1]) ||
                (grid[i - 1][j] == grid[i + 1][j]))
            {
              whiten(row_len, col_len, grid, grid[i][j], i, j);
            }
          }
        }
      }
      eliminate_around_shaded_parts(row_len, col_len, grid);
    }
  }
}

void solve_hitori(int row, int col, vector<vector<int>> &grid){
  for (int j = 0; j < col; j++){
    for (int i = 0; i < row; i++){
      if (((col_count(row, grid, grid[i][j], i, j) == 0) ||
        (row_count(row, col, grid, grid[i][j], i, j) == 0)) &&
          is_neither_shaded_or_unshaded(grid, i, j))
      {
        whiten(row, col, grid, grid[i][j], i, j);
        eliminate_around_shaded_parts(row, col, grid);
      }
    }
  }
}

void switch_map(int number){
  switch (number){
  case 1: {
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
        {10, 10, 8, 7, 1, 2, 1, 3, 6, 4}};

    vector<vector<int>> final(10, vector<int>(10, 0));
    new_array(10, 10, data1, final);
    three_adjacent_num_eliminate(10, 10, final);
    between_pair_eliminate(10, 10, final);
    solve_hitori(10, 10, final);
    final_print(10, 10, data1, final);
    cout << "Solution:" << endl;
    print_final(10, 10, data1);
    break;
  }

  case 2: {
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
        {4, 7, 5, 6, 8, 7, 4, 3, 6, 3}};

    vector<vector<int>> final(10, vector<int>(10, 0));
    new_array(10, 10, data2, final);
    three_adjacent_num_eliminate(10, 10, final);
    between_pair_eliminate(10, 10, final);
    solve_hitori(10, 10, final);
    final_print(10, 10, data2, final);
    cout << "Solution:" << endl;
    print_final(10, 10, data2);
    break;
  }

  case 3: {
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
        {8, 6, 4, 6, 5, 2, 4, 3, 7, 9}};



    vector<vector<int>> final(10, vector<int>(10, 0));
    new_array(10, 10, data3, final);
    three_adjacent_num_eliminate(10, 10, final);
    between_pair_eliminate(10, 10, final);
    solve_hitori(10, 10, final);
    final_print(10, 10, data3, final);
    cout << "Solution:" << endl;
    print_final(10, 10, data3);
    break;
  }

  case 4: {
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
        {10, 1, 2, 3, 7, 6, 11, 10, 4, 1, 9, 5}};

    vector<vector<int>> final(12, vector<int>(12, 0));
    new_array(12, 12, data4, final);
    three_adjacent_num_eliminate(12, 12, final);
    between_pair_eliminate(12, 12, final);
    solve_hitori(12, 12, final);
    final_print(12, 12, data4, final);
    cout << "Solution:" << endl;
    print_final(12, 12, data4);
    break;
  }

  default: {
    cout << "Wrong map" << endl;
  }
  }
}
