#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

#define MAXN 1000
#define MAXK 30
#define INF 1e9

using namespace std;

int n, k, p;
int c[MAXN][MAXK];
vector<int> adjs[MAXN];

int dp[MAXN][MAXK][MAXK];

// --- start min-cost max flow

#define MAXGN (MAXN + MAXK + 2)

int gn, cn;

vector<int> gadjs[MAXGN];
int cost[MAXGN][MAXGN];

int dist[MAXGN], parent[MAXGN], pi[MAXGN];  // shortest path
bool flow[MAXGN][MAXGN];                    // mcmf

inline int pot(int u, int v) { return dist[u] + pi[u] - pi[v]; }

int dijkstra(int src, int dest) {
  memset(dist, 0x3f, sizeof(dist));
  memset(parent, -1, sizeof(parent));

  priority_queue<pair<int, int>> q;
  q.push(make_pair(0, src)); dist[src] = 0;

  while(!q.empty()) {
    int curr = q.top().second; q.pop();

    if(parent[curr] >= 0) continue;
    parent[curr] = -parent[curr] - 1;

    for(int adj : gadjs[curr]) {
      if(parent[adj] >= 0) continue;

      if(flow[adj][curr] && pot(curr, adj) - cost[adj][curr] < dist[adj]) {
        dist[adj] = pot(curr, adj) - cost[adj][curr];
        parent[adj] = -curr - 1;
        q.push(make_pair(-dist[adj], adj));
      }

      if(!flow[curr][adj] && pot(curr, adj) + cost[curr][adj] < dist[adj]) {
        dist[adj] = pot(curr, adj) + cost[curr][adj];
        parent[adj] = -curr - 1;
        q.push(make_pair(-dist[adj], adj));
      }
    }
  }

  for(int i = 0; i < gn; i++) { pi[i] += dist[i]; }
  return dist[dest];
}

int mcmf(int src, int sink) {
  memset(flow, false, sizeof(flow));
  memset(pi, 0, sizeof(pi));

  int minCost = 0;
  while(dijkstra(src, sink) < INF) {
    for(int v = sink, u = parent[v]; v != src; u = parent[v = u]) {
      if(flow[v][u]) { flow[v][u] = false; minCost -= cost[v][u]; }
      else { flow[u][v] = true; minCost += cost[u][v]; }
    }
  }
  return minCost;
}

// --- end min-cost max flow

void buildFlowGraph(int node) {
  cn = adjs[node].size();
  gn = (cn == 0 ? 0 : cn + k) + 2;
  int src = gn - 2, sink = gn - 1;

  for(int i = 0; i < gn; i++)
    gadjs[i].clear();

  if(cn == 0) {
    gadjs[src].push_back(sink);
    cost[src][sink] = 0;
    return;
  }

  for(int i = 0; i < cn; i++) {
    gadjs[src].push_back(i);
    cost[src][i] = 0;
    for(int kc = 0; kc < k; kc++) {
      gadjs[i].push_back(cn + kc);
      gadjs[cn + kc].push_back(i);
    }
  }

  for(int kc = 0; kc < k; kc++) {
    gadjs[cn + kc].push_back(sink);
    cost[cn + kc][sink] = 0;
  }
}

void setFlowGraphCosts(int node, int kn, int kp) {
  for(int i = 0; i < cn; i++) {
    int adj = adjs[node][i];
    for(int kc = 0; kc < k; kc++) {
      cost[i][cn + kc] = cost[cn + kc][i] =
        kc == kp ? INF : dp[adj][kc][kn];
    }
  }
}

void solve(int node, int parent) {
  for(int i = 0; i < adjs[node].size(); i++) {
    if(adjs[node][i] == parent) {
      adjs[node].erase(adjs[node].begin() + i); i--;
    } else {
      solve(adjs[node][i], node); 
    }
  }

  buildFlowGraph(node);

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
        setFlowGraphCosts(node, kn, -1);
        dp[node][kn][0] = min(dp[node][kn][0],
          c[node][kn] + mcmf(gn - 2, gn - 1));
      }

    } else {
      for(int kp = 0; kp < k; kp++)
        dp[node][kn][kp] = withPenalty;

      if(adjs[node].size() < k) {
        for(int kp = 0; kp < k; kp++) {
          setFlowGraphCosts(node, kn, kp);
          dp[node][kn][kp] = min(dp[node][kn][kp],
            c[node][kn] + mcmf(gn - 2, gn - 1));
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
