// 参考原文 https://blog.csdn.net/qq_45776114/article/details/147288240 
// 实现方法 贪心 + 线段树
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const int MAXB = 400005;
// tree1[i]：支持候选人 i 的所有票价
vector<int> tree1[MAXN];
// f[i]：每个候选人第 i 张便宜的票集合
vector<int> f[MAXN];

int num[MAXB * 4]; // 线段树：num[i] 表示区间内票的数量
long long t[MAXB * 4]; // 线段树：t[i] 表示区间内票的总价格

// 线段树更新操作：插入一张价格为 q 的票
void change(int x, int l, int r, int q) {
    if (l == r) {
        num[x]++;
        t[x] += l;
        return;
    }
    int mid = (l + r) / 2;
    if (q <= mid) {
        change(x * 2, l, mid, q);
    } else {
        change(x * 2 + 1, mid + 1, r, q);
    }
    // 更新当前节点信息
    t[x] = t[x * 2] + t[x * 2 + 1];
    num[x] = num[x * 2] + num[x * 2 + 1];
}

// 查询线段树中价格最小的 q 张票的总费用
long long query(int x, int l, int r, int q) {
    if (l == r) {
        return 1LL * l * q;
    }
    int mid = (l + r) / 2;
    if (q == num[x * 2]) {
        return t[x * 2];
    }
    if (q > num[x * 2]) {
        return t[x * 2] + query(x * 2 + 1, mid + 1, r, q - num[x * 2]);
    } else {
        return query(x * 2, l, mid, q);
    }
}



int main() {
    int n;
    scanf("%d", &n);

    int max_a = 0, max_b = 1;
    long long result = 0;

    // 输入处理
    for (int i = 0; i < n; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        // 最大候选人数
        max_a = max(max_a, x);
        if (y == 0) continue;
        // 最大值
        max_b = max(max_b, y);
        result += y;
        tree1[x].push_back(y);
    }

    // 对每个候选人的支持票价进行排序，并按位置填入 f[]
    for (int i = 1; i <= max_a; ++i) {
        if (!tree1[i].empty()) {
            sort(tree1[i].begin(), tree1[i].end());
            for (int j = 0; j < (int)tree1[i].size(); ++j) {
                f[j + 1].push_back(tree1[i][j]);
            }
        }
    }

    // 初始我拥有所有票
    int k = n;
    // 初始我拥有所有票的花费
    long long tmp = result;

    // 允许其它候选人有i张票
    for (int i = 1; i <= n; ++i) {
        // 手中余票减少的数量
        k -= f[i].size();
        for (int j = 0; j < (int)f[i].size(); ++j) {
           // 释放这些票
            change(1, 1, max_b, f[i][j]);
           // 减少的花费
            tmp -= f[i][j];
        }
        long long add = 0;
        // 让所有人可以拥有i张票的情况下,我手头的票可能不足 i + 1,我需要再购买一些回来 
        if (k <= i) {
            add = query(1, 1, max_b, min(i + 1 - k, n));
        }
        result = min(result, tmp + add);
    }

    printf("%lld\n", result);
    return 0;
}

