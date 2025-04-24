// 参考博文地址： https://blog.csdn.net/qq_45776114/article/details/145583068
// 解题思路： 动态规划 + 二分  
// 关键： 遇到多维的问题，优先找规律先 减少要考虑的维度

#include<iostream>
#include<vector>
#include<string>
#include <utility> 
#include <sstream>
#include <regex>
#include<algorithm>
using namespace std;

// 处理[[1,2],[2,3]] 输入
vector<vector<int>> parseStringTo2DArray(const string &s) {
    vector<vector<int>> result;
    regex rowPattern(R"(\[(\d+),(\d+)\])"); // 正则匹配 [num1,num2]
    smatch match;

    string::const_iterator searchStart(s.cbegin());
    while (regex_search(searchStart, s.cend(), match, rowPattern)) {
        result.push_back({stoi(match[1]), stoi(match[2])});
        searchStart = match.suffix().first; // 继续搜索下一个匹配项
    }

    return result;
}

bool cmp(vector<int> ans1, vector<int> ans2) {
    if (ans1[0] == ans2[0]) {
        // 宽度降序
        return ans1[1] > ans2[1];
    } 
    // 长度升序
    return ans1[0] < ans2[0];
}


int main() {
    string s;
    cin >> s;
    vector<vector<int>> ans = parseStringTo2DArray(s);
    if (ans.size() == 0) {
        cout << 0;
        return 0;
    }
    // 通过排序 确定一个条件，减少要考虑的维度
    sort(ans.begin(), ans.end(), cmp);
    int n = ans.size();
    vector<int> width(n); 
    for (int i = 0; i < n; i++) {
        width[i] = ans[i][1];
    }
    // 获取最长递增子序列
    // dp[i]代表递增子序列长度为i能取的最小值
    vector<int> dp;
    dp.push_back(width[0]);
    for (int i = 1; i < width.size(); i++) {
        if (width[i] > dp[dp.size() -1]) {
            dp.push_back(width[i]);
        } else {
            auto it = lower_bound(dp.begin(), dp.end(), width[i]);
            *it = width[i];
        }
        
    }

    cout << dp.size();
    return 0;
}


