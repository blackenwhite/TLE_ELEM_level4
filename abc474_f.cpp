/**
 * problem: https://atcoder.jp/contests/abc474/tasks/abc474_f

 
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

ll dirs[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

// ----- end of utilities ------ //

ll n;
vector<ll> v;
vector<ll> a, b;

void print(vector<ll>& v) {
    cout << "printing vector---->\n";
    for (auto it : v) {
        cout << it << " ";
    }
    cout << "\n";
}

void solve() {
    cin >> n;
    v.assign(n + 1, 0);
    a.assign(n + 1, 0);
    b.assign(n + 1, 0);

    for (ll i = 1; i <= n; i++) {
        cin >> v[i];
    }

    ll low = -inf, high = inf;

    for (ll i = n; i > 0; i--) {
        a[i] = 1;
        b[i] = -v[i];

        for (ll j = 2 * i; j <= n; j += i) {
            a[i] -= a[j];
            b[i] -= b[j];
        }

        if (a[i] < 0) {
            // X <= floor(B/A)
            ll fl = b[i] / (-a[i]);
            high = min(high, fl);
        } else if (a[i] > 0) {
            // x>= ceil(-b[i]/a[i])
            ll cl = (ll)(ceil(-1.0 * b[i] / a[i]));
            low = max(low, cl);
        } else {
            // a = 0,
            if (b[i] < 0) {
                cout << -1 << "\n";
                return;
            }
        }
    }

    if (low > high) {
        cout << -1 << "\n";
        return;
    }

    cout << low - v[1] << "\n";
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
