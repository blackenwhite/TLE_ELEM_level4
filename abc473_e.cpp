/*
Problem Statement
You are given a sequence of length 
N consisting of non-negative integers: 
A=(A 
1
​
 ,A 
2
​
 ,…,A 
N
​
 ) .

Define the score of a sequence of length 
1 or more consisting of sequences of non-negative integers, 
S=(S 
1
​
 ,S 
2
​
 ,…,S 
k
​
 ), as the number of sequences 
S 
i
​
  (1≤i≤k) whose sum of elements is divisible by 
K.

Find the maximum possible score of a sequence of non-negative integer sequences obtained by dividing 
A into one or more contiguous subsequences. Here, dividing a sequence 
A of length 
N into one or more contiguous subsequences means choosing a sequence of integers 
l=(l 
1
​
 ,l 
2
​
 ,…,l 
k
​
 ) (1=l 
1
​
 <l 
2
​
 <⋯<l 
k
​
 ≤N) of length 
1 or more, and forming the following 
k sequences.

(A 
l 
i
​
 
​
 ,A 
l 
i
​
 +1
​
 ,…,A 
l 
i+1
​
 −1
​
 ) (1≤i≤k) (Here, let 
l 
k+1
​
 =N+1.)
Constraints
1≤N≤2×10 
5
 
1≤K≤10 
9
 
0≤A 
i
​
 <K
All input values are integers.

*/



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

ll n, K;
vector<ll> v;

void print(vector<ll>& v) {
    cout << "printing vector---->\n";
    for (auto it : v) {
        cout << it << " ";
    }
    cout << "\n";
}

void solve() {
    cin >> n >> K;
    v.assign(n + 1, 0);

    for (ll i = 1; i <= n; i++) {
        cin >> v[i];
        if (i > 0) {
            v[i] += v[i - 1];
        }
        v[i] %= K;
    }

    // print(v);

    map<ll, ll> last_seen;
    vector<ll> dp(n + 1);
    dp[0] = 0;
    last_seen[0] = 0;

    for (ll i = 1; i <= n; i++) {
        ll opt1 = dp[i - 1];
        ll opt2 = 0;
        if (last_seen.find(v[i]) != last_seen.end()) {
            opt2 = dp[last_seen[v[i]]] + 1;
        }
        last_seen[v[i]] = i;
        dp[i] = max(opt1, opt2);
    }

    cout << dp[n] << "\n";
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
