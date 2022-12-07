#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>

using namespace std;

int oScore(char opponent, char played) {
  if (opponent == played) return 3;
  if (opponent == 'C' && played == 'A') return 6;
  if (opponent == 'A' && played == 'C') return 0;
  if (opponent > played) return 0;
  return 6;
}

int score(char opponent, char played) {
  char playedConverted = (char)(played - 23);
  int shapeScore = played - 'X' + 1;
  int outcome = oScore(opponent, playedConverted);
  return shapeScore + outcome;
}

int main() {
  ifstream input ("input.txt");
  // ifstream input("test.txt");
  int totalScore = 0;
  string line;
  while (getline(input, line)) {
    char opponent = line[0];
    char played = line[2];
    totalScore += score(opponent, played);
  }
  cout << "total score is " << totalScore << endl;
  return 0;
}
