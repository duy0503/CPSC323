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
#include <fstream>

using namespace std;

const int TOTAL_RESERVED_WORD = 4;
const int TOTAL_SPECIAL  = 10;
const string Reserved_Word[TOTAL_RESERVED_WORD] = {"cout<<", "for", "int", "while"};
const string Special[TOTAL_SPECIAL] = {"=", "_", "*", ";", "(", ")", "<=", "<", ">", ","};

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
void get_tokens(string w, vector<string> &tokens);
void add_token_to_list( string &token, vector<string>& tokens);

int main() { 
  char option = 'y';  /* variable to get option from user, 
							either continue with another expression or stop */
  string statement = "";
  vector<string> tokens;

  // Open file
  ifstream inFile("data.txt");
  if ( !inFile.is_open() ) {
    cout << "Couldn't open file!" <<endl;
    exit(1);
  }

  getline(inFile, statement);
  do {
    
    get_tokens(statement, tokens);

  } while (getline(inFile, statement));

  vector<string>::iterator it;

  // Write to new file
  ofstream outFile("newdata.txt");
  if ( !outFile.is_open() ) {
    cout << "Couldn't open new file to write data" <<endl;
    exit(2);
  }
  for ( it = tokens.begin(); it != tokens.end(); it++ ) {
    if ( *it == ";" ) outFile <<" "<<*it <<endl;
    else outFile <<" "<<*it;

  }

  inFile.close();
  outFile.close();
  return 0;
}

/* Implementation of function get_tokens */
void get_tokens(string w, vector<string> &tokens) {

  string var = "";
  int i, j;
  bool not_id = false;
  bool reserved = false;
  string token;
  
  for ( i = 0; i < w.length(); i++ ) {


    // Get rid of comment from the file

    if ( (w[i] == '/') && (w[i+1] == '/')) return;

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
	
	token = var;
        add_token_to_list(token, tokens);
	not_id = false;
      }
      else {
	
	token = var;
        add_token_to_list(token, tokens);
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
	  token = var;
	  add_token_to_list(token, tokens);
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
	// token is a reserved word
	token = var;
        add_token_to_list(token, tokens);
      }
      else {
	// token is an identifier
        token = var;
        add_token_to_list(token, tokens);
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
	
	//token is a special symbol
        token = var;
        add_token_to_list(token, tokens);
      }
      else {
	//token is not a special symbol
	token = var;
        add_token_to_list(token, tokens);
      }  
      var = "";
    }  else {
      for ( j = 0; j < TOTAL_SPECIAL; j++ ) {
	if ( w[i] == Special[j][0] ) {

	  //token is a special symbol	  
	  token = w[i];
	  add_token_to_list(token, tokens);
	  break;
	}
      }
    }

    // Check for operator
    if ( w[i] == '+' || w[i] == '-' || w[i] == '*' || w[i] == '/' ) {
      //token is an operator
      token = w[i];
      add_token_to_list(token, tokens);
    }
      
  }

}

void add_token_to_list( string &token, vector<string>& tokens) {

  tokens.push_back(token);
  token = "";

}
