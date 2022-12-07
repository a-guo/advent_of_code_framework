#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>

using namespace std;

char findOption(char opponent, int outcomeScore) {
  switch (outcomeScore) {
    case 0:
      // I need to lose
      if (opponent == 'A') return 'C';
      else return (char)(opponent-1);
    case 3:
      // I need to tie
      return opponent;
    case 6:
      // I need to win
      if (opponent == 'C') return 'A';
      else return (char)(opponent+1);
  }
  return ' ';
}

int score(char opponent, char outcome) {
  int outcomeScore = (outcome - 'X')*3;
  char played = findOption(opponent, outcomeScore);
  int shape = played - 'A' + 1;
  return shape + outcomeScore;
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
