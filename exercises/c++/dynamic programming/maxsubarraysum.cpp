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

ll n;

const int N = 2e+6; // 2 x 10^6
ll arr[N];
ll dp[N];

int main() {
     ios_base::sync_with_stdio(0);
     cin.tie(0);

     // https://cses.fi/problemset/result/1226260/

     cin >> n;

     rep(i, 1, n) {
          cin >> arr[i];
     }

     // dp[i] guarda el max subarray sum de arr[] hasta el índice 'i'

     // caso base, el max subarray de los 1-primeros elementos, es arr[1]
     dp[1] = arr[1];
     ll maxsubarraysum = dp[1];
     rep(i, 2, n) {
          // si el actual elemento es mayor al max subarray sum que hemos estado acumulando, 
          // entonces emepzamos un nuevo max subarray sum
          dp[i] = max(arr[i], dp[i-1]+arr[i]);
          maxsubarraysum = max(maxsubarraysum, dp[i]);
     }

     cout << maxsubarraysum;

     return 0;
}