#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/*
Function: main
Input: None
Output: None
Description: 
1. Sets up FA table in 2d array.
2. Opens data.txt.
3. Takes a line in data.txt and processes it through the FA switch code.
4. Checks the final state and determines if acceptable.
5. Takes next line and repeats until no more lines in data.txt.
*/

int main() {
  int table[5][3] = {1, 2, 4, //FA table
		     1, 3, 4,
		     4, 2, 4,
		     4, 4, 4,
		     4, 4, 4 };

  string w; 
  fstream myfile;
  myfile.open("data.txt");

  int state = 0, i =0, col;

  while (getline(myfile, w)) //for each line in myfile
  {
	  cout << "Processing " << w << ":" << endl;
	  while (i < w.length())
	  {
		  switch (w[i])
		  {
		  case 'a':
			  col = 0;
			  break;
		  case 'b':
			  col = 1;
			  break;
		  case '$':
			  if (state == 0 || state == 1 || state == 4)
				  cout << "W is not acceptable" << endl;
			  else cout << "W is acceptable" << endl;
			  break;
		  default:
			  col = 2;
			  break;
		  }
		  state = table[state][col]; // new state
		  i++;
	  }
  }
  cin.get();
  return 0;
}
