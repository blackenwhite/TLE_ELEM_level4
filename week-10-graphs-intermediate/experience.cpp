/*
In a novel online game, the players fight the monsters and get the experience, as usual. To fight monsters players join together in raid teams. After the destruction of the monster, all the players of the team get the same amount of experience points. The special feature of the game is that a team cannot be split up and no one can leave a team. The only supported operation is to join two teams together.

Since there are already a lot of people playing the game, you are asked to maintain the experience points of the players.

Input
The first line of the input contains two integers n and m (1 ≤ n, m ≤ 2·105) — the number of players and the number of queries.

Next m lines contain the description of queries, one per line. A query can be of three types:

join X Y — join two teams to which players X and Y belong to (if they are already in the same team, nothing changes).
add X V — add V (1 ≤ V ≤ 100) experience points to each player in a team to which player X belongs to.
get X — output the current number of experience points of player X.
Initially, each player has 0 experience points and each of the player is in its own team of size one.

Output
For each query get X output the current number of experience points of player X on a separate line.


*/

// author: nabajyoti
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<ll, ll>;

class DSU {
    vector<ll> par, rnk, comm;

   public:
    DSU(ll n) {
        par.resize(n + 1);
        rnk.resize(n + 1);
        comm.resize(n + 1);

        for (ll i = 0; i <= n; i++) {
            par[i] = i;
            rnk[i] = 1;
        }
    }
    /*
    int find_parent(ll m) {
        if (par[m] == m) return m;
        return par[m] = find_parent(par[m]);
    } */

    ll find_parent(ll m) {
        if (par[m] == m) return m;
        return find_parent(par[m]);
    }

    void union_sets(ll a, ll b) {
        a = find_parent(a);
        b = find_parent(b);
        if (a != b) {
            if (rnk[a] < rnk[b]) swap(a, b);
            par[b] = a;
            rnk[a] += rnk[b];
            comm[b] -= comm[a];
        }
    }

    void add(ll a, ll val) {
        // cout << "adding " << a << " and " << val << "\n";  // test
        ll par_a = find_parent(a);
        comm[par_a] += val;
    }

    void join(ll u, ll v) {
        // cout << "joining " << u << " and " << v << "\n";  // test
        union_sets(u, v);
    }

    ll _get(ll x) {
        if (par[x] == x) return comm[x];
        return comm[x] + _get(par[x]);
    }

    ll get(ll x) {
        // cout << "getting ans for " << x << "\n";  //  test 
        return _get(x);
    }
};

void solve() {
    ll n, m;
    cin >> n >> m;
    DSU dsu(n);

    for (int i = 0; i < m; i++) {
        string x;
        cin >> x;
        if (x == "add") {
            ll a, p;
            cin >> a >> p;
            dsu.add(a, p);
        } else if (x == "join") {
            ll u, v;
            cin >> u >> v;
            dsu.join(u, v);
        } else if (x == "get") {
            ll u;
            cin >> u;
            cout << dsu.get(u) << "\n";
        }
    }
}

signed main() { solve(); }
