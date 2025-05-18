// problem: https://cses.fi/problemset/result/12948953/
/** 
 * author: Nabajyoti
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <queue>
#include <deque>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cassert>
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
        tree.resize(3*n, inf);
    }

    void update(ll node, ll start, ll end, ll id, ll new_val) {
        // node -> node_number, id means the pos in the array
        if (start == end) {
            // cout<<"updating node_num = "<<node<<", id = "<<id<<", with value="<<new_val<<"\n"; // test nabjo
            tree[node] = new_val;
            return;
        }

        ll mid = (start + end) / 2;
        if (id <= mid) {
            update(node * 2, start, mid, id, new_val);
        } else {
            update(node * 2 + 1, mid + 1, end, id, new_val);
        }

        tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
    }

    ll query(ll node, ll start, ll end, const ll &ql, const ll &qr) {
        // ql-> query's left , qr-> query's right
        if (start > qr || end < ql) return inf;
        if (start >= ql && end <= qr) return tree[node];
        ll mid = (start + end) / 2;
        return min(query(node * 2, start, mid, ql, qr), query(node * 2 + 1, mid + 1, end, ql, qr));
    }

    void printTree() {
        cout<<"Printing tree\n";
        for(ll i=1;i<tree.size();i++) {
            cout<<tree[i]<<" ";
        }
        cout<<"\n------\n";
    }
};

void solve() {
    ll n, q;
    cin >> n >> q;
    SegTree t(n);

    for (ll i = 0; i < n; i++) {
        ll x;
        cin >> x;
        t.update(1, 0, n - 1, i, x);
    }

    // t.printTree();

    while (q--) {
        ll p, a, b;
        cin >> p >> a >> b;
        if(p==1) {
            t.update(1, 0, n - 1, a-1, b);
        } else {
            ll ans = t.query(1, 0, n - 1, a-1, b-1);
            cout << ans << "\n";
        }
        // switch (p) {
        //     case 1LL:
        //         // update
        //         t.update(1, 0, n - 1, a, b);
        //         break;
        //     case 2LL:
        //         // range query
        //         ll ans = t.query(1, 0, n - 1, a, b);
        //         cout << ans << "\n";
        //         break;
        //     default:
        //         cout << "hatt bc\n";
        // }
    }
}

signed main() { solve(); }
