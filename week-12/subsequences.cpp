/**
 * problem: https://codeforces.com/contest/597/problem/C
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
        tree.resize(3 * n, 0);
    }

    SegTree() {}

    void initialise(ll nn) {
        n = nn;
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

    ll merge(ll a, ll b) { return a + b; }

    void print() {
        cout << "\nPrinting tree-->\n";
        for (ll i = 1; i < tree.size(); i++) {
            cout << tree[i] << " ";
        }
        cout << "\n";
    }
};

// ----- end of utilities ------ //

ll n, k;
vector<ll> a;
vector<SegTree> vt;

void solve() {
    cin >> n >> k;
    k++;
    a.resize(n);
    for (ll i = 0; i < n; i++) {
        cin >> a[i];
    }

    vt.resize(k + 1);
    for (ll i = 0; i <= k; i++) {
        vt[i].initialise(n + 1);
    }

    ll dp[n + 1][k + 1];
    memset(dp, 0, sizeof(dp));

    // process the elements one by one
    for (ll i = 0; i < n; i++) {
        for (ll k1 = 1; k1 <= k; k1++) {
            ll elem = a[i];
            ll temp;  // dp[elem][k1] = sum(dp[elem-1][k1-1] + ....... + dp[1][k1-1])

            if (k1 == 1) {
                temp = 1;
                dp[elem][1] = 1;
                vt[k1].update(1, 0, n, elem, temp);
                continue;
            }

            temp = vt[k1 - 1].query(1, 0, n, 1, elem - 1);
            dp[elem][k1] = temp;
            // cout << "dp[" << elem << "][" << k1 << "]" << " = " << temp << "\n";
            vt[k1].update(1, 0, n, elem, temp);
        }
    }

    ll ans = 0;
    for (ll i = 0; i < n; i++) {
        ll elem = a[i];
        ans += dp[elem][k];
    }
    cout << ans;
}

signed main() { solve(); }
