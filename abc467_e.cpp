/*
Problem Statement
The problem statement of Problem E is the same as Problem C. Only the constraint shown in red differ.

You are given integer sequences 
A=(A 
1
​
 ,A 
2
​
 ,…,A 
N
​
 ) and 
B=(B 
1
​
 ,B 
2
​
 ,…,B 
N−1
​
 ) consisting of integers between 
0 and 
M−1, inclusive. The lengths of 
A and 
B are 
N and 
N−1, respectively.
You can perform the following operation on 
A any number of times.

Choose an integer 
i with 
1≤i≤N, and add 
1 to 
A 
i
​
 .
Find the minimum number of operations required to satisfy the following condition.
It can be proved that the condition can always be satisfied under the constraints of this problem.

For 
i=1,2,…,N−1, the remainder when 
A 
i
​
 +A 
i+1
​
  is divided by 
M equals 
B 
i
​
 .
Constraints
2≤N≤2×10 
5
 
3≤M≤10 
9
 
0≤A 
i
​
 ≤M−1
0≤B 
i
​
 ≤M−1
All input values are integers.


*/


/**
 * problem:
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
using vl = vector<ll>;

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

// ----- end of utilities ------ //

ll n, m;
vector<ll> a, b;

void solve() {
    cin >> n >> m;
    a.assign(n, 0);
    b.assign(n - 1, 0);

    for (ll i = 0; i < n; i++) {
        cin >> a[i];
    }

    for (ll i = 0; i < n - 1; i++) {
        cin >> b[i];
    }

    vector<ll> plusD, minusD, C(n), D(n);
    C[0] = 0;
    for (ll i = 0; i < n - 1; i++) {
        C[i + 1] = ((b[i] - C[i]) % m + m) % m;
    }

    // D[i] = cost of element when s = 0
    for (ll i = 0; i < n; i++) {
        D[i] = ((C[i] - a[i]) % m + m) % m;
    }

    vector<ll> candidates;  // candidates := possible values of s
    ll plusSum = 0, minusSum = 0;

    for (ll i = 0; i < n; i++) {
        if (i % 2 == 0) {
            plusD.push_back(D[i]);
            candidates.push_back((m - D[i]) % m);

            plusSum += D[i];
        } else {
            minusD.push_back(D[i]);
            candidates.push_back(D[i]);

            minusSum += D[i];
        }
    }

    sort(plusD.begin(), plusD.end());
    sort(minusD.begin(), minusD.end());

    ll ans = inf;

    for (ll s : candidates) {
        ll overflows = plusD.end() - lower_bound(plusD.begin(), plusD.end(), m - s);
        ll plusCost = plusSum + plusD.size() * s - m * overflows;

        ll underflows = lower_bound(minusD.begin(), minusD.end(), s) - minusD.begin();
        ll minusCost = minusSum - minusD.size() * s + m * underflows;

        ans = min(ans, plusCost + minusCost);
    }

    cout << ans << "\n";
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
