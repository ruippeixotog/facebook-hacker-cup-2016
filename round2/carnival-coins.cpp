#include <algorithm>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <vector>

#define ll long long
#define ld long double

#define MAXN 3000

using namespace std;

ld cumProbs[MAXN];

int main() {
  int t; cin >> t;
  for(int tc = 1; tc <= t; tc++) {
    int n, k; ld p; cin >> n >> k >> p;

    for(int i = k; i <= n; i++) {
      ld lastPmf = log(1 - p) * i;
      ld cumProb = exp(lastPmf);

      for(int j = 0; j < k - 1; j++) {
        lastPmf = (log(p) + log(i - j) + lastPmf) - (log(j + 1) + log(1 - p));
        cumProb += exp(lastPmf);
      }

      cumProbs[i] = 1.0 - cumProb;
      // cerr << i << ": " << cumProbs[i] << endl;
    }

    ld best = 0.0;
    for(int i = k; i <= n; i++) {
      int rem = n % i;

      ld prob = cumProbs[i] * (n / i);
      for(int j = 1; j <= min(rem, n / i); j++) {
        int divRem = rem / j;
        int remRem = rem % j;

        prob = max(prob, cumProbs[i] * (n / i - j)
          + cumProbs[i + divRem] * (j - remRem)
          + cumProbs[i + divRem + 1] * remRem);
      }

      // cerr << i << ": " << rem << " " << (i / k) << endl;
      // ld prob = cumProbs[i] * (n / i - 1) + cumProbs[i + rem];
      // ld prob2 = cumProbs[i] * (n / i - rem) + cumProbs[i + 1] * rem;
      // cerr << i << " total: " << prob << endl;

      // if(best2 > best) cerr << "best is " << i << " rem " << rem << endl;
      best = max(best, prob);
    }

    cout << "Case #" << tc << ": " << fixed << setprecision(9) << best << endl;
  }
  return 0;
}
