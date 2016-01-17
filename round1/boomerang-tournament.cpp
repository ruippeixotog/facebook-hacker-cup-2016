#include <iostream>
#include <utility>
#include <vector>

#define MAXN 16

using namespace std;

bool w[MAXN][MAXN];

vector<vector<int>> winsToPlace = {
  { 1 },
  { 2, 1 },
  { 3, 2, 1 },
  { 5, 3, 2, 1 },
  { 9, 5, 3, 2, 1 }
};

vector<pair<int, int>> solve(vector<int>& ps);

vector<pair<int, int>> solve2(vector<int>& ps, vector<int>& left, vector<int>& right, int k) {
  if(k == ps.size()) {
    auto leftRes = solve(left);
    auto rightRes = solve(right);

    int winnerScore = 0;
    for(int i = left.size(); i > 1; i /= 2) winnerScore++;

    vector<pair<int, int>> res;
    int lIdx = 0, rIdx = 0;
    for(int i = 0; i < ps.size(); i++) {
      pair<int, int> pRes = leftRes[lIdx];

      if(lIdx < left.size() && left[lIdx] == ps[i]) {
        if(leftRes[lIdx].second == winnerScore) {
          bool alwaysWins = true;
          for(int j = 0; j < right.size(); j++) {
            if(rightRes[j].second == winnerScore) {
              if(w[left[lIdx]][right[j]]) pRes.second = winnerScore + 1;
              else alwaysWins = false;
            }
          }
          if(pRes.first == winnerScore && alwaysWins)
            pRes.first = winnerScore + 1;
        }
        res.push_back(pRes);
        lIdx++;

      } else {
        pair<int, int> pRes = rightRes[rIdx];

        if(rightRes[rIdx].second == winnerScore) {
          bool alwaysWins = true;
          for(int j = 0; j < left.size(); j++) {
            if(leftRes[j].second == winnerScore) {
              if(w[right[rIdx]][left[j]]) pRes.second = winnerScore + 1;
              else alwaysWins = false;
            }
          }
          if(pRes.first == winnerScore && alwaysWins)
            pRes.first = winnerScore + 1;
        }
        res.push_back(pRes);
        rIdx++;
      }
    }
    return res;

  } else if(k == 0 || right.size() == ps.size() / 2) {
    left.push_back(ps[k]);
    auto res = solve2(ps, left, right, k + 1);
    left.pop_back();
    return res;

  } else if(left.size() == ps.size() / 2) {
    right.push_back(ps[k]);
    auto res = solve2(ps, left, right, k + 1);
    right.pop_back();
    return res;

  } else {
    left.push_back(ps[k]);
    auto res1 = solve2(ps, left, right, k + 1);
    left.pop_back();
    right.push_back(ps[k]);
    auto res2 = solve2(ps, left, right, k + 1);
    right.pop_back();

    for(int i = 0; i < ps.size(); i++) {
      res1[i] = make_pair(
        min(res1[i].first, res2[i].first),
        max(res1[i].second, res2[i].second));
    }
    return res1;
  }
}

vector<pair<int, int>> solve(vector<int>& ps) {
  if(ps.size() == 1) return { make_pair(0, 0) };

  vector<int> left, right;
  return solve2(ps, left, right, 0);
}

int main() {
  int t; cin >> t;
  for(int tc = 1; tc <= t; tc++) {
    int n; cin >> n;
    for(int i = 0; i < n; i++) {
      for(int j = 0; j < n; j++) {
        cin >> w[i][j];
      }
    }

    int maxWins = 0;
    for(int i = n; i > 1; i /= 2) maxWins++;

    vector<int> ps;
    for(int i = 0; i < n; i++) {
      ps.push_back(i);
    }
    auto res = solve(ps);

    cout << "Case #" << tc << ":" << endl;
    for(int i = 0; i < n; i++) {
      cout <<
        winsToPlace[maxWins][res[i].second] << " " <<
        winsToPlace[maxWins][res[i].first] << endl;
    }
  }
  return 0;
}
