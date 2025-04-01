// author: nabajyoti
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<ll, ll>;

class DSU {
    vector<ll> par, rnk;
    vector<ll> sup;  // stores the supervisor for each node

   public:
    DSU(ll n) {
        par.resize(n + 1);
        rnk.resize(n + 1);
        sup.resize(n + 1);

        for (ll i = 0; i <= n; i++) {
            par[i] = i;
            rnk[i] = 1;
        }
    }

    int find_parent(ll m) {
        if (par[m] == m) return m;
        return par[m] = find_parent(par[m]);
    }

    /*
         -- inline comment shift+option+A
        ll find_parent(ll m) {
        if (par[m] == m) return m;
        return find_parent(par[m]);
    } */

    void union_sets(ll a, ll b) {
		sup[a] = b;
        a = find_parent(a);
        b = find_parent(b);
        if (a != b) {
            if (rnk[a] < rnk[b]) swap(a, b);
            par[b] = a;
            rnk[a] += rnk[b];
        }
    }

    bool isConnected(ll a, ll b) {
        a = find_parent(a);
        b = find_parent(b);
        return a == b;
    }

    ll getPar(ll x) { return sup[x]; }
};

vector<vector<pii>>
    adj;  // node ->[ {supervisor1, cost1}, {supervisor2, cost2}, .... {supervisorN, costN} ]

struct edge {
    ll a;
    ll b;
    ll wt;

    edge(ll _a, ll _b, ll _wt) {
        a = _a;
        b = _b;
        wt = _wt;
    }

    edge() {}
};

void solve() {
    ll n;
    cin >> n;
    vector<ll> qual(n);

    for (ll i = 0; i < n; i++) {
        cin >> qual[i];
    }

    adj.resize(n + 1);
    ll m;
    cin >> m;

    vector<edge> edges;

    for (int i = 0; i < m; i++) {
        ll a, b, c;
        cin >> a >> b >> c;
        adj[b].push_back({a, c});
        edges.push_back(edge(b, a, c));
    }

    // check for infeasibility
    ll count = 0;  // count of nodes that have 0 supervisor
    for (ll i = 1; i <= n; i++) {
        if (adj[i].size() == 0) count++;
    }

    if (count > 1) {
        cout << -1 << "\n";
        return;
    }

    // make a MST using Kruskal's algo

    DSU dsu(n);
    sort(edges.begin(), edges.end(), [](const edge &e1, const edge &e2) { return e1.wt < e2.wt; });

    ll cost = 0;

    for (auto it : edges) {
        ll node = it.a;
        ll par = it.b;
        ll wt = it.wt;
        if (dsu.getPar(node) == 0) {
            dsu.union_sets(node, par);
            cost += wt;
        }
    }
    cout << cost << "\n";
}

signed main() { solve(); }
