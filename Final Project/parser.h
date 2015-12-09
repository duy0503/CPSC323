#ifndef PARSER_H
#define PARSER_H

#include "std_types.h"

using namespace std;

bool parse(vector<string> tokens);
deque<char> get_tokens_lists(vector<string> tokens, deque<string> &id, deque<string> &num, vector<string> &reserved);
char convert_reserved_word ( string reserved );
#endif