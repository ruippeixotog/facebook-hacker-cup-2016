#include <cstring>
#include <iostream>

#define MAXN 100000
#define INF 1e9

using namespace std;

int n;
int probs[MAXN];

int dp[MAXN + 2][4];

int extraProbsTo(int i, int k1, int k2) {
  int best = INF;

  bool canEnd1 = (i == 0 || probs[i - 1] <= 100 - (3 - k1));
  bool canBegin2 = (i == n || probs[i] >= k2);

  bool canGoDirect = i > 0 && i < n && k1 < k2 &&
    probs[i] - probs[i - 1] >= k2 - k1 &&
    probs[i] - probs[i - 1] <= 10 * (k2 - k1);

  if(canEnd1 && canBegin2)
    best = min(best, (i == 0 ? 0 : 3 - k1) + (i == n ? 0 : k2));

  if(canGoDirect)
    best = min(best, k2 - k1 - 1);

  return best;
}

int main() {
  int t; cin >> t;
  for(int tc = 1; tc <= t; tc++) {
    cin >> n;
    for(int i = 0; i < n; i++) {
      cin >> probs[i];
    }

    memset(dp, 0x3f, sizeof(dp));
    dp[0][3] = 0;

    for(int i = 0; i < n + 1; i++) {
      for(int k1 = 0; k1 < 4; k1++) {
        for(int k2 = 0; k2 < 4; k2++) {
          dp[i + 1][k2] = min(
            dp[i + 1][k2],
            dp[i][k1] + extraProbsTo(i, k1, k2));
        }
      }
    }
    cout << "Case #" << tc << ": " << dp[n + 1][0] << endl;
  }
  return 0;
}
