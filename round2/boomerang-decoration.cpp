#include <algorithm>
#include <iostream>
#include <string>

#define ll long long
#define ld long double

#define MAXN 100000
#define INF 1e9

using namespace std;

int dpLeft[MAXN], dpRight[MAXN];

int main() {
  int t; cin >> t;
  for(int tc = 1; tc <= t; tc++) {
    int n; cin >> n;
    string a, b; cin >> a >> b;

    dpLeft[0] = 1;
    for(int i = 1; i < n; i++) {
      dpLeft[i] = dpLeft[i - 1] + (b[i] != b[i - 1]);
    }

    dpRight[n - 1] = 1;
    for(int i = n - 2; i >= 0; i--) {
      dpRight[i] = dpRight[i + 1] + (b[i] != b[i + 1]);
    }

    int best = INF;
    for(int i = 0; i < n - 1; i++) {
      int l = i, r = i + 1;
      while(l >= 0 && a[l] == b[l]) l--;
      while(r < n && a[r] == b[r]) r++;
      best = min(best, max(
        l >= 0 ? dpLeft[l] : 0,
        r < n ? dpRight[r] : 0));
    }
    cout << "Case #" << tc << ": " << best << endl;
  }
  return 0;
}
