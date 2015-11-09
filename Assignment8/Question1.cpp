#include <iostream>
#include <string>
#include <stack>
#include <vector>

using namespace std;

const string table[16][11] = {"s5",""  ,""  ,""  ,""  ,"s4",""  ,""  ,"1" ,"2" ,"3" ,
			      ""  ,"s6","s7",""  ,""  ,""  ,""  ,"ac", "" ,""  ,""  ,
			      ""  ,"r3","r3","s8","s9",""  ,"r3","r3",""  ,""  ,""  ,
			      ""  ,"r6","r6","r6","r6",""  ,"r6","r6",""  ,""  ,""  ,
			      "s5",""  ,""  ,""  ,""  ,"s4",""  ,""  ,"10","2" ,"3" ,
			      ""  ,"r8","r8","r8","r8",""  ,"r8","r8",""  ,""  ,""  ,
			      "s5",""  ,""  ,""  ,""  ,"s4",""  ,""  ,""  ,"11","3" ,
			      "s5",""  ,""  ,""  ,""  ,"s4",""  ,""  ,""  ,"12","3" ,
			      "s5",""  ,""  ,""  ,""  ,"s4",""  ,""  ,""  ,""  ,"13",
			      "s5",""  ,""  ,""  ,""  ,"s4",""  ,""  ,""  ,""  ,"14",
			      ""  ,"s5","s7",""  ,""  ,""  ,"s15",""  ,""  ,""  ,""  ,
			      ""  ,"r1","r1","s8","s9",""  ,"r1","r1",""  ,""  ,""  ,
			      ""  ,"r2","r2","s8","s9",""  ,"r2","r2",""  ,""  ,""  ,
			      ""  ,"r4","r4","r4","r4",""  ,"r4","r4",""  ,""  ,""  ,
			      ""  ,"r5","r5","s5","s5",""  ,"r5","r5",""  ,""  ,""  ,
			      ""  ,"r7","r7","r7","r7",""  ,"r7","r7",""  ,""  ,""  };

const string rules[8] = {"E->E+T" , "E->E-T", "E->T" , "T->T*F",
			 "T->T/F" , "T->F"  ,"F->(E)", "F->i"  };

int get_col(char token){

  switch(token){
    
  case 'i': return 0;
  case '+': return 1;
  case '-': return 2;
  case '*': return 3;
  case '/': return 4;
  case '(': return 5;
  case ')': return 6;
  case '$': return 7;
  case 'E': return 8;
  case 'T': return 9;
  case 'F': return 10;
  default: return -1;
    
  }

}

int get_row(char state) {
  return (state - '0');
}

int main(){

  string input;
  int counter = 0;
  char token;
  stack<char> mystack;
  cout << "Enter the string: ";
  getline(cin, input);
  cout <<input<<endl;

  char state = '0';
  int row;
  row = get_row(state);
  cout <<row<<endl;

  return 0;
}

			      
