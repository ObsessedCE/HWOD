#include<iostream>
#include<vector>
#include<string>
// 参考原文 https://blog.csdn.net/qq_45776114/article/details/147141325
// 实现方式 动态规划
#include <utility> 
#include <sstream>
#include<algorithm>
#include<list>
#include<queue>
#include<map>
#include<set>
#include<climits>
using namespace std;

int main() {
    string A,B;
    cin>>A>>B;
    int m = A.size(),n = B.size();
    // 使用两个数组压缩数组大小, 状态转义方程只涉及两行
    vector<int> dp(m+1,INT_MAX);
    // 记录上一行的状态
    vector<int> pre(m+1, INT_MAX);

    for (int i = 0; i <= m; i++) {
        pre[i] = i;
    }

    for (int i = 1; i <= n; i++) {
        // 重新初始化
        dp.assign(m+1, INT_MAX);
        // (i,0)到(0,0)的距离
        dp[0] = i;
        for (int j = 1; j <= m; j++) {
            dp[j] = min(pre[j], dp[j-1]) + 1;
            if (A[j-1] == B[i-1]) {
                dp[j] = min(dp[j], pre[j-1] + 1);
            }
        }
        pre = dp;
    }

    cout << dp[m];
    return 0;
}
