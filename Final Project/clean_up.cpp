#include "clean_up.h"
using namespace std;


vector<string> clean_up(string file_name){
  string statement = "";
  stack<int> comment;
  vector<string> tokens;

  // Open file
  ifstream inFile(file_name.c_str());
  if ( !inFile.is_open() ) {
    cout << "Couldn't open file!" <<endl;
    exit(1);
  }

  getline(inFile, statement);
  do {
    
    remove_comments(statement, tokens, comment);

  } while (getline(inFile, statement));

  vector<string>::iterator it;

  // Write to new file
  ofstream outFile("finalv2.txt");
  if ( !outFile.is_open() ) {
    cout << "Couldn't open new file to write data" <<endl;
    exit(2);
  }
  for ( it = tokens.begin(); it != tokens.end(); it++ ) {
    if ( *it == ";" ) outFile <<" "<<*it <<endl;
    else if ( *it == "var" || *it == "begin" || *it == "end." ) outFile <<" "<<*it<<endl;
    else outFile <<" "<<*it;

  }

  inFile.close();
  outFile.close();
  return tokens;
}

/* Implementation of function remove comments */
void remove_comments(string w, vector<string> &tokens, stack<int> &comment) {

  int i, j;
  bool not_id = false;
  bool reserved = false;
  string token = "";
  stack<char> print_string;
  
  for ( i = 0; i < w.length(); i++ ) {

    // Get rid of comment from the file

    if ( (w[i] == '/') && (w[i+1] == '/')) return;
    
    if ( (w[i] == '(') && (w[i+1] == '*')) {
      i++;
      i++;
      comment.push(1);
    }
    else if ( (w[i] == '*') && (w[i+1] == ')')) {
      i++;
      i++;
      comment.pop();
    }

    if ( !comment.empty() ) continue;

    // w[i] is a number
    if ( isdigit(w[i]) ) {
      while ( isalpha(w[i]) || isdigit(w[i]) ) {
	token = token + w[i];
	i++;
      }   
      add_token_to_list(token, tokens);

    }

    // token is a string
    if ( w[i] == '"' ) {

      print_string.push('"');
      while ( !print_string.empty() && i < w.length() ) {
	token = token + w[i];
	i++;
	if ( w[i] == '"' ) {
	  print_string.pop();
	  token = token + w[i];
	  i++;
	}
      }

      add_token_to_list(token, tokens);
    }
    //w[i] is a letter
    if ( isalpha(w[i]) ) {
      while ( isalpha(w[i]) || isdigit(w[i]) || w[i] == '.') {
	token = token + w[i];
	i++;
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
    for ( j = 0; j < TOTAL_SPECIAL; j++ ) {
      if ( w[i] == Special[j][0] ) {

	//token is a special symbol	  
	token = w[i];
	add_token_to_list(token, tokens);
	break;
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
