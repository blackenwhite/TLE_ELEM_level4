/**
 * problem: https://codeforces.com/edu/course/2/lesson/5/3/practice/contest/280799/problem/C
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

template <typename T>
class LazySGT {
   private:
    const ll sz;
    vector<T> tree;
    vector<T> lazy;

    void build(int v, int l, int r, const vector<T>& a) {
        if (l == r) {
            tree[v] = a[r];
            return;
        }

        ll m = (l + r) / 2;
        build(2 * v, l, m, a);
        build(2 * v + 1, m + 1, r, a);
        tree[v] = merge(tree[2 * v], tree[2 * v + 1]);
    }

    /** applies lazy update to tree[v], places update at lazy[v] */
    void apply(int v, int len, const T add) {
        tree[v] += add;
        lazy[v] += add;
    }

    T merge(T a, T b) { return max(a, b); }

    void push_down(int v, int l, int r) {
        int m = (l + r) / 2;
        apply(2 * v, m - l + 1, lazy[v]);
        apply(2 * v + 1, r - m, lazy[v]);
        lazy[v] = 0;
    }

    void range_update(int v, int l, int r, int ql, int qr, const T& x) {
        if (qr < l || ql > r) return;
        if (l >= ql && r <= qr) {
            apply(v, r - l + 1, x);
            return;
        }
        push_down(v, l, r);
        int m = (l + r) / 2;
        range_update(2 * v, l, m, ql, qr, x);
        range_update(2 * v + 1, m + 1, r, ql, qr, x);
        tree[v] = merge(tree[2 * v], tree[2 * v + 1]);
    }

    T range_query(int v, int l, int r, int ql, int qr) {
        if (qr < l || ql > r) return INT_MIN;
        if (l >= ql && r <= qr) return tree[v];
        push_down(v, l, r);
        int m = (l + r) / 2;
        return merge(range_query(2 * v, l, m, ql, qr), range_query(2 * v + 1, m + 1, r, ql, qr));
    }

   public:
    LazySGT(const vector<T>& a) : sz(a.size()), tree(4 * sz), lazy(4 * sz) {
        build(1, 0, sz - 1, a);
    }

    void range_update(int ql, int qr, T add) { range_update(1, 0, sz - 1, ql, qr, add); }

    T range_max(int ql, int qr) { return range_query(1, 0, sz - 1, ql, qr); }

    void printTree() {
        cout << "Printing tree ---> \n";
        for (ll i = 1; i < tree.size(); i++) {
            cout << tree[i] << "(" << lazy[i] << ")" << ", ";
        }
        cout << "\n";
    }
};

// ----- end of utilities ------ //

void solve() {
    ll n, m;
    cin >> n >> m;
    vector<ll> a(n);
    LazySGT<ll> sgt(a);

    while (m--) {
        ll type;
        cin >> type;
        if (type == 1) {
            ll l, r, add;
            cin >> l >> r >> add;
            r--;
            sgt.range_update(l, r, add);
        } else {
            ll l, x;
            cin>>x>>l;
            // ---- binary search ----------
            ll lo = l, hi = n - 1;
            ll ans = n;
            while (lo <= hi) {
                ll mid = (lo + hi) / 2;
                ll rangeMax = sgt.range_max(lo, mid);
                if (rangeMax >= x) {
                    ans = mid;
                    hi = mid - 1;
                } else {
                    lo = mid + 1;
                }
            }

            // ---- end: binary search ------

            if (ans == n) {
                cout << -1 << "\n";
            } else {
                cout << ans << "\n";
            }
        }
    }
}

signed main() { solve(); }
