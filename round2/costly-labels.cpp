#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

#define MAXN 1000
#define MAXK 30
#define INF 1e9

using namespace std;

int n, k, p;
int c[MAXN][MAXK];
vector<int> adjs[MAXN];

int dp[MAXN][MAXK][MAXK];

// --- start kuhn-munkres

int w[MAXK][MAXK], s[MAXK], rem[MAXK], remx[MAXK];
int mx[MAXK], my[MAXK], lx[MAXK], ly[MAXK];

void kuhnAdd(int x, int n) {
  s[x] = true;
  for(int y = 0; y < n; y++)
    if(rem[y] != -INF && rem[y] > lx[x] + ly[y] - w[x][y])
      rem[y] = lx[x] + ly[y] - w[x][y], remx[y] = x;
}

int kuhnMunkres(int n) {
  for(int i = 0; i < n; i++) {
    mx[i] = my[i] = -1;
    lx[i] = ly[i] = 0;
  }
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++)
      ly[j] = max(ly[j], w[i][j]);
  }
  for(int i = 0; i < n; i++) {
    memset(s, 0, sizeof(s));
    memset(rem, 0x3f, sizeof(rem));

    int st;
    for(st = 0; st < n; st++) {
      if(mx[st] == -1) { kuhnAdd(st, n); break; }
    }
    while(mx[st] == -1) {
      int miny = -1;
      for(int y = 0; y < n; y++) {
        if(rem[y] != -INF && (miny == -1 || rem[miny] >= rem[y]))
          miny = y;
      }

      if(rem[miny]) {
        for(int x = 0; x < n; x++) if(s[x]) lx[x] -= rem[miny];
        for(int y = 0, d = rem[miny]; y < n; y++) {
          if(rem[y] == -INF) ly[y] += d;
          else rem[y] -= d;
        }
      }

      if(my[miny] == -1) {
        int cur = miny;
        while(remx[cur] != st) {
          int pmate = mx[remx[cur]];
          my[cur] = remx[cur]; mx[my[cur]] = cur;
          my[pmate] = -1; cur = pmate;
        }
        my[cur] = remx[cur]; mx[my[cur]] = cur;
      } else {
        kuhnAdd(my[miny], n); rem[miny] = -INF;
      }
    }
  }

  int ret = 0;
  for(int i = 0; i < n; i++)
    ret += w[i][mx[i]];
  return ret;
}

// --- end kuhn-munkres

int minCostMatching(int node, int kn, int kp) {
  memset(w, 0, sizeof(w));

  for(int i = 0; i < adjs[node].size(); i++) {
    int adj = adjs[node][i];
    for(int kc = 0; kc < k; kc++)
      w[i][kc] = kc == kp ? -INF : -dp[adj][kc][kn];
  }
  return -kuhnMunkres(k);
}

void solve(int node, int parent) {
  for(int i = 0; i < adjs[node].size(); i++) {
    if(adjs[node][i] == parent) {
      adjs[node].erase(adjs[node].begin() + i); i--;
    } else {
      solve(adjs[node][i], node); 
    }
  }

  for(int kn = 0; kn < k; kn++) {
    int withPenalty = c[node][kn] + p;
    for(int adj : adjs[node]) {
      int cbest = INF;
      for(int kc = 0; kc < k; kc++)
        cbest = min(cbest, dp[adj][kc][kn]);

      withPenalty += cbest;
    }

    if(parent == -1) {
      dp[node][kn][0] = withPenalty;
      if(adjs[node].size() <= k) {
        dp[node][kn][0] = min(dp[node][kn][0],
          c[node][kn] + minCostMatching(node, kn, -1));
      }

    } else {
      for(int kp = 0; kp < k; kp++)
        dp[node][kn][kp] = withPenalty;

      if(adjs[node].size() < k) {
        for(int kp = 0; kp < k; kp++) {
          dp[node][kn][kp] = min(dp[node][kn][kp],
            c[node][kn] + minCostMatching(node, kn, kp));
        }
      }
    }
  }
}

int main() {
  int t; cin >> t;
  for(int tc = 1; tc <= t; tc++) {
    cin >> n >> k >> p;
    for(int i = 0; i < n; i++) {
      adjs[i].clear();
      for(int j = 0; j < k; j++)
        cin >> c[i][j];
    }

    for(int i = 0; i < n - 1; i++) {
      int a, b; cin >> a >> b;
      adjs[--a].push_back(--b);
      adjs[b].push_back(a);
    }

    solve(0, -1);
    int best = INF;
    for(int kn = 0; kn < k; kn++)
      best = min(best, dp[0][kn][0]);

    cout << "Case #" << tc << ": " << best << endl;
  }
  return 0;
}
