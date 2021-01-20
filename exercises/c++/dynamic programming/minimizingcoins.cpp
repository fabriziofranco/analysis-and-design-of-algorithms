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

const int N = 2e+6;

ll dp[N];
ll coins[N];

int main() {
     ios_base::sync_with_stdio(0);
     cin.tie(0);

     // https://cses.fi/problemset/task/1634

     ll n, x;
     cin >> n >> x;
     rep(i, 0, n-1) {
          cin >> coins[i];
     }

     // si x = 0, entonces 0 monedas son necesaias
     dp[0] = 0;

     // top down, empezamos desde x=1 hasta x=x
     // top down: nos movemos desde los casos base hacia arriba
     // i = el vuelto que quiero dar
     rep(i, 1, x) { // por cada suma posible 
          dp[i] = x+1; // inicialmente, no podemos llegar a la suma, pero este valor de puede actualizar abajo (linea 43)
          rep(j, 0, n-1) { // por cada moneda
               if (i - coins[j] >= 0) {  // si x-c >= 0, actualizamos dp[i], sino, lo dejamos en x+1
                    dp[i] = min( dp[i], 1 + dp[ i-coins[j] ] );
               }
          }
     }

     if (dp[x] == x+1) {
          cout << -1; // no se pudo llegar a la suma
     } else {
          cout << dp[x]; // se puedo llegar a la suma, extraer el minimo numero de monedas
     }

     return 0;
}