#include "parser.h"
using namespace std;

/*

To make the table smaller, we convert the big parsing table to a smaller table with new grammar
A -> p i ; v B b C e                   where:      A = <prog>
B -> D : t ;                                       B = <dec-list>
D -> i X                                           C = <stat-list>
X -> , D                                           D = <dec>
X -> LAMBDA                                        E = <stat>
C -> E L                                           F = <write>
L -> C                                             H = <str>
L -> LAMBDA                                        I = <expr>
E -> F | G                                         G = <assign>       
F -> w ( H i ) ;                                   T = <term>
H -> s , | LAMBDA                                  Q = <factor>
G -> i = I;                                        N = <number>
I -> T Z                                           S = <sign>
Z -> + I
Z -> - I                                           n = <digit>  , this is verified by function check_number
Z -> LAMBDA                                        i = <identifier> , this is verified by function check_identifier   
T -> K Q                                           p = program , reserved words are verified by function check_reserved_word
Q -> * K Q                                         v = var
Q -> / K Q                                         b = begin
Q -> LAMBDA                                        e = end.
K -> i | N | ( I )                                 w = write
N -> S n                                           s = "what ever" , this is verified by function check_string
S -> + | - | LAMBDA
*/

// LL table used to parse all of the tokens
string Table[17][20] = 
{
        // p            i      ;    v     b     e    +   -     *      /    =    (      )    w         n    s    $    ,    :   t
  "pi;vBbCe"        , ""    , "" , ""  , "",  "" ,  " ",  "" , ""  , ""  , "" , "" , ""   , ""      , ""  , "" , "", "" , ""  ,  "",// A
   ""               , "D:t;", "" , ""  , "", ""  , ""  , ""  , ""  , ""  , "" , "" , ""   , ""      , ""  ,""  ,"" , "" , ""  ,  "",// B
   ""               , "EL"  , "" , ""  , "", ""  , ""  , ""  , ""  , ""  , "" , "" , ""   , "EL"    , ""  , "" ,"" , "" , ""  ,  "",// C
   ""               , "iX"  , "" , ""  , "", ""  , ""  , ""  , ""  , ""  , "" , "" , ""   , ""      , ""  , "" ,"" , "" , ""  ,  "",// D
   ""               , "G"   , "" , ""  , "", ""  , ""  , ""  , ""  , ""  , "" , "" , ""   , "F"     , ""  , "" ,"" , "" , ""  ,  "",// E
   ""               , ""    , "" , ""  , "", ""  , ""  , ""  , ""  , ""  , "" , "" , ""   , "w(Hi);", ""  , "" ,"" , "" , ""  ,  "",// F
   ""               , "i=I;", "" , ""  , "", ""  , ""  , ""  , ""  , ""  , "" , "" , ""   , ""      , ""  , "" ,"" , "" , ""  ,  "",// G
   ""               , "#"   , "" , ""  , "", ""  , ""  , ""  , ""  , ""  , "" , "" , ""   , ""      , ""  ,"s,","" , "" , ""  ,  "",// H
   ""               , "TZ"  , "" , ""  , "", ""  , "TZ", "TZ", ""  , ""  , "" ,"TZ", ""   , ""      , "TZ", "" ,"" , "" , ""  ,  "",// I
   ""               , "#"   , "#", ""  , "", ""  , "+I", "-I", ""  , ""  , "" , "" , "#"  , "#"     , ""  , "" ,"" , "" , ""  ,  "",// Z
   ""               , "KQ"  , "" , ""  , "", ""  , "KQ", "KQ", ""  , ""  , "" ,"KQ", ""   , ""      , "KQ", "" ,"" , "" , ""  ,  "",// T
   ""               , "#"   , "#", ""  , "", ""  , "#" , "#" ,"*KQ","/KQ", "" , "" , "#"  , "#"     , ""  , "" ,"" , "" , ""  ,  "",// Q
   ""               , "i"   , "" , ""  , "", ""  , "N" , "N" , ""  , ""  , "" ,"(I)", ""  , ""      , "N" , "" ,"" , "" , ""  ,  "",// K
   ""               , ""    , "" , ""  , "", ""  , "+" , "-" , ""  , ""  , "" , ""  , ""  , ""      , "#" , "" ,"" , "" , ""  ,  "",// S
   ""               , ""    , "" , ""  , "", ""  , "Sn", "Sn", ""  , ""  , "" , ""  , ""  , ""      , "Sn", "" ,"" , "" , ""  ,  "",// N
   ""               , "C"   , "" , ""  , "", "#" , ""  , ""  , ""  , ""  , "" , ""  , ""  , "C"     , ""  , "" ,"" , "" , ""  ,  "",// L
  ""                , ""    , "" , ""  , "", ""  , ""  , ""  , ""  , ""  , "" , ""  , ""  , ""      , ""  , "" ,"" ,",D", "#" , ""  // X
};

// FA table used to verify the identifier
int ID_Table[3][3] = { 1, 2, 2,
		       1, 1, 2,
		       2, 2, 2};

// Array used to check the reserved list
bool reserved_word_used[6] = { false, false, false, false, false, false};

static bool check_number(vector<string> num) {

  string current;
  for ( vector<string>::iterator it = num.begin(); it != num.end(); it++ ) {

    current = *it;

    for ( int i = 0; i < current.length(); i++ ) {

      if ( !isdigit(current[i]) ) {
	cout << current <<" is not a number. Rejected"<<endl;
	return false;
      }
    }
  }
  return true;
}


static bool check_string(vector<string> s ) {

  string current;
  for ( vector<string>::iterator it = s.begin(); it != s.end(); it++ ) {

    current = *it;
    if ( current[0] != '"' || current[current.length()-1] != '"' ) {
      cout << "Token string is not correct, \" is missing" << endl;
      return false;
    }
  }
  return true;  
}

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

static bool check_identifier(vector<string> id ) {

  string current_id;
  int state = 0, i, col;
  char w;
  for ( vector<string>::iterator it = id.begin(); it != id.end(); it++) {

    i = 0;
    current_id = *it + "$";
    while ( i < current_id.length() ) {
      if ( current_id[i]=='a' || current_id[i]=='b' || current_id[i]=='c' || current_id[i]=='d' ) col = 0;
      else if ( isdigit(current_id[i]) ) col = 1;
      else if ( current_id[i] =='$' ) {
	if (state==2){
	  cout << "Token " << *it <<" is not an identifier"<<endl;
	  cout << "Rejected"<<endl;
	  return false;
	};
      }
      else col = 2;

      state = ID_Table[state][col];
      ++i;
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

static char convert_reserved_word ( string reserved ) {

  if (reserved == "program") return 'p';
  else if ( reserved == "var" ) return 'v';
  else if ( reserved == "begin") return 'b';
  else if ( reserved == "end." ) return 'e';
  else if ( reserved == "integer" ) return 't';
  else if ( reserved == "write" ) return 'w';

}

vector<char> get_tokens_lists(vector<string> tokens, vector<string> &id, vector<string> &num, vector<string> &reserved, vector<string> &str){

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
    else if ( current[0] == '"' ) {
      new_tokens.push_back('s');
      str.push_back(current);
    }

    // if token is a special character
    else new_tokens.push_back(current[0]);
  }

  return new_tokens;
}

bool parse(vector<string> tokens){

  vector<string> id;
  vector<string> num;
  vector<string> reserved;
  vector<string> str;
  vector<char> new_tokens;
  new_tokens = get_tokens_lists(tokens, id, num, reserved, str);
  
#if LOG_FILE==1  // used for debugging purpose
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
  cout << endl;
#endif
  
  if ( !check_reserved_word(reserved)) return false;
  if ( !check_string(str) ) return false;
  if ( !check_number(num) ) return false;
  if ( !check_identifier(id) ) return false;
  if ( !check(new_tokens) ) return false;
  return true;

}

bool check(vector<char> tokens) {
  
  char w;
  stack<char> my_stack;
  vector<char> stack_content; // use this to print out the content of the stack
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

#if LOG_FILE==1  // used for debugging purpose
      // Print out the content of the stack from stack_content
      for (  vector<char>::iterator it = stack_content.begin(); it != stack_content.end(); it++) cout << *it <<" ";
      cout <<endl;
#endif 
      // This is the last character
      if ( s == '$' ) {
	cout << "Accepted"<<endl;
	cout << "File is now translated to final.cpp"<<endl;
	return true;
      }
      // If it's not the last character, read the next character in the input
      else {
	current_it++;
	w = *current_it;
	col = get_column(w);
	if ( col < 0 ) {
	  cout << "Token " << w << " is not valid"<<endl;
	  cout << "Rejected!"<< endl;
	  return false;
	}
	continue;
      }
    }
    
    row = get_row (s);
    if ( row  < 0 ) {
      if ( w == '(' ) cout << "write is missing" <<endl;
      else  cout << s << " is missing" << endl;
      cout << "Rejected!"<< endl;
      return false;
    }

    // Get the content in the table based on the row and column
    content = Table[row][col];

    // if the content is empty, reject the input
    if ( content.length() == 0 ) {
      get_error(s,w);
      cout << "Rejected"<<endl;
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

void get_error(char non_term, char term) {

  string content;
  if ( non_term == 'X' ) {
    if ( term == 'i' ) cout << " , is missing" <<endl;
    else if ( term == 't' ) cout << " : is missing" <<endl;
  }
  else {
    for ( int i = 0; i < 20; i++ ) {
      content = Table[get_row(non_term)][i];
      if ( content != "" && content != "#" ) {
	cout << content[0] << " is missing"<<endl;
      }
    }
  }
}
