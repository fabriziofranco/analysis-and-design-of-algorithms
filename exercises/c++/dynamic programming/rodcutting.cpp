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

const int N = 1e+6; // max rod length

ll l, p;
ll precios[N];

ll dp[N][N];

int main() {
     ios_base::sync_with_stdio(0);
     cin.tie(0);

     // tamaño del rod
     cin >> l;

     // leer los precios por cada pieza del rod
     rep(i, 1, l) {
          cin >> precios[i];
     }

     // caso base, si tengo un rod de tamano 0, entonces mi profit maximo será 0
     rep(i, 1, l) {
          dp[l][0] = 0;
     }

     // caso base, corto de 1 en 1
     // ejemplo, si mi rod tiene length 5, entonces tendré 5 piezas de tamaño 1
     rep(i, 1, l) {
          // si tengo un rod de tamaño 'i' y solo lo puedo cortar en pedazos de tamano 1
          dp[1][i] = i*precios[1];
     } 

     rep(i, 2, l) { // 'i' =  el tamaño maximo de corte que puedo hacer
          rep(j, 0, l) { // 'j' =  el tamaño de mi rod
               // uso el corte de tamano 'i'? o no?
               if (j-i >= 0) { // prevenir seg fault
                    // si PUEDO usar el corte de tamaño 'i', entonces 
                    // escogo el máximo entre cortar el rod y no cortarlo
                    // dp[i][j-1] = max profit del tamano que me queda si lo corto, como lo corte en 'i', tengo que sumar su precio
                    // dp[i-1][j] = max profit al no cortar
                    dp[i][j] = max(dp[i][j-i]+precios[i], dp[i-1][j]);
               } else {
                    // si el corte es más grande que el tamaño del rod
                    // de frente sé que no puedo usar ese tamaño de corte
                    dp[i][j] = dp[i-1][j];
               }
          }
     }

     cout << dp[l][l];

     return 0;
}