#include <iostream>
#include <fstream>
#include <sstream>
#include <array>
#include <vector>
#include <string>
#include <set>

using namespace std;

int direction[4][2] = {
  {0, 1}, // R
  {0, -1}, // L
  {1, 0}, // U
  {-1, 0} // D
};

bool isTouching(pair<int, int> head, pair<int, int> tail) {
  if (head.first == tail.first && head.second == tail.second) return true;
  if (abs(tail.first - head.first) == 1 && abs(tail.second - head.second) == 0) return true;
  if (abs(tail.first - head.first) == 0 && abs(tail.second - head.second) == 1) return true;
  if (abs(tail.first - head.first) == 1 && abs(tail.second - head.second) == 1) return true;
  return false;
}

void updateTail(pair<int, int>& head, pair<int, int>& tail) {
  if (abs(tail.first - head.first) == 2 && abs(tail.second - head.second) == 0) {
    if (tail.first > head.first) tail.first--;
    else tail.first++;
    return;
  }
  if (abs(tail.first - head.first) == 0 && abs(tail.second - head.second) == 2) {
    if (tail.second > head.second) tail.second--;
    else tail.second++;
    return;
  }
  // move diagonally
  if (head.first > tail.first) {
    // move up
    if (head.second > tail.second) {
      // up & right
      tail.first++;
      tail.second++;
      return;
    } else {
      // up & left
      tail.first++;
      tail.second--;
      return;
    }
  } else {
    if (head.second > tail.second) {
      // down & right
      tail.first--;
      tail.second++;
      return;
    } else {
      tail.first--;
      tail.second--;
      return;
    }
  }
}

void doUpdate(pair<int, int>& head, pair<int, int>& tail, set<pair<int, int> >& tailVisited, bool wantUpdate) {
  cout << "head: " << head.first << ", " << head.second << endl;
  if (!isTouching(head, tail)) {
    cout << "not touching: " << tail.first << ", " << tail.second << endl;
    updateTail(head, tail);
    cout << "update tail: " << tail.first << ", " << tail.second << endl;
    if (wantUpdate) tailVisited.insert(make_pair(tail.first, tail.second));
  }
}

void update(vector<pair<int, int> >& knots, set<pair<int, int> >& tailVisited) {
  // call doUpdate on each pair, then check if tail moved and update
  for (int i = 1; i < knots.size(); i++) {
    pair<int, int>& prev = knots[i-1];
    pair<int, int>& curr = knots[i];
    if (i == knots.size() - 1) doUpdate(prev, curr, tailVisited, true);
    else doUpdate(prev, curr, tailVisited, false);
  }
}


int main() {
  ifstream input ("input.txt");
  // ifstream input("test.txt");
  string line;
  vector<pair<int, int> > knots(10, make_pair(0,0));
  set<pair<int, int> > tailVisited;
  tailVisited.insert(make_pair(0, 0));
  while (getline(input, line)) {
    stringstream s(line);
    string dir;
    int steps;
    s >> dir >> steps;
    cout << endl << dir << ", " << steps << endl;
    if (dir == "R") {
      for (int i = 0; i < steps; i++) {
        knots[0].first += direction[0][0];
        knots[0].second += direction[0][1];
        update(knots, tailVisited);
      }
    } else if (dir == "L") {
      for (int i = 0; i < steps; i++) {
        knots[0].first += direction[1][0];
        knots[0].second += direction[1][1];
        update(knots, tailVisited);
      }
    } else if (dir == "U") {
      for (int i = 0; i < steps; i++) {
        knots[0].first += direction[2][0];
        knots[0].second += direction[2][1];
        update(knots, tailVisited);
      }
    } else if (dir == "D") {
      for (int i = 0; i < steps; i++) {
        knots[0].first += direction[3][0];
        knots[0].second += direction[3][1];
        update(knots, tailVisited);
      }
    }
  }
  cout << "positions tail visited: " << tailVisited.size() << endl;
  return 0;
}
