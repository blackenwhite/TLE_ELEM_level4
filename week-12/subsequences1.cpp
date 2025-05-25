#include<bits/stdc++.h>
using namespace std;
#define int long long
 
 
struct segmentTree {
    int n;
    vector<long long> tree;
 
    segmentTree(){}
 
    segmentTree(int _n) {
        n = _n;
        tree.assign(4 * n, 0); // 0 is the identity for sum
    }
 
    // Customize this merge logic as needed (min, max, gcd, etc.)
    long long merge(long long a, long long b) {
        return a + b;
    }
 
    void build(const vector<long long>& a, int node = 1, int l = 0, int r = -1) {
        if (r == -1) r = n - 1;
        if (l == r) {
            tree[node] = a[l];
            return;
        }
        int mid = (l + r) / 2;
        build(a, 2 * node, l, mid);
        build(a, 2 * node + 1, mid + 1, r);
        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }
 
    void update(int idx, long long val, int node = 1, int l = 0, int r = -1) {
        if (r == -1) r = n - 1;
        if (l == r) {
            tree[node] = val;
            return;
        }
        int mid = (l + r) / 2;
        if (idx <= mid)
            update(idx, val, 2 * node, l, mid);
        else
            update(idx, val, 2 * node + 1, mid + 1, r);
        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }
 
    long long query(int ql, int qr, int node = 1, int l = 0, int r = -1) {
        if (r == -1) r = n - 1;
        if (qr < l || ql > r)
            return 0; // identity
        if (ql <= l && r <= qr)
            return tree[node];
        int mid = (l + r) / 2;
        return merge(
            query(ql, qr, 2 * node, l, mid),
            query(ql, qr, 2 * node + 1, mid + 1, r)
        );
    }
};
 
 
segmentTree segTree[12];
 
int32_t main(){
 
    int n , k;
    cin >> n >> k;
    k++;
    for(int i = 0 ; i <= k; i++) segTree[i] = segmentTree(n + 5);
 
    vector<int> arr(n + 1);
 
    for(int i = 1 ; i <= n ; i++){
        cin >> arr[i];
    }
 
    segTree[0].update(0 , 1);
 
    for(int i = 1 ; i <= n ; i++){
 
        for(int j = 1 ; j <= k ; j++){
            segTree[j].update( arr[i] , segTree[j-1].query(0 , arr[i]-1));
        }
    }
    cout << segTree[k].query(0 , n) << endl;
    return 0;
}
