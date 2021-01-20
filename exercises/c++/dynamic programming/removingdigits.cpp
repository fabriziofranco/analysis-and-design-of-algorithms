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

// algoritmo recursivo
int minways(string number) {
     int num = stoi(number);
     // casos base
     if (num == 0) return 0;
     if (num <= 9) return 1; // 1 <= num <= 9
     int best = INT_MAX;
     // le resto a 'number' cada uno de sus digitos y agarro el mínimo número de pasos en 'best'
     for (auto& digit : number) {
          int diff = num - (digit - '0'); // si number=10, diff = 10 - 1 = 9
          if (diff == num) { // si number=10, por ejemplo, en una tendría 10 - 0, ahi podríamos caer el loop inifinito
               continue;
          }
          // 10: diff = 9
          // if (exist[diff]) {
          //      return memo[diff];
          // } else {
          //      memo[diff] = 1 + minways(to_string(diff));
          //      exist[diff] = true;
          // }
          // actualizar el minimo número de pasos
          best = min( best, 1 + minways(to_string(diff)) );
     }
     return best;
}

// algoritmo memoizado
// TODO

const int N = 1e+8;

int n;
int dp[N];

// algoritmo con programación dinámica
int minwaysdp(string number) {
     // casos base
     dp[0] = 0;
     rep(i, 1, 9) {
          dp[i] = 1;
     }
     // top-down, empezamos desde 10 hasta llegar a 'n'
     rep(x, 10, n) {
          dp[x] = INT_MAX;
          for (auto& digit : to_string(x)) {
               int numdigit = digit - '0'; // char to int
               // notar que aprovechamos las respuestas a subproblemas que ya han sido calculados
               // así nos ahorramos trabajo innecesario
               dp[x] = min(dp[x], 1 + dp[x-numdigit]);
          }
     }
     return dp[n];
}

int main() {
     ios_base::sync_with_stdio(0);
     cin.tie(0);

     // https://cses.fi/problemset/task/1637/

     // probar con un n <= 115, sino el recursivo se demorará demasiado
     // si prueba un n grande, aumente el valor de la variable global 'N'
     // probar con un n <= 10^6, sino el dp se demorará mucho
     cin >> n;

     auto start = chrono::high_resolution_clock::now();
     
     cout << "Respuesta del algoritmo recursivo: " << minways(to_string(n)) << '\n';

     auto end = chrono::high_resolution_clock::now();
     auto executionTime = chrono::duration_cast<chrono::milliseconds>(end - start);
     cout << "Tiempo de ejecución del algoritmo recursivo: " << executionTime.count() << " ms.\n";

     start = chrono::high_resolution_clock::now();

     cout << "Respuesta del algoritmo con programación dinámica: " << minwaysdp(to_string(n)) << '\n';

     end = chrono::high_resolution_clock::now();
     executionTime = chrono::duration_cast<chrono::milliseconds>(end - start);
     cout << "Tiempo de ejecución del algoritmo con programación dinámica: " << executionTime.count() << " ms.\n";

     return 0;
}