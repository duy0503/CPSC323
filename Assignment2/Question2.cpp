#include <iostream>
#include <ctype.h>
#include <string>
#include <stack>
#include <unordered_map>

using namespace std;
enum input { letter, underscore, digit, space, op, dollar, etc };

bool input_validation(string input);
void get_variable ( unordered_map<string, int> & variable_map, string w);
void get_value ( unordered_map<string, int> &variable_map);
void compute(stack<int> & mystack, char OP);
int compute_the_expression(unordered_map<string,int> & variable_map, string w);

int main() {

  string expression;
  char option = 'y';  /* variable to get option from user, 
							either continue with another expression or stop */
  int final_value = 0;

  do {

    cout << "Enter a postfix expression with a $ at the end: ";
    getline(cin, expression);

    if ( input_validation(expression)) {

      unordered_map<string, int> variable_map;
      get_variable(variable_map, expression);
      get_value(variable_map);
      final_value = compute_the_expression(variable_map, expression);
      cout << "Final value = " << final_value << endl;
      cout << "Continue(y/n)? ";
      cin >> option;
      cin.ignore();
    }

  } while (option == 'y');
  
  return 0;
}

bool input_validation(string w) {
  
 int table[6][6] = { 2, 2, 1, 0, 5, 5,
		     5, 5, 1, 3, 4, 5,
		     2, 2, 2, 3, 4, 5,
		     2, 2, 1, 3, 4, 5,
		     2, 2, 1, 3, 4, 5,
		     5, 5, 5, 5, 5, 5 };

  int state = 0, i =0, col;
  input Input;

  while ( i < w.length() )
    {
      if ( isalpha(w[i]) ) //A-Z, a-z = letterif ( (int)w[i] >=
	{
	  Input = letter;
	}
      else if ( w[i] == '_')
	{
	  Input = underscore;
	}
      else if ( isdigit(w[i]) )
	{
	  Input = digit;
	}
      else if ( (int)w[i] == 32 )
	{
	  Input = space;
	}
      else if ( w[i] == '+' || w[i] == '*' || w[i] == '/' || w[i] == '-' )
	{
	  Input = op;
	}
      else if ( w[i] == '$' )
	{
	  Input = dollar;
	}
      else Input = etc;

      switch( Input )
	{
	case letter:
	  col = 0;
	  break;
	case underscore:
	  col = 1;
	  break;
	case digit:
	  col = 2;
	  break;
	case space:
	  col = 3;
	  break;
	case op:
	  col = 4;
	  break;
	case etc:
	  col = 5;
	  break;
	case dollar:
	  if ( state == 0 || state == 3 || state == 5 )
	    {
	    cout << "Expression is not acceptable!"<<endl;
	    return false;
	    }
	  else {
	    cout << "Expression is acceptable!"<<endl;
	    return true;
	  }
	  break;
	default:
	  col = 5;
	  break;
	}
      state = table[state][col]; // new state
      i++;
    }
}


void get_variable ( unordered_map<string, int> & variable_map, string w) {

  int i = 0;
  string var = "";
  unordered_map<string, int>::const_iterator found;
  for ( i = 0; i < w.length(); i++ ) {

    // Check to see if the current character is a letter or '_',
    // If it is, then we know this is the start of a variable, use while loop to get all the characters of that variable
    if ( isalpha(w[i]) || w[i] == '_') { 
      while ( isalpha(w[i]) || isdigit(w[i]) || w[i] == '_' ) {
	var = var + w[i];
	i++;
      }

      // search the variable_map to see if the variable is already existed in the map,
      // If it is not, insert the variable to the map
      
      found = variable_map.find(var);
      if ( found == variable_map.end() ){     // var is not in the map
	
	variable_map.insert({var, 0});
	
      }
      
      var="";      	
    }
  }
}

void get_value ( unordered_map<string, int> &variable_map) {

  int value;
  for ( auto it = variable_map.cbegin(); it != variable_map.cend(); ++it ) {
    cout << "Enter values for " << it->first << ":";
    cin >> value;
    variable_map[it->first] = value;
  }

}

int compute_the_expression(unordered_map<string,int> & variable_map, string w){
  
  string var = "";
  int number = 0;
  int i=0;
  stack<int> compute_stack;
  for ( i = 0; i < w.length(); i++ ) {
    if ( isdigit(w[i]) ) {
	while ( isdigit(w[i]) ){
	number = 10*number + (int)w[i] - '0';
	i++;
      }
      compute_stack.push(number);
      number = 0;
    }

    if ( isalpha(w[i]) || w[i] == '_') {
      while ( isalpha(w[i]) || isdigit(w[i]) || w[i] == '_' ) {
	var = var + w[i];
	i++;
      }
      compute_stack.push(variable_map.at(var));
      var="";
      	
    }

    if ( w[i] =='+' || w[i] == '-' || w[i] == '*' || w[i] == '/' ) {
      if ( compute_stack.size() > 1 ) {
	compute(compute_stack, w[i]);
      }
    }

  }

  return compute_stack.top();


}
void compute(stack<int> & mystack, char OP){
  int result = 0;
  int first_op;
  int second_op;
  second_op = mystack.top();
  mystack.pop();
  first_op = mystack.top();
  mystack.pop();
  switch (OP)
    {

    case '+':
      result = first_op + second_op;
      mystack.push(result);
      break;

    case '-':
      result = first_op - second_op;
      mystack.push(result);
      break;

    case '*':
      result = first_op * second_op;
      mystack.push(result);
      break;

    case '/':
      result = first_op / second_op;
      mystack.push(result);
      break;

    default:
      mystack.push(first_op);
      mystack.push(second_op);
      break;
    }

}
