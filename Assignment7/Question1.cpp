#include <iostream>
#include <string>
#include <stack>

using namespace std;

const string Table[5][8] = { "TQ", ""   , ""   , ""   , ""   , "TQ" , "" , "" ,
			     ""  , "+TQ", "-TQ", ""   , ""   , ""   , "#", "#",
			     "FR", ""   , ""   , ""   , ""   , "FR" , "" , "" ,
			     ""  , "#"  , "#"  , "*FR", "/FR", ""   , "#", "#",
			     "i" , ""   , ""   , ""   , ""   , "(E)", "" , ""  };

int get_column(char w){
  switch(w) {
  case 'i':
    return 0;
  case '+':
    return 1;
  case '-':
    return 2;
  case '*': 
    return 3;
  case '/':
    return 4;
  case '(':
    return 5;
  case ')':
    return 6;
  case '$':
    return 7;
  default:
    return -1;
  }
}

int get_row(char w) {
  switch(w) {
  case 'E':
    return 0;
  case 'Q':
    return 1;
  case 'T':
    return 2;
  case 'R':
    return 3;
  case 'F':
    return 4;
  default:
    return -1;
  }
}
int main(){

  string input;
  char w;
  stack<char> my_stack;
  char s;
  int row = 0;
  int col = 0;
  int counter = 0;
  string content;

  cout <<"Enter the input string: "<<endl;
  getline(cin, input);
  my_stack.push('$');
  my_stack.push('E');
  w = input[counter];
  col = get_column(w);
  while ( !my_stack.empty() ) {
    
    //Get the top of the stack
    s = my_stack.top();
    my_stack.pop();

    // Compare s with the current input character
    if ( s == w ) {

      // This is the last character
      if ( s == '$' ) {
	cout << "Accepted"<<endl;
	return 0;
      }
      // If it's not the last character, read the next character in the input
      else {
	counter++;
	w = input[counter];
	col = get_column(w);
	continue;
      }
    }
    
    row = get_row (s);

    // Get the content in the table based on the row and column
    content = Table[row][col];

    // if the content is empty, reject the input
    if ( content.length() == 0 ) {
      cout<<"rejected"<<endl;
      return -1;
    }
    // if it is lambda ( I put '#' for lambda in the table )
    // go back to the top of the loop
    else if ( content == "#" ) continue;

    // push the content to the stack starting from the last character of the content
    else {
      for ( int i = content.length()-1; i >= 0; i-- ) {
	my_stack.push(content[i]);
      }
    }
    
  } 
 
  return 0;
}
