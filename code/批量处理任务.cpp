// 参考原文 https://blog.csdn.net/qq_45776114/article/details/147398095
// 实现方式 贪心算法 让实际执行时间位于每个任务的区间末尾 
#include <algorithm>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

// 定义一个结构体表示时间区间
struct Interval {
    int l, r; // 区间左右端点（闭区间）
    int sum;  // 从栈底到当前区间的总工作时间
    Interval(int l, int r, int sum) : l(l), r(r), sum(sum) {}
};

// 通用 split 函数
vector<string> split(const string& str, const string& delimiter) {
    vector<string> result;
    size_t start = 0;
    size_t end = str.find(delimiter);
    while (end != string::npos) {
        result.push_back(str.substr(start, end - start));
        start = end + delimiter.length();
        end = str.find(delimiter, start);
    }
    // 添加最后一个部分
    result.push_back(str.substr(start));
    return result;
}

int main() {
    string s;
    getline(cin, s);

    // [[1,3,2],[2,5,3],[5,6,2]] => 1,3,2],[2,5,3],[5,6,2
    s = s.substr(2, s.size() - 4);
    vector<string> ansStr = split(s, "],[");
    int n = ansStr.size();
    vector<vector<int>> tasks(n);
    for (int i = 0; i < n; i++) {
        vector<string> tmp = split(ansStr[i], ",");
        int start = stoi(tmp[0]);
        int end = stoi(tmp[1]);
        int p = stoi(tmp[2]);
        tasks[i] = {start, end, p};
    }
    // 按结束时间升序排序
    sort(
        tasks.begin(), tasks.end(),
        [](const vector<int>& a, const vector<int>& b) { return a[1] < b[1]; });

    vector<Interval> st{{-2, -2, 0}}; // 初始化哨兵节点

    for (const auto& t : tasks) {
        int start = t[0], end = t[1], d = t[2];

        // 找到 start 左侧最近的区间
        auto it = --lower_bound(
            st.begin(), st.end(), start,
            [](const Interval& interval, int val) { return interval.l < val; });

        d -= st.back().sum - it->sum; // 去掉中间已运行时间

        if (start <= it->r) {
            d -= it->r - start + 1; // 去掉当前区间内的运行时间
        }

        if (d <= 0)
            continue;

        // 合并后缀区间，填满剩余时间 d
        while (end - st.back().r <= d) {
            auto back = st.back();
            d += back.r - back.l + 1;
            st.pop_back();
        }

        // 插入新区间
        st.push_back({end - d + 1, end, st.back().sum + d});
    }

    cout << st.back().sum;
    return 0;
}
