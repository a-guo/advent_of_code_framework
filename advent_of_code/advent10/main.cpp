#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <vector>

using namespace std;

int getSignalStrength(int cycle, int x, vector<int>& cycles) {
  if (cycles.empty()) return 0;
  if (cycle >= cycles[0]) {
    // cout << "cycle: " << cycle << " , x: " << x << " , sig: " << cycle * x << endl;
    cycles.erase(cycles.begin());
    return cycle * x;
  }
  return 0;
}

int main() {
  ifstream input ("input.txt");
  // ifstream input("tgest.txt");
  string line;
  int sum = 0;
  int cycle = 1;
  int x = 1;
  vector<int> cycles;
  cycles.push_back(20);
  cycles.push_back(60);
  cycles.push_back(100);
  cycles.push_back(140);
  cycles.push_back(180);
  cycles.push_back(220);
  while (getline(input, line)) {
    stringstream s(line);
    string instr;
    int v;
    s >> instr >> v;
    // cout << cycle << endl;
    if (instr == "noop") {
      cycle++;
    } else {
      cycle++;
      sum += getSignalStrength(cycle, x, cycles);
      cycle++;
      x += v;
    }
    sum += getSignalStrength(cycle, x, cycles);
  }
  cout << "signal strenght: " << sum << endl;
  return 0;
}
