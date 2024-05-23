#include <iostream>
#include <unordered_map>
#include <string>
#include <utility>
#include <vector>
#include <typeinfo>
#include <bits/stdc++.h>
using namespace std;

pair<int, int*> func() {
  int v = 5;
  cout << &v << endl;
  return {v, &v};
}

int main() {
  const auto& [i, p] = func();
  cout << i << endl << p << endl << *p << endl;
    
  return 0;
}
