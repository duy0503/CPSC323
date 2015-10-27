#include <iostream>
#include <string>
#include <stack>
#include <vector>

using namespace std;

const string Table[6][8] = { "i=E", ""   , ""   , ""   , ""   , ""   , "" , "" ,
			     "TQ" , ""   , ""   , ""   , ""   , "TQ" , "" , "" ,
			     ""   , "+TQ", "-TQ", ""   , ""   , ""   , "#", "#",
			     "FR" , ""   , ""   , ""   , ""   , "FR" , "" , "" ,
			     ""   , "#"  , "#"  , "*FR", "/FR", ""   , "#", "#",
			     "i"  , ""   , ""   , ""   , ""   , "(E)", "" , "" };

int get_column(char w){
  switch (w) {
  case 'i':
    return 0;
  case '=': 
    break;
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
  switch (w) {
  case 'S':
    return 0;
  case 'E':
    return 1;
  case 'Q':
    return 2;
  case 'T':
    return 3;
  case 'R':
    return 4;
  case 'F':
    return 5;
  default:
    return -1;
  }
}

int main(){

  string input;
  char w;
  stack<char> my_stack;
  vector<char> stack_content; // use this to print out the content of the stack
  vector<char>::iterator it;
  char s;
  int row = 0;
  int col = 0;
  int counter = 0;
  string content;

  cout << "Enter the input string: ";
  getline(cin, input);
  my_stack.push('$');
  my_stack.push('S');

  // For the purpose of printing the stack
  stack_content.push_back('$');
  stack_content.push_back('S');

  w = input[counter];
  col = get_column(w);
  while (!my_stack.empty()) {

    //Get the top of the stack
    s = my_stack.top();
    my_stack.pop();

    //Keep track of the content in the stack
    stack_content.pop_back();

    // current token matches with s
    if (s == w) {

      // Print out the content of the stack from stack_content
      for (it = stack_content.begin(); it != stack_content.end(); it++) cout << *it << " ";
      cout << endl;

      // This is the last character
      if (s == '$') {
	cout << "Accepted" << endl;
	return 0;
      }
      // If it's not the last character, read the next character in the input
      else {
	counter++;
	w = input[counter];
	col = get_column(w);
	if (col < 0) {
	  cout << "Input error, rejected!" << endl;
	  return -1;
	}
	continue;
      }
    }

    row = get_row(s);
    if (row  < 0) {
      cout << "Input error, rejected!" << endl;
      return -1;
    }

    // Get the content in the table based on the row and column
    content = Table[row][col];

    // if the content is empty, reject the input
    if (content.length() == 0) {
      cout << "rejected" << endl;
      return -1;
    }
    // if it is lambda ( I put '#' for lambda in the table )
    // go back to the top of the loop
    else if (content == "#") continue;

    // push the content to the stack starting from the last character of the content
    else {
      for (int i = content.length() - 1; i >= 0; i--) {
	my_stack.push(content[i]);
	stack_content.push_back(content[i]);
      }
    }

  }

  return 0;
}
