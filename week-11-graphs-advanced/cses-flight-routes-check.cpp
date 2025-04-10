// CSES Flight routes check - > strongly connected components solution
// author : nabajyoti
#include <bits/stdc++.h>
using namespace std;

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

ll n, m;
vector<ll> adj[N];
vector<ll> adjT[N];  // inverted graph --> will be used in finding SCC

void topoSort(ll start, vector<ll> &topo, vector<bool> &visited) {
    visited[start] = true;
    for (auto it : adj[start]) {
        if (!visited[it]) {
            topoSort(it, topo, visited);
        }
    }
    topo.push_back(start);
}

void getComponent(ll start, vector<ll> &component, vector<bool> &visited) {
    component.push_back(start);

    visited[start] = true;
    
    for (auto it : adjT[start]) {
        if (!visited[it]) {
            getComponent(it, component, visited);
        }
    }
}

vector<vector<ll>> getSCC() {
    vector<bool> visited(n+1);
    vector<ll> topo;

    for (ll i = 1; i <= n; i++) {
        if (!visited[i]) {
            topoSort(i, topo, visited);
        }
    }

    fill(visited.begin(), visited.end(), false);

    vector<vector<ll>> SCC;

    for (ll i = topo.size() - 1; i >= 0; i--) {
        if (!visited[topo[i]]) {
            vector<ll> comp;
            getComponent(topo[i], comp, visited);
            SCC.push_back(comp);
        }
    }
    return SCC;
}

void solve() {
    cin >> n >> m;
    for (ll i = 0; i < m; i++) {
        ll a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adjT[b].push_back(a);
    }

    vector<vector<ll>> scc = getSCC();
   
    if (scc.size() == 1) {
        cout << "YES\n";
        return;
    } else {
        cout << "NO\n";
        cout<<scc[1][0]<<" "<<scc[0][0]<<"\n";
        // cout << stronglyConnectedComponents[0][0] << " " << stronglyConnectedComponents[1][0]
        //      << "\n";

    }
}

signed main() { solve(); }
