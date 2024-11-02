/*
You are given a rooted tree consisting of n nodes. The nodes are numbered 1,2,\ldots,n, and node 1 is the root. Each node has a value.
Your task is to process following types of queries:

change the value of node s to x
calculate the sum of values in the subtree of node s

Input
The first input line contains two integers n and q: the number of nodes and queries. The nodes are numbered 1,2,\ldots,n.
The next line has n integers v_1,v_2,\ldots,v_n: the value of each node.
Then there are n-1 lines describing the edges. Each line contans two integers a and b: there is an edge between nodes a and b.
Finally, there are q lines describing the queries. Each query is either of the form "1 s x" or "2 s".
Output
Print the answer to each query of type 2.

*/

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

int n, q;
vector<int> tree[N];
vector<int> arr;
vector<int> val;  // euler tour tree
map<int, pii>
    mp;  // map to store inTime and outTime ... key -> {inTime,outTime}
int globalTime;

/*
----- Segment Tree Impl. --------
*/

struct SegTree {
  int n;
  vector<int> Tree;

  SegTree(int _n) {
    n = _n;
    Tree.resize(4 * n);
  }

  void update(int node, int start, int end, int idx, int val) {
    if (start == end) {
      Tree[node] = val;
      return;
    }

    int mid = (start + end) / 2;
    if (idx <= mid) {
      update(2 * node, start, mid, idx, val);
    } else {
      update(2 * node + 1, mid + 1, end, idx, val);
    }

    Tree[node] = Tree[2 * node] + Tree[2 * node + 1];
  }

  int query(int node, int start, int end, const int l, const int r) {
    if (start > r || end < l) {
      return 0;
    }

    if (start >= l && end <= r) return Tree[node];
    int mid = (start + end) / 2;
    return query(2 * node, start, mid, l, r) +
           query(2 * node + 1, mid + 1, end, l, r);
  }
};

/*---- End of Segment tree Impl -------*/

void dfs(int nn, int par) {
  globalTime++;
  mp[nn].ff = globalTime;

  val.push_back(arr[nn]);

  for (auto it : tree[nn]) {
    if (it != par) {
      dfs(it, nn);
    }
  }

  globalTime++;
  mp[nn].ss = globalTime;
  val.push_back(0);
}

void solve() {
  cin >> n >> q;
  arr.resize(n + 1);
  for (int i = 1; i <= n; i++) {
    cin >> arr[i];
  }

  // build the tree
  for (int i = 1; i < n; i++) {
    int u, v;
    cin >> u >> v;
    tree[u].push_back(v);
    tree[v].push_back(u);
  }

  globalTime = -1;

  // do the euler tour
  dfs(1, 0);

  int m = val.size();
  // cout<<"printing the flattened tree --> \n";
  // for(auto it:val) {
  //   cout<<it<<" ";
  // }
  // cout<<"\n";
  SegTree segTree(m);
  for (int i = 0; i < m; i++) {
    segTree.update(1, 0, m - 1, i, val[i]);
  }
  // int a = 5;
  // int b = segTree.query(1,0, m-1, mp[a].ff, mp[a].ss);
  // cout<<"subtree sum for node="<<a<<" is "<<b<<"\n";

  while (q--) {
    int x, a, b;
    cin >> x;
    if (x == 1) {
      cin >> a >> b;
      arr[a] = b;
      val[mp[a].ff] = b;
      segTree.update(1, 0, m - 1, mp[a].ff, b);
    } else {
      cin >> a;
      int ans = segTree.query(1, 0, m - 1, mp[a].ff, mp[a].ss);
      cout << ans << "\n";
    }
  }
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
