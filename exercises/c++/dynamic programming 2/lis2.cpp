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

int n;
vi arr;
vi dp;
vi solution;

int main() {
     ios_base::sync_with_stdio(0);
     cin.tie(0);

     // leer el #elementos
     cin >> n;

     arr.resize(n+1);
     dp.resize(n+1, 1);
     dp[0] = 0; // indexamos desde 1, dp[0] no significará nada

     // leer el arreglo
     rep(i, 1, n) {
          cin >> arr[i];
     }

     // así se vería el dp sin la construcción de la solución:
     int lisLength = INT_MIN;
     // rep(i, 2, n) {
     //      rep(j, 1, i) {
     //           if (arr[j] < arr[i]) {
     //                lisLength = max(lisLength, dp[i]);
     //                dp[i] = max(dp[i], 1 + dp[j]);
     //           }
     //      }
     // }

     bool firstTime = false;

     // así se vería el dp con la consturcción de la solución en simultáneo con el dp
     rep(i, 2, n) {
          rep(j, 1, i) {
               if (arr[j] < arr[i]) {
                    if (1 + dp[j] > dp[i]) {
                         dp[i] = 1 + dp[j];
                         if (lisLength < dp[i]) {
                              if (!firstTime) {
                                   // si estamos construyendo la solucion por 1era vez, tambien tenemos que insertar
                                   // el elemento en arr[j], ya que es el 1er elemento del LIS
                                   solution.PB(arr[j]);
                                   firstTime = true;
                              }
                              solution.PB(arr[i]);
                              lisLength = dp[i];
                         }
                    }
               }
          }
     }

     // cout << "dp: ";
     // print(dp); // nota: el 0 que esto printea no significa nada, ya que indexamos desde 1 dp[0] no tiene significado

     cout << "LIS: ";
     print(solution);

     cout << "len(LIS): " << lisLength << endl;

     return 0;
}