/**
 * problem: https://codeforces.com/edu/course/2/lesson/4/1/practice/contest/273169/problem/C
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
    ll cnt;

    Node(ll a, ll b) {
        num = a;
        cnt = b;
    }

    Node() {
        num = inf;
        cnt = 0;
    }
};

struct SegTree {
    ll n;  // the number of elements or nodes
    vector<Node> tree;

    SegTree(ll n) {
        this->n = n;
        tree.resize(4 * n);
    }

    void update(ll node, ll start, ll end, ll id, const Node& new_val) {
        // node -> node_number, id means the pos in the array
        if (start == end) {
            // cout<<"updating node_num = "<<node<<", id = "<<id<<", with value="<<new_val<<"\n"; //
            // test nabjo
            tree[node].cnt = new_val.cnt;
            tree[node].num = new_val.num;
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

    Node query(ll node, ll start, ll end, const ll& ql, const ll& qr) {
        // ql-> query's left , qr-> query's right
        if (start > qr || end < ql) return Node();
        // cout << "query: start = " << start << ", end = " << end << "\n";
        if (start >= ql && end <= qr) return tree[node];
        ll mid = (start + end) / 2;
        Node left = query(node * 2, start, mid, ql, qr);
        Node right = query(node * 2 + 1, mid + 1, end, ql, qr);
        return merge(left, right);
    }

    void printTree() {
        cout << "Printing tree\n";
        for (ll i = 1; i < tree.size(); i++) {
            cout << tree[i].num << "," << tree[i].cnt<<" ";
        }
        cout << "\n------\n";
    }

    Node merge(const Node& a, const Node& b) {
        if (a.num == b.num) {
            Node ans;
            ans.num = a.num;
            ans.cnt = (a.cnt + b.cnt);
            return ans;
        } else {
           if(a.num<b.num) {
                return a;
           } else {
                return b;
           }
        }
    }
};

void solve() {
    ll n, q;
    cin >> n >> q;
    SegTree t(n);

    for (ll i = 0; i < n; i++) {
        Node x;
        cin >> x.num;
        x.cnt = 1;
        t.update(1, 0, n - 1, i, x);
    }

    // t.printTree();

    while (q--) {
        ll a, b, c;
        cin >> a >> b >> c;
        if (a == 1) {
            // update
            Node x(c, 1);
            t.update(1, 0, n - 1, b, x);
        } else {
            Node ans = t.query(1, 0, n - 1, b, c);
            cout << ans.num << " " << ans.cnt << "\n";
        }
    }
}

signed main() { solve(); }
