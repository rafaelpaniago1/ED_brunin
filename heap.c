#include <stdbool.h>
#include <limits.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct node{
   int vertex;
   double distance;
} node;


typedef struct heap{
   size_t capacity;
   size_t size;
   node* data;
} heap;


bool isLess(node a, node b){
   return a.distance < b.distance;
}


void swap(node* a, node* b){
   node tmp = *a;
   *a = *b;
   *b = tmp;
}


heap* newHeap(size_t capacity){
   heap* newHeap = (heap*) malloc(sizeof(heap));
   newHeap->capacity = capacity;
   newHeap->size = 0;
   newHeap->data = (node*) malloc(sizeof(node) * capacity);
   if(newHeap->data == NULL){
      printf("Could no allocate data, heap is full");
      abort();
   }
   return newHeap;
}


void printHeap(heap* h){
   printf("Heap elements:\n");
   for(size_t i = 0 ; i < h->size ; i++){
      printf("(%d, %lf), ", h->data[i].vertex, h->data[i].distance);
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
   return (leftSonIndex < h->size ? leftSonIndex : SIZE_MAX);
}


size_t rightSon(heap* h, size_t index){
   size_t rightSonIndex = 2*index + 2;
   return (rightSonIndex < h->size ? rightSonIndex : SIZE_MAX);
}


void destroyData(heap* h){
   free(h->data);
}


void heapifyUp(heap* h, size_t index){
   if(index > h->size || index == 0){
      return;
   }
   size_t parentIndex = parent(h, index);
   if(isLess(h->data[index], h->data[parentIndex])){


      swap(&h->data[parentIndex], &h->data[index]);
      heapifyUp(h, parentIndex);
   }
}


void heapifyDown(heap* h, size_t index){
   if(index > h->size){
      return;
   }
   size_t leftSonIndex = leftSon(h, index);
   if(leftSonIndex == SIZE_MAX) return;

   size_t rightSonIndex = rightSon(h, index);

   if(rightSonIndex == SIZE_MAX){
      if(isLess(h->data[leftSonIndex], h->data[index])){
         swap(&h->data[leftSonIndex], &h->data[index]);
         heapifyDown(h, leftSonIndex);
      }
      return;
   }

   size_t swapIndex = isLess(h->data[leftSonIndex], h->data[rightSonIndex]) ? leftSonIndex : rightSonIndex;
   if(isLess(h->data[swapIndex], h->data[index])){
      swap(&h->data[swapIndex], &h->data[index]);
      heapifyDown(h, swapIndex);
   }
}


bool insert(heap* h, node a){
   if(h->size == h->capacity){
      node* ptr = realloc(h->data, 2 * h->capacity * sizeof(node));
      if(!ptr) return false;
      h->data = ptr;         
      h->capacity = 2*h->capacity;
   } 


   if(h->size == 0 && h->capacity != 0){
      h->data[0] = a;
      h->size++;
      return true;
   }

   h->data[h->size] = a;
   int tmpSize = h->size;
   h->size++;
   heapifyUp(h, tmpSize);
   return true;
}


node pop(heap* h){
   if(h->size == 0){
      printf("Can't call pop in an empty heap");
      abort();
   }
   node top = h->data[0];
   swap(&h->data[0], &h->data[h->size-1]);
   h->size--;
   heapifyDown(h, 0);
   return top;
}



int main(){
   size_t capacity = 10;
   heap* pq = newHeap(capacity);

   for(size_t i = 0 ; i < capacity + 1 ; i++){
      node n; n.distance = capacity - i; n.vertex = 0;
      insert(pq, n);
   }
   printHeap(pq);
   printf("\n");

   for(size_t i = 0 ; i < capacity ; i++){
      pop(pq);
      printHeap(pq);
      printf("\n");
   }
   destroyData(pq);
}







