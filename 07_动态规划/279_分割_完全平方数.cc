/*
 * 题目描述：
   给定一个链表，如果有环路，找出环路的开始点的值。
 */

#include <vector>
#include <limits.h> // INT_MAX需要使用
#include <iostream>

int numSquares(int n) {
  std::vector<long> dp(n + 1, INT_MAX);
  dp[0] = 0;
  // 第i个位置的dp 只与i-k^2位置有关
  for (long i = 1; i < n + 1; ++i) {
    // 易错点： j * j < i， 忘记添加等于号，导致完全平方数会计算错误，结果超限
    for (long j = 1; j * j <= i; ++j) {
      dp[i] = std::min(dp[i], dp[i - j * j] + 1);
    }
  }
  return dp[n];
}

int main(){
    auto res = numSquares(13);
    std::cout << "res: " << res << std::endl; // 2: 4+9
    return 0;
}

