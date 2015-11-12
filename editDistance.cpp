//editDistance.cpp
#include <algorithm>
#include <stdio.h>
#include <string>
#include <map>
#include <map>
#include <sstream>
#include <iostream>
#include <fstream>
#include <utility>
#include <string>
#include <vector>

#define READ(f) freopen(f,"r",stdin)
#define WRITE(f) freopen(f,"w",stdin)

using namespace std;

map <string,int> sentence;
vector<pair <int, string> > words;
typedef vector<pair <int, string> > VECTOR;


void entrySentence(string inp){
  transform(inp.begin(),inp.end(),inp.begin(), ::tolower);
  if (sentence[inp] ==NULL){
    sentence[inp] = 1;
  }
  else {
    sentence[inp]++;
  }
}

int main(){
  READ("hound.txt");
  //WRITE("outHound.txt");
  while(!cin.eof()){

		  string input;
		  string t;
		  getline(cin,t);
		  istringstream iss(t);
		  while(iss>>input){
		    //cout<<input<<" ";
		
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
		  }//end while loop
  }


  for (map<string,int>::iterator a=sentence.begin();a!=sentence.end();++a){ //test outuput map
    words.push_back(make_pair(a->second,a->first));
    cout<< a->first<<"  "<<a->second<<endl;
  }

  sort(words.begin(),words.end());
  /*
  for(const auto&p : words){
    cout<<p.first <<" "<<p.second<<endl;
  }*/

  for (VECTOR::const_iterator pos=words.begin();pos != words.end(); pos++){
    cout<< pos->first<<" "<<pos->second<<endl;
  }
}//end
