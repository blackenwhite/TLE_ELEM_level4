#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define fastio() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define MOD1 998244353
#define INF 1e18
#define pb push_back
#define ppb pop_back
#define ff first
#define ss second
#define PI 3.141592653589793238462
#define set_bits __builtin_popcountll
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define fori(i,a,b) for(int i=a; i<b;i++)
#define Y { cout <<"YES"<< endl;}
#define NN { cout <<"NO"<< endl;}

const int mod = 1e9+7;


//function to check whether nth node is reachable
void mark_dfs(ll node, vector<ll> &vis, vector<ll> adj[]){
    vis[node] = 1;
    for(auto child : adj[node]){
        if(!vis[child]){
            mark_dfs(child,vis,adj);
        }
    }
}

//function to return the max_len and store the path using child array
ll dfs(ll node, vector<ll> &dp, vector<ll> adj[],int n, vector<ll> &child){
    //base condition
    if(node==n) return dp[n] = 1;
    //memoization step
    if(dp[node]!=-1) return dp[node];
    ll len = 0;
    //standard dfs approach
    for(auto v : adj[node]){
        ll tmp = dfs(v,dp,adj,n,child);
        //temp_len checks whether the len is coming from the nth node or not
        ll temp_len = tmp==0?0:1+tmp;
        if(temp_len>len){
            // updating the child node and len
            child[node] = v;
            len = temp_len;
        }
    }
    //dp assignment step
    return dp[node] = len;
}
 
int main(){
    ll n,m;
    cin>>n>>m; 
    vector<ll> adj[n+1];
    fori(i,0,m){
        ll x,y;
        cin>>x>>y;
        adj[x].pb(y);
    }

    vector<ll> vis(n+1,0);
    //function call to check if nth node is reachable
    mark_dfs(1,vis,adj);
    if(!vis[n]) cout<<"IMPOSSIBLE\n";
    else{
        vector<ll> dp(n+1,-1);
        vector<ll> child(n+1,0);
        ll len = dfs(1,dp,adj,n,child);
        int node = 1;
        vector<ll> path;
        //forward traversal to print the path.
        while(node){
            path.pb(node);
            node = child[node];
        }
        cout<<len<<endl;
        for(auto it : path){
            cout<<it<<" ";
        }
    }
    return 0;

}
