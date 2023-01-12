#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <utility>
#include <queue>

using namespace std;

void printElevation(vector<vector<char> >& e) {
  for (int i = 0; i < e.size(); i++) {
    for (int j = 0; j < e[0].size(); j++) {
      cout << e[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl;
}

void getStartEndCoords(pair<int,int>& start, pair<int,int>& end, vector<vector<char> >& grid) {
  for (int row = 0; row < grid.size(); row++) {
    for (int col = 0; col < grid[0].size(); col++) {
      if (grid[row][col] == 'S') start = make_pair(row, col);
      if (grid[row][col] == 'E') end = make_pair(row, col);
    }
  }
}

int getHeight(char s) {
  if (s == 'S') return 0;
  else if (s == 'E') return 25;
  else return s - 'a';
}

vector<pair<int, int> > getNeighbors(pair<int, int> curr, int n, int m, vector<vector<char>>& grid) {
  vector<pair<int, int> > neighbors;
  vector<vector<int>> dirs = { {1, 0}, {0, -1}, {-1, 0}, {0, 1} };

  for (int i = 0; i < dirs.size(); i++) {
    int row = curr.first + dirs[i][0];
    int col = curr.second + dirs[i][1];
    if (!(row >= 0 && row < n && col >= 0 && col < m)) continue;
    // cout << "next : " << getHeight(grid[row][col]) << ", curr: " << getHeight(grid[curr.first][curr.second]) << endl;
    if (getHeight(grid[row][col]) >= getHeight(grid[curr.first][curr.second]) - 1) {
      pair<int, int> valid = make_pair(row, col);
      neighbors.push_back(valid);
    }
  }

  return neighbors;
}

int dijkstra(vector<vector<char>>& grid, pair<int, int>& start, pair<int, int>& end) {
  vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(), false));
  queue<pair<int, pair<int, int>>> H;
  H.push(make_pair(0, make_pair(end.first, end.second)));

  while (!H.empty()) {
    int steps = H.front().first;
    int row = H.front().second.first;
    int col = H.front().second.second;
    // cout << "curr: " << row << "," << col << ", grid[i][j]: " << grid[row][col]<< ", steps: " << steps << endl;
    H.pop();
    if (visited[row][col]) continue;
    visited[row][col] = true;
    if (getHeight(grid[row][col]) == 0) {
      // cout << "steps: " << steps << endl;
      return steps;
    }

    pair<int, int> curr = make_pair(row, col);
    vector<pair<int, int>> neighbors = getNeighbors(curr, grid.size(), grid[0].size(), grid);
    for (int x = 0; x < neighbors.size(); x++) {
      H.push(make_pair(steps + 1, make_pair(neighbors[x].first, neighbors[x].second)));
    }
  }
  cout << endl;
  return 0;
}

int main() {
  ifstream input ("input.txt");
  // ifstream input("test.txt");
  string line;
  vector<vector<char> > grid;
  while (getline(input, line)) {
    vector<char> v(line.begin(), line.end());
    grid.push_back(v);
    cout << endl;
  }

  printElevation(grid);

  pair<int,int> start, end;
  getStartEndCoords(start, end, grid);
  cout << "start coords: " << start.first << " " << start.second << endl;
  cout << "end coords: " << end.first << " " << end.second << endl;
  int final = dijkstra(grid, start, end);
  cout << "ans: " << final << endl;
  return 0;
}
