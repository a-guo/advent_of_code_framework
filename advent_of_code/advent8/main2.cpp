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

int scenicScoreUp(int row, int col, vector<vector<int> >& grid) {
  int curr = grid[row][col];
  int trees = 0;
  for (int i = row - 1; i >= 0; i--) {
    trees++;
    if (grid[i][col] >= curr) break;
  }
  return trees;
}

int scenicScoreDown(int row, int col, vector<vector<int> >& grid) {
  int curr = grid[row][col];
  int trees = 0;
  for (int i = row + 1; i < grid.size(); i++) {
    trees++;
    if (grid[i][col] >= curr) break;
  }
  return trees;
}

int scenicScoreLeft(int row, int col, vector<vector<int> >& grid) {
  int curr = grid[row][col];
  int trees = 0;
  for (int i = col - 1; i >= 0; i--) {
    trees++;
    if (grid[row][i] >= curr) break;
  }
  return trees;
}

int scenicScoreRight(int row, int col, vector<vector<int> >& grid) {
  int curr = grid[row][col];
  int trees = 0;
  for (int i = col + 1; i < grid[0].size(); i++) {
    trees++;
    if (grid[row][i] >= curr) break;
  }
  return trees;
}

int scenicScore(int row, int col, vector<vector<int> >& grid) {
  // cout << scenicScoreUp(row, col, grid) << " * " << scenicScoreLeft(row, col, grid) <<
  // " * " << scenicScoreRight(row, col, grid) << " * " << scenicScoreDown(row, col, grid) << endl;
  return scenicScoreUp(row, col, grid) * scenicScoreDown(row, col, grid)
  * scenicScoreLeft(row, col, grid) * scenicScoreRight(row, col, grid);
}

int isVisibleUp(int row, int col, vector<vector<int> >& grid) {
  int curr = grid[row][col];
  for (int i = row - 1; i >= 0; i--) {
    if (grid[i][col] >= curr) return false;
  }
  return true;
}

int isVisibleDown(int row, int col, vector<vector<int> >& grid) {
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

int findMaxScore(vector<vector<int> >& grid) {
  int maxScore = 0;
  int rowMax = grid.size();
  int colMax = grid[0].size();
  for (int row = 1; row < rowMax - 1; row++) {
    for (int col = 1; col < colMax - 1; col++) {
      if (isVisible(row, col, grid)) {
        int score = scenicScore(row, col, grid);
        // cout << "score: " << row << "," << col << " : " << grid[row][col] << "; " << score << endl;
        maxScore = max(maxScore, score);
      }
    }
  }
  return maxScore;
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
  int maxScore = findMaxScore(grid);
  cout << "maxScore: " << maxScore << endl;
  return 0;
}
