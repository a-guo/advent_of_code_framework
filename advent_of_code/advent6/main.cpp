#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

using namespace std;

bool isUnique(const string& S) {
  unordered_map<char, int> M;
  for (auto& c : S) {
    if (M.find(c) != M.end()) return false;
    M[c] = 1;
  }
  return true;
}

int main() {
  ifstream input ("input.txt");
  // ifstream input("test.txt");
  string line;
  getline(input, line);
  int lower = 0;
  for (int i = 0; i < line.length() - 14; i++) {
    string letters = line.substr(i, 14);
    // cout << letters << endl;
    if (isUnique(letters)) {
      cout << i+14 << endl;
      break;
    }
  }
  return 0;
}
