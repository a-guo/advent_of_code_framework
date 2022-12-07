#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <unordered_map>
#include <set>

using namespace std;

int sum(vector<char>& commonItems) {
  int sum = 0;
  for (auto& item : commonItems) {
    int priority;
    if (islower(item)) {
      priority = item - 96;
    } else {
      priority = item - 38;
    }
    // cout << "priority " << priority << endl;
    sum += priority;
  }
  return sum;
}

set<char> removeDups(string& a) {
  set<char> letters;
  for (auto& letter : a) {
    letters.insert(letter);
  }
  return letters;
}

char findCommonItem(string a, string b, string c) {
  unordered_map<char, int> seen;
  set<char> lettersA = removeDups(a);
  set<char> lettersB = removeDups(b);
  set<char> lettersC = removeDups(c);
  for (auto& letter : lettersA) {
    seen[letter] = 1;
  }
  for (auto& letter : lettersB) {
    if (seen.find(letter) != seen.end()) {
      seen[letter] = 2;
    } else {
      seen[letter] = 1;
    }
  }
  for (auto& letter : lettersC) {
    if (seen.find(letter) != seen.end()) {
      if (seen[letter] == 2) {
        // cout << "common: " << letter << endl;
        return letter;
      }
    } else {
      seen[letter] = 2;
    }
  }
  return ' ';
}

int main() {
  ifstream input ("input.txt");
  // ifstream input("test.txt");
  string elf1;
  string elf2;
  string elf3;
  vector<char> commonItems;

  while (getline(input, elf1) && getline(input, elf2) && getline(input, elf3)) {
    char commonItem = findCommonItem(elf1, elf2, elf3);
    commonItems.push_back(commonItem);
  }
  int sumPriorities = sum(commonItems);
  cout << "sum is " << sumPriorities << endl;
  return 0;
}
