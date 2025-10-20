/*
You are given an integer array nums.

A subarray is called balanced if the number of distinct even numbers in the subarray is equal to the number of distinct odd numbers.

Return the length of the longest balanced subarray.

Hint 1
Store the first (or all) occurrences for each value in pos[val].
Hint 2
Build a lazy segment tree over start indices l in [0..n-1] that supports range add and can tell if any index has value 0 (keep mn/mx).
Hint 3
Use sign = +1 for odd values and sign = -1 for even values.
Hint 4
Initialize by adding each value's contribution with update(p, n-1, sign) where p is its current first occurrence.
Hint 5
Slide left l: pop pos[nums[l]], let next = next occurrence or n, do update(0, next-1, -sign), then query for any r >= l with value 0 and update ans = max(ans, r-l+1).
*/

using ll = long long;

struct LazySGT {
    ll sz;
    vector<ll> _min_tree;
    vector<ll> _max_tree;
    vector<ll> lazy;

    void build(ll v, ll l, ll r, const vector<ll>& a) {
        if (l == r) {
            _min_tree[v] = a[r];
            _max_tree[v] = a[r];
            return;
        }

        ll m = (l + r) / 2;
        build(2 * v, l, m, a);
        build(2 * v + 1, m + 1, r, a);
        _min_tree[v] = min(_min_tree[2 * v], _min_tree[2 * v + 1]);
        _max_tree[v] = max(_max_tree[2 * v], _max_tree[2 * v + 1]);
    }

    void apply(ll v, ll len, ll add) {
        _min_tree[v] += add;
        _max_tree[v] += add;
        lazy[v] += add;
    }

    void push_down(ll v, ll l, ll r) {
        if (lazy[v] == 0) return;  // Optimization: skip if no lazy value
        ll m = (l + r) / 2;
        apply(2 * v, m - l + 1, lazy[v]);
        apply(2 * v + 1, r - m, lazy[v]);
        lazy[v] = 0;  // IMPORTANT: Reset after pushing
    }

    void range_update(ll v, ll l, ll r, ll ql, ll qr, ll x) {
        if (qr < l || ql > r)
            return;
        if (l >= ql && r <= qr) {
            apply(v, r - l + 1, x);
            return;
        }
        push_down(v, l, r);
        ll m = (l + r) / 2;
        range_update(2 * v, l, m, ql, qr, x);
        range_update(2 * v + 1, m + 1, r, ql, qr, x);
        _min_tree[v] = min(_min_tree[2 * v], _min_tree[2 * v + 1]);
        _max_tree[v] = max(_max_tree[2 * v], _max_tree[2 * v + 1]);
    }

    ll find_leftmost_zero(ll v, ll l, ll r) {
        if (_min_tree[v] > 0 || _max_tree[v] < 0) {
            return -1;
        }
        if (l == r) {
            return (_min_tree[v] == 0) ? l : -1;  // Check actual value
        }
        
        push_down(v, l, r);  // Push before accessing children
        ll m = (l + r) / 2;
        ll left = find_leftmost_zero(2 * v, l, m);
        if (left != -1)
            return left;
        return find_leftmost_zero(2 * v + 1, m + 1, r);
    }

    LazySGT(const vector<ll>& a) : sz(a.size()) {
        _min_tree.resize(4 * sz);
        _max_tree.resize(4 * sz);
        lazy.resize(4 * sz);
        build(1, 0, sz - 1, a);  // Build the tree
    }

    void update(ll ql, ll qr, ll val) {
        if (ql > qr) return;  // Safety check
        range_update(1, 0, sz - 1, ql, qr, val);
    }
    
    ll find_leftmost_zero() {
        return find_leftmost_zero(1, 0, sz - 1);
    }
};

class Solution {
public:
    int longestBalanced(vector<int>& nums) {
        int n = nums.size();
        unordered_map<int, int> last_pos;
        
        // Initialize with extra position for "before array" state
        vector<ll> balance(n + 1, 0);
        LazySGT sgt(balance);
        
        int ans = 0;
        
        for (int i = 0; i < n; i++) {
            int val = (nums[i] % 2 == 0) ? -1 : 1;  
            
            if (last_pos.count(nums[i])) {
                // Remove previous contribution for all positions up to last occurrence
                sgt.update(0, last_pos[nums[i]], -val);
            }
            
            // Add current contribution for all positions up to current
            sgt.update(0, i, val);
            
            // Find leftmost zero
            ll l = sgt.find_leftmost_zero();
            if (l != -1 && l <= i) {
                ans = max(ans, i - (int)l + 1);
            }
            
            last_pos[nums[i]] = i;
        }
        
        return ans;
    }
};
