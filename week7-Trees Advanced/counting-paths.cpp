// author : Nabajyoti
#include <bits/stdc++.h>
using namespace std;
#define int long long
int mod = 1000000007;
// int mod = 998244353;
int modd = 1e9 + 7;
#define pii pair<int, int>
#define N 303
int inf = 1e15;
#define ff first
#define ss second

int gcd(int a, int b)
{
    if (a < b)
        return gcd(b, a);
    if (b == 0)
        return a;
    return gcd(a % b, b);
}

int mult(int a, int b) // O(1)
{
    return ((a % mod) * (b % mod)) % mod;
}

int exponent(int a, int b)
{
    int ans = 1;
    while (b > 0)
    {
        if (b % 2 == 1)
        {
            ans = (ans * a) % mod;
        }
        a = (a * a) % mod;
        b /= 2;
    }
    return ans;
}

int inverse(int a) { return exponent(a, mod - 2); }

int fact[N];
int invFact[N];

void init()
{
    fact[0] = 1;
    for (int i = 1; i < N; i++)
    {
        fact[i] = mult(i, fact[i - 1]);
    }

    invFact[N - 1] = inverse(fact[N - 1]);
    for (int i = N - 2; i >= 0; i--)
    {
        invFact[i] = mult(invFact[i + 1], i + 1);
    }
}

int nCr(int n, int r)
{
    return mult(fact[n], mult(invFact[n - r], invFact[r]));
}

int add(int a, int b)
{ // O(1)
    int ans = (a + b);
    if (ans >= mod)
        ans -= mod;
    if (ans < 0)
        ans += mod;
    return ans;
}

// int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

void pr(vector<int> &v)
{
    // cout << "Printing vector---\n";
    for (auto x : v)
    {
        // cout << x.ff << " "<<x.ss<<"\n";
        cout << x << " ";
    }
    cout << "\n";
}

vector<int> getFactors(int x)
{
    vector<int> factors;
    for (int i = 1; i * i <= x; i++)
    {
        if (x % i == 0)
        {
            if (i != 1)
                factors.push_back(i);
            if (i != x / i)
                factors.push_back(x / i);
        }
    }
    return factors;
}

/*


*/

// struct less_than_key
// {
//     bool operator()(const Pair &a, const Pair &b)
//     {
//         if(a.count == b.count) return a.word<b.word;
//         return a.count>b.count;
//     }
// };

int dirs[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

const int NN = 2e5+1, M = 20;
vector<int> g[NN];
int dep[NN];
int Par[NN][M];
int n,m;

void dfs(int nn, int pp) {
    dep[nn] = dep[pp]+1;
    Par[nn][0] = pp;
    for(int j=1;j<M;j++) {
        Par[nn][j] = Par[Par[nn][j-1]][j-1];
    }

    for(auto x:g[nn]) {
        if(x!=pp) {
            dfs(x,nn);
        }
    }
}

int KthParent(int u, int k) {
    for(int i=0;i<M;i++) {
        if(k&(1<<i)) {
            u = Par[u][i];
        }
    }
    return u;
}

int findLca(int u, int v) {
    if(u==v) return u;
    if(dep[u]<dep[v]) swap(u,v);

    int diff = dep[u]-dep[v];
    u = KthParent(u,diff); // take them to the same level

    if(u==v) return u;

    for(int j=M-1;j>=0;j--) {
        if(Par[u][j]!=Par[v][j]) {
            u = Par[u][j];
            v = Par[v][j];
        }
    }
    return (u!=v? Par[u][0]:u);

}

void helper(int nn, int pp, vector<int>&ans) {
    for(auto x:g[nn]) {
        if(x!=pp) {
            helper(x,nn,ans);
            ans[nn] += ans[x];
        }
    }
}

void solve()
{
    cin>>n>>m;

    for(int i=1;i<n;i++) {
        int u,v;
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dep[0] = -1;
    dfs(1,0);

    vector<int>ans(n+1,0);

    while(m--) {
        int x,y;
        cin>>x>>y;
        int lca = findLca(x,y);
        ans[x]++;
        ans[y]++;
        ans[lca]--;
        ans[Par[lca][0]]--;
    }

    helper(1,0, ans);
    for(int i=1;i<=n;i++){
        cout<<ans[i]<<" ";
    }
    cout<<"\n";

}


signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t = 1;
    // cin >> t;

    while (t--)
    {
        solve();
    }
    // for(tt=1;tt<=t;tt++){
    //     cin>>s;
    //     cout<<rec(0,1,1)<<"\n";
    // }
    return 0;
}
