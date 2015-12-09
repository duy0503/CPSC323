#include "parser.h"
using namespace std;

/*
program id num integer + - * / ( ) : Åg write ; end. 
i = identifier
n = number
s = string
*/

string Table[17][20] = 
{
        // p            i      ;    v     b     e    +   -     *      /    =    (      )    w         n    s    $    ,    :   t
  "pi;vBbCe"        , ""    , "" , ""  , "",  "" ,  " ",  "" , ""  , ""  , "" , "" , ""   , ""      , ""  , "" , "", "" , ""   , "",// A
   ""               , "D:t;", "" , ""  , "", ""  , ""  , ""  , ""  , ""  , "" , "" , ""   , ""      , ""  ,""  ,"" , "" , ""  ,  "",// B
   ""               , "EL"  , "" , ""  , "", ""  , ""  , ""  , ""  , ""  , "" , "" , ""   , "EL"    , ""  , "" ,"" , "" , ""  ,  "",// C
   ""               , "iX"  , "" , ""  , "", ""  , ""  , ""  , ""  , ""  , "" , "" , ""   , ""      , ""  , "" ,"" , "" , ""  ,  "",// D
   ""               , "G"   , "" , ""  , "", ""  , ""  , ""  , ""  , ""  , "" , "" , ""   , "F"     , ""  , "" ,"" , "" , ""  ,  "",// E
   ""               , ""    , "" , ""  , "", ""  , ""  , ""  , ""  , ""  , "" , "" , ""   , "w(Hi);", ""  , "" ,"" , "" , ""  ,  "",// F
   ""               , "i=I;", "" , ""  , "", ""  , ""  , ""  , ""  , ""  , "" , "" , ""   , ""      , ""  , "" ,"" , "" , ""  ,  "",// G
   ""               , "#"   , "" , ""  , "", ""  , ""  , ""  , ""  , ""  , "" , "" , ""   , ""      , ""  ,"s,","" , "" , ""  ,  "",// H
   ""               , "TZ"  , "" , ""  , "", ""  , "TZ", "TZ", ""  , ""  , "" ,"TZ", ""   , ""      , "TZ", "" ,"" , "" , ""  ,  "",// I
   ""               , ""    , "#", ""  , "", ""  , "+I", "-I", ""  , ""  , "" , "" , "#"  , ""      , ""  , "" ,"" , "" , ""  ,  "",// Z
   ""               , "KQ"  , "" , ""  , "", ""  , "KQ", "KQ", ""  , ""  , "" ,"KQ", ""   , ""      , "KQ", "" ,"" , "" , ""  ,  "",// T
   ""               , ""    , "#", ""  , "", ""  , "#" , "#" ,"*KQ","/KQ", "" , "" , "#"  , ""      , ""  , "" ,"" , "" , ""  ,  "",// Q
   ""               , "i"   , "" , ""  , "", ""  , "N" , "N" , ""  , ""  , "" ,"(I)", ""  , ""      , "N" , "" ,"" , "" , ""  ,  "",// K
   ""               , ""    , "" , ""  , "", ""  , "+" , "-" , ""  , ""  , "" , ""  , ""  , ""      , "#" , "" ,"" , "" , ""  ,  "",// S
   ""               , ""    , "" , ""  , "", ""  , "Sn", "Sn", ""  , ""  , "" , ""  , ""  , ""      , "Sn", "" ,"" , "" , ""  ,  "",// N
   ""               , "C"   , "" , ""  , "", "#" , ""  , ""  , ""  , ""  , "" , ""  , ""  , "C"     , ""  , "" ,"" , "" , ""  ,  "",// L
  ""                , ""    , "" , ""  , "", ""  , ""  , ""  , ""  , ""  , "" , ""  , ""  , ""      , ""  , "" ,"" ,",D", "#" , ""  // X
};

bool reserved_word_used[6] = { false, false, false, false, false, false};

static bool check_reserved_word(vector<string> reserved) {

  vector<string>::iterator it;
  for ( it = reserved.begin(); it != reserved.end(); it++) {

    for ( int i=0; i < 6; i++) {
      if ( *it == Reserved_Word[i] ) reserved_word_used[i] = true;
    }
  }

  for ( int i=0; i < 6; i++) {
    if ( reserved_word_used[i] == false ) {

      cout << Reserved_Word[i] << " is missing." <<endl;
      return false;
    }
  }
  return true;
}

static int get_column(char w){
  switch(w) {
  case 'p':
    return 0;
  case 'i':
    return 1;
  case ';':
    return 2;
  case 'v': 
    return 3;
  case 'b':
    return 4;
  case 'e':
    return 5;
  case '+':
    return 6;
  case '-':
    return 7;
  case '*':
    return 8;
  case '/':
    return 9;
  case '=':
    return 10;
  case '(': 
    return 11;
  case ')':
    return 12;
  case 'w':
    return 13;
  case 'n':
    return 14;
  case 's':
    return 15;
  case '$':
    return 16;
  case ',':
    return 17;
  case ':':
    return 18;
  case 't':
    return 19;
  default:
    return -1;
  }
}

static int get_row(char w) {
  switch(w) {
  case 'A':
    return 0;
  case 'B':
    return 1;
  case 'C':
    return 2;
  case 'D':
    return 3;
  case 'E':
    return 4;
  case 'F':
    return 5;
  case 'G':
    return 6;
  case 'H':
    return 7;
  case 'I':
    return 8;
  case 'Z':
    return 9;
  case 'T':
    return 10;
  case 'Q':
    return 11;
  case 'K':
    return 12;
  case 'S':
    return 13;
  case 'N':
    return 14;
  case 'L':
    return 15;
  case 'X':
    return 16;
  default:
    return -1;
  }
}

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
  bool accepted = false;
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

  if ( !check_reserved_word(reserved)) return false;
  accepted = check(new_tokens);
  return accepted;

}

bool check(vector<char> tokens) {
  
  char w;
  stack<char> my_stack;
  vector<char> stack_content; // use this to print out the content of the stack
  vector<char>::iterator it;
  vector<char>::iterator current_it;
  char s;
  int row = 0;
  int col = 0;
  int counter = 0;
  string content;

  my_stack.push('$');
  my_stack.push('A');
  tokens.push_back('$');

  // For the purpose of printing the stack
  stack_content.push_back('$');
  stack_content.push_back('A');

  current_it = tokens.begin();
  w = *current_it;
  col = get_column(w);
  while ( !my_stack.empty() ) {
    
    //Get the top of the stack
    s = my_stack.top();
    my_stack.pop();

    //Keep track of the content in the stack
    stack_content.pop_back();

    // current token matches with s
    if ( s == w ) {

      // Print out the content of the stack from stack_content
      for ( it = stack_content.begin(); it != stack_content.end(); it++) cout << *it <<" ";
      cout <<endl;
      
      // This is the last character
      if ( s == '$' ) {
	cout << "Accepted"<<endl;
	return true;
      }
      // If it's not the last character, read the next character in the input
      else {
	current_it++;
	w = *current_it;
	col = get_column(w);
	if ( col < 0 ) {
	  cout << "w rejected!"<< endl;
	  return false;
	}
	continue;
      }
    }
    
    row = get_row (s);
    if ( row  < 0 ) {
      cout << "rejected!"<< endl;
      cout << s << " is missing" << endl;
      return false;
    }

    // Get the content in the table based on the row and column
    content = Table[row][col];

    // if the content is empty, reject the input
    if ( content.length() == 0 ) {
      cout<<"error"<<endl;
      get_error(my_stack);
      return false;
    }
    // if it is lambda ( I put '#' for lambda in the table )
    // go back to the top of the loop
    else if ( content == "#" ) continue;

    // push the content to the stack starting from the last character of the content
    else {
      for ( int i = content.length()-1; i >= 0; i-- ) {
	my_stack.push(content[i]);
	stack_content.push_back(content[i]);
      }
    }
    
  } 
 
  return true;
}

void get_error(stack<char> stack_content) {

  char i;

  while ( !stack_content.empty() ) {

    i = stack_content.top();
    stack_content.pop();
    if ( (int) i < 65 || (int) i > 90 ) {
      cout << i << " is missing"<<endl;
      return;
    }
  }

}
