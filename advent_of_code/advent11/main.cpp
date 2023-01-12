#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <math.h>
#include <queue>

using namespace std;

struct Monkey {
  int id;
  deque<long long int> items;
  string operation;
  int opNum;
  int divisibleBy;
  int onTrue;
  int onFalse;
  int inspectedItems;
};

void printMonkey(Monkey& m) {
  cout << "---------------- print monkey" << endl;
  cout << "#: " << m.id << endl;
  cout << "items: ";
  for (auto& i : m.items) {
    cout << i << " ";
  }
  cout << endl;
  cout << "operation: " << m.operation << " " << m.opNum << endl;
  cout << "divisible by: " << m.divisibleBy << ", true: " << m.onTrue << ", false: " << m.onFalse << endl;
  cout << "inspected: " << m.inspectedItems << endl;
  cout << endl;
}

int printInspected(Monkey& m) {
  cout << "Monkey " << m.id << " inspected items " << m.inspectedItems << endl;
  return m.inspectedItems;
}

void printItems(Monkey& m) {
  cout << "Monkey " << m.id << ": ";
  for (auto& item : m.items) {
    cout << item << " ";
  }
  cout << endl;
}

void doRound(vector<Monkey>& monkeys, int numMonkeys) {
  for (int i = 0; i < numMonkeys; i++) {
    Monkey& m = monkeys[i];
    // cout << "Monkey " << m.id << endl;
    m.inspectedItems += m.items.size();
    while(!m.items.empty()) {
      // inspect each item
      long long worryLevel = m.items.front();
      // cout << "item: " << worryLevel << " ";
      m.items.pop_front();
      if (m.operation == "*") {
        if (m.opNum == -1) worryLevel *= worryLevel;
        else worryLevel *= m.opNum;
      } else { // addition
        worryLevel += m.opNum;
      }
      // cout << "worry : " << worryLevel << " ";
      // worryLevel %= 9699690;
      worryLevel = floor(worryLevel / 3.0);
      // cout << "div 3: " << worryLevel << " ";
      if (worryLevel % m.divisibleBy == 0) {
        // pass to True
        // cout << " to T " << m.onTrue << endl;
        monkeys[m.onTrue].items.push_back(worryLevel);
      } else {
        // pass to False
        // cout << " to F " << m.onFalse << endl;
        monkeys[m.onFalse].items.push_back(worryLevel);
      }
    }
  }

}

int main() {
  ifstream input ("input.txt");
  // ifstream input("test.txt");
  string line;
  vector<Monkey> monkeys;
  int numMonkeys = 8;
  for (int i = 0; i < numMonkeys; i++) {
    // reads one line
    Monkey m;
    m.inspectedItems = 0;
    for (int i = 0; i < 7; i++) {
      getline(input, line);
      stringstream s(line);
      string op = "";
      string currWord = "";
      while(s >> currWord) {
        if (op == "Monkey") {
          m.id = (int)currWord[0] - 48;
        } else if (op == "items:") {
          currWord.erase(std::remove(currWord.begin(), currWord.end(), ','), currWord.end());
          m.items.push_back(stoll(currWord));
          while(s >> currWord) {
            currWord.erase(std::remove(currWord.begin(), currWord.end(), ','), currWord.end());
            m.items.push_back(stoll(currWord));
          }
        } else if (op == "old") {
          // deal with operation
          m.operation = currWord;
          s >> currWord;
          if (currWord == "old") m.opNum = -1;
          else m.opNum = stoi(currWord);
        } else if (op == "by") {
          m.divisibleBy = stoi(currWord);
        } else if (op == "true:") {
          s >> currWord >> currWord >> currWord;
          m.onTrue = stoi(currWord);
        } else if (op == "false:") {
          s >> currWord >> currWord >> currWord;
          m.onFalse = stoi(currWord);
        } else {
          op = currWord;
        }
      }
    }
    printMonkey(m);
    monkeys.push_back(m);
  }
  cout << "++++++++++++++++++++++++++++++++++++++" << endl;
  cout << "round " << 0 << endl;
  for (auto& monkey : monkeys) {
    printItems(monkey);
  }
  // done parsing input
  for (int j = 0; j < 20; j++) {
    cout << "++++++++++++++++++++++++++++++++++++++" << endl;
    doRound(monkeys, numMonkeys);
    cout << "round " << j+1 << endl;
    for (auto& monkey : monkeys) {
      printItems(monkey);
    }
    for (auto& monkey : monkeys) {
      int inspected = printInspected(monkey);
    }

  }

  // int max1, max2 = 0;
  // for (auto& monkey : monkeys) {
  //   int inspected = printInspected(monkey);
  // }

  return 0;
}
