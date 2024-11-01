// author : Nabajyoti
#include <bits/stdc++.h>
using namespace std;
#define int long long
int mod = 1000000007;
// int mod = 998244353;
int modd = 1e9 + 7;
#define pii pair<int, int>
#define N 200100
int inf = 1e15;
#define ff first
#define ss second

int gcd(int a, int b) {
  if (a < b) return gcd(b, a);
  if (b == 0) return a;
  return gcd(a % b, b);
}

int mult(int a, int b)  // O(1)
{
  return ((a % mod) * (b % mod)) % mod;
}

int exponent(int a, int b) {
  int ans = 1;
  while (b > 0) {
    if (b % 2 == 1) {
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

void init() {
  fact[0] = 1;
  for (int i = 1; i < N; i++) {
    fact[i] = mult(i, fact[i - 1]);
  }

  invFact[N - 1] = inverse(fact[N - 1]);
  for (int i = N - 2; i >= 0; i--) {
    invFact[i] = mult(invFact[i + 1], i + 1);
  }
}

int nCr(int n, int r) {
  return mult(fact[n], mult(invFact[n - r], invFact[r]));
}

int add(int a, int b) {  // O(1)
  int ans = (a + b);
  if (ans >= mod) ans -= mod;
  if (ans < 0) ans += mod;
  return ans;
}

// int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

void pr(vector<int>& v) {
  // cout << "Printing vector---\n";
  for (auto x : v) {
    // cout << x.ff << " "<<x.ss<<"\n";
    cout << x << " ";
  }
  cout << "\n";
}

vector<int> getFactors(int x) {
  vector<int> factors;
  for (int i = 1; i * i <= x; i++) {
    if (x % i == 0) {
      if (i != 1) factors.push_back(i);
      if (i != x / i) factors.push_back(x / i);
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

int n;
vector<int> tree[N];
vector<int> maxVal;
vector<int> ans;
vector<int> val;

void dfs(int node, int par) {
  maxVal[node] = val[node];

  for (int it : tree[node]) {
    if (it != par) {
      dfs(it, node);
      maxVal[node] += max(0LL, maxVal[it]);
    }
  }
}

void changeRoot(int currentRoot, int nextRoot) {
  maxVal[currentRoot] -= max(0LL, maxVal[nextRoot]);
  maxVal[nextRoot] += max(0LL, maxVal[currentRoot]);
}

void reroot(int node, int par) {
  ans[node] = maxVal[node];

  for (int it : tree[node]) {
    if (it != par) {
      changeRoot(node, it);
      reroot(it, node);
      changeRoot(it, node);
    }
  }
}

void solve() {
  cin >> n;
  maxVal.resize(n + 1);
  ans.resize(n + 1);
  val.resize(n + 1);

  for (int i = 1; i <= n; i++) {
    cin >> val[i];
    if (val[i] == 0) {
      val[i] = -1;
    }
  }

  for (int i = 1; i < n; i++) {
    int u, v;
    cin >> u >> v;
    tree[u].push_back(v);
    tree[v].push_back(u);
  }

  dfs(1, 0);
  reroot(1, 0);

  for (int i = 1; i <= n; i++) {
    cout << ans[i] << " ";
  }
  cout << "\n";
}

signed main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int t = 1;
  // cin >> t;

  while (t--) {
    solve();
  }
  // for(tt=1;tt<=t;tt++){
  //     cin>>s;
  //     cout<<rec(0,1,1)<<"\n";
  // }
  return 0;
}
