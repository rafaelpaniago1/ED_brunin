#include <limits.h>
#include <stdio.h>

void merge(int* arr, size_t l, size_t m, size_t r){

   size_t leftSize = m - l + 1;
   size_t rightSize = r - m;

   int leftArr[leftSize + 1];
   int rightArr[rightSize + 1];

   for(int i = l ; i < l + leftSize ; i++) leftArr[i - l] = arr[i];
   for(int i = m + 1 ; i < m + 1 + rightSize ; i++) rightArr[i - m - 1] = arr[i];

   leftArr[leftSize] = INT_MAX;
   rightArr[rightSize] = INT_MAX;
   
   int lP = 0;
   int rP = 0;

   for(int i = l ; i <= r ; i++){
      if(leftArr[lP] < rightArr[rP]) {
         arr[i] = leftArr[lP];
         lP++;
      } 
      else{
         arr[i] = rightArr[rP];
         rP++;
      }
   }
}

void mergeSortAux(int* arr, size_t l, size_t r){
   if(l < r){
      int m = l + (r - l)/2;
      mergeSortAux(arr, l, m);
      mergeSortAux(arr, m+1, r);
      merge(arr, l, m, r);
   }
}

void mergeSort(int* arr, size_t arrSize){
   mergeSortAux(arr, 0, arrSize - 1);
}

int main(){

   int arr[] = {5, 4, 3, 2, 1, 7, 8 ,12, 3, 5, 5, 10};
   mergeSort(arr, 12);
   for(size_t i = 0 ; i < 12 ; i++) printf("%d, ",arr[i]);

}




