/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  This program gneerates a 
  table that tells if a segment
  of a string is a palindrome
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#include <cstdio>
#include <iostream>
#include <vector>

typedef long long lint;

using namespace std;
bool DEBUGGING=false;
bool pal[3000][3000]; // Substring[i..j] is a palindrome (or not)
lint start[3000]; // NUmber of palindromes till i-th position from start
lint end[3000];
lint lft[3000];
lint rgt[3000];

void palmark(string S) {
  int len = S.size();
  for (int i=0 ; i<len ; i++) {
    start[i] = end[i] = lft[i] = rgt[i] = 0;
    for (int j=0 ; j<len ; j++) {
      pal[i][j] = false;
    }
  }

  for (int j=0 ; j<len ; j++) {
    if (DEBUGGING) cout << "Testing length: " << j << endl;
    for (int i=0 ; (i+j)<len ; i++) {
      int l = i;
      int r = i+j;
      if (DEBUGGING) cout << "Testing: " << S.substr(l,r-l+1) << endl;
      pal[l][r] = ((S[l]==S[r])&&(pal[l+1][r-1]))||(j==0)||((S[l]==S[r])&&(l==r-1));
      if (pal[l][r] == true) {
        if (DEBUGGING) cout << S.substr(l,r-l+1) << endl;
        end[r]++;
        start[l]++;
      }
    }
  }

  // Storing cumulative sum of palindrome numbers from start till i
  lft[0] = 1;
  rgt[len-1] = 1;
  for (int i=1 ; i<len ; i++) {
    lft[i] = lft[i-1]+end[i];
    int j = (len-1)-i;
    rgt[j] = rgt[j+1]+start[j];
  }

}


int main() {
  DEBUGGING = false;
  string I = "yuy";
  while( cin >> I ) {
    palmark(I); 
    if (DEBUGGING) {
      for (int i=0 ; i<I.size() ; i++) {
        for (int j=0 ; j<I.size() ; j++) {
          cout << pal[i][j] << " ";
        }
        cout << endl;
      }
    }
    
    if (DEBUGGING)
    for (int i=0 ; i<I.size() ; i++) {
      for (int j=0 ; j<I.size() ; j++) {
        if (pal[i][j]==true) {
          lint x=i, y=j;
          if (x>y) {
            lint t = x;
            x = y;
            y = t;
          }
          cout << "[" << x << ", " << y << "] : { " << I.substr(x,y-x+1) << " } " << endl;
        }
      }
    }
    if (DEBUGGING)
    for (int i=0 ; i<I.size() ; i++) {
      cout << "Number of palindromes before and with " << i << ": " << lft[i] << endl;
      cout << "Number of palindromes after and excluding " << i << ": " << (i<I.size()-1?rgt[i+1]:I.size()-1-i) << endl;
      cout << "Number of palindromes that start with " << i << ": " << start[i] << endl;
      cout << "Number of palindromes that end with " << i << ": " << end[i] << endl;
      for (int j=0 ; j<I.size() ; j++) {
        if (pal[j][i]) cout << I.substr(j,i-j+1) << endl;
      }
    }
    lint res = 0;
    for (int i=0 ; i<I.size() ; i++) {
      res = res + (lft[i]*(i<I.size()-1?rgt[i+1]:I.size()-1-i));
      int j=i-1;
      if (j>=0) res = res - (lft[j]*(i<I.size()-1?rgt[i+1]:I.size()-1-i));
    }
    cout << res << endl;
  }
  return 0;
}
