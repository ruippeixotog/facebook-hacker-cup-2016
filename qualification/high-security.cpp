#include <iostream>

#define MAXN 1000

using namespace std;

int n;
char grid[2][MAXN];

int guards;

int isSingle(int i, int j) {
  if(j == 0) return grid[i][j + 1] == 'X';
  if(j == n - 1) return grid[i][j - 1] == 'X';
  return grid[i][j + 1] == 'X' && grid[i][j - 1] == 'X';
}

bool putGuard(int i, int j) {
  if(grid[i][j] != '.') return false;

  guards++;
  if(grid[1 - i][j] != 'X')
    grid[1 - i][j] = 'G';

  for(int j2 = j; j2 >= 0 && grid[i][j2] != 'X'; j2--) grid[i][j2] = 'G';
  for(int j2 = j; j2 < n && grid[i][j2] != 'X'; j2++) grid[i][j2] = 'G';
  return true;
}

int main() {
  int t; cin >> t;
  for(int tc = 1; tc <= t; tc++) {
    cin >> n;
    for(int i = 0; i < 2; i++) {
      for(int j = 0; j < n; j++)
        cin >> grid[i][j];
    }

    guards = 0;

    for(int i = 0; i < 2; i++) {
      for(int j = 0; j < n; j++) {
        if(isSingle(i, j)) {
          putGuard(1 - i, j) || putGuard(i, j);
        }
      }
    }

    for(int i = 0; i < 2; i++) {
      for(int j = 0; j < n; j++) {
        if(grid[i][j] == '.') putGuard(i, j);
      }
    }

    cout << "Case #" << tc << ": " << guards << endl;
  }
  return 0;
}
