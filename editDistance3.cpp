//editDistance.cpp

#include <stdio.h>
#include <string>
#include <map>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>


using namespace std;

class TextsAttr{
public :
    TextsAttr();
    TextsAttr(int counts, int editDist);
    int textCount;
    int textEditDistance;
    ~TextsAttr();
};

TextsAttr::TextsAttr(int counts, int editDist){
        textCount = counts;
        textEditDistance = editDist;
}

map<string,TextsAttr*> ClassMap;
vector<string> VectorKey;

void entrySentence(string inp){
  transform(inp.begin(), inp.end(), inp.begin(), ::tolower);
        if (ClassMap.count(inp) == 0) { //Kalau ga ada key inp di map
            ClassMap.insert(make_pair(inp,new TextsAttr(1,0)));
        }
        else {
            ClassMap[inp]->textCount++;
        }
}//end entrySentence

void swap(string &a, string &b){
  string temp = a;
  a = b;
  b = temp;
}

bool objSwap(string a, string b){
    return ClassMap[a]->textCount < ClassMap[b]->textCount;
}

size_t edit_distance(const std::string &s1, const std::string &s2) // http://rosettacode.org/wiki/Levenshtein_distance#C.2B.2B
{
  const size_t m(s1.size());
  const size_t n(s2.size());

  if( m==0 ) return n;
  if( n==0 ) return m;

  size_t *costs = new size_t[n + 1];

  for( size_t k=0; k<=n; k++ ) costs[k] = k;

  size_t i = 0;
  for ( std::string::const_iterator it1 = s1.begin(); it1 != s1.end(); ++it1, ++i )
  {
    costs[0] = i+1;
    size_t corner = i;

    size_t j = 0;
    for ( std::string::const_iterator it2 = s2.begin(); it2 != s2.end(); ++it2, ++j )
    {
      size_t upper = costs[j+1];
      if( *it1 == *it2 )
      {
		  costs[j+1] = corner;
	  }
      else
	  {
		size_t t(upper<corner?upper:corner);
        costs[j+1] = (costs[j]<t?costs[j]:t)+1;
	  }

      corner = upper;
    }
  }

  size_t result = costs[n];
  delete [] costs;

  return result;
}

int main(){

  fstream data;
  data.open("hound.txt");

  while(!data.eof()){

		  string input;
		  string t;
		  getline(data,t);
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
        }//end while loop
  }

  data.close();

  for (map<string,TextsAttr*>::const_iterator a=ClassMap.begin();a!=ClassMap.end(); ++a){ //test outuput map
    cout<< a->first <<" "<< a->second->textCount <<endl;
  }

    int maxDistance;
    string stringToTest;


    cout << endl << "Masukkan String untuk di test" << endl;
    cin >> stringToTest;

    cout << endl << "Masukkan Distance Maksimal" << endl;
    while(true){
        cin >> maxDistance;
        if(cin.fail() || maxDistance <= 0){
            cout << "Salah, Ulangi" << endl;
            cin.ignore();
            cin.sync();
        } else {
            break;
        }
    }

    transform(stringToTest.begin(),stringToTest.end(),stringToTest.begin(), ::tolower);

    bool ketemu = false;

    for (map<string,TextsAttr*>::iterator a=ClassMap.begin();a!=ClassMap.end();++a){
    int distance = edit_distance(stringToTest,a->first);
        a->second->textEditDistance = distance;

    //untuk print string yang distancenya kurang dari max distance
    if(distance <= maxDistance){

      VectorKey.push_back(a->first); //pake ini buat sorting berdasarkan keynya... jadi nanti urutan key di vector itu yang edit distancenya mulai dari terkecil hingga terbesar

        ketemu = true;
    }
  }

    sort(VectorKey.begin(),VectorKey.end(),objSwap); //Need another sort function... :<

    for(vector<string>::iterator a=VectorKey.begin(); a!=VectorKey.end(); ++a){
        cout << *a << "\t" << ClassMap[*a]->textEditDistance << "\t" << ClassMap[*a]->textCount << endl;
    }

    if(!ketemu){
      string Kappa = "( ͡° ͜ʖ ͡°)";
      cout << Kappa << endl;
    }
}//end
