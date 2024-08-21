class Solution {
public:
    int dp[100100];

    int f(int ind, int mask, int n) {
        if(ind==n+1) return dp[mask]=1;
        if(dp[mask]!=-1) {
            return dp[mask];
        }

        int ans = 0;
        for(int i=0;i<n;i++) {
            if((mask&(1<<i))==0) {
                if(ind%(i+1)==0 || (i+1)%ind == 0) {
                    ans+=f(ind+1, mask+(1<<i), n);
                }
            }
        }
        return dp[mask] = ans;
    }
    int countArrangement(int n) {
        memset(dp,-1,sizeof(dp));
        return f(1,0,n);
    }
};
