#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
 public:
  int climbStairs(int n) {
    // dp
    // if (n <= 2) return n;
    // vector<int> dp(n + 1, 1);
    // for (int i = 2; i <= n; i++) {
    //   dp[i] = dp[i - 1] + dp[i - 2];
    // }
    // return dp[n];

    // 优化版： 两个变量，空间复杂度O(1)
    if (n <= 2) return n;
    int prev2 = 1, prev1 = 2, cur = 0;
    for (int i = 2; i < n; i++) {
      cur = prev2 + prev1;
      prev2 = prev1;
      prev1 = cur;
    }
    return cur;
  }
};

int main() {
  int test = 7;
  Solution s;
  std::cout << "Test result: " << s.climbStairs(test) << std::endl;
  return 0;
}