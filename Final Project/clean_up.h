#ifndef CLEAN_UP_H
#define CLEAN_UP_H

#include "std_types.h"

// Function to clean up the file, this is called in main
vector<string> clean_up(string file_name);

// Function to remove comments from the code
void remove_comments(string w, vector<string> &tokens, stack<int> &comment);

// Function to add one token to a list of all tokens
void add_token_to_list( string &token, vector<string>& tokens);


#endif