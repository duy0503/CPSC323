#include <iostream>
#include <string>
#include <ctype.h>

using namespace std;

const string Reserved_Word[4] = {"cout<<", "for", "int", "while"};
const string Special[8] = {"=", "+", "-", "*", ";", "(", ")", "<="};

int main() {

  string var = "";
  int i, j;
  bool not_id = false;
  bool reserved = false;
  string w = "for(int tom_jones=22;tom_jones<=100;tom_jones=tom+1)cout<<2tom;";

  for ( i = 0; i < w.length(); i++ ) {

    // w[i] is a number
    if ( isdigit(w[i]) ) {
      while ( isalpha(w[i]) || isdigit(w[i]) || w[i] == '_' ) {

	var = var + w[i];
	i++;
      }

      for ( j = 0; j < var.length(); j++ ) {
	if ( !isdigit(var[j])) {
	  not_id = true;
	  break;
	}
      }

      if ( not_id ) {
	cout << var <<"\t\tnot identifier"<<endl;
	not_id = false;
      }
      else cout << var <<"\t\tnumber"<<endl;
      var = "";
    }

    //w[i] is a letter or '_'
    if ( isalpha(w[i]) || w[i] == '_' ) {
      while ( isalpha(w[i]) || isdigit(w[i]) || w[i] == '_' ) {
	var = var + w[i];
	i++;
      }

      //Check if var is "cout"
      if ( var == "cout" ) {
	//check the next two character to see if they are "<<"
	if ( w[i] == '<' && w[i+1] == '<' ) {
	  var = var + "<<";
	  cout << var <<"\t\treserved word"<<endl;
	  i++;
	  var = "";
	  continue;
	}
      }
      // Check if var is a reserved word
      for ( j = 0; j < 4; j++ ) {
	if ( var == Reserved_Word[j] ) {
	  reserved = true;
	  break;
	}
      }

      if ( reserved ) cout << var <<"\t\treserved word"<<endl;
      else cout << var <<"\t\tidentifier"<<endl;

      reserved = false;
      var = "";
    }

    // Check the special symbol
    if ( w[i] == '<' ) {
      var = var + w[i];
      i++;
      if ( w[i] == '=' ) {
	var = var + w[i];
	cout << var <<"\t\tspecial symbol"<<endl;
      }
      else cout << var <<"\t\tnot special symbol"<<endl;

      var = "";
    }
    
    else {
      for ( j = 0; j < 7; j++ ) {
	if ( w[i] == Special[j][0] ) {
	  cout << w[i] <<"\t\tspecial symbol"<<endl;
	  break;
	}
      }
    }
      
  }

  return 0;
}
