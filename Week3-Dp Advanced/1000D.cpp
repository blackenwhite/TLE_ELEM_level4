// author : Nabajyoti
//https://codeforces.com/contest/1000/problem/D
#include <bits/stdc++.h>
using namespace std;
#define int long long
// int mod = 1000000007;
int mod = 998244353;
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
vector<int>a;
int dp[1001][1001];

int rec(int ind, int rem) {
    if(ind==n) {
        return rem==0;
    }
    if(dp[ind][rem]!=-1) return dp[ind][rem];
    int ans = 0;
    if(rem>0) {
        int pick = rec(ind+1, rem-1);
        int not_pick = rec(ind+1, rem);
        ans = (pick+not_pick)%mod;
        return dp[ind][rem] = ans;
    }
    else{
        int pick = 0;
        if(a[ind]>0 && a[ind]<=n) {
            pick = rec(ind+1,a[ind]);
        }
        int not_pick = rec(ind+1,rem);
        ans = (pick+not_pick)%mod;
        return dp[ind][rem] = ans;
    }
}

void solve(){
    cin>>n;
    a.resize(n);

    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    memset(dp,-1,sizeof(dp));
    int ans = rec(0,0);
    ans = (ans-1+mod)%mod;
    cout<<ans<<"\n";

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
