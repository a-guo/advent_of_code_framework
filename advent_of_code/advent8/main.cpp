#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void printGrid(vector<vector<int> >& grid) {
  for (auto& row : grid) {
    for (auto& i : row) {
      cout << i;
    }
    cout << endl;
  }
  cout << endl;
}

int findPerimeter(vector<vector<int> >& grid) {
  int width = grid[0].size();
  int len = grid.size() - 2;
  return (width + len) * 2;
}

bool isVisibleUp(int row, int col, vector<vector<int> >& grid) {
  int curr = grid[row][col];
  for (int i = row - 1; i >= 0; i--) {
    if (grid[i][col] >= curr) return false;
  }
  return true;
}

bool isVisibleDown(int row, int col, vector<vector<int> >& grid) {
  int curr = grid[row][col];
  for (int i = row + 1; i < grid.size(); i++) {
    if (grid[i][col] >= curr) return false;
  }
  return true;
}

bool isVisibleLeft(int row, int col, vector<vector<int> >& grid) {
  int curr = grid[row][col];
  for (int i = col - 1; i >= 0; i--) {
    if (grid[row][i] >= curr) return false;
  }
  return true;
}

bool isVisibleRight(int row, int col, vector<vector<int> >& grid) {
  int curr = grid[row][col];
  for (int i = col + 1; i < grid[0].size(); i++) {
    if (grid[row][i] >= curr) return false;
  }
  return true;
}

bool isVisible(int row, int col, vector<vector<int> >& grid) {
  return isVisibleUp(row, col, grid) || isVisibleDown(row, col, grid)
  || isVisibleLeft(row, col, grid) || isVisibleRight(row, col, grid);
}

int findInterior(vector<vector<int> >& grid) {
  int visible = 0;
  int rowMax = grid.size();
  int colMax = grid[0].size();
  for (int row = 0; row < rowMax; row++) {
    for (int col = 0; col < colMax; col++) {
      if (isVisible(row, col, grid)) {
        visible++;
        cout << "visible: " << row << "," << col << " : " << grid[row][col] << endl;
      }
    }
  }
  return visible;
}

int main() {
  ifstream input ("input.txt");
  // ifstream input("test.txt");
  string line;
  vector<vector<int> > grid;
  while (getline(input, line)) {
    vector<int> row;
    for (auto& c : line) {
      row.push_back((int)c - 48);
    }
    grid.push_back(row);
  }
  // printGrid(grid);
  int visibleEdge = findPerimeter(grid);
  int visibleInterior = findInterior(grid);
  // int totalVisible = visibleEdge + visibleInterior;
  // cout << "total = " << visibleEdge << " + " << visibleInterior << " = " << totalVisible << endl;
  cout << "visible: " << visibleInterior << endl;
  return 0;
}
