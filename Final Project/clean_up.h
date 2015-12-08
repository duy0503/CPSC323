#ifndef CLEAN_UP_H
#define CLEAN_UP_H

#include "std_types.h"

void remove_comments(string w, vector<string> &tokens, stack<int> &comment);

void add_token_to_list( string &token, vector<string>& tokens);

vector<string> clean_up(string file_name);

#endif