#include <iostream>
#include <string>
#include <ctype.h>
#include <vector>
#include <stdlib.h>
#include <cstring>
#include <fstream>
#include <stack>
#include "generator.h"

void translate(vector<string> tokens) {

  vector<string> variables;
  vector<string>::iterator it;

  // Write to new file
  ofstream outFile("final.cpp");
  if ( !outFile.is_open() ) {
    cout << "Couldn't open new file to write data" <<endl;
    exit(2);
  }

  outFile<<"#include <iostream>"<<endl;
  outFile<<"using namespace std;"<<endl;
  outFile<<"int main()"<<endl;
  outFile<<"{"<<endl;
  
  for ( it = tokens.begin(); it != tokens.end(); it++ ) {
    if ( *it == "var") {
      it++;
      while(*it != ":") {
	variables.push_back(*it);
	it++;
      }

      //write all of the variables
      outFile<<"\tint ";
      for (vector<string>::iterator i = variables.begin(); i!= variables.end(); i++){
	outFile<<*i<<" ";
      }
      outFile<<";"<<endl;
    }
    if ( *it == "begin" ) {
      it++;
      outFile <<"\t";
      while ( *it != "end." ) {
	if ( *it == ";" ) {
	  outFile <<" "<<*it <<endl;
	  outFile <<"\t";
	}
	else if ( *it == "write" ) {
	  outFile << "cout";
	  it++;
	  while (*it != ")") {
	    if ( *it == "(" ) outFile <<"<<";
	    else if ( *it == "," ) outFile <<"<<";
	    else outFile<<*it;
	    it++;
	  }
	  outFile<<"<<endl";
	}
	else outFile<<*it;
	it++;
      }    
    }
    if ( *it == "end.") {
      outFile<<"return 0;"<<endl;
      outFile<<"}"<<endl;
    }
      
  }

  outFile.close();
}
