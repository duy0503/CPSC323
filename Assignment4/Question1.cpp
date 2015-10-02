/*
  Author Name: Duy Do, Tetsuya Tanaka
  Course: CPSC 323
  Assignment 4
  Question 1
  Due Date: 10/01/2015
  Project Information: Read file data.txt and copy it into file newdata.txt by removing all comment lines
                       extra spaces, and placing space before and after each token

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
         a vector to store all of the tokens 
  Output: None.

  Description:
    - Declare string variable named token to store the current token
    - Parse the string w from left to right character by character
      - Whenenver we encounter "//" in the string, skip the rest of the string because it is a comment
      - If the character is one of the digits
        - As long as the next character is either a number, a letter or underscore, keep adding those characters to the token
	- Check every single charater in var to see if all of them are numbers.
	  - If they are, then this token is a number. Add the token to the vector 
	  - Else, it is not identifier ( which is an error ). Add the token to the vector
     
      - If the character is a letter or underscore
        - Keep looping and adding the next characters to token as long as they are either a digit, a letter or underscore.
	- If token is "cout", check the next two characters to see if they are "<<".
	   - If they are, then this token is a reserved_word. Add the token to the vector
        - Loop through each items in the array Reserved_Word to see if token is one of them.
           - If it is, then the token is a reserved_word. Add the token to the vector
           - Else, the token is an idenfifier. Add the token to the vector

      - Loop through each items in the array Special to see if the character is one of them
         - If it is, then the token is a special symbol. Add the token to the vector

      - If the character is one of the operators ( +, -, *, /). Add the token to the vector
	  

 */
void get_tokens(string w, vector<string> &tokens);

/*
  Function: add_token_to_list
  Input: reference to the token
         reference to the tokens vector that contains all of the tokens
  Output: None.
  Description:
     - Add the token to the end of the list
     - Set the value of token to an empty string.
 */
void add_token_to_list( string &token, vector<string>& tokens);

/*

  Function: main
  Description:
     - Open the data.txt file to read in data.
     - Read the file line by line
        - call function get_tokens to parse the line and get all of the tokens in that line
     - Open the file newdata.txt and write all of the tokens into that file
        - Iterate through the tokens vector and write them out to the file
           - If the token is ";", then add a new line.
 */
int main() { 

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

  int i, j;
  bool not_id = false;
  bool reserved = false;
  string token = "";
  
  for ( i = 0; i < w.length(); i++ ) {

    // Get rid of comment from the file

    if ( (w[i] == '/') && (w[i+1] == '/')) return;

    // w[i] is a number
    if ( isdigit(w[i]) ) {
      while ( isalpha(w[i]) || isdigit(w[i]) || w[i] == '_' ) {
	token = token + w[i];
	i++;
      }

      for ( j = 0; j < var.length(); j++ ) {
	if ( !isdigit(var[j])) {
	  not_id = true;
	  break;
	}
      }

      if ( not_id ) {
        add_token_to_list(token, tokens);
	not_id = false;
      }
      else {
        add_token_to_list(token, tokens);
      }
    }

    //w[i] is a letter or '_'
    if ( isalpha(w[i]) || w[i] == '_' ) {
      while ( isalpha(w[i]) || isdigit(w[i]) || w[i] == '_' ) {
	token = token + w[i];
	i++;
      }

      //Check if token is "cout"
      if ( token == "cout" ) {
	//check the next two character to see if they are "<<"
	if ( w[i] == '<' && w[i+1] == '<' ) {
	  token = token + "<<";
	  add_token_to_list(token, tokens);
	  i++;
	  continue;
	}
      }
      // Check if token is a reserved word
      for ( j = 0; j < TOTAL_RESERVED_WORD; j++ ) {
	if ( token == Reserved_Word[j] ) {
	  reserved = true;
	  break;
	}
      }

      if ( reserved ) {
	// token is a reserved word
        add_token_to_list(token, tokens);
      }
      else {
	// token is an identifier
        add_token_to_list(token, tokens);
      }

      reserved = false;
    }

    // Check for the special symbol
    if ( w[i] == '<' ) {
      token = token + w[i];
      i++;
      if ( w[i] == '=' ) {
	token = token + w[i];
	
	//token is a special symbol
        add_token_to_list(token, tokens);
      }
      else {
	//token is not a special symbol
        add_token_to_list(token, tokens);
      }  
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

/* Implementation of function add tokens_to_list */
void add_token_to_list( string &token, vector<string>& tokens) {

  tokens.push_back(token);
  token = "";

}
