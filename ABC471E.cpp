/**
 * problem:https://atcoder.jp/contests/abc471/tasks/abc471_e

Problem Statement
There are 
N balls numbered 
1 to 
N. Ball 
i has an integer 
A 
i
​
  written on it.

For a way of choosing some balls from the 
N balls, define the score of that choice as the square of the sum of the numbers written on the chosen balls.

Find the sum, modulo 
998244353, of the scores of all 
( 
K
N
​
 ) ways of choosing 
K balls from the 
N balls.

Constraints
1≤K≤N≤2×10 
5
 
1≤A 
i
​
 ≤10 
9
 
All input values are integers.
 
 * author: Nabajyoti
 */
#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

#define ff first
#define ss second
#define pb push_back

using ll = long long int;
using ld = long double;
using pii = pair<ll, ll>;
const ll N = 2e5 + 5;
// const ll mod = 1e9 + 7;
const ll mod = 998244353;
ll inf = 1e18;
using i128 = __int128;
using vl = vector<ll>;

ll gcd(ll a, ll b) {
    if (a < b) return gcd(b, a);
    if (b == 0) return a;
    return gcd(a % b, b);
}

ll mult(ll a, ll b)  // O(1)
{
    return ((a % mod) * (b % mod)) % mod;
}

ll exponent(ll a, ll b) {
    ll ans = 1;
    while (b > 0) {
        if (b % 2 == 1) {
            ans = (ans * a) % mod;
        }
        a = (a * a) % mod;
        b /= 2;
    }
    return ans;
}

ll inverse(ll a) { return exponent(a, mod - 2); }

ll fact[N];
ll invFact[N];

void init() {
    fact[0] = 1;
    for (int i = 1; i < N; i++) {
        fact[i] = mult(i, fact[i - 1]);
    }

    invFact[N - 1] = inverse(fact[N - 1]);
    for (int i = N - 2; i >= 0; i--) {
        invFact[i] = mult(invFact[i + 1], i + 1);
    }
}

ll nCr(ll n, ll r) {
    if (n < 0 || r < 0 || r > n) return 0;
    return mult(fact[n], mult(invFact[n - r], invFact[r]));
}

ll add(ll a, ll b) {  // O(1)
    ll ans = (a + b);
    if (ans >= mod) ans -= mod;
    if (ans < 0) ans += mod;
    return ans;
}

long long power(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

long long modInverse(long long a, long long mod) { return power(a, mod - 2, mod); }

// ----- end of utilities ------ //

ll n, K;
vector<ll> a;

void solve() {
    cin >> n >> K;
    init();
    a.assign(n, 0);

    for (ll i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<ll> prefixSum(n);
    prefixSum[0] = a[0];

    for (ll i = 1; i < n; i++) {
        prefixSum[i] = prefixSum[i - 1] + a[i];
    }

    ll cumSum = 0;
    for (ll i = n - 1; i >= 1; i--) {
        cumSum = add(cumSum, mult(a[i], prefixSum[i - 1]));
    }

    ll sum_squares = 0;
    for (ll i = 0; i < n; i++) {
        sum_squares = add(sum_squares, mult(a[i], a[i]));
    }

    // ans = (n-1)C(k-1)*(sum of squares of ai) + 2*(n-2)C(k-2)*(sum of ai*aj)
    ll ans = 0;
    ans = add(ans, mult(nCr(n - 1, K - 1), sum_squares));
    ans = add(ans, mult(2, mult(nCr(n - 2, K - 2), cumSum)));

    cout << ans << "\n";
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}
