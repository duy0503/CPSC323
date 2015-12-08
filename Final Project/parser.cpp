#include "parser.h"
using namespace std;

char convert_reserved_word ( string reserved ) {

  if (reserved == "program") return 'p';
  else if ( reserved == "var" ) return 'v';
  else if ( reserved == "begin") return 'b';
  else if ( reserved == "end." ) return 'e';
  else if ( reserved == "integer" ) return 't';
  else if ( reserved == "write" ) return 'w';

}

vector<char> get_tokens_lists(vector<string> tokens, vector<string> &id, vector<string> &num, vector<string> &reserved){

  string current;
  vector<string>::iterator it;
  vector<char> new_tokens;
  char type;
  bool is_reserved = false;
  for ( it = tokens.begin(); it != tokens.end(); it++) {
    current = *it;
    // current starts with a number
    if ( isdigit(current[0]) ){
      num.push_back(current);
      new_tokens.push_back('n');
    }
    else if ( isalpha(current[0])){
      // check for reserved words
      for ( int i = 0; i < TOTAL_RESERVED_WORD; i++ ) {
	if ( current == Reserved_Word[i] ) {
	  is_reserved = true;
	  break;
	}
      }
      if ( is_reserved ) {
	reserved.push_back(current);
	new_tokens.push_back(convert_reserved_word(current));
      }
      else {
	id.push_back(current);
	new_tokens.push_back('i');
      }
      is_reserved = false;
    }

    // if token is a string
    else if ( current[0] == '"' ) new_tokens.push_back('s');

    // if token is a special character
    else new_tokens.push_back(current[0]);
  }

  return new_tokens;
}

bool parse(vector<string> tokens){

  vector<string> id;
  vector<string> num;
  vector<string> reserved;
  vector<char> new_tokens;
  new_tokens = get_tokens_lists(tokens, id, num, reserved);
  vector<string>::iterator it;
  for ( it = id.begin(); it != id.end(); it++) cout<< *it <<" ";
  cout<<endl;
  for ( it = num.begin(); it != num.end(); it++) cout << *it <<" ";
  cout <<endl;
  for ( it = reserved.begin(); it != reserved.end(); it++) cout << *it <<" ";
  cout <<endl;

  vector<char>::iterator i;
  for ( i = new_tokens.begin(); i != new_tokens.end(); i++) {

    if ( *i == ';' ) cout << *i<<endl;
    else cout <<*i <<" ";
  }
  return true;

}

