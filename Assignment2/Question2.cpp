#include <iostream>
#include <ctype.h>
#include <string>
#include <stack>
#include <unordered_map>

using namespace std;
enum input { letter, underscore, digit, space, op, dollar, etc }; //used in input_validation

bool input_validation(string input);
void get_variable ( unordered_map<string, int> & variable_map, string w);
void get_value ( unordered_map<string, int> &variable_map);
void compute(stack<int> & mystack, char OP);
int compute_the_expression(unordered_map<string,int> & variable_map, string w, bool* succeeded); 

/*
Function: main
Input: None
Output: None
Description: Main function.
Program executes the following steps:
1. Prompts user input for string expression.
2. Processes expression through input_validation.
3. If validated, uses get_variable to place each unique variable from the expression into the unordered map
4. Uses get_value to ask user for values of each unique variable
5. compute_the_expression computes the value of the expression, or sets the bool succeeded to false if an error occurs.
6. Output the final value, if succeeded is true.
7. Ask user if they want to continue.

*/


int main() {

  string expression;
  char option = 'y';  /* variable to get option from user, 
							either continue with another expression or stop */
  int final_value = 0;
  bool succeeded = true; //this bool will be used in compute_the_expression to see if compute works.

  do {
    cout << "Enter a postfix expression with a $ at the end: ";
    getline(cin, expression);

    if ( input_validation(expression)) {

      unordered_map<string, int> variable_map;
      get_variable(variable_map, expression);
      get_value(variable_map);
      final_value = compute_the_expression(variable_map, expression, &succeeded);
	  if (succeeded) {
		  cout << "Final value = " << final_value << endl;
	  }
	  else
	  {
		  cout << "Computational error. Check operator number and placement.\n";
	  }
	  cout << "Continue(y/n)? ";
	  cin >> option;
	  cin.ignore();
    }

  } while (option == 'y');
  
  return 0;
}

/*
Function:input_validation
Input: string
Output: bool
Description: Uses a FA to see if the syntax of the expression is acceptable. 
It ends when it detects a $, and determines if it is acceptable at that state.
Before the function begins, it checks if the string ends with a $. If it doesn't it returns false for error.
*/

bool input_validation(string w) {
  
 int table[6][6] = { 2, 2, 1, 0, 5, 5, //The FA table. There are 6 states. 
		     5, 5, 1, 3, 4, 5,
		     2, 2, 2, 3, 4, 5,
		     2, 2, 1, 3, 4, 5,
		     2, 2, 1, 3, 4, 5,
		     5, 5, 5, 5, 5, 5 };

  int state = 0, i =0, col;
  input Input;

  if (w[w.size() - 1] != '$')
  {
	  cout << "Error. Expression is missing $ at end.\n";
	  return false;
  }

  while ( i < w.length() ) //Determines the input for the FA. The enum is declared at the beginning of the file
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
	  if (state == 0 || state == 3 || state == 5 || i < w.size() - 1)
	    {
	    cout << "Error. $ detected in inappropriate location."<<endl;
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

/*
Function: get_variable
Input: unordered_map with string keys and int values, and a string.
Output: None
Description: Parses each named variable in the function, and if it is not already in the unordered_map, it places it there.
*/

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

/*
Function: get_value
Input: unordered_map with string keys and int values
Output: None
Description: Asks user to enter values for each variable that is stored in unordered_map.
*/


void get_value ( unordered_map<string, int> &variable_map) {

  int value;
  for ( auto it = variable_map.cbegin(); it != variable_map.cend(); ++it ) {
    cout << "Enter values for " << it->first << ":";
    cin >> value;
    variable_map[it->first] = value;
  }

}

/*
Function: compute_the_expression
Input: unordered_map with string keys and int values, a string, and a bool pointer
Output: an int value that represents the outcome of the expression
Description: Parses the expression for variables, operators, and numbers. 
When it encounters a variable or number, it pushes its value onto a stack of ints (compute_stack).
When it encounters an operator, it calls the function compute, which will use the top 2 ints in the stack.
	If there are less than 2 elements in the stack when it calls compute, it sets the bool to false which will result in an error message in main().
If, at the end of the function, the stack has more than 1 value, the bool will be set to false.
These 2 error checks should cover all instances where operators are misplaced or a wrong number of them is used.
*/


int compute_the_expression(unordered_map<string,int> & variable_map, string w, bool* succeeded){
  
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
	  else { *succeeded = false; } //if the compute_stack is less than 2, error. 
    }

  }
  if (compute_stack.size() > 1)
  {
	  *succeeded = false; //if there are more than one variable left in the stack at the end of the function, error.
  }
  return compute_stack.top();


}

/*
Function: compute
Input: stack of ints, and a char representing an operator
Output: None
Description: Takes the top 2 ints in the stacks and does an arithmetic operation on them based on what the operator char is.
It then takes the result and pushes it onto the stack.
*/

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
