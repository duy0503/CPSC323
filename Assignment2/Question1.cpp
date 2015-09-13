#include <iostream>
#include <string>

using namespace std;

int main() {
  int table[5][3] = {1, 2, 4,
		     1, 3, 4,
		     4, 2, 4,
		     4, 4, 4,
		     4, 4, 4 };

  string w = "aaab$";

  int state = 0, i =0, col;

  while ( i < w.length() )
    {
      switch( w[i] )
	{
	case 'a':
	  col = 0;
	  break;
	case 'b':
	  col = 1;
	  break;
	case '$':
	  if ( state == 0 || state == 1 || state == 4 )
	    cout << "W is not acceptable"<<endl;
	  else cout << "W is acceptable"<<endl;
	  break;
	default:
	  col = 2;
	  break;
	}
      state = table[state][col]; // new state
      i++;
    }
  return 0;
}
