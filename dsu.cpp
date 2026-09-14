#include <bits/stdc++.h>
using namespace std;


void Switch(int* a, int* b){
   int tmp = *a;
   *a = *b;
   *b = tmp;
}

class dsu{

public:
   vector<int> leader;
   vector<int> size;
   dsu(size_t n){
      leader.resize(n);
      size.resize(n);
      for(size_t i = 0; i < n; i++){
         leader[i] = i;
         size[i] = 1;
      }
   }

   int find(int n){
      return leader[n] = (leader[n] == n ? n : find(leader[n]));
   }

   void Union(int n, int m){
      int a = find(n);
      int b = find(m);
      if(a == b) return;

      if(size[a] < size[b]){
         Switch(&a, &b);
      }
      
      size[a] += size[b];
      leader[b] = a;
   }
   
   bool sameRep(int n, int m){
      return find(n) == find(m);
   }
};


int main(){

   dsu teste(10);

   teste.Union(4,5);
   teste.Union(5,6);
   teste.Union(1,2);
   teste.Union(2,3);
   teste.Union(3,4);
 
   cout<<teste.sameRep(1,6)<<endl;
   cout<<teste.sameRep(1,3)<<endl;
   cout<<teste.sameRep(0,3)<<endl;
}

