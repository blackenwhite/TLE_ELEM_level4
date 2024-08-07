// author : Nabajyoti
/*
https://atcoder.jp/contests/abc222/tasks/abc222_d
*/
#include <bits/stdc++.h>
using namespace std;
#define int long long
// int mod = 1000000007;
int mod = 998244353;
int modd = 1e9 + 7;
#define pii pair<int, int>
#define N 300300
int inf = 1e18;
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
    cout << "Printing vector---\n";
    for (auto x : v)
    {
        // cout << x.ff << " "<<x.ss<<"\n";
        cout << x << " ";
    }
    cout << "\n";
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

int dirs[4][2] = {{0,1}, {1,0}, {0,-1}, {-1,0}};

int n;
vector<int>a,b;

void solve(){
    cin>>n;
    a.resize(n+1);
    b.resize(n+1);
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=n;i++) {
        cin>>b[i];
    }

    int mx = b[n];
    vector<vector<int>>dp(n+1, vector<int>(mx+1, 0));
    vector<vector<int>>sum(n+1, vector<int>(mx+1, 0));

    for(int j=0;j<=mx;j++){
        sum[0][j] = 1;
    }

    for(int i=1;i<=n;i++){
        for(int j=0;j<=mx;j++){
            if(j>=a[i] && j<=b[i]){
                dp[i][j] = (dp[i][j] + sum[i-1][j])%mod;
            }
            sum[i][j] = ((j>0? sum[i][j-1]:0) + dp[i][j]);
            sum[i][j]%=mod;
        }
    }
    cout<<sum[n][mx]<<"\n";

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
