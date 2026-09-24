/**
 * problem: https://atcoder.jp/contests/abc475/tasks/abc475_e
 * author: Nabajyoti
 */
#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

#define ff first
#define ss second
#define pb push_back

using ll = long long int;
using ld = long double;
using pii = pair<ll, ll>;
const ll N = 2e5 + 5;
// const ll mod = 1e9 + 7;
const ll mod = 998244353;
ll inf = 1e18;
using i128 = __int128;
using vl = vector<ll>;

ll gcd(ll a, ll b) {
    if (a < b) return gcd(b, a);
    if (b == 0) return a;
    return gcd(a % b, b);
}

ll mult(ll a, ll b)  // O(1)
{
    return ((a % mod) * (b % mod)) % mod;
}

ll exponent(ll a, ll b) {
    ll ans = 1;
    while (b > 0) {
        if (b % 2 == 1) {
            ans = (ans * a) % mod;
        }
        a = (a * a) % mod;
        b /= 2;
    }
    return ans;
}

ll inverse(ll a) { return exponent(a, mod - 2); }

ll fact[N];
ll invFact[N];

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

ll nCr(ll n, ll r) {
    if (n < 0 || r < 0 || r > n) return 0;
    return mult(fact[n], mult(invFact[n - r], invFact[r]));
}

ll add(ll a, ll b) {  // O(1)
    ll ans = (a + b);
    if (ans >= mod) ans -= mod;
    if (ans < 0) ans += mod;
    return ans;
}

long long power(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

long long modInverse(long long a, long long mod) { return power(a, mod - 2, mod); }

ll dirs[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

// ----- end of utilities ------ //

ll n, m, K;
string T;
vector<string> v;
ll q;

void print(vector<ll>& v) {
    cout << "printing vector---->\n";
    for (auto it : v) {
        cout << it << " ";
    }
    cout << "\n";
}

struct TrieNode {
    TrieNode* children[2];
    int cnt;

    TrieNode() {
        this->cnt = 0;
        children[0] = nullptr;
        children[1] = nullptr;
    }
};

struct Trie {
    TrieNode* root;

    Trie() { root = new TrieNode(); }

    void insert(const string& s) {
        ll sz = s.size();
        TrieNode* cur = this->root;
        cur->cnt++;
        for (ll i = 0; i < sz; i++) {
            int val = s[i] - '0';
            if (cur->children[val] == nullptr) {
                cur->children[val] = new TrieNode();
            }
            cur->children[val]->cnt++;
            cur = cur->children[val];
        }
    }

    void remove(const string& s) {
        ll sz = s.size();
        TrieNode* cur = this->root;
        cur->cnt--;
        for (ll i = 0; i < sz; i++) {
            int val = s[i] - '0';
            cur->children[val]->cnt--;
            assert(cur->children[val]->cnt >= 0);
            cur = cur->children[val];
        }
    }

    ll getGreaterCount(const string& s) {
        ll sz = s.size();
        ll ans = 0;

        TrieNode* cur = this->root;
        for (ll i = 0; i < sz; i++) {
            ll val = s[i] - '0';
            if (val == 0) {
                if (cur->children[1]) {
                    ans += cur->children[1]->cnt;
                }
            }
            cur = cur->children[val];
        }
        return ans;
    }
};

void solve() {
    cin >> n >> m >> K;
    cin >> T;
    v.assign(n, "");
    for (ll i = 0; i < n; i++) {
        cin >> v[i];
    }

    Trie trie;
    for (ll i = 0; i < n; i++) {
        string res = "";
        for (ll j = 0; j < K; j++) {
            if (v[i][j] == T[j]) {
                res += '0';
            } else {
                res += '1';
            }
        }
        v[i] = res;
        trie.insert(res);
    }

    cin >> q;
    while (q--) {
        ll i, j;
        cin >> i >> j;
        i--;
        j--;
        trie.remove(v[i]);

        // flip
        ll val = 1 - (v[i][j] - '0');
        v[i][j] = (char)(val + '0');

        trie.insert(v[i]);

        ll countgreater = trie.getGreaterCount(v[i]);
        ll equalOrLess = n - countgreater;

        bool allWrong = (v[i].find('0') == string::npos);
        if (n == m && allWrong) {
            cout << "No\n";
        }

        else if (equalOrLess <= m) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}
