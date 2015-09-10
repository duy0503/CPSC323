
/*
	Filename: postfix.cpp
	This files contains all the implementations of the functions declared in file postfix.h
*/

#include <iostream>
#include <stack>
#include <string>
#include "postfix.h"

using namespace std;

/*
	Function: initialize_variables
	Input: Array variable[] of struct Variable_type
	Output: None
	Description: Initialize all of the elements in the array variable[].
			variable[i].name = '\0'
			variable[i].value = 0
			variable[i].use = false

*/
void initialize_variables(Variable_type variable[]) {
  for (int i = 0; i < NUM_OF_LETTERS; i++) {
    variable[i].use = false;
    variable[i].value = 0;
    variable[i].name = '\0';
  }
}

/*
	Function: parse_string_to_get_variables
	Input: Array variable[], the string of postfix expression
	Output: If there is an error in the postfix expression, display an error message and return false
		If there is no error, return true
	Discription: This function is used to parse the entire string of postfix expression to get all 
		     of the variables that are used in the expression.
		     It also checks if the expression satisfies all of the following rules:
			1) The length of the expression has to be at least 4, including $ at the end.
			2) The first two characters in the expression must be a variable ( or variables )
			3) The expression must end with $
			4) The number of operands must equal the number of operators + 1
			5) Only A-Z, a-z, +, -, *, / and $ are contained in the expression
		     If one of these rules is not satisfied, an error message will be displayed and function return false.
		     Otherwise,
			The expression is parsed from left to right, 
			if a character in the expression is a letter ( A-Z or a-z ), the ASCII value of the letter is used 
			as an index to access the array variable[]: 
				variable[index].use is set to true to indicate this letter is used in the expression
				variable[index].name is set to this letter, such as ( a or b or etc...)
		    Return true at the end of the function
		
*/
bool parse_string_to_get_variables(Variable_type variable[], string expression) {
  int index = 0;
  int num_of_operands = 0;
  int num_of_operators = 0;
  
  if (expression.size() < 4) {
    cout << "ERROR, expression is too short.\n";
    return false;
  }

  /* 
     Check if the first two characters are letters
   */
  for ( int i = 0; i < 2; i++ ) {
    if ( (int)expression[i] < FIRST_UPPER_CASE_LETTER ||
	 (int)expression[i] > LAST_UPPER_CASE_LETTER &&  (int)expression[i] < FIRST_LOWER_CASE_LETTER ||
         (int)expression[i] > LAST_LOWER_CASE_LETTER ) {
    cout << "ERROR, non-letter detected in first two chars.\n";
    return false;
    }
  }

  
  if (expression[expression.size() - 1] != '$') {
    cout << "ERROR, expression does not end with $.\n";
    return false;
  }

  /*
    Parse the string, 
    if the character is a letter:
       Using the ASCII value of that letter to compute the index to access the array variable,
       The array variable has 52 elements, the first half are for A-Z, the second half are for a-z
       Set variable[index].use = true to indicate that the letter is used in the expression.
       Increment is number of operands.

    else if the character is one of the four operators, increment the number of operators
    else check to see this is the last character and it is $,
    if it is not $, then display an error message and return false

   */
  for (int i = 0; i < expression.length(); i++) {
    if ((int)expression[i] >= FIRST_UPPER_CASE_LETTER && (int)expression[i] <= LAST_UPPER_CASE_LETTER) {
      index = (int)expression[i] - FIRST_UPPER_CASE_LETTER;
      num_of_operands++;
      variable[index].use = true;
      variable[index].name = expression[i];
    }

    else if ((int)expression[i] >= FIRST_LOWER_CASE_LETTER && (int)expression[i] <= LAST_LOWER_CASE_LETTER) {
      index = (int)expression[i] - FIRST_LOWER_CASE_LETTER + NUM_OF_LETTERS / 2;
      num_of_operands++;
      variable[index].use = true;
      variable[index].name = expression[i];

    }
    else if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/') {
      num_of_operators++;
    }
    
    else {
      if (expression[i] != '$') {
		cout << "ERROR, non-letter or non-operator detected.\n";
		return false;
      }

      else if (i != expression.size() - 1) {
	    cout << "ERROR, $ detected before end of string.\n";
	    return false;
	  }
    }
  }
  
  if (num_of_operands != num_of_operators + 1) {
    cout << "ERROR, the number of operators does not equal the number of operands - 1.\n";
    return false;
  }

  return true;

}


/*
	Function: get_values_for_variables
	Input: array variable[]
	Output: Display a message to get the value for each variable from user.
	Discription: Check all of the elements in the array varible,
		     If varialble[i].use = true, display a message and get the value from user
		     The set variable[i].value = the input value from user
	
*/
void get_values_for_variables(Variable_type variable[]) {
  for (int i = 0; i < NUM_OF_LETTERS; i++) {
    if (variable[i].use) {
      cout << "Enter the value for " << variable[i].name << " : ";
      cin >> variable[i].value;
    }
  }
}


/*
	Function: parse_string_to_compute_values
	Input: array variable[], the string of expression
	Output: Return the final value computed using the expression and its values
	Description: Create a stack of type int
                     Parse the expression from left to right:
		         If a character in the expression is a variable, push the value of the variable to the stack
		         If a character is one of the four operators, and the size of the stack is greater than 1
			   call function compute(mystack, expression[i]) to compute the top two values in the stack
		     Return the top value in the stack, this is the final value
*/
int parse_string_to_compute_values(Variable_type variable[], string expression) {

  stack<int> mystack;
  int index;
  for (int i = 0; i < expression.length(); i++) {
    if ((int)expression[i] >= FIRST_UPPER_CASE_LETTER && (int)expression[i] <= LAST_UPPER_CASE_LETTER) {
      index = (int)expression[i] - FIRST_UPPER_CASE_LETTER;
      mystack.push(variable[index].value);
    }
    else if ((int)expression[i] >= FIRST_LOWER_CASE_LETTER && (int)expression[i] <= LAST_LOWER_CASE_LETTER) {
      index = (int)expression[i] - FIRST_LOWER_CASE_LETTER + NUM_OF_LETTERS / 2;
      mystack.push(variable[index].value);
    }
    else {
      if (mystack.size() > 1) {
	compute(mystack, expression[i]);
      }
    }
  }

  return mystack.top();
}


/*
	Function: compute
	Input: A stack of type int is passed by referenced, the operator to compute
	Output: None
	Discription: Pop the top two values from the stack, 
		     compute those values using the operator, then push the result back to the stack
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
