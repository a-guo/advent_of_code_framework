#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <stack>

using namespace std;

vector<stack<char> > getStacks() {
  vector<stack<char> > stacks;
  stack<char> S1;
  S1.push('B');
  S1.push('Q');
  S1.push('C');
  stacks.push_back(S1);
  stack<char> S2;
  S2.push('R');
  S2.push('Q');
  S2.push('W');
  S2.push('Z');
  stacks.push_back(S2);
  stack<char> S3;
  S3.push('B');
  S3.push('M');
  S3.push('R');
  S3.push('L');
  S3.push('V');
  stacks.push_back(S3);
  stack<char> S4;
  S4.push('C');
  S4.push('Z');
  S4.push('H');
  S4.push('V');
  S4.push('T');
  S4.push('W');
  stacks.push_back(S4);
  stack<char> S5;
  S5.push('D');
  S5.push('Z');
  S5.push('H');
  S5.push('B');
  S5.push('N');
  S5.push('V');
  S5.push('G');
  stacks.push_back(S5);
  stack<char> S6;
  S6.push('H');
  S6.push('N');
  S6.push('P');
  S6.push('C');
  S6.push('J');
  S6.push('F');
  S6.push('V');
  S6.push('Q');
  stacks.push_back(S6);
  stack<char> S7;
  S7.push('D');
  S7.push('G');
  S7.push('T');
  S7.push('R');
  S7.push('W');
  S7.push('Z');
  S7.push('S');
  stacks.push_back(S7);
  stack<char> S8;
  S8.push('C');
  S8.push('G');
  S8.push('M');
  S8.push('N');
  S8.push('B');
  S8.push('W');
  S8.push('Z');
  S8.push('P');
  stacks.push_back(S8);
  stack<char> S9;
  S9.push('N');
  S9.push('J');
  S9.push('B');
  S9.push('M');
  S9.push('W');
  S9.push('Q');
  S9.push('F');
  S9.push('P');
  stacks.push_back(S9);
  return stacks;
}

void parseInstrs(int& m, int& f, int& t, const string& instr) {
  string a, b, c;
  string word;
  stringstream s(instr);
  s >> word >> a >> word >> b >> word >> c;

  cout << a << "," << b << "," << c << endl;
  m = stoi(a);
  f = stoi(b);
  t = stoi(c);
  return;
}

vector<stack<char> > doAction(int move, int from, int to, vector<stack<char> > stacks) {
  vector<char> itemsMoved(move);
  for (int i = 0; i < move; i++) {
    char letter = stacks[from-1].top();
    stacks[from-1].pop();
    cout << letter << endl;
    itemsMoved[i] = letter;

  }
  for (int i = 0; i < move; i++) {
    stacks[to-1].push(itemsMoved[move - 1 - i]);
  }
  return stacks;
}

string findTop(vector<stack<char> > stacks) {
  string top = "";
  for (int i = 0; i < stacks.size(); i++) {
    char letter = stacks[i].top();
    top += letter;
  }
  return top;
}

void printStack(stack<char> S) {
  if (S.empty()) return;
  char x = S.top();
  S.pop();
  printStack(S);
  cout << x << " ";
  S.push(x);
}

void printStacks(vector<stack<char> > stacks) {
  for (int i = 0; i < stacks.size(); i++) {
    cout << "stack: " << i << " ";
    printStack(stacks[i]);
    cout << endl;
  }
}

int main() {
  ifstream input ("input.txt");
  // ifstream input("test.txt");
  string line;
  bool readStacks = false;
  int numStacks = 3;
  vector<stack<char> > stacks = getStacks();
  while (getline(input, line)) {
    if (!readStacks) {
      if (line.empty()) {
        // keep reading boxes
        readStacks = true;
      }
    } else {
      int move, from, to = 0;
      parseInstrs(move, from, to, line);
      stacks = doAction(move, from, to, stacks);
      // printStacks(stacks);
    }
  }
  string ret = findTop(stacks);
  cout << "top crates: " << ret << endl;
  return 0;
}
