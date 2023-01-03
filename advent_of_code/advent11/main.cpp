#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;

struct Monkey {
  int id;
  vector<long long int> items;
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
  for (int j = 1; j <= 20; j++) {
    for (int i = 0; i < numMonkeys; i++) {
      Monkey& m = monkeys[i];
      // if (j == 7) cout << "Monkey " << m.id << endl;
      while(!m.items.empty()) {
        // inspect each item
        // if (j == 7) cout << "item: " << m.items[0] << " ";
        m.inspectedItems++;
        long long worryLevel = m.items[0];
        if (m.operation == "*") {
          if (m.opNum == -1) worryLevel = worryLevel * worryLevel;
          else worryLevel = worryLevel * m.opNum;

        } else {
          // +
          if (m.opNum == -1) worryLevel = worryLevel + worryLevel;
          else worryLevel = worryLevel + m.opNum;
        }
        worryLevel = floorl(worryLevel / 3);
        // if (j == 7) cout << "worryLevel: " << worryLevel << " ";
        if (worryLevel % m.divisibleBy == 0) {
          // pass to True
          // if (j == 7) cout << "pass to " << m.onTrue << " ";
          monkeys[m.onTrue].items.push_back(worryLevel);
        } else {
          // pass to False
          // if (j == 7) cout << "pass to " << m.onFalse << " ";
          monkeys[m.onFalse].items.push_back(worryLevel);
        }
        vector<long long int> updatedItems = m.items;
        updatedItems.erase(updatedItems.begin());
        m.items = updatedItems;
        // cout << "updated items: ";
        // for (auto i : m.items) {
        //   cout << i << " ";
        // }
        // if (j== 7) cout << endl;
      }
      // if (j == 7) printMonkey(monkeys[6]);
    }
    cout << "round " << j << endl;
    for (auto& monkey : monkeys) {
      printItems(monkey);
    }
  }

  int max1, max2 = 0;
  for (auto& monkey : monkeys) {
    int inspected = printInspected(monkey);
  }

  return 0;
}
