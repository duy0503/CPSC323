#include "clean_up.h"
#include "generator.h"
#include "parser.h"
using namespace std;

int main() { 

  vector<string> tokens;
  bool pass = false;

  string file_v1 = "finalv3.txt";

  // Clean up all of the comments
  // and create a new txt file from the original file
  tokens = clean_up(file_v1);

  // Get tokens from the new txt files
  pass = parse(tokens);
  if ( pass ) translate(tokens);
  return 0;
}
