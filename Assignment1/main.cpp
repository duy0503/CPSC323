/*
	Author Name: Duy Do, Tetsuya Tanaka
	Course: CPSC 323
	Assigment number: 1
	Due Date: 09/10/2015
	Project Information:
		Project Title: Compute Postfix Expression
		Purpose: Read a postfix expression and compute its values
		Project files: postfix.h, postfix.cpp, main.cpp
	Precondition: 
		All variables in the expression are single letters of type integer
		The operators allowed are +, -, *, /
		The expression must end with a $
	Postcondtion:
		Print out the final value of the expression
		Print out error messages if there is a violation in the expression
	
*/


#include <iostream>
#include <string>
#include <stack>
#include "postfix.h"

using namespace std;

int main()
{
  string expression;  /* variable to get the string from user */
  char option = 'y';  /* variable to get option from user, 
							either continue with another expression or stop */
	

  /* Create an array of structure Variable_type with 52 elements
     This represents the 52 letters that are possible to be used in the postfix expression
  */					 
  Variable_type variable[NUM_OF_LETTERS];
  int final_value = 0;

  do {

    cout << "Enter a postfix expression with a $ at the end: ";
    getline(cin, expression);

    /* 	Initialize all of the elements in array variable */
    initialize_variables(variable);

	/*
		Call function parse_string_to_get_variables
		If this function returns false, it means there is some type of error in the expression.
		If it returns true, the expression is acceptable.
	*/
    if (parse_string_to_get_variables(variable, expression)) {

      get_values_for_variables(variable);

      final_value = parse_string_to_compute_values(variable, expression);

      cout << "Final value = " << final_value << endl;
      cout << "Continue(y/n)? ";
      cin >> option;
      cin.ignore();
    }

  } while (option == 'y');

  return 0;
}

