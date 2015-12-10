#ifndef PARSER_H
#define PARSER_H

#include "std_types.h"

using namespace std;

// Function to parse the tokens after converting into a simple list
bool check(vector<char> tokens);

// Function to parse the tokens, this is called by main
bool parse(vector<string> tokens);

// Function to categorize the list of all tokens into different list of tokens
vector<char> get_tokens_lists(vector<string> tokens, vector<string> &id, vector<string> &num, vector<string> &reserved, vector<string>&str);

// Function to print out the type of error detected
void get_error(char non_term, char term);

#endif