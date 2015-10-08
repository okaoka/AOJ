#define _USE_MATH_DEFINES
#define INF 0x3f3f3f3f
#include <cstdio>
#include <iostream>
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
#include <complex>
using namespace std;
 
typedef long long ll;
typedef pair <int,int> P;
typedef pair <int,P > PP;
 
const static int tx[] = {0,1,1,1,0,-1,-1,-1};
const static int ty[] = {-1,-1,0,1,1,1,0,-1};
 
static const double EPS = 1e-6;

class State {
public:
  int word_i;
  int word_j;
  int remaining;
  int cost;
  State(int word_i, int word_j, int remaining, int cost)
    : word_i(word_i), word_j(word_j), remaining(remaining), cost(cost) {}
  bool operator<(const State& s) const {
    return cost < s.cost;
  }
};

int dp[101][101][51];

const static int offset = 25;

bool is_palindrome(const string& str){
  for(int i = 0; i < str.size() / 2; i++){
    if(str[i] != str[str.size() - i - 1]){
      return false;
    }
  }
  return true;
}

int connect(const vector<string>& words,
	    vector<int> forward_connection[101],
	    vector<int> backward_connection[101],
	    int word_i, int word_j, int remaining,
	    priority_queue<State>& que){
  // remaining == 25 => 0
  remaining -= offset;

  // add to left side
  if(remaining > 0){
    for(int i = 0; i < backward_connection[word_i].size(); i++){
      string front = words[word_j];
      string rear = words[backward_connection[word_i][i]];
      
      if(front.size() - remaining < 0) continue;

      int add_len = min(remaining,(int)rear.size());
      string other_side = front.substr(front.size() - remaining,add_len);
      string add_side = rear.substr(rear.size() - add_len,add_len);

      if(!is_palindrome(add_side + other_side)) continue;

      // goh + abccba hoge
      // agufegoh + abccba hoge
      if(dp[backward_connection[word_i][i]][word_j][offset + remaining - add_len]
	 < dp[word_i][word_j][offset + remaining] + add_len){
	que.push(State(backward_connection[word_i][i],word_j,offset + remaining - add_len,dp[word_i][word_j][offset + remaining] + add_len * 2));
      }
    }
  }

  // add to right side
  else {
    for(int i = 0; i < forward_connection[word_j].size(); i++){
      string front = words[forward_connection[word_j][i]];
      string rear = words[word_i];

      if((int)rear.size() - abs(remaining) < 0) continue;

      int add_len = min(abs(remaining),(int)front.size());
      string add_side = front.substr(front.size() - add_len,add_len);
      string other_side = rear.substr(rear.size() - abs(remaining),add_len);

      if(!is_palindrome(other_side + add_side)) continue;

      // egoh abccba + hog (rem:-4 add:3 -> rem:-1)
      // egoh abccba + hogefuga (rem:-4 add 8 -> rem:4)
      if(dp[word_i][forward_connection[word_j][i]][offset + remaining + add_len]
	 < dp[word_i][word_j][offset + remaining] + add_len){
	que.push(State(word_i,forward_connection[word_j][i],offset + remaining + add_len,dp[word_i][word_j][offset + remaining] + add_len * 2));
      }
    }
  }
}

int main(){
  int num_of_words;
  int num_of_pairs;
  while(~scanf("%d %d",&num_of_words,&num_of_pairs)){
    memset(dp,-1,sizeof(dp));

    vector<string> words;
    for(int word_i = 0; word_i < num_of_words; word_i++){
      string word;
      cin >> word;
      words.push_back(word);
    }
    
    vector<int> forward_connection[101];
    vector<int> backward_connection[101];
    for(int pair_i = 0; pair_i < num_of_pairs; pair_i++){
      int from, to;
      scanf("%d %d",&from,&to);
      from--; to--;
      forward_connection[from].push_back(to);
      backward_connection[to].push_back(from);
    }

    priority_queue<State> que;
    for(int i = 0; i < words.size(); i++){
      if(is_palindrome(words[i])){
	que.push(State(i,i,offset,words[i].size()));
      }
      else {
	que.push(State(i,i,offset + words[i].size(),0));
      }
    }

    while(!que.empty()){
      State s = que.top();
      que.pop();
      if(dp[s.word_i][s.word_i][s.remaining] >= s.cost){
	continue;
      }
      dp[s.word_i][s.word_i][s.remaining] = s.cost;
      connect(words,forward_connection,backward_connection,s.word_i,s.word_j,s.remaining,que);
    }

    int res = 0;
    for(int word_i = 0; word_i < num_of_words; word_i++){
      for(int word_j = 0; word_j < num_of_words; word_j++){
	res = max(res,dp[word_i][word_j][offset]);
      }
    }

    printf("%d\n",res < INF ? res : -1);
  }
}
