#include <bits/stdc++.h>
using namespace std;
// author: Nabajyoti
using ll = long long;
using pii = pair<ll, ll>;
const ll N = 2e5 + 5;

/*
class DSU {
    vector<ll> par, rnk;

   public:
    DSU(ll n) {
        par.resize(n + 1);
        rnk.resize(n + 1);

        for (ll i = 0; i <= n; i++) {
            par[i] = i;
            rnk[i] = 1;
        }
    }

    ll find_parent(ll m) {
        if (par[m] == m) return m;
        return par[m] = find_parent(par[m]);
    }

    //
    //      -- inline comment shift+option+A
    //     ll find_parent(ll m) {
    //     if (par[m] == m) return m;
    //     return find_parent(par[m]);
    // }

    void union_sets(ll a, ll b) {
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
};
 */

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

ll n;
vector<ll> cost;
vector<ll> adj[N];
vector<ll> indegree;

unordered_set<ll> vis;

void dfs(ll x, ll& mini) {
    vis.insert(x);
    mini = min(mini, cost[x]);
    for (auto it : adj[x]) {
        if (vis.find(it) == vis.end()) {
            dfs(it, mini);
        }
    }
}

void solve() {
    cin >> n;
    cost.resize(n + 1);
    indegree.resize(n + 1);

    for (ll i = 1; i <= n; i++) {
        cin >> cost[i];
    }

    for (ll i = 1; i <= n; i++) {
        ll x;
        cin >> x;
        adj[i].push_back(x);
        indegree[x]++;
    }

    queue<ll> q;

    for (ll i = 1; i <= n; i++) {
        if (indegree[i] == 0) q.push(i);
    }

    while (q.size() > 0) {
        ll cur = q.front();
        q.pop();

        for (auto it : adj[cur]) {
            indegree[it]--;
            if (indegree[it] == 0) {
                q.push(it);
            }
        }
    }

    ll cost = 0;

    for (ll i = 1; i <= n; i++) {
        if (indegree[i] > 0 && vis.find(i) == vis.end()) {
            ll minn = INT_MAX;
            dfs(i, minn);
            cost += minn;
        }
    }

    cout << cost;
}

signed main() { solve(); }
