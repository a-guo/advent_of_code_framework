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

vector<string> drawSprite(int x) {
  vector<string> line(40, ".");
  for (int i = 0; i < 40; i++) {
    if (i == x || i == x + 1 || i == x-1) {
      line[i] = "#";
    }
  }
  // cout << "sprite: ";
  // for (auto& s : line) {
  //   cout << s;
  // }
  // cout << endl;
  return line;
}

void printCRT(string& crt, vector<string>& crts, int cycle, vector<string>& sprite) {
  int pos = (cycle - 1) % 40;
  // cout << "pos: " << pos << endl;
  // cout << "sprite[pos]: " << sprite[pos] << endl;
  if (sprite[pos] == "#") crt += "#";
  else crt += ".";
  // cout << crt << endl;
  if (crt.length() == 40) {
    cout << crt << endl;
    crts.push_back(crt);
    crt = "";
  }
}

int main() {
  ifstream input ("input.txt");
  // ifstream input("test.txt");
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
  string crt = "";
  vector<string> crts;
  vector<string> sprite = drawSprite(x);
  while (getline(input, line)) {
    stringstream s(line);
    string instr;
    int v;
    s >> instr >> v;
    // cout << "cycle: " << cycle << endl;

    if (instr == "noop") {
      printCRT(crt, crts, cycle, sprite);
      cycle++;
    } else {
      printCRT(crt, crts, cycle, sprite);
      cycle++;
      printCRT(crt, crts, cycle, sprite);
      cycle++;
      x += v;
      sprite = drawSprite(x);
    }

  }
  return 0;
}
