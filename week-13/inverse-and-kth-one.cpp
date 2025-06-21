/**
 * problem: https://codeforces.com/edu/course/2/lesson/5/3/practice/contest/280799/problem/B
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
using ppi = pair<ll, pii>;
const ll N = 1e5 + 5;
const ll mod = 1e9 + 7;
ll inf = 1e18;

// T = pair<ll,pii>
// first = sum
// second.first = ones
// second.second = zeros

struct Node {
    ll sum = 0;
    ll ones = 0;
    ll zeros = 0;

    Node() {
        sum = 0;
        ones = 0;
        zeros = 0;
    }

    void print() {
        cout << "printing node ==== ";
        cout << sum << " " << ones << " " << zeros << "\n";
    }
};

class LazySGT {
   private:
    const ll sz;
    vector<Node> tree;
    vector<ll> lazy;

    void build(int v, int l, int r, const vector<ll>& a) {
        if (l == r) {
            tree[v].zeros = 1;
            return;
        }

        ll m = (l + r) / 2;
        build(2 * v, l, m, a);
        build(2 * v + 1, m + 1, r, a);
        tree[v] = merge(tree[2 * v], tree[2 * v + 1]);
    }

    void apply(int v, int len, const ll rev) {
        if (rev) {
            reverse(tree[v]);
            lazy[v] = lazy[v] ^ 1;
        }
    }

    void reverse(Node& node) {
        ll ones = node.ones;
        ll zeros = node.zeros;
        node.ones = zeros;
        node.zeros = ones;

        node.sum = node.ones;
    }

    Node merge(const Node& a, const Node& b) {
        Node ans;
        ans.sum = a.sum + b.sum;
        ans.ones = a.ones + b.ones;
        ans.zeros = a.zeros + b.zeros;
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

    void range_update(ll ql, ll qr) { range_update(1, 0, sz - 1, ql, qr, 1); }

    Node range_query(ll ql, ll qr) { return range_query(1, 0, sz - 1, ql, qr); }

    void printTree() {
        printf("Segment Tree State:\n");
        for (ll i = 1; i < tree.size(); i++) {
            printf("{%lld, %lld, %lld},(%lld) -- ", tree[i].sum, tree[i].ones, tree[i].zeros,
                   lazy[i]);
        }
        printf("\n");
    }
};

// ----- end of utilities ------ //

void solve() {
    ll n, m;
    cin >> n >> m;
    vector<ll> a(n, 0);

    LazySGT sgt(a);
    // sgt.printTree();

    while (m--) {
        ll type;
        cin >> type;
        if (type == 1) {
            ll l, r;
            cin >> l >> r;
            r--;
            sgt.range_update(l, r);
            // sgt.printTree();
        } else {
            ll k;
            cin >> k;
            k++;
            // binary search
            ll lo = 0, hi = n - 1;
            ll ans = n;
            while (lo <= hi) {
                ll mid = (lo + hi) / 2;
                ll sum = (sgt.range_query(0, mid)).sum;
                if (sum >= k) {
                    ans = mid;
                    hi = mid - 1;
                } else {
                    lo = mid + 1;
                }
            }
            cout << ans << "\n";
        }
    }
}

signed main() { solve(); }
