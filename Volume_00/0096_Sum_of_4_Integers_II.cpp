#define _USE_MATH_DEFINES
#define INF 0x3f3f3f3f

#include <iostream>
#include <cstdio>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <stack>
#include <limits>
#include <map>
#include <string>
#include <cstring>
#include <set>
#include <deque>
#include <bitset>
#include <list>
#include <cctype>
#include <utility>
  
using namespace std;
  
typedef long long ll;
typedef pair <int,int> P;
typedef pair <int,P> PP;
  
static const double EPS = 1e-8;

int main(){
  int n;
  int patterns[2001];
  memset(patterns,0,sizeof(patterns));
  for(int a=0;a<=1000;a++){
    for(int b=0;b<=1000;b++){
      patterns[a+b]++;
    }
  }

  while(~scanf("%d",&n)){
    ll res = 0;
    for(int lhs=0;lhs<=2000;lhs++){
      for(int rhs=0;rhs<=2000;rhs++){
	if(lhs == n - rhs){
	  res += patterns[lhs] * patterns[rhs];
	}
      }
    }
    printf("%lld\n",res);
  }
}
