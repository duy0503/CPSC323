#ifndef STD_TYPES_H
#define STD_TYPES_H

#include <iostream>
#include <string>
#include <ctype.h>
#include <vector>
#include <stdlib.h>
#include <cstring>
#include <fstream>
#include <stack>
using namespace std;
const int TOTAL_RESERVED_WORD = 6;
const int TOTAL_SPECIAL  = 9;
const string Reserved_Word[TOTAL_RESERVED_WORD] = {"program", "var", "begin", "end.", "integer", "write"};
const string Special[TOTAL_SPECIAL] = {"=", "_", ";", "(", ")", "<", ">", ",", ":"};

#endif