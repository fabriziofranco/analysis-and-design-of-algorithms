#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for (ll i = a; i <= b; ++i)
#define F first
#define S second
#define PB push_back
#define MP make_pair

typedef unsigned long long ull;
typedef long double ld;
typedef long long ll;
typedef vector<ll> vll;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

int n, m;
string s1;
string s2;

const int N = 5e3 + 10;  // 5 x 10^3 + 10

int dp[N][N];

int main() {
     ios_base::sync_with_stdio(0);
     cin.tie(0);

     cin >> s1;
     cin >> s2;

     n = s1.length();
     m = s2.length();

     // https://cses.fi/problemset/task/1639

     // convertir s1 a s2

     // dp[fila][columna]
     // dp[m][n]

     /*
     dp[][] se vería así:

     e = ''

       e M O V I E
     e
     L
     O
     V
     E

     */

     // casos base, comparo el 'empty string' de s1 con cada caracter de s2
     // lo unico que puedo hacer es hacer la operación 'add' a s1
     rep(i, 0, m) {
          dp[i][0] = i; // hago 'i' operaciones 'add', ya que s1 está vacío y s2 no, y queremos transformar s1 a s2
     }
     // casos base, comparo el 'empty string' de s2 con cada caracter de s1
     // lo unico que puedo hacer es hacer la operación 'delete' a s2
     rep(i, 0, n) {
          dp[0][i] = i; // hago 'i' operaciones 'delete', ya que s2 está vacío y s1 no, y queremos transformar s1 a s2
     }

     rep(i, 1, m) {
          rep(j, 1, n) {
               // RECORDADR: queremos transformar s1 a s2 mediante el mínimo número de operaciones
               // transformado el substring de 1..j de s1 al substring de 1..i de s2
                // insert
                // delete
                // replace
               int cost = 1;
               if (s1.substr(j-1, 1) == s2.substr(i-1, 1)) {
                    // si tienen el mismo caracter, entonces cuesta 0 el 'replace', ya que sería un replace trivial, por así decirlo
                    cost = 0;
               }
               // minimo entre 'insert', 'add' o 'delete'
               // cada operacion cuesta 1, excepto por 'replace' que tiene costo variable
               // dp[i][j] = min(1 + delete, 1 + add, costoDeReplace + replace);
               dp[i][j] = std::min({1 + dp[i][j-1], 1 + dp[i-1][j], cost + dp[i-1][j-1]});
          }
     }

     // complejidad: O(mn)
     // dp[m][n] tiene la respuesta que queremos
     cout << dp[m][n];

     return 0;
}