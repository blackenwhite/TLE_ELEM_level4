/**
 * problem: CSES Range Updates and Sums
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

enum QueryType { ADD, SET, NONE };

struct Query {
    QueryType type = NONE;
    ll val = 0;
};

template <typename T>
class LazySGT {
   private:
    const ll sz;
    vector<T> tree;
    vector<Query> lazy;

    void build(int v, int l, int r, const vector<T>& a) {
        if (l == r) {
            tree[v] = a[r];
        } else {
            int m = (l + r) / 2;
            build(2 * v, l, m, a);
            build(2 * v + 1, m + 1, r, a);
            tree[v] = tree[2 * v] + tree[2 * v + 1];
        }
    }

    void apply(int v, int len, const Query& x) {
        if (x.type == ADD) {
            if (lazy[v].type != SET) {
                lazy[v] = Query{ADD, lazy[v].val + x.val};
            } else {
                lazy[v] = Query{SET, lazy[v].val + x.val};
            }
            tree[v] += x.val * len;
        } else if (x.type == SET) {
            tree[v] = x.val * len;
            lazy[v] = x;
        }
    }

    void push_down(int v, int l, int r) {
        int m = (l + r) / 2;
        apply(2 * v, m - l + 1, lazy[v]);
        apply(2 * v + 1, r - m, lazy[v]);
        lazy[v] = Query();
    }

    void range_update(int v, int l, int r, int ql, int qr, const Query& x) {
        // cout<<"hola\n";
        if (qr < l || ql > r) return;
        if (l >= ql && r <= qr)
            apply(v, r - l + 1, x);
        else {
            push_down(v, l, r);
            int m = (l + r) / 2;
            range_update(2 * v, l, m, ql, qr, x);
            range_update(2 * v + 1, m + 1, r, ql, qr, x);
            tree[v] = tree[2 * v] + tree[2 * v + 1];
        }
    }

    T range_sum(int v, int l, int r, int ql, int qr) {
        if (qr < l || ql > r) return 0;
        if (l >= ql && r <= qr) return tree[v];
        push_down(v, l, r);
        int m = (l + r) / 2;
        return range_sum(2 * v, l, m, ql, qr) + range_sum(2 * v + 1, m + 1, r, ql, qr);
    }

   public:
    LazySGT(const vector<T>& a) : sz(a.size()), tree(4 * sz), lazy(4 * sz) {
        build(1, 0, sz - 1, a);
    }

    void range_update(int ql, int qr, const Query& x) { range_update(1, 0, sz - 1, ql, qr, x); }

    T range_sum(int ql, int qr) { return range_sum(1, 0, sz - 1, ql, qr); }

    void printTree() {
        cout<<"Printing tree--->\n";
        for(ll i=1;i<tree.size();i++) {
            cout<<tree[i]<<" - ";
        }
    }
};

// ----- end of utilities ------ //

void solve() {
    ll n, q;
    cin >> n >> q;
    vector<ll> v(n);

    for (ll i = 0; i < n; i++) {
        cin >> v[i];
    }
    // cout<<"hiii";

    LazySGT<ll> laz(v);

    while (q--) {
        ll type, a, b;
        cin >> type >> a >> b;
        a--;
        b--;
        if (type == 1) {
            ll x;
            cin >> x;
            // cout<<"hola\n"; // nabjo test
            laz.range_update(a, b, Query{ADD, x});
            
        } else if (type == 2) {
            ll x;
            cin >> x;
            laz.range_update(a, b, Query{SET, x});
            // cout<<"halo\n"; // nabjo test
        } else {
            cout << laz.range_sum(a, b) << "\n";
        }
    }
}

signed main() { solve(); }
