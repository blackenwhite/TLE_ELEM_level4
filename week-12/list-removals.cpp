/**
 * problem: https://cses.fi/problemset/task/1749/
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
ll inf = 1e18;

struct Node {
    ll num;
};

struct SegTree {
    ll n;
    vector<ll> tree;

    SegTree(ll _n) {
        n = _n;
        tree.resize(3 * n, 0);
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

    // this gives the number of elements that are removed between ql and qr
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

    ll merge(ll a, ll b) { return a + b; }
};

ll n;

ll bin_search(SegTree* tree, ll pi) {
    ll ans = n;
    ll left = 0;
    ll right = n - 1;
    while (left <= right) {
        ll mid = (left + right) / 2;
        ll removed = tree->query(1, 0, n - 1, 0, mid);
        ll number_of_elements_present = mid + 1 - removed;

        if (number_of_elements_present >= pi) {
            ans = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return ans;
}

void solve() {
    cin >> n;
    vector<ll> v(n);

    for (ll i = 0; i < n; i++) {
        cin >> v[i];
    }

    SegTree* stree = new SegTree(n);

    // process the queries
    for (ll i = 0; i < n; i++) {
        ll pi;
        cin >> pi;
        ll ind = bin_search(stree, pi);
        if (ind >= n) {
            cout << "not possible\n";
            return;
        }
        cout << v[ind] << " ";
        stree->update(1, 0, n - 1, ind, 1);
    }
    cout << "\n";
}

signed main() { solve(); }
