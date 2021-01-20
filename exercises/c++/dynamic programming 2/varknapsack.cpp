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
#define compress(v) sort(all(v)), (v).erase(unique(all((v))), v.end())

typedef unsigned long long ull;
typedef long double ld;
typedef long long ll;
typedef vector<ll> vll;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

int n;
int totalSum;
vi w;
vector<vi> possible;

int main() {
     ios_base::sync_with_stdio(0);
     cin.tie(0);

     cin >> n;
     w.resize(n+1);

     rep(i, 1, n) {
          cin >> w[i];
          totalSum += w[i];
     }

     possible.resize(totalSum+1, vi(n+1, false));

     possible[0][0] = true;

     rep(k, 1, n) { // usando los primeros 'k' pesos
          rep(x, 0, totalSum) { // itero sobre todas las sumas posibles
               if (x - w[k] >= 0) {
                    possible[x][k] = possible[x][k] | possible[x-w[k]][k-1];
                    possible[x][k] = possible[x][k] | possible[x][k-1];
               }
               else {
                    possible[x][k] = possible[x][k] | possible[x][k-1];
               }
          }
     }

     rep(k, 0, n) {
          rep(x, 0, totalSum) {
               cout << possible[x][k] << " ";
          }
          cout << endl;
     }

     return 0;
}