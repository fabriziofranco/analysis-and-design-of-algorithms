#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for (ll i = a; i <= b; ++i)
#define per(i, a, b) for (ll i = a; i >= b; --i)
#define F first
#define S second
#define PB push_back
#define MP make_pair
#define endl '\n'
#define print(x) for (auto& item : x) cout << item << " "; cout << endl;
#define all(v) (v).begin(), (v).end()

typedef unsigned long long ull;
typedef long double ld;
typedef long long ll;
typedef vector<ll> vll;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

int n, m;
string a, b;
// matriz de dp
vector<vi> dp;
// guarda la celda 'padre' de una celda [i][j], sirve para luego construir la solución a partir de la matriz dp llena
vector<vector<pii>> p;

int main() {
     ios_base::sync_with_stdio(0);
     cin.tie(0);

     cin >> a;
     cin >> b;
     n = a.size();
     m = b.size();

     dp.resize(m+1, vi(n+1, 0)); // matriz n x m inicializada en 0s
     p.resize(m+1, vector<pii>(n+1, {-1, -1})); // matriz n x m inicializada en (0, 0)s

     string s;

     // llenar la 1era columna
     rep(i, 0, m-1) {
          if (a[0] == b[i]) {
               dp[i][0] = 1;
               if (i >= 1) {
                    p[i][0] = {i-1, 0};
               }
          } 
          else {
               if (i >= 1) {
                    dp[i][0] = dp[i-1][0];
                    p[i][0] = {i-1, 0};
               }
               else {
                    dp[i][0] = 0;
               }
          }
     }

     // llenar la 1era fila
     rep(i, 0, n-1) {
          if (a[i] == b[0]) {
               dp[0][i] = 1;
               if (i >= 1) {
                    p[0][i] = {0, i-1};
               }
          }
          else {
               if (i >= 1) {
                    dp[0][i] = dp[0][i-1];
                    p[0][i] = {0, i-1};
               }
               else {
                    dp[0][i] = 0;
               }
          }
     }

     // dp
     rep(i, 1, m-1) {
          rep(j, 1, n-1) {
               if (a[j] == b[i]) {
                    dp[i][j] = 1 + dp[i-1][j-1];
                    p[i][j] = {i-1, j-1};
               }
               else {
                    if (dp[i-1][j] > dp[i][j-1]) {
                         dp[i][j] = dp[i-1][j];
                         p[i][j] = {i-1, j};
                    }
                    else {
                         dp[i][j] = dp[i][j-1];
                         p[i][j] = {i, j-1};
                    }
               }
          }
     }
     
     // construyendo la solución
     int i = m-1;
     int j = n-1;

     while (true) {
          if (i == -1 && j == -1) break;
          int pi = p[i][j].F;
          int pj = p[i][j].S;
          if (b[i] == a[j]) {
               s.PB(a[j]);
          }
          i = pi;
          j = pj;
     }

     reverse(all(s));

     cout << "len(LCS): " << dp[m-1][n-1] << endl;
     cout << "LCS: " << s << endl;

     return 0;
}