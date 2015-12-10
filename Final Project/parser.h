#ifndef PARSER_H
#define PARSER_H

#include "std_types.h"

using namespace std;
bool check(vector<char> tokens);
bool parse(vector<string> tokens);
vector<char> get_tokens_lists(vector<string> tokens, vector<string> &id, vector<string> &num, vector<string> &reserved);
void get_error(char non_term, char term);
#endif