#include <algorithm>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>

#define ll long long
#define ld long double

#define MAXN 3000

using namespace std;

ld dp[MAXN];

int main() {
  int t; cin >> t;
  for(int tc = 1; tc <= t; tc++) {
    int n, k; ld p; cin >> n >> k >> p;

    memset(dp, 0, sizeof(dp));

    for(int i = k; i <= n; i++) {
      ld lastPmf = log(1 - p) * i;
      ld cumProb = exp(lastPmf);

      for(int j = 0; j < k - 1; j++) {
        lastPmf = (log(p) + log(i - j) + lastPmf) - (log(j + 1) + log(1 - p));
        cumProb += exp(lastPmf);
      }

      dp[i] = 1.0 - cumProb;
      for(int j = 1; j <= i / 2; j++) {
        dp[i] = max(dp[i], dp[j] + dp[i - j]);
      }
    }

    cout << "Case #" << tc << ": " << fixed << setprecision(9) << dp[n] << endl;
  }
  return 0;
}
