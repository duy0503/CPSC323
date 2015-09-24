/*
  Author Name: Duy Do, Tetsuya Tanaka
  Course: CPSC 323
  Assignment 3
  Question 1
  Due Date: 09/24/2015
  Project Information: Read a statement and determine whether each token is a number, identifier, a reserved word, or special character

 */

#include <iostream>
#include <string>
#include <ctype.h>
#include <vector>
#include <stdlib.h>
#include <cstring>

using namespace std;

const int TOTAL_RESERVED_WORD = 4;
const int TOTAL_SPECIAL  = 7;
const string Reserved_Word[TOTAL_RESERVED_WORD] = {"cout<<", "for", "int", "while"};
const string Special[TOTAL_SPECIAL] = {"=", "_", "*", ";", "(", ")", "<="};

/*
  Function: get_tokens
  Input: string w, which is the input statement from user
         the vectors to store the tokens including number, identifier, reserved_word, special_symbol, operators
  Output: Print out each token with its type
  Description:
    - Declare string variable named var to store the current token
    - Parse the string w from left to right character by character
      - If the character is one of the digits
        - As long as the next character is either a number, a letter or underscore, keep adding those characters to var
	- Check every single charater in var to see if all of them are numbers.
	  - If they are, then this token is a number, print it out and add it to the number vector.
	  - Else, it is not identifier ( which is an error ), print it out.
     
      - If the character is a letter or underscore
        - Keep looping and adding the next characters to var as long as they are either a digit, a letter or underscore.
	- If var is "cout", check the next two characters to see if they are "<<".
	   - If they are, then this token is a reserved_word, print it out and add it to the reserved_word vector.
        - Loop through each items in the array Reserved_Word to see if var is one of them.
           - If it is, then the token is a reserved_word, print it out and add it to the reserved_word vector.
           - Else, the token is an idenfifier, print it out and add it to the idendifier vector.

      - Loop through each items in the array Special to see if the character is one of them
         - If it is, then the token is a special symbol, print it out and add it to the special_symbol vector.

      - If the character is one of the operators ( +, -, *, /), print it out and add it tho the operators vector.
	  

 */
void get_tokens(string w, vector<int> & number, vector<string> &identifier, vector<string> &reserved_word, 
                vector<string> &special_symbol, vector<char> &operators);

int main() { 
  char option = 'y';  /* variable to get option from user, 
							either continue with another expression or stop */
  string statement = "";
  vector<int> number;
  vector<string> identifier;
  vector<string> reserved_word;
  vector<string> special_symbol;
  vector<char> operators;
  
  do {
    cout << "Enter a statement: ";
    getline(cin, statement);

    get_tokens(statement, number, identifier, reserved_word, special_symbol, operators);

    cout << "Continue(y/n)? ";
    cin >> option;
    cin.ignore();
  } while (option == 'y');

  return 0;
}

/* Implementation of function get_tokens */
void get_tokens(string w, vector<int> & number, vector<string> &identifier, vector<string> &reserved_word, 
                vector<string> &special_symbol, vector<char> &operators) {

  string var = "";
  int i, j;
  bool not_id = false;
  bool reserved = false;
  
  for ( i = 0; i < w.length(); i++ ) {

    // w[i] is a number
    if ( isdigit(w[i]) ) {
      while ( isalpha(w[i]) || isdigit(w[i]) || w[i] == '_' ) {

	var = var + w[i];
	i++;
      }

      for ( j = 0; j < var.length(); j++ ) {
	if ( !isdigit(var[j])) {
	  not_id = true;
	  break;
	}
      }

      if ( not_id ) {
	cout << var <<"\t\tnot identifier"<<endl;
	not_id = false;
      }
      else {
	cout << var <<"\t\tnumber"<<endl;
	number.push_back(atoi(var.c_str()));
      }
      var = "";
    }

    //w[i] is a letter or '_'
    if ( isalpha(w[i]) || w[i] == '_' ) {
      while ( isalpha(w[i]) || isdigit(w[i]) || w[i] == '_' ) {
	var = var + w[i];
	i++;
      }

      //Check if var is "cout"
      if ( var == "cout" ) {
	//check the next two character to see if they are "<<"
	if ( w[i] == '<' && w[i+1] == '<' ) {
	  var = var + "<<";
	  cout << var <<"\t\treserved word"<<endl;
	  reserved_word.push_back(var);
	  i++;
	  var = "";
	  continue;
	}
      }
      // Check if var is a reserved word
      for ( j = 0; j < TOTAL_RESERVED_WORD; j++ ) {
	if ( var == Reserved_Word[j] ) {
	  reserved = true;
	  break;
	}
      }

      if ( reserved ) {
	cout << var <<"\t\treserved word"<<endl;
	reserved_word.push_back(var);
      }
      else {
	cout << var <<"\t\tidentifier"<<endl;
	identifier.push_back(var);
      }

      reserved = false;
      var = "";
    }

    // Check for the special symbol
    if ( w[i] == '<' ) {
      var = var + w[i];
      i++;
      if ( w[i] == '=' ) {
	var = var + w[i];
	cout << var <<"\t\tspecial symbol"<<endl;
	special_symbol.push_back(var);
      }
      else cout << var <<"\t\tnot special symbol"<<endl;
      
      var = "";
    }  else {
      for ( j = 0; j < TOTAL_SPECIAL; j++ ) {
	if ( w[i] == Special[j][0] ) {
	  cout << w[i] <<"\t\tspecial symbol"<<endl;
	  special_symbol.push_back(var);
	  break;
	}
      }
    }

    // Check for operator
    if ( w[i] == '+' || w[i] == '-' || w[i] == '*' || w[i] == '/' ) {
      cout << w[i] <<"\t\toperator"<<endl;
      operators.push_back(w[i]);
    }
      
  }

}
