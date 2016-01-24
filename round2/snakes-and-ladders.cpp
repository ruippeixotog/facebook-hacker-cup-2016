#include <algorithm>
#include <iostream>
#include <map>
#include <utility>

#define ll long long
#define ld long double

#define MAXN 200000
#define MOD 1000000007

using namespace std;

struct Stair {
  int cnt; ll sum, sqSum, multSum;
  Stair(): cnt(0), sum(0), sqSum(0), multSum(0) {}

  void add(ll x) {
    cnt++;
    sqSum = sqSum + (x * x % MOD) % MOD;
    multSum = multSum + (sum * x) % MOD; 
    sum = (sum + x) % MOD;
  }

  ll cost() {
    return (cnt - 1) * sqSum - 2 * multSum;
  }
};

pair<ll, ll> xh[MAXN];

int main() {
  int t; cin >> t;
  for(int tc = 1; tc <= t; tc++) {
    int n; cin >> n;
    for(int i = 0; i < n; i++)
      cin >> xh[i].first >> xh[i].second;
    
    sort(xh, xh + n);

    ll res = 0;
    map<ll, Stair> stairs;
    for(int i = 0; i < n; i++) {
      for(auto it = stairs.begin(); it != stairs.end();) {
        if(it->first >= xh[i].second) break;
        res = (res + it->second.cost()) % MOD;

        auto tmp = it; it++; stairs.erase(tmp);
      }

      Stair& st = stairs[xh[i].second];
      st.add(xh[i].first);
    }

    for(auto it = stairs.begin(); it != stairs.end(); it++) {
      res = (res + it->second.cost()) % MOD;
    }

    cout << "Case #" << tc << ": " << res << endl;
  }
  return 0;
}
