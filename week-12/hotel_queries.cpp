/**
 * problem: https://cses.fi/problemset/task/1143/
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

using ll = long long;
using pii = pair<ll, ll>;
const ll N = 1e5 + 5;
const ll mod = 1e9 + 7;
ll inf = 1e2;

struct Node {
    ll num;
};

struct SegTree {
    ll n;
    vector<ll> tree;

    SegTree(ll _n) {
        n = _n;
        tree.resize(3 * n, -inf);
    }

    void update(ll node, const ll& start, const ll& end, ll id, const ll& new_val) {
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

    // this gives the maximum between ql and qr
    ll query(ll node, const ll& start, const ll& end, const ll& ql, const ll& qr) {
        if (start > qr || end < ql) return -inf;
        if (start >= ql && end <= qr) {
            return tree[node];
        }

        ll mid = (start + end) / 2;
        ll left = query(node * 2, start, mid, ql, qr);
        ll right = query(node * 2 + 1, mid + 1, end, ql, qr);
        return merge(left, right);
    }

    ll merge(ll a, ll b) { return max(a, b); }

    void print() {
        cout << "\nPrinting tree-->\n";
        for (ll i = 1; i < tree.size(); i++) {
            cout << tree[i] << " ";
        }
        cout << "\n";
    }
};

// ----- start of the solving ------ //

ll n, m;

ll bin_search(SegTree* tree, ll x) {
    ll ans = -1;
    ll left = 0;
    ll right = n - 1;
    while (left <= right) {
        ll mid = (left + right) / 2;
        ll maxxi = tree->query(1, 0, n - 1, 0, mid);

        if (maxxi >= x) {
            ans = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return ans;
}

void solve() {
    cin >> n >> m;
    vector<ll> v(n);

    SegTree* stree = new SegTree(n);

    for (ll i = 0; i < n; i++) {
        cin >> v[i];
        stree->update(1, 0, n - 1, i, v[i]);
    }

    while (m--) {
        ll x;
        cin >> x;
        ll ind = bin_search(stree, x);
        // cout <<"ans for "<<x<<" is "<< (ind + 1) << "\n";
        cout << (ind + 1) << " ";
        if (ind == -1) continue;
        // cout<<"v["<<ind<<"]"<<" = "<<v[ind]<<"\n";
        v[ind] = v[ind] - x;
        stree->update(1, 0, n - 1, ind, v[ind]);
    }
    cout << "\n";
}

signed main() { solve(); }
