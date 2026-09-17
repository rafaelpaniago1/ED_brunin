#include <stdio.h>

void swap(int* a, int* b){
   int tmp = *a;
   *a = *b;
   *b = tmp; 
}

int partition(int* arr, int l, int r){

   int i = l;
   int j = l - 1;
   int pivot = arr[r];

   while(i != r){
      if(arr[i] < pivot){
         j++;
         swap(&arr[i], &arr[j]);
      }
      i++;
   }

   j++;
   swap(&arr[j], &arr[r]);
   return j;
}

void quickSortAux(int* arr, int l, int r){
   if(l < r){

      int p = partition(arr, l, r);

      quickSortAux(arr, l, p - 1);
      quickSortAux(arr, p + 1, r);
   }
}

void quickSort(int* arr, int n){
   quickSortAux(arr, 0, n-1);
}

int main(){

   int arr[] = {5,4,1,6};
   quickSort(arr, 4);
   for(int i = 0 ; i < 4 ; i++) printf("%d, ", arr[i]);
   printf("\n");

}
