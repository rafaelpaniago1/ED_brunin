#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>


typedef struct student{
   unsigned int matricula;
   char* nome;
} student;


typedef struct listNode{
   student thisStudent;
   struct listNode* next;
} listNode;


typedef struct hashTable{
   listNode** arr; 
   size_t capacity;
   size_t size;
} hashTable;


size_t hash(unsigned int k){
   k^= k>>16;
   k *= 0x85ebca6b;
   k ^= k >> 13;
   k *= 0xc2b2ae35;
   k ^= k >> 16;
   return k;
} 


void pushStudent(listNode** head, unsigned int matricula, char* nome){
   listNode* node = (listNode*) malloc(sizeof(listNode));
   student novoEstudante = {matricula, nome};
   node->thisStudent = novoEstudante;
   node->next = *head;
   *head = node;
} 


void pushNode(listNode** head, listNode* newNode){
   newNode->next = (*head);
   (*head) = newNode;
}


void freeList(listNode* head){
   listNode* curr = head;
   while(curr != NULL){
      listNode* tmp = curr;
      curr = curr->next;
      free(tmp);
   }
}


hashTable* newTable(size_t capacity){
   hashTable* t = (hashTable*) malloc(sizeof(hashTable));
   t->arr = (listNode**) malloc(sizeof(listNode*) * capacity);
   for(size_t i = 0 ; i < capacity ; i ++){
      t->arr[i] = NULL;
   }
   t->capacity = capacity;
   t->size = 0;
   return t;
}


void insertOrUpdate(hashTable* t, student s, size_t hash_value){
   listNode* l = t->arr[hash_value];
   while(l != NULL){
      if(l->thisStudent.matricula == s.matricula){
         l->thisStudent.nome = s.nome;
         return;
      }
      l = l->next;
   } 
   pushStudent(&(t->arr[hash_value]), s.matricula, s.nome);
   t->size++;
}


void freeTable(hashTable* t){
   for(size_t i = 0 ; i < t->capacity ; i++){
      freeList(t->arr[i]);
   }
   free(t->arr);
   free(t);
}


void resize(hashTable** t){
   hashTable* table = newTable((*t)->capacity * 2);
   for(size_t i = 0 ; i < (*t)->capacity ; i++){
      listNode* node = (*t)->arr[i];
      while(node){
         listNode* next = node->next;
         size_t index = hash(node->thisStudent.matricula);
         pushNode(&table->arr[index % table->capacity], node);
         node = next;
      }
   }
   free((*t)->arr);
   free(*t);
   (*t) = table;
}


void insert(hashTable** t, unsigned int matricula, char* nome){
   if((*t)->size >= (0.75) * (*t)->capacity){
      resize(t);
   }
   size_t index = hash(matricula) % (*t)->capacity;
   student tmp = {matricula, nome};
   insertOrUpdate(*t, tmp, index);
}


char* getNameFromMatricula(hashTable* t, unsigned int matricula){
   size_t index = hash(matricula) % t->capacity;
   listNode* curr = t->arr[index];
   while(curr){
      if(curr->thisStudent.matricula == matricula) return curr->thisStudent.nome;
      curr = curr->next;
   }
   return NULL;
} 


int main(){

   hashTable* t = newTable(10);

   char* a = "Rafael";
   char* b = "Claudia";
   char* c = "Rogerio";
   char* d = "Bruno";

   insert(&t, 123, a);
   insert(&t, 456, b);
   insert(&t, 789, c);
   insert(&t, 101112, d);

   char* rafael = getNameFromMatricula(t, 123);
   char* claudia = getNameFromMatricula(t, 456);
   char* rogerio = getNameFromMatricula(t, 789);
   char* bruno = getNameFromMatricula(t, 101112);

   printf("Name: %s\n", rafael);
   printf("Name: %s\n", claudia);
   printf("Name: %s\n", rogerio);
   printf("Name: %s\n", bruno);

   freeTable(t);
}






