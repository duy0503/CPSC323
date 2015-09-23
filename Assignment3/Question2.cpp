/*
Author Name: Duy Do, Tetsuya Tanaka
Course: CPSC 323
Assignment 3
Question 2
Due Date: 09/24/2015
Project Information: Determine if 3 specified words are part of a grammar

*/

#include <iostream>
#include <string>
using namespace std;

/*FA table given by grammar:
S -> aS | bB | cC
B -> bB | aC | cD | lambda
C -> aS | (b + c)D | lambda
D -> bD | aB | cC

Has 4 states and 3 inputs: a, b, c
*/
int fatable[4][3] =
{
	0, 1, 2,
	2, 1, 3,
	0, 3, 3,
	1, 3, 2
};

/*
Function: fa
Input: string w
Output: bool
Description: Processes w through an FA loop, then returns true if w is in an accepting state and false if otherwise.
*/
bool fa(string w)
{
	int state = 0;
	char iltr;
	for (int i = 0; i < w.size(); i++)
	{
		iltr = w[i];
		switch (iltr)
		{
		case 'a': state = fatable[state][0];
			break;
		case 'b': state = fatable[state][1];
			break;
		case 'c': state = fatable[state][2];
			break;
		default: return false;
			break;
		}
	}
	switch (state)
	{
	case 1: return true;
		break;
	case 2: return true;
		break;
	default: return false; 
		break;
	}
}

/*
Function: process
Input: string w
Output: None
Description: takes w and passes it to the fa function, and outputs a message depending on the outcome.
*/
void process(string w)
{
	if (fa(w))
	{
		cout << "String " << w << " is accepted by grammar.\n";
	}
	else cout << "String " << w << " is not accepted by grammar.\n";
}

/*
Function: main
Description: Declares 3 strings and passes them to the function process.
*/

int main()
{
	string w1 = "abbbcaaa", w2 = "ccccbbb", w3 = "aabbcbbb"; //all of these should not be accepted.
	process(w1);
	process(w2);
	process(w3);
	cin.get();
}