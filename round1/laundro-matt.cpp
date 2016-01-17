#include <iostream>
#include <queue>
#include <utility>

#define ll long long

#define MAXN 100000

#define WASHED 0
#define DRIED 1

using namespace std;

int w[MAXN];

int main() {
  int t; cin >> t;
  for(int tc = 1; tc <= t; tc++) {
    int l, n, m, d; cin >> l >> n >> m >> d;
    for(int i = 0; i < n; i++) {
      cin >> w[i];
    }

    priority_queue<pair<ll, int>> events;
    priority_queue<pair<ll, int>> washs;
    int waiting = 0;
    int driers = m;

    for(int i = 0; i < n; i++) {
      washs.push(make_pair(-w[i], i));
    }

    for(int i = 0; i < l; i++) {
      pair<ll, int> wash = washs.top(); washs.pop();
      ll t = wash.first;
      events.push(make_pair(t, WASHED));
      washs.push(make_pair(t - w[wash.second], wash.second));
    }

    ll last = 0;
    while(!events.empty()) {
      pair<ll, int> ev = events.top(); events.pop();
      ll t = ev.first;
      switch(ev.second) {
        case WASHED:
          if(driers == 0) waiting++;
          else {
            events.push(make_pair(t - d, DRIED));
            driers--;
          } 
          break;
        case DRIED:
          last = -t;
          if(waiting == 0) driers++;
          else {
            events.push(make_pair(t - d, DRIED));
            waiting--;
          }
      }
    }

    cout << "Case #" << tc << ": " << last << endl;
  }
  return 0;
}
