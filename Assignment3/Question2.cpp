#include <iostream>
#include <string>
using namespace std;

int fatable[4][3] =
{
	0, 1, 2,
	2, 1, 3,
	0, 3, 3,
	1, 3, 2
};

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
	case 0: return false;
		break;
	case 1: return true;
		break;
	case 2: return true;
		break;
	case 3: return false;
		break;
	default: return false; 
		break;
	}
}

void process(string w)
{
	if (fa(w))
	{
		cout << "String " << w << " is accepted by grammar.\n";
	}
	else cout << "String " << w << "is not accepted by grammar.\n";
}

int main()
{
	string w1 = "abbbcaaa", w2 = "ccccbbb", w3 = "aabbcbbb"; //all of these should not be accepted.
	process(w1);
	process(w2);
	process(w3);
	cin.get();
}