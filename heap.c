#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>


typedef struct heap{
   size_t capacity;
   size_t size;
   int* data;
} heap;


void swap(int* a, int* b){
   int tmp = *a;
   *a = *b;
   *b = tmp;
}


heap newHeap(size_t capacity){
   heap newHeap;
   newHeap.capacity = capacity;
   newHeap.size = 0;
   newHeap.data = (int*) malloc(sizeof(int) * capacity);
   return newHeap;
}


void printHeap(heap* h){
   printf("Heap elements:\n(");
   for(size_t i = 0 ; i < h->size ; i++){
      printf("%d, ", h->data[i]);
   }
   printf(")\n");
}


size_t parent(heap* h, size_t index){
   if(index > h->size){
      printf("Invalid access. Index should be within heap size range.");
      abort();
   } 
   return (index-1) / 2; 
}


size_t leftSon(heap* h, size_t index){
   size_t leftSonIndex = 2*index + 1;
   return (leftSonIndex < h->size ? leftSonIndex : 0);
}


size_t rightSon(heap* h, size_t index){
   size_t rightSonIndex = 2*index + 2;
   return (rightSonIndex < h->size ? rightSonIndex : 0);
}


void destroyHeap(heap* h){
   free(h->data);
}


void heapifyUp(heap* h, size_t index){
   if(index > h->size || index == 0){
      return;
   }
   size_t parentIndex = parent(h, index);
   if(h->data[parentIndex] > h->data[index]){


      swap(&h->data[parentIndex], &h->data[index]);
      heapifyUp(h, parentIndex);
   }
}


void heapifyDown(heap* h, size_t index){
   if(index > h->size){
      return;
   }
   size_t leftSonIndex = leftSon(h, index);
   if(leftSonIndex == 0) return;

   size_t rightSonIndex = rightSon(h, index);

   if(rightSonIndex == 0){
      if(h->data[leftSonIndex] < h->data[index]){
         swap(&h->data[leftSonIndex], &h->data[index]);
         heapifyDown(h, leftSonIndex);
      }
      return;
   }

   size_t swapIndex = h->data[leftSonIndex] < h->data[rightSonIndex] ? leftSonIndex : rightSonIndex;
   if(h->data[swapIndex] < h->data[index]){
      swap(&h->data[swapIndex], &h->data[index]);
      heapifyDown(h, swapIndex);
   }
}


bool insert(heap* h, int a){
   if(h->size == h->capacity) return false;


   if(h->size == 0 && h->capacity != 0){
      h->data[0] = a;
      h->size++;
      return true;
   }

   h->data[h->size] = a;
   heapifyUp(h, h->size);
   h->size++;
   return true;
}


int pop(heap* h){
   if(h->size == 0){
      printf("Can't call pop in an empty heap");
      abort();
   }
   int top = h->data[0];
   swap(&h->data[0], &h->data[h->size-1]);
   h->size--;
   heapifyDown(h, 0);
   return top;
}


heap buildMaxHeap(size_t capacity, int* originalArray){
   heap tmpHeap = newHeap(capacity);
   tmpHeap.size = capacity;
   for(int i = 0 ; i < capacity ; i ++){
      tmpHeap.data[i] = originalArray[i];
   }
   for(int i = capacity/2 ; i >= 0 ; i--){
      heapifyDown(&tmpHeap, i);
   }
   return tmpHeap;
}

void heapSort(size_t size, int* originalArray){

   heap tmpHeap = buildMaxHeap(size, originalArray);
   for(int i = 0 ; i < size ; i++){
      originalArray[i] = pop(&tmpHeap);
   }
   destroyHeap(&tmpHeap);
}

int main(){
   size_t capacity = 10;
   heap pq = newHeap(capacity);

   for(size_t i = 0 ; i < capacity ; i++){
      insert(&pq, capacity - i);
   }
   printHeap(&pq);
   printf("\n");

   for(size_t i = 0 ; i < capacity ; i++){
      pop(&pq);
      printHeap(&pq);
      printf("\n");
   }
   destroyHeap(&pq);

   int myVector[10];
   for(int i = 0 ; i < 10 ; i++) myVector[i] = 10 - i;

   heapSort(10, myVector);

   for(int i = 0 ; i < 10 ; i++) printf("%d, ", myVector[i]);
}







