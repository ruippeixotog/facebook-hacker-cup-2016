#include <iostream>
#include <map>
#include <string>

#define nodeiter map<char, Node>::iterator

#define MAXN 300

using namespace std;

int n;

struct Node {
  map<char, Node> children;
  bool isWord;
  int costs[MAXN + 4];

  Node(): isWord(false) {}

  void add(const char* str) {
    if(*str == 0) isWord = true;
    else children[*str].add(str + 1);
  }

  void calcCosts() {
    memset(costs, 0x3F, sizeof(costs));
    costs[isWord] = 1;

    for(nodeiter it = children.begin(); it != children.end(); it++) {
      int newCosts[MAXN + 4];
      memcpy(newCosts, costs, sizeof(costs));

      it->second.calcCosts();
      for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= n - i; j++) {
          newCosts[i + j] = min(newCosts[i + j], costs[i] + it->second.costs[j]);
        }
      }
      memcpy(costs, newCosts, sizeof(costs));
    }
  }
};

int main() {
  int t; cin >> t;
  for(int tc = 1; tc <= t; tc++) {
    int k; cin >> n >> k;

    Node trie;
    for(int i = 0; i < n; i++) {
      string str; cin >> str;
      trie.add(str.c_str());
    }

    trie.calcCosts();
    int ops = (trie.costs[k] - 1) * 2 + k;
    cout << "Case #" << tc << ": " << ops << endl;
  }
  return 0;
}
