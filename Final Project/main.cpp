/*
  Author Name: Duy Do, Tetsuya Tanaka
  Course: CPSC 323
  Final Project

 */

#include "clean_up.h"
#include "generator.h"
#include "parser.h"
using namespace std;

int main() { 

  vector<string> tokens;
  bool passed = false;

  string file_v1 = "finalv3.txt";

  // Clean up all of the comments
  // and create a new txt file from the original file
  tokens = clean_up(file_v1);

  // Parse the list of tokens got from the new txt file
  passed = parse(tokens);

  // if there is no error, then translate the txt file to cpp
  if ( passed ) translate(tokens);
  
  return 0;
}
