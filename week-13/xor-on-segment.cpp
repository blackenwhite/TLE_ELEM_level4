/**
 * problem:https://codeforces.com/contest/242/problem/E
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
const int nn = 20;

struct Node {
    vector<pii> bits;

    Node() { bits.resize(nn); }

    /*
    Node(vector<pii> bits){
        this->bits = bits;
    }
     */

    void print() {
        for (ll i = bits.size() - 1; i >= 0; i--) {
            cout << "{" << bits[i].ff << ", " << bits[i].ss << "}";
        }
    };
};

class LazySGT {
   private:
    const ll sz;
    vector<Node> tree;
    vector<ll> lazy;

    void build(int v, int l, int r, const vector<ll>& a) {
        if (l == r) {
            // a[r] is the number to be broken down into bits
            tree[v] = getBits(a[r]);
            return;
        }

        ll m = (l + r) / 2;
        build(2 * v, l, m, a);
        build(2 * v + 1, m + 1, r, a);
        tree[v] = merge(tree[2 * v], tree[2 * v + 1]);
    }

    Node getBits(ll x) {
        Node ans;
        for (int i = nn - 1; i >= 0; i--) {
            if (x & (1 << i)) {
                ans.bits[i].ff++;
            } else {
                ans.bits[i].ss++;
            }
        }
        return ans;
    }

    void apply(int v, int len, const ll& xorr) {
        for (int i = 0; i < nn; i++) {
            if ((1 << i) & xorr) {
                swap(tree[v].bits[i].ff, tree[v].bits[i].ss);
            }
        }
        lazy[v] = lazy[v] ^ xorr;
    }

    Node merge(const Node& a, const Node& b) {
        Node ans;
        for (ll i = nn - 1; i >= 0; i--) {
            ans.bits[i].ff = a.bits[i].ff + b.bits[i].ff;
            ans.bits[i].ss = a.bits[i].ss + b.bits[i].ss;
        }
        return ans;
    }

    void push_down(int v, int l, int r) {
        int m = (l + r) / 2;
        apply(2 * v, m - l + 1, lazy[v]);
        apply(2 * v + 1, r - m, lazy[v]);
        lazy[v] = 0;
    }

    void range_update(int v, int l, int r, int ql, int qr, const ll& x) {
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

    Node range_query(int v, int l, int r, int ql, int qr) {
        if (qr < l || ql > r) {
            Node ans;
            return ans;
        }
        if (l >= ql && r <= qr) return tree[v];
        push_down(v, l, r);
        int m = (l + r) / 2;
        return merge(range_query(2 * v, l, m, ql, qr), range_query(2 * v + 1, m + 1, r, ql, qr));
    }

   public:
    LazySGT(const vector<ll>& a) : sz(a.size()), tree(4 * sz), lazy(4 * sz) {
        build(1, 0, sz - 1, a);
    }

    void range_update(ll ql, ll qr, ll xorr) { range_update(1, 0, sz - 1, ql, qr, xorr); }

    Node range_query(ll ql, ll qr) { return range_query(1, 0, sz - 1, ql, qr); }

    void printTree() {
        printf("Segment Tree State:\n");
        for (ll i = 1; i < tree.size(); i++) {
            cout << i << ": ";
            tree[i].print();
            cout << " and (" << lazy[i] << ")\n";
        }
        printf("\n");
    }
};

// ----- end of utilities ------ //

ll getSum(const Node& t) {
    ll ans = 0;
    // cout<<"gettin sum \n";
    for (ll i = 0; i < t.bits.size(); i++) {
        // ll temp = (t.bits[i].ff);
        // cout<<temp<<" ";
        ans += (1 << i) * (t.bits[i].ff);
    }

    return ans;
}

void solve() {
    ll n, m;
    cin >> n;
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) {
        cin >> a[i];
    }

    LazySGT sgt(a);
    // sgt.printTree();

    cin >> m;
    while (m--) {
        ll type;
        cin >> type;
        if (type == 1) {
            ll l, r;
            cin >> l >> r;
            l--;
            r--;
            Node t = sgt.range_query(l, r);
            cout << getSum(t) << "\n";
        } else {
            ll l, r, xorr;
            cin >> l >> r >> xorr;
            l--;
            r--;
            sgt.range_update(l, r, xorr);
            // sgt.printTree();
        }
    }
}

signed main() { solve(); }
