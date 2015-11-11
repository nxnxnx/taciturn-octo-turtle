//editDistance.cpp

#include <stdio.h>
#include <string>
#include <map>
#include <map>
#include <sstream>
#include <iostream>
#include <fstream>

#define READ(f) freopen(f,"r",stdin)
#define WRITE(f) freopen(f,"w",stdin)

using namespace std;

map <string,int> sentence;


void entrySentence(string inp){
  if (sentence[inp] ==NULL) sentence[inp] = 1;
  else sentence[inp]++;

}

int main(){

  string input;
  string t;
  getline(cin,t);
  istringstream iss(t);
  while(iss>>input){
    string toSentence="";
    
    for (int a=0;input.length()>a;++a){
      if (( int(input[a])>=48 && input[a]<=57 ) || ( int(input[a])>=65 && input[a]<=90 ) || ( int(input[a])>=97 && input[a]<=122 ) || int(input[a]==39)) toSentence += input[a];
    
      else {
	if (toSentence == "");
	else entrySentence(toSentence);

	toSentence = "";
      }
    }
    //entrySentence(input);
  }
  
  for (map<string,int>::iterator a=sentence.begin();a!=sentence.end();++a){ //test outuput map
    cout<< a->first<<" "<<a->second<<endl;
  }


}//end
