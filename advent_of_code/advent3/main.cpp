#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
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

char findCommonItem(string a, string b) {
  set<char> seenA;
  // cout << "a: " << a << " vs b: " << b << endl;
  for (auto& letter : a) {
    seenA.insert(letter);
  }
  for (auto& letter : b) {
    if (seenA.find(letter) != seenA.end()) {
      // cout << "common : " << letter << endl;
      return letter;
    }
  }
  return ' ';
}

int main() {
  ifstream input ("input.txt");
  // ifstream input("test.txt");
  string line;
  vector<char> commonItems;

  while (getline(input, line)) {
    int len = line.length();
    string firstCompartment = line.substr(0, len/2);
    string secondCompartment = line.substr(len/2);
    char commonItem = findCommonItem(firstCompartment, secondCompartment);
    commonItems.push_back(commonItem);
  }
  int sumPriorities = sum(commonItems);
  cout << "sum is " << sumPriorities << endl;
  return 0;
}
