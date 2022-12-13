#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

bool fullyContains(int aLeft, int aRight, int bLeft, int bRight) {
  if (aLeft <= bLeft && aRight >= bRight) return true;
  return false;
}

void parseAssignments(string& a, string& b, const string& line) {
  stringstream s(line);
  getline(s, a, ',');
  getline(s, b, ',');
  return;
}

void parseRange(int& min, int& max, const string& range) {
  string a, b;
  stringstream s(range);
  getline(s, a, '-');
  getline(s, b, '-');
  min = stoi(a);
  max = stoi(b);
  return;
}

int main() {
  ifstream input ("input.txt");
  // ifstream input("test.txt");
  string line;
  int fullyContained = 0;
  while (getline(input, line)) {
    // get A and B
    string a, b;
    int aMin, aMax, bMin, bMax;
    parseAssignments(a, b, line);
    parseRange(aMin, aMax, a);
    parseRange(bMin, bMax, b);
    if (fullyContains(aMin, aMax, bMin, bMax) || fullyContains(bMin, bMax, aMin, aMax)) {
      fullyContained++;
    }
  }
  cout << "fully contained: " << fullyContained << endl;
  return 0;
}