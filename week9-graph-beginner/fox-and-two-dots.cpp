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

// struct less_than_key
// {
//     bool operator()(const Pair &a, const Pair &b)
//     {
//         if(a.count == b.count) return a.word<b.word;
//         return a.count>b.count;
//     }
// };

int dirs[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

int n, m;
vector<vector<char>> grid;
vector<vector<bool>> vis;

bool dfs(int x, int y, int fromX, int fromY, char needColor) {
  vis[x][y] = true;

  bool ans = false;

  for (int k = 0; k < 4; k++) {
    int nx = x + dirs[k][0];
    int ny = y + dirs[k][1];

    if (nx == fromX && ny == fromY) continue;

    if (nx >= 0 && ny >= 0 && nx < n && ny < m && grid[nx][ny] == needColor) {
      if (vis[nx][ny])
        return true;
      else
        ans = ans || dfs(nx, ny, x, y, needColor);
    }
  }

  return ans;
}

void solve() {
  cin >> n >> m;
  grid = vector<vector<char>>(n, vector<char>(m));

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> grid[i][j];
    }
  }

  vis = vector<vector<bool>>(n, vector<bool>(m, false));

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (!vis[i][j]) {
        bool temp = dfs(i, j, -1, -1, grid[i][j]);
        if (temp) {
          cout << "Yes\n";
          return;
        }
      }
    }
  }
  cout << "No\n";
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
