/**
 * problem:
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
#define pb push_back

using ll = long long int;
using ld = long double;
using pii = pair<ll, ll>;
const ll N = 2e5 + 5;
const ll mod = 1e9 + 7;
ll inf = 1e18;
using vl = vector<ll>;

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
    void apply(int v, int len, const T mult) {
        tree[v] = (tree[v] * mult) % mod;
        lazy[v] = (lazy[v] * mult) % mod;
    }

    T merge(T a, T b) { return (a + b) % mod; }

    void push_down(int v, int l, int r) {
        int m = (l + r) / 2;
        apply(2 * v, m - l + 1, lazy[v]);
        apply(2 * v + 1, r - m, lazy[v]);
        lazy[v] = 1;
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
        if (qr < l || ql > r) return 0;
        if (l >= ql && r <= qr) return tree[v];
        push_down(v, l, r);
        int m = (l + r) / 2;
        return merge(range_query(2 * v, l, m, ql, qr), range_query(2 * v + 1, m + 1, r, ql, qr));
    }

   public:
    LazySGT(const vector<T>& a) : sz(a.size()), tree(4 * sz), lazy(4 * sz, 1) {
        build(1, 0, sz - 1, a);
    }

    void range_update(int ql, int qr, T add) { range_update(1, 0, sz - 1, ql, qr, add); }

    T range_sum(int ql, int qr) { return range_query(1, 0, sz - 1, ql, qr); }

    void printTree() {
        cout << "Printing tree ---> \n";
        for (ll i = 1; i < tree.size(); i++) {
            cout << tree[i] << "(" << lazy[i] << ")" << ", ";
        }
        cout << "\n";
    }
};

// ----- end of utilities ------ //
ll n, m;

struct Pipe {
    ll a;
    ll b;
    ll c;
    ll f;
};

struct Edge {
    ll v;
    ll c;
    ll f;
};

vector<Pipe> pipes;

// we are going to maximise the d
struct State {
    ld x;  // x=flow_rate / cost
    ll node;
    ll total_cost;
    ll min_fl;  // min flow rate upto now

    bool operator>(const State& other) const { return x < other.x; }
};

void solve() {
    cin >> n >> m;
    pipes.resize(m);

    for (ll i = 0; i < m; i++) {
        cin >> pipes[i].a >> pipes[i].b >> pipes[i].c >> pipes[i].f;
    }

    vector<vector<Edge>> adj(n + 1);
    for (auto pipe : pipes) {
        ll u = pipe.a, v = pipe.b, wt = pipe.c, f = pipe.f;
        adj[u].pb({v, wt, f});
        adj[v].pb({u, wt, f});
    }

    vector<ld> dist(n + 1, -1);

    priority_queue<State, vector<State>, greater<State>> pq;

    dist[1] = 0;
    pq.push({0, 1, 0, inf});

    while (!pq.empty()) {
        auto [x, u, cost, fl] = pq.top();
        pq.pop();

        if (x < dist[u]) continue;

        if (u == n) {
            cout << (ll)(x * 1e6) << "\n";
            return;
        }

        for (auto& [v, w, f] : adj[u]) {
            ll nxtCost = w + cost;
            ll nextFl = (fl == inf) ? f : min(fl, f);
            ld nx = (nextFl * 1.0) / nxtCost;

            if (dist[v] < nx) {
                dist[v] = nx;
                pq.push({nx, v, nxtCost, nextFl});
            }
        }
    }
}

signed main() {
    freopen("pump.in", "r", stdin);
    freopen("pump.out", "w", stdout);

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
}
