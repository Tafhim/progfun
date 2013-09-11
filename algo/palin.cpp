/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  This program gneerates a 
  table that tells if a segment
  of a string is a palindrome
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

bool pal[5000][5000];

void palmark(string S) {
  int len = S.size();
  for (int i=0 ; i<len ; i++)
    for (int j=i ; j<len ; j++)
      pal[i][j] = false;
  for (int j=0 ; j<len ; j++) {
    for (int i=0 ; (i+j)<len ; i++) {
      int l = i;
      int r = i+j;
      pal[l][r] = (S[l]==S[r]*pal[l+1][r-1])||(j==0);
    }
  }
}


int main() {
  string I = "yuy";
  while( cin >> I ) {
    palmark(I);
    for (int i=0 ; i<I.size() ; i++) {
      for (int j=i ; j<I.size() ; j++) {
        if (pal[i][j]==true)
          cout << "[" << i << ", " << j << "] : { " << I.substr(i,j-i+1) << " } " << endl;
      }
    }
  }
}
