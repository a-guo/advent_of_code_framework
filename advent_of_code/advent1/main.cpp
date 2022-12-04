#include <iostream>
#include <string>
#include <fstream>
#include <queue>

using namespace std;

int main() {
  ifstream input ("advent1.txt");
  // ifstream input("test.txt");
  priority_queue <int, vector<int>, greater<int> > max3;
  int currentElfCalories = 0;
  string line;
  while (getline(input, line)) {

    if (!line.empty()) {
      currentElfCalories += stoi(line);
    } else {
      if (max3.size() >= 3) {
        if (currentElfCalories > max3.top()) {
          max3.pop();
          max3.push(currentElfCalories);
        }
      } else {
        max3.push(currentElfCalories);
      }
      currentElfCalories = 0;
    }
  }
  if (currentElfCalories != 0) {
    if (currentElfCalories > max3.top()) {
      max3.pop();
      max3.push(currentElfCalories);
    }
  }
  int sum = 0;
  while (!max3.empty()) {
    sum += max3.top();
    max3.pop();
  }
  cout << "total top calories is " << sum << endl;
  return 0;
}
