/**
 * problem:
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
using vl = vector<ll>;

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

ll n, lives;


void solve() {
    cin >> n >> lives;

    ld sum = 0;
    for (ll i = 0; i < n; i++) {
        ld a;
        cin >> a;
        sum += a;
    }

    // f[l][c0][c1]; f[0][*][*] = 0 (no lives); f[*][0][0] = 0 (no cards)
    vector<vector<vector<ld>>> f(
        lives + 1, vector<vector<ld>>(n + 1, vector<ld>(n + 1, 0.0)));

    for (ll l = 1; l <= lives; l++) {
        for (ll c0 = 0; c0 <= n; c0++) {
            for (ll c1 = 0; c0 + c1 <= n; c1++) {
                ll unknown = 2 * c0 + c1;
                if (unknown == 0) continue;

                ld v = 0;

                // first flip completes a half seen pair: free match
                if (c1 > 0) v += (ld)c1 / unknown * (1 + f[l][c0][c1 - 1]);

                if (c0 > 0) {
                    // first flip came from a dark pair; second flip is random
                    // among the remaining (unknown-1) cards
                    ld pDark = (ld)(2 * c0) / unknown;
                    ll rest = unknown - 1;

                    // second flip is its partner: lucky match
                    v += pDark / rest * (1 + f[l][c0 - 1][c1]);

                    // second flip is from another dark pair: mismatch,
                    // both pairs become half seen
                    if (c0 >= 2)
                        v += pDark * (2 * c0 - 2) / rest * f[l - 1][c0 - 2][c1 + 2];

                    // second flip completes a half seen pair: mismatch now,
                    // but we know a full pair and grab it next turn (if alive)
                    if (c1 > 0 && l > 1)
                        v += pDark * c1 / rest * (1 + f[l - 1][c0 - 1][c1]);
                }
                f[l][c0][c1] = v;
            }
        }
    }
    printf("%.10Lf\n", f[lives][n][0] * sum / n);
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
