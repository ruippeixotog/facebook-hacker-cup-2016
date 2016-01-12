#include <iostream>

#define ll long long

#define MAXN 100000

using namespace std;

int b[MAXN];

int main() {
  int t; cin >> t;
  for(int tc = 1; tc <= t; tc++) {
    int n, p; cin >> n >> p;
    for(int i = 0; i < n; i++)
      cin >> b[i];

    ll cnt = 0;
    int sum = 0, curr = 0;
    for(int i = 0; i < n; i++) {
      curr = max(curr, i);
      
      while(curr < n && sum + b[curr] <= p) {
        sum += b[curr++];
      }
      cnt += curr - i;
      sum = max(0, sum - b[i]);
    }
    cout << "Case #" << tc << ": " << cnt << endl;
  }
  return 0;
}
