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

map <string,int> sentence;
vector< pair <int, string> >words;
map <string,int> distanceValue;

typedef vector<pair <int, string> > VECTOR;

void entrySentence(string inp){
  transform(inp.begin(), inp.end(), inp.begin(), ::tolower);
  if (sentence[inp] ==NULL) sentence[inp] = 1;
  else sentence[inp]++;

}//end entrySentence

void swap(int &a, int &b){
  int temp = a;
  a = b;
  b = temp;
}

void Qsort(int a, int b){
  int pivot, left, right;

  if (b>a){
    int tengah = int((a+b)/2);
    pivot = (words.begin()+tengah)->first;
    left = a;
    right = b;

    while (left <= right){
      while((words.begin()+left)->first < pivot ) left++;
      while((words.begin()+right)->first > pivot ) right--;

      if (left <= right){
	swap( ((words.begin()+left)->first),((words.begin()+right)->first) );
	left++;
	right++;
      }

    }//end while(left<=right)
  }//end if

}//end Qsort


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
    //cout<< a->first<<" "<<a->second<<endl;
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

   for (map<string,int>::iterator a=sentence.begin();a!=sentence.end();++a){ //test outuput map
    int distance = edit_distance(stringToTest,a->first);
    distanceValue[a->first] = distance;

    //untuk print string yang distancenya kurang dari max distance
    if(distance <= maxDistance){
      words.push_back(make_pair(distance,a->first));
      //cout<< a->first <<" "<< distance <<endl;
        ketemu = true;
    }
  }

   sort(words.begin(),words.end()); //butuh function sort sendiri

   /*if (ketemu){
     Qsort(0, words.size());
     //Qsort2(0, words.size());]
     }*/


   for (VECTOR::const_iterator pos = words.begin(); pos!=words.end();++pos){
     cout<< pos->second <<"\t"<<pos->first<<"\t"<<sentence[pos->second]<< endl;
   }

    if(!ketemu){
      string Kappa = "( ͡° ͜ʖ ͡°)";
      cout << Kappa << endl;
    }

}//end

