#include "parser.h"
#include <deque>
using namespace std;

/*
program id num integer + - * / ( ) : g write ; end. ,
i = identifier
n = number
s = string
*/

string table[16][16] = 
{
	{ "p i ; v 1 b 5 e", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "" }, // program
	{ "", "2 : 4 ;", "", "", "", "", "", "", "", "", "", "", "", "", "", "" }, // dec-list
	{ "", "i 3", "", "", "", "", "", "", "", "", "", "", "", "", "", "" }, // dec
	{ "", "", "", "", "", "", "", "", "", "", "l", "", "", "", "", ", 2" }, // X
	{ "", "", "", "t", "", "", "", "", "", "", "", "", "", "", "", "" }, // type
	{ "", "7 6", "", "", "", "", "", "", "", "", "", "", "7 6", "", "", "" }, // stat-list
	{ "", "5", "", "", "", "", "", "", "", "", "", "", "5", "", "l", "" }, // Y
	{ "", "10", "", "", "", "", "", "", "", "", "", "", "8", "", "", "" }, // stat
	{ "", "", "", "", "", "", "", "", "", "", "", "", "w ( 9 i ) ;", "", "", "" }, // write
	{ "", "l", "", "", "", "", "", "", "", "", "", "s ,", "", "", "", "" }, // str
	{ "", "i = 11 ;", "", "", "", "", "", "", "", "", "", "", "", "", "", "" }, // assign
	{ "", "13 12", "13 12", "", "", "", "", "", "13 12", "", "", "", "", "", "", "" }, // expr
	{ "", "", "", "", "+ 11", "- 11", "", "", "", "l", "", "", "", "l", "", "" }, // Z
	{ "", "15 14", "15 14", "", "", "", "", "", "15 14", "", "", "", "", "", "", "" }, // term
	{ "", "", "", "", "l", "l", "* 15 14", "/ 15 14", "", "l", "", "", "", "l", "", "" }, // term prime
	{ "", "i", "n", "", "", "", "", "", "( 11 )", "", "", "", "", "", "", "" } // factor
};

int get_col(char token)
{
	switch (token)
	{
	case 'p': return 0;
		break;
	case 'i': return 1;
		break;
	case 'n': return 2;
		break;
	case 't': return 3;
		break;
	case '+': return 4;
		break;
	case '-': return 5;
		break;
	case '*': return 6;
		break;
	case '/': return 7;
		break;
	case '(': return 8;
		break;
	case ')': return 9;
		break;
	case ':': return 10;
		break;
	case 's': return 11;
		break;
	case 'w': return 12;
		break;
	case ';': return 13;
		break;
	case 'e': return 14;
		break;
	case ',': return 15;
		break;
	default: return 16;
		break;
	}
}

void error(char expected)
{
	switch (expected)
	{
	case 'p': cout << "Error. Expected 'program'.\n";
		break;
	case 'i': cout << "Error. Expected identifier.\n";
		break;
	case 'n': cout << "Error. Expected number.\n";
		break;
	case 't': cout << "Error. Expected 'integer'.\n";
		break;
	case '+': cout << "Error. Expected '+'.\n";
		break;
	case '-': cout << "Error. Expected '-'.\n";
		break;
	case '*': cout << "Error. Expected '*'.\n";
		break;
	case '/': cout << "Error. Expected '/'.\n";
		break;
	case '(': cout << "Error. Expected '('.\n";
		break;
	case ')': cout << "Error. Expected ')'.\n";
		break;
	case ':': cout << "Error. Expected ':'.\n";
		break;
	case 's': cout << "Error. Expected string.\n";
		break;
	case 'w': cout << "Error. Expected 'write'.\n";
		break;
	case ';': cout << "Error. Expected ';'.\n";
		break;
	case 'e': cout << "Error. Expected 'end.'.\n";
		break;
	case ',': cout << "Error. Expected ','.\n";
		break;
	case 'v': cout << "Error. Expected 'var'.\n";
		break;
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

deque<char> get_tokens_lists(vector<string> tokens, deque<string> &id, deque<string> &num, vector<string> &reserved){

  string current;
  vector<string>::iterator it;
  deque<char> new_tokens;
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

void push_as_ints( deque <int>& stack, string input )
{
	for (int i = input.size() - 1; i >= 0; i--)
	{
		if (input[i] == ' ');
		else
		{
			if (input[i] >= '0' && input[i] <= '9')
			{
				if (i != 0 && input[i - 1] == '1')
				{
					stack.push_back(10 + input[i] - 48);
					i--;
				}
				else
				stack.push_back(input[i] - 48);
			}
			else
			{
				stack.push_back(input[i]);
			}
		}
	}
}

bool parse(vector<string> tokens){

  deque<string> id;
  deque<string> num;
  vector<string> reserved;
  deque<char> new_tokens;
  new_tokens = get_tokens_lists(tokens, id, num, reserved);
  /*vector<string>::iterator it;
  for ( it = id.begin(); it != id.end(); it++) cout<< *it <<" ";
  cout<<endl;
  for ( it = num.begin(); it != num.end(); it++) cout << *it <<" ";
  cout <<endl;
  for ( it = reserved.begin(); it != reserved.end(); it++) cout << *it <<" ";
  cout <<endl;*/
  /*
  vector<char>::iterator i;
  for ( i = new_tokens.begin(); i != new_tokens.end(); i++) {

    if ( *i == ';' ) cout << *i<<endl;
    else cout <<*i <<" ";
  }
  */
  deque<int> stack;
  stack.push_back(0);
  string rule;
  if (new_tokens.front() != 'p')
  {
	  cout << "Error. Expected 'program'.\n";
	  return true;
  }
  while (true)
  {
	  if (stack.back() >= 0 && stack.back() <= 15) // if top of stack is a rule 0 - 15
	  {
		  rule = table[stack.back()][get_col(new_tokens.front())];
		  if (rule == "") //return error
		  {
			  cout << "Error. Unacceptable grammar. " << stack.back() << ", " << int(new_tokens.front()) << endl;
			  break;
		  }
		  else
		  {
			  //cout << rule << " " << new_tokens.front() << endl;
			  stack.pop_back();
			  push_as_ints(stack, rule);
		  }
	  }
	  else //if top of stack is a nonterminal
	  {
		  if (stack.back() == 'l') //if it's lambda
		  {
			  stack.pop_back();
		  }
		  else if (stack.back() == new_tokens.front())//if it's other nonterminal and it matches
		  {
			  if (stack.back() == 'e')
			  {
				  cout << "Accepted.\n";
				  return true;
			  }
			  stack.pop_back();
			  new_tokens.pop_front();
		  }
		  else //return error due to mismatch
		  {
			  error(stack.back());
			  break;
		  }
	  }
  } //end of loop

  return true;

}

