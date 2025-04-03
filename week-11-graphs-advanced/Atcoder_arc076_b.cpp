#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<ll, ll>;

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

struct Point {
    ll id;
    ll x;
    ll y;
};

void solve() {
    ll n;
    cin >> n;
    vector<Point> pts(n);
    for (ll i = 0; i < n; i++) {
        cin >> pts[i].x >> pts[i].y;
        pts[i].id = i + 1;
    }

    // sort the points based on the x co-ordinate
    sort(pts.begin(), pts.end(), [](const Point &a, const Point &b) { return a.x < b.x; });

    vector<edge> edges;

    // add the edges
    for (ll i = 1; i < n; i++) {
        Point a = pts[i - 1];
        Point b = pts[i];
        ll dist = abs(a.x - b.x);

        edges.push_back(edge(a.id, b.id, dist));
    }

    // sort the points on the y coordinate
    sort(pts.begin(), pts.end(), [](const Point &a, const Point &b) { return a.y < b.y; });

    // add the edges
    for (ll i = 1; i < n; i++) {
        Point a = pts[i - 1];
        Point b = pts[i];
        ll dist = abs(a.y - b.y);

        edges.push_back(edge(a.id, b.id, dist));
    }

    // now find the MST
    DSU dsu(n);
    sort(edges.begin(), edges.end(), [](const edge &a, const edge &b) { return a.wt < b.wt; });

	ll cost = 0;

	for(auto it:edges) {
		ll a = it.a;
		ll b = it.b;
		if(!dsu.isConnected(a,b)) {
			cost+=it.wt;
			dsu.union_sets(a,b);
		}
	}

	cout<<cost<<"\n";

}

signed main() { solve(); }
