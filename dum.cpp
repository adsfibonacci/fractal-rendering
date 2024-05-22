#include <iostream>
#include <unordered_map>
#include <string>
#include <utility>
#include <vector>
#include <typeinfo>
#include <bits/stdc++.h>
using namespace std;

int* func(int* i) {
  int v = 5;
  i = &v;
  return i;
}

int main() {
  int l = 1;
  int* k = &l;
  k = func(k);

  for(long i = 0; i < 10000000000; ++i) {*(k+sizeof(int)) = 0;}

  cout << k << "\t" << *k << endl;
    
  return 0;
}
