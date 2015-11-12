#include <iostream>
#include <string>
#include <deque>
#include <queue>
using namespace std;

enum columns {i = 0, pl, mi, ti, di , lpar, rpar, $, E, T, F};
/*
Rules of grammar:
r1: E -> E + T
r2: E -> E -T
r3: E -> T
r4: T -> T * F
r5: T -> T / F
r6: T -> F
r7: F -> (E)
r8: F -> i
*/

string lrtable[16][11] =
{ //  0i   1+   2-   3*   4/   5(   6)   7$   8E   9T   10F
	{ "s5", "", "", "", "", "s4", "", "", "s1", "s2", "s3" }, //0
	{ "", "s6", "s7", "", "", "", "", "acc", "", "", "" }, //1
	{ "", "r3", "r3", "s8", "s9", "", "r3", "r3", "", "", "" }, //2
	{ "", "r6", "r6", "r6", "r6", "", "r6", "r6", "", "", "" }, //3
	{ "s5", "", "", "", "", "s4", "", "", "s10", "s2", "s3" }, //4
	{ "", "r8", "r8", "r8", "r8", "", "r8", "r8", "", "", "" }, //5
	{ "s5", "", "", "", "", "s4", "", "", "", "s11", "s3" }, //6
	{ "s5", "", "", "", "", "s4", "", "", "", "s12", "s3" }, //7
	{ "s5", "", "", "", "", "s4", "", "", "", "", "s13" }, //8
	{ "s5", "", "", "", "", "s4", "", "", "", "", "s14" }, //9
	{ "", "s6", "s7", "", "", "", "s15", "", "", "", "" }, //10
	{ "", "r1", "r1", "s8", "s9", "", "r1", "r1", "", "", "" }, //11
	{ "", "r2", "r2", "s8", "s9", "", "r2", "r2", "", "", "" }, //12
	{ "", "r4", "r4", "r4", "r4", "", "r4", "r4", "", "", "" }, //13
	{ "", "r5", "r5", "r5", "r5", "", "r5", "r5", "", "", "" }, //14
	{ "", "r7", "r7", "r7", "r7", "", "r7", "r7", "", "", "" }  //15
};

const string rules[8] = { "E -> E+T", "E -> E-T", "E -> T", "T -> T*F",
"T -> T/F", "T -> F", "F -> (E)", "F -> i" };

int getcol(char input)
{
	switch (input)
	{
	case 'i': return i;
		break;
	case '+': return pl;
		break;
	case '-': return mi;
		break;
	case '*': return ti;
		break;
	case '/': return di;
		break;
	case '(': return lpar;
		break;
	case ')': return rpar;
		break;
	case '$': return $;
		break;
	case 'E': return E;
		break;
	case 'T': return T;
		break;
	case 'F': return F;
		break;
	default: return -1;
		break;
	}
}

string table(int row, int col)
{
	return lrtable[row][col];
}

void output(deque<int> mydeque, queue<char> input, string entry) 
{
	queue <int> tempqueue;
	queue <char> inputqueue = input;
	cout << "Stack: ";
	for (int i = 0; i < mydeque.size(); i++)
	{
		if (mydeque[i] > 15)
		{
			cout << char(mydeque[i]);
		}
		else cout << mydeque[i];
	}
	cout << " Input: ";
	for (int i = 0; i < input.size(); i++)
	{
		cout << inputqueue.front();
		inputqueue.pop();
	}
	cout << " Entry: " << entry;
}


int main()
{
	deque <int> mydeque; //this deque will store the state OR the ascii value of a character
	mydeque.push_back(0); //initialize deque
	queue <char> input;
	string problem1 = "(i+i)*i$";
	string problem2 = "(i*)$";
	string entry;
	int state = 0, temp;
	char nt;
	for (int i = 0; i < problem1.size(); i++) //initialize queue. To change between strings, switch the number
	{
		input.push(problem1[i]);
	}
	
	while (state != -1)
	{
		state = mydeque.back();
		entry = table(state, getcol(input.front()));
		output(mydeque, input, entry);

		if (entry == "") //if table value is empty, return error
		{
			cout << "Error, empty table value\n";
			break;
		}

		if (entry == "acc")
		{
			cout << "\nAccepted.\n";
			break;
		}

		if (entry.size() == 3) //if table value has a two digit number
		{
			temp = 10 * (entry[1] - '0') + (entry[2] - '0');
		}
		else if (entry.size() == 2) //if table value has single digit
		{
			temp = entry[1] - '0';
		}
		cout << " Action/Production: ";

		if (entry[0] == 's') //go to state
		{
			cout << "Shift, enter State " << temp << endl;
			mydeque.push_back(input.front());
			input.pop();
			mydeque.push_back(temp);
		}
		else if (entry[0] == 'r') //go to rule
		{
			cout << rules[temp - 1] << endl;
			if (temp > 6) nt = 'F';
			else if (temp > 3) nt = 'T';
			else nt = 'E';
			if (temp == 3 || temp == 6 || temp == 8) //pop two for each element in rule.
			{
				mydeque.pop_back(); 
				mydeque.pop_back();
			}
			else
			{
				mydeque.pop_back();
				mydeque.pop_back();
				mydeque.pop_back();
				mydeque.pop_back();
				mydeque.pop_back();
				mydeque.pop_back();
			}
			state = mydeque.back();
			entry = table(state, getcol(nt));
			//output(mydeque, input, entry);
			if (entry.size() == 3) //if table value has a two digit number
			{
				temp = 10 * (entry[1] - '0') + (entry[2] - '0');
			}
			else if (entry.size() == 2) //if table value has single digit
			{
				temp = entry[1] - '0';
			}
			mydeque.push_back(nt);
			mydeque.push_back(temp);
		}
	}

}