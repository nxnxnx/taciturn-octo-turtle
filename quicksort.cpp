#include <iostream>
#include <stdio.h>

int arr[101]{0};

using namespace std;

void swap(int &a, int &b){
  int temp = a;
  a = b;
  b = temp;
}



void QuickSort(int a, int b){ //int a = index array pertama, int b = index array terakhir
  int pivot, left,right;

  if (b>a){
    pivot = arr[int((a+b) / 2)];
    left = a;
    right = b;

    while (left <= right){
      while (arr[left] < pivot) left ++;
      while (arr[right] > pivot) right--;

      if (left <= right){
	swap(arr[left],arr[right]);
	left++;
	right++;
      }

    }

    QuickSort(a, right);
    QuickSort(left, b);
  }

}//end Qs




int main(){
  arr[0] = 3;
  arr[1] = 10;
  arr[2] = 20;
  arr[3] = 7;
  arr[4] = 14;
  arr[5] = 159;
  arr[6] = 26;
  arr[7] = 5;
  arr[8] = 358;


  QuickSort(0,8);

  for (int a=0;9>a;++a){
  printf("%d ", arr[a]);
  }

}//end
