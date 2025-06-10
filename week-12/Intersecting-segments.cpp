/**
 * problem: https://codeforces.com/edu/course/2/lesson/4/3/practice/contest/274545/problem/C
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


struct SegTree {
    // sum segment tree
    ll n;
    vector<ll> tree;

    SegTree(ll _n) {
        n = _n;
        tree.resize(4 * n + 5);
    }

    SegTree() {}  // def constructor

    void update(ll node, const ll& start, const ll& end, ll id, ll new_val) {
        if (start == end) {
            tree[node] = new_val;
            return;
        }

        ll mid = (start + end) / 2;
        if (id <= mid) {
            update(node * 2, start, mid, id, new_val);
        } else {
            update(node * 2 + 1, mid + 1, end, id, new_val);
        }
        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

    // this gives the sum between ql and qr
    ll query(ll node, const ll& start, const ll& end, const ll& ql, const ll& qr) {
        if (start > qr || end < ql) return 0;
        if (start >= ql && end <= qr) {
            return tree[node];
        }

        ll mid = (start + end) / 2;
        ll left = query(node * 2, start, mid, ql, qr);
        ll right = query(node * 2 + 1, mid + 1, end, ql, qr);
        return merge(left, right);
    }

    ll merge(ll n1, ll n2) {
        return n1+n2;
    }

    void print() {
        cout << "\nPrinting tree-->\n";
        for (ll i = 1; i < tree.size(); i++) {
            cout << tree[i]<< " ";
        }
        cout << "\n";
    }
};

// ----- end of utilities ------ //

void solve() {
    ll n;
    cin >> n;
    vector<ll> v(2 * n);
    for (ll i = 0; i < 2 * n; i++) {
        cin >> v[i];
    }

    SegTree* sgt = new SegTree(2 * n);

    unordered_map<ll, ll> last_seen;
    unordered_map<ll, ll> ans;

    for (ll i = 0; i < 2 * n; i++) {
        ll x = v[i];
        if (last_seen.find(x) != last_seen.end()) {
            ll left = last_seen[x];
            ll pairs = sgt->query(1, 0, 2 * n - 1, left, i);
            ans[x] = (i-left-1)-2*pairs;
            sgt->update(1, 0, 2 * n - 1, left, 1);
        } else {
            last_seen[x] = i;
        }
    }

    for (ll i = 1; i <= n; i++) {
        cout << ans[i] << " ";
    }
}

signed main() { solve(); }
