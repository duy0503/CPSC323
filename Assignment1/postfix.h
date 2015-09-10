

/*
	This is the header file for postfix.cpp
*/

#include <string>
#include <stack>

using namespace std;

/*
	Declare a few constant variables based on the ASCII values 
	of the first upper-case letter (A), the last upper-case letter (Z),
	the first lower-case letter (a), the last lower_case letter (z),
	and the maximum number of characters available ( A-Z and a-z )
*/
const int FIRST_UPPER_CASE_LETTER = 65;
const int LAST_UPPER_CASE_LETTER = 90;
const int FIRST_LOWER_CASE_LETTER = 97;
const int LAST_LOWER_CASE_LETTER = 122;
const int NUM_OF_LETTERS = 52;

/*
	This structure represents the properties of a variable including the name
	of the variable, the value of the variable, and a boolean type to indicate 
	if this variable is used in the postfix expression.
*/
struct Variable_type {
  char name;
  int value;
  bool use;
};

/*
	Function: initialize_variables
	Input: Array variable[] of struct Variable_type
	Output: None
	Description: Initialize all of the elements in the array variable[].
			variable[i].name = '\0'
			variable[i].value = 0
			variable[i].use = false

*/
void initialize_variables(Variable_type variable[]);

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
bool parse_string_to_get_variables(Variable_type variable[], string expression);

/*
	Function: get_values_for_variables
	Input: array variable[]
	Output: Display a message to get the value for each variable from user.
	Discription: Check all of the elements in the array varible,
		     If varialble[i].use = true, display a message and get the value from user
		     The set variable[i].value = the input value from user
	
*/
void get_values_for_variables(Variable_type variable[]);

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
int parse_string_to_compute_values(Variable_type variable[], string expression);
/*
	Function: compute
	Input: A stack of type int is passed by referenced, the operator to compute
	Output: None
	Discription: Pop the top two values from the stack, 
		     compute those values using the operator, then push the result back to the stack
*/
void compute(stack<int> & mystack, char OP);
