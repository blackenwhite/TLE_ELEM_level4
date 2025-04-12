// auth: Nabajyoti
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<ll, ll>;
const ll N = 1e5 + 5;
const ll mod = 1e9 + 7;

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
vector<ll> dp;
vector<bool> visited;

ll dfs(ll start) {
    if (start == n) return 1;
    if (dp[start] != -1) return dp[start];

    ll ans = 0;
    for (auto it : adj[start]) {
        if (!visited[it]) {
            ans += dfs(it);
            ans %= mod;
        }
    }
    visited[start] = true;
    return dp[start] = ans;
}

void solve() {
    cin >> n >> m;
    dp.resize(n + 1, -1);
    visited.resize(n + 1);

    dp[n] = 1;
    for (int i = 0; i < m; i++) {
        ll a, b;
        cin >> a >> b;
        adj[a].push_back(b);
    }

    dfs(1);
    cout << dp[1] << "\n";
}

signed main() { solve(); }
