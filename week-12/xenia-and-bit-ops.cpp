/**
 * problem: https://codeforces.com/contest/339/problem/D
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
const ll N = 2e5 + 5;
const ll mod = 1e9 + 7;
ll inf = 1e18;

struct SegTree {
    ll n;
    vector<ll> tree;

    SegTree(ll n) {
        this->n = n;
        tree.resize(3 * n, 0);
    }

    void update(ll node, ll start, ll end, ll id, ll new_val, ll count) {
        // node -> node_number, id means the pos in the array
        if (start == end) {
            // cout<<"updating node_num = "<<node<<", id = "<<id<<", with value="<<new_val<<"\n"; //
            // test nabjo
            tree[node] = new_val;
            return;
        }

        ll mid = (start + end) / 2;
        if (id <= mid) {
            update(node * 2, start, mid, id, new_val, count - 1);
        } else {
            update(node * 2 + 1, mid + 1, end, id, new_val, count - 1);
        }
        if (count % 2) {
            tree[node] = tree[node * 2] | tree[node * 2 + 1];
        } else {
            tree[node] = tree[node * 2] ^ tree[node * 2 + 1];
        }
    }

    ll query(ll node, ll start, ll end, const ll &ql, const ll &qr) {
        // ql-> query's left , qr-> query's right
        if (start > qr || end < ql) return inf;
        // cout << "query: start = " << start << ", end = " << end << "\n";
        if (start >= ql && end <= qr) return tree[node];
        ll mid = (start + end) / 2;
        ll left = query(node * 2, start, mid, ql, qr);
        ll right = query(node * 2 + 1, mid + 1, end, ql, qr);
        return operation(left, right);
    }

    void printTree() {
        cout << "Printing tree\n";
        for (ll i = 1; i < tree.size(); i++) {
            cout << tree[i] << " ";
        }
        cout << "\n------\n";
    }

    ll operation(ll a, ll b) { return a | b; }
};

void solve() {
    ll n, q;
    cin >> n >> q;
    ll m = pow(2, n);
    SegTree t(m);

    for (ll i = 0; i < m; i++) {
        ll x;
        cin >> x;
        t.update(1, 0, m - 1, i, x, n);
    }

    // t.printTree();

    while (q--) {
        ll p, b;
        cin >> p >> b;
        t.update(1, 0, m - 1, p - 1, b, n);

        ll ans = t.query(1, 0, m - 1, 0, m - 1);
        cout << ans << "\n";
    }
}

signed main() { solve(); }
