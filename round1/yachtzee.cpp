#include <iomanip>
#include <iostream>

#define ll long long
#define ld long double

#define MAXN 100000

using namespace std;

ll c[MAXN];

int main() {
  int t; cin >> t;
  for(int tc = 1; tc <= t; tc++) {
    cerr << "-- Case #" << tc << " --" << endl;
    int n, a, b; cin >> n >> a >> b;
    for(int i = 0; i < n; i++) {
      cin >> c[i];
    }

    ll cycleSum = 0;
    ld cycleAvg = 0.0;
    for(int i = 0; i < n; i++) {
      cycleSum += c[i];
      cycleAvg += c[i] * c[i];
    }
    cycleAvg /= cycleSum;

    // cerr << "cycle " << cycleSum << " " << cycleAvg << endl;

    ll init = a % cycleSum;
    ll end = b % cycleSum;
    ll cycles = (b / cycleSum) - (a / cycleSum) - 1;

    cerr << init << " " << cycles << " " << end << " " << endl;

    ll initSum = 0;
    ld initAvg = 0.0;
    for(int i = 0; i < n; i++) {
      if(init >= c[i]) { init -= c[i]; continue; }
      initSum += c[i] - init;
      initAvg += (init + c[i]) * (c[i] - init);
      init = 0;
    }
    if(initSum > 0) initAvg /= initSum;

    // cerr << "init " << initSum << " " << initAvg << endl;

    ll endSum = 0;
    ld endAvg = 0.0;
    for(int i = 0; i < n; i++) {
      if(end >= c[i]) {
        endSum += c[i];
        endAvg += c[i] * c[i];
      } else {
        endSum += end;
        endAvg += end * end;
        break;
      }
      end -= c[i];
    }
    if(endSum > 0) endAvg /= endSum;

    // cerr << "end " << endSum << " " << endAvg << endl;

    ll allSum = initSum + cycleSum * cycles + endSum;
    if(allSum != b - a) cerr << "ERROR" << endl;
    ld allAvg = initAvg * initSum + cycleAvg * cycleSum * cycles + endSum * endAvg;
    allAvg /= allSum * 2.0;

    cout << "Case #" << tc << ": " << fixed << setprecision(9) << allAvg << endl;
  }
  return 0;
}
