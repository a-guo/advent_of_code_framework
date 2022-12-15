#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Node {
  bool isDir;
  int fileSize;
  vector<Node*> children;
  Node* parent;
public:
  Node(bool isDir): isDir(isDir), fileSize(0) {}
  Node(int fileSize): isDir(false), fileSize(fileSize) {}
};

int main() {
  // ifstream input ("input.txt");
  ifstream input("test.txt");
  string line;
  Node* root = new Node(true);
  Node* curr = root;
  while (getline(input, line)) {
    stringstream s(line);
    string a,b,c;
    s >> a >> b >> c;
    if (a == "$") {
      if (b == "cd") {
        // go into dir
        cout << "cd: " << c << endl;
        if (c == "..") {
          // traverse back up
        } else if (c == "/") {
          curr = root;
        } else {
          // go down
        }
      } else {
        // ls & make tree
        cout << "ls: " << b << endl;
        
      }
    }
  }
  return 0;
}
