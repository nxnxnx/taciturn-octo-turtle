//editDistance-final.cpp

#include <string>
#include <map>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>


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

void swapFirst(int &a, int &b){
  int temp = a;
  a = b;
  b = temp;
}//end swap1st

void swapSecond(string &a, string &b){
  string temp = a;
  a = b;
  b = temp;
}//end swap2nd

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
	swapFirst( ((words.begin()+left)->first),((words.begin()+right)->first) );
	swapSecond((words.begin()+left)->second,(words.begin()+right)->second);

	left++;
	right--;
      }

      }//end while(left<=right)

    if (a < right)
            Qsort(a, right);
    if (left < b)
            Qsort(left, b);

  }//end if

}//end Qsort

void QsortString(int a, int b){
  string pivot;
  int left, right;

  if (b>a){
    int tengah = int((a+b)/2);
    pivot = (words.begin()+tengah)->second;
    left = a;
    right = b;

    while (left <= right){
      while((words.begin()+left)->second.compare(pivot) < 0) left++;
      while((words.begin()+right)->second.compare(pivot) > 0) right--;

      if (left <= right){
	swapFirst( ((words.begin()+left)->first),((words.begin()+right)->first) );
	swapSecond((words.begin()+left)->second,(words.begin()+right)->second);
	left++;
	right--;
      }

    }

    if (a < right)
            QsortString(a, right);
    if (left < b)
            QsortString(left, b);

  }
}//end qsortstring


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
}//end edit_distance

int main(){

  fstream data;
  data.open("hound.txt");
    if(!data.is_open())
    {
        cout << "No \"hound.txt\" found" << endl;
        string dummykian;
        cout << "\nTekan enter untuk keluar" << endl;
        getline(cin,dummykian);

        return 0;
    }

  while(!data.eof()){

        string input;
        while(getline(data,input)){
		    string toSentence="";

		    for (int a=0;input.length()>a;++a){

                if (( int(input[a])>=48 && input[a]<=57 ) || ( int(input[a])>=65 && input[a]<=90 ) || ( int(input[a])>=97 && input[a]<=122 ) || int(input[a]==39))

                    toSentence += input[a];

                else {
                    if (toSentence == "");
                        else entrySentence(toSentence);

                    toSentence = "";
                }
		    }
		    //entrySentence(input);
		  }//end while loop
  }

    data.close();

    int maxDistance;
    string stringToTest;

    cout << endl << "Masukkan String untuk di test" << endl;
    getline(cin,stringToTest,'\n');
    cout << endl;

    cout << endl << "Masukkan Distance Maksimal (Tidak boleh negatif dan harus berupa Angka)" << endl;
    while(true){
        cin >> maxDistance;
        if(cin.fail() || maxDistance < 0){
            cin.clear();
            cin.ignore();
            cin.sync();
            cout << endl;
            cout << "Salah, Ulangi" << endl;
        } else {
            cout << endl;
            break;
        }
    }

    //transform(stringToTest.begin(),stringToTest.end(),stringToTest.begin(), ::tolower);

    bool ketemu = false;

   for (map<string,int>::iterator a=sentence.begin();a!=sentence.end();++a){ // Hitung Distance
    int distance = edit_distance(stringToTest,a->first);
    distanceValue[a->first] = distance;

    if(distance <= maxDistance){ //Masukkan ke Map
      words.push_back(make_pair(distance,a->first));
        ketemu = true;
    }
  }

   if (ketemu){

    //initial sort
     Qsort(0,words.size()-1);

     //Sort per-part
     int indexPartisi1;
     int indexPartisi2;
     int nilaiIndexPartisi;
     for(indexPartisi1 = 0, indexPartisi2 = 0, nilaiIndexPartisi=(words.begin()+indexPartisi1)->first ;indexPartisi2<words.size();indexPartisi2++){
        if((words.begin()+indexPartisi2)->first != nilaiIndexPartisi){
            QsortString(indexPartisi1,indexPartisi2-1);
            indexPartisi1 = indexPartisi2;
            nilaiIndexPartisi = (words.begin()+indexPartisi1)->first;
        }
     }
     QsortString(indexPartisi1,indexPartisi2-1);

    }


    //For Output Manipulation Purposes
    int longestWordEver = 0;
    for (VECTOR::const_iterator pos = words.begin(); pos!=words.end();++pos){
        if(pos->second.length() > longestWordEver){
            longestWordEver = pos->second.length();
        }
     }
    int numberLength = 0;
    for(int x = maxDistance; x!=0 ; x /= 10, numberLength++);


   for (VECTOR::const_iterator pos = words.begin(); pos!=words.end();++pos){
     cout.width(longestWordEver);
     cout << pos->second << " |";
     cout.width(numberLength + 1);
     cout << pos->first<<" | " <<sentence[pos->second]<< endl;
   }

    if(!ketemu){
      string Kappa = "No Match Found \n";
      cout << Kappa << endl;
    }

    cin.ignore();
    string dummy;
    cout << "\nTekan enter untuk keluar" << endl;
    getline(cin,dummy);

    return 0;
}//end
