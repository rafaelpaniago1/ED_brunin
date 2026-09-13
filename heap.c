#include <stdbool.h>
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


typedef struct vertexNode{
   struct vertexNode* next;
   node node;
} vertexNode;


void printList(vertexNode* head){
   vertexNode* curr = head;
   while(curr){
      printf("%d, ", curr->node.vertex);
      printf("\n");
      curr = curr->next;
   }
}


void listPush(vertexNode** head, int vertex, double distance){
   vertexNode* vNode = (vertexNode*) malloc(sizeof(vertexNode));
   vNode->next = *head;
   node data = {vertex, distance};
   vNode->node = data;
   *head = vNode;
}


void freeList(vertexNode* head){
   vertexNode* curr = head;
   while(curr != NULL){
      vertexNode* tmp = curr;
      curr = curr->next;
      free(tmp);
   }
}


typedef struct graph{
   vertexNode** adjList;
   size_t n;
} graph;


graph* newGraph(size_t n){
   vertexNode** adjList = (vertexNode**) malloc(sizeof(vertexNode*) * n); 
   if(!adjList){
      printf("couldnt allocate adjList for graph of this size");
      abort();
   }
   for(size_t i = 0 ; i < n ; i++){
      adjList[i] = NULL;
   }
   graph* newGraph = (graph*) malloc(sizeof(graph));
   newGraph->adjList = adjList;
   newGraph->n = n;
   return newGraph;
}


void freeGraph(graph* g){
   for(size_t i = 0 ; i < g->n ;i++){
      freeList(g->adjList[i]);
   }
   free(g->adjList);
   free(g);
}


void addEdge(graph* g, int src, int dst, double weight){
   //printf("Adding edge from node: %d, with weight: %f\n", src, weight);
   listPush(&g->adjList[src], dst, weight);
}


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


void freeHeap(heap* h){
   free(h->data);
   free(h);
}


bool isEmpty(heap* h){
   return h->size == 0;
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


double* dijkstra(graph* g, int src){

   double* dists = (double*) malloc(sizeof(double) * g->n);
   bool visited[g->n];

   for(size_t i = 0 ; i < g->n ; i++){
      dists[i] = SIZE_MAX;
      visited[i] = false;
   }

   dists[src] = 0;
   heap* pq = newHeap(g->n);
   node n = {src, 0};
   insert(pq, n);

   while(!isEmpty(pq)){

      node curr = pop(pq);
      if(visited[curr.vertex]) continue;
      visited[curr.vertex] = true;

      vertexNode* neigh = g->adjList[curr.vertex];

      while(neigh){
         double newDist = dists[curr.vertex] + neigh->node.distance;

         if(!visited[neigh->node.vertex] && newDist < dists[neigh->node.vertex]){
            dists[neigh->node.vertex] = newDist;
            node n; n.distance = newDist; n.vertex = neigh->node.vertex;
            insert(pq, n);
         }
         neigh = neigh->next;
      }
   }

   freeHeap(pq);
   return dists;
}


int main(){
   graph* g = newGraph(5);
   addEdge(g, 0, 1, 4);
   addEdge(g, 0, 2, 2);
   addEdge(g, 1, 2, 1);
   addEdge(g, 1, 3, 5);
   addEdge(g, 2, 3, 8);
   addEdge(g, 2, 4, 10);
   addEdge(g, 3, 4, 2);

   double* dists = dijkstra(g, 0); 

   for(int i = 0 ; i < 5 ; i++){
      printf("%f, ", dists[i]);
   }
   printf("\n");

   free(dists);
   freeGraph(g);
}
