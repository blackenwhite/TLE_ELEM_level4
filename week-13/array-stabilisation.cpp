/**
 * problem: https://codeforces.com/contest/1547/problem/F
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
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

#define ff first
#define ss second

using ll = long long int;
using pii = pair<ll, ll>;
const ll N = 1e5 + 5;
const ll mod = 1e9 + 7;
ll inf = 1e18;
const int nn = 20;

ll __gcd(ll a, ll b) {
    if (a == 0) return b;
    return __gcd(b % a, a);
}

class SGT {
   private:
    const ll sz;
    vector<ll> tree;

    void build(int v, int l, int r, const vector<ll>& a) {
        if (l == r) {
            tree[v] = a[r];
            return;
        }

        int m = (l + r) / 2;
        build(2 * v, l, m, a);
        build(2 * v + 1, m + 1, r, a);
        tree[v] = merge(tree[2 * v], tree[2 * v + 1]);
    }

    ll merge(const ll a, const ll b) { return __gcd(a, b); }

    void update(int v, int l, int r, int qId, const ll& x) {
        if (l == r) {
            tree[v] = x;
            return;
        }

        int m = (l + r) / 2;
        if (qId <= m) {
            update(2 * v, l, m, qId, x);
        } else {
            update(2 * v + 1, m + 1, r, qId, x);
        }
        tree[v] = merge(tree[2 * v], tree[2 * v + 1]);
    }

    ll range_query(int v, int l, int r, int ql, int qr) {
        if (qr < l || ql > r) {
            return 0;
        }
        if (l >= ql && r <= qr) return tree[v];
        int m = (l + r) / 2;
        return merge(range_query(2 * v, l, m, ql, qr), range_query(2 * v + 1, m + 1, r, ql, qr));
    }

   public:
    SGT(const vector<ll>& a) : sz(a.size()), tree(4 * sz) { build(1, 0, sz - 1, a); }

    ll range_query(ll ql, ll qr) {
        ll ans;
        if (qr >= sz) {
            ll res1 = range_query(1, 0, sz - 1, ql, sz - 1);
            ll res2 = range_query(1, 0, sz - 1, 0, (qr % sz));
            ans = merge(res1, res2);
        } else {
            ans = range_query(1, 0, sz - 1, ql, qr);
        }
        // printf(". range query ans between %lld and %lld = %lld\n", ql,qr%sz,ans);
        return ans;
    }

    void printTree() {
        cout << "Printing tree--->\n";
        for (ll i = 0; i < tree.size(); i++) {
            cout << tree[i] << " ";
        }
        cout << "\n*** ---- ****\n";
    }
};

// ----- end of utilities ------ //

bool check(ll k, SGT& sgt, ll n) {
    // cout<<"Checking for k = "<<k<<"\n";
    unordered_set<ll> st;
    for (ll i = 0; i < n; i++) {
        ll ql = i;
        ll qr = (i + k);
        ll res = sgt.range_query(ql, qr);
        st.insert(res);
        // cout<<" -- set size = "<<st.size()<<"\n";
        if (st.size() > 1) return false;
    }
    // cout<<"---returning true\n";
    return true;
}

void solve() {
    ll n;
    cin >> n;
    vector<ll> a(n);
    bool all_equal = true;
    for (ll i = 0; i < n; i++) {
        cin >> a[i];
    }

    for (ll i = 0; i < n; i++) {
        if (a[i] != a[(i + 1) % n]) all_equal = false;
    }

    if (all_equal) {
        cout << 0 << "\n";
        return;
    }

    SGT sgt(a);
    // sgt.printTree();
    // binary search
    ll lo = 1, hi = n - 1;
    ll ans = n - 1;
    while (lo <= hi) {
        ll mid = (lo + hi) / 2;
        if (check(mid, sgt, n)) {
            ans = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    cout << ans << "\n";
}

ll t;

signed main() {
    cin >> t;
    while (t--) {
        solve();
    }
}
