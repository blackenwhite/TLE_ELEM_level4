/**
 * problem: https://atcoder.jp/contests/abc476/tasks/abc476_e
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

ll n, m;
vector<ll> v;

void print(vector<ll>& v) {
    cout << "printing vector---->\n";
    for (auto it : v) {
        cout << it << " ";
    }
    cout << "\n";
}

struct minSegTree {
    ll n;
    vector<pii> tree;  // {max, id of max}

    minSegTree(ll n) {
        this->n = n;
        tree.assign(4 * n + 2, {inf, -1});
    }

    pii merge(const pii& a, const pii& b) {
        pii ans;
        if (a.ff <= b.ff) {
            ans = {a.ff, a.ss};
        } else {
            ans = {b.ff, b.ss};
        }
        return ans;
    }

    void update(ll node, ll start, ll end, ll id, pii val) {
        if (start == end) {
            tree[node] = val;
            return;
        }

        ll mid = (start + end) / 2;
        if (id <= mid) {
            update(2 * node, start, mid, id, val);
        } else {
            update(2 * node + 1, mid + 1, end, id, val);
        }

        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }

    pii query(ll node, ll start, ll end, const ll& ql, const ll& qr) {
        if (start > qr || end < ql) return {inf, -1};
        if (start >= ql && end <= qr) {
            return tree[node];
        }
        ll mid = (start + end) / 2;
        pii left = query(2 * node, start, mid, ql, qr);
        pii right = query(2 * node + 1, mid + 1, end, ql, qr);
        pii ans = merge(left, right);
        return ans;
    }
};

struct maxSegTree {
    ll n;
    vector<pii> tree;

    maxSegTree(ll n) {
        this->n = n;
        tree.assign(4 * n + 1, {-inf, -1});
    }

    pii merge(const pii& a, const pii& b) {
        pii ans;
        if (a.ff >= b.ff) {
            ans = {a.ff, a.ss};
        } else {
            ans = {b.ff, b.ss};
        }
        return ans;
    }

    void update(ll node, ll start, ll end, ll id, pii val) {
        if (start == end) {
            tree[node] = val;
            return;
        }

        ll mid = (start + end) / 2;
        if (id <= mid) {
            update(2 * node, start, mid, id, val);
        } else {
            update(2 * node + 1, mid + 1, end, id, val);
        }
        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }

    pii query(ll node, ll start, ll end, const ll& ql, const ll& qr) {
        if (start > qr || end < ql) return {-inf, -1};
        if (start >= ql && end <= qr) {
            return tree[node];
        }

        ll mid = (start + end) / 2;
        pii left = query(2 * node, start, mid, ql, qr);
        pii right = query(2 * node + 1, mid + 1, end, ql, qr);
        return merge(left, right);
    }
};

void solve() {
    cin >> n >> m;
    v.assign(n, 0);

    minSegTree minT(n);
    maxSegTree maxT(n);

    for (ll i = 0; i < n; i++) {
        cin >> v[i];
        minT.update(1, 0, n - 1, i, {v[i], i});
        maxT.update(1, 0, n - 1, i, {v[i], i});
    }

    while (m--) {
        ll L, R;
        cin >> L >> R;
        L--;
        R--;

        pii maxx = maxT.query(1, 0, n - 1, L, R);
        pii minn = minT.query(1, 0, n - 1, L, R);

        ll id1 = maxx.ss;
        ll id2 = minn.ss;

        swap(v[id1], v[id2]);
        minT.update(1, 0, n - 1, id1, {v[id1], id1});
        maxT.update(1, 0, n - 1, id1, {v[id1], id1});

        minT.update(1, 0, n - 1, id2, {v[id2], id2});
        maxT.update(1, 0, n - 1, id2, {v[id2], id2});
    }

    for (ll i = 0; i < n; i++) {
        cout << v[i] << " ";
    }
    cout << "\n";
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
