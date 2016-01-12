#include <iostream>

#define MAXN 2000

using namespace std;

int x[MAXN], y[MAXN];

int dist2(int i, int j) {
  int dx2 = (x[i] - x[j]) * (x[i] - x[j]);
  int dy2 = (y[i] - y[j]) * (y[i] - y[j]);
  return dx2 + dy2;
}

int main() {
  int t; cin >> t;
  for(int tc = 1; tc <= t; tc++) {
    int n; cin >> n;
    for(int i = 0; i < n; i++)
      cin >> x[i] >> y[i];

    int cnt = 0;
    for(int i = 0; i < n; i++) {
      for(int j = i + 1; j < n; j++) {
        for(int k = j + 1; k < n; k++) {
          cnt += (dist2(i, j) == dist2(i, k)) +
            (dist2(i, j) == dist2(j, k)) +
            (dist2(i, k) == dist2(j, k));
        }
      }
    }
    cout << "Case #" << tc << ": " << cnt << endl;
  }
  return 0;
}
