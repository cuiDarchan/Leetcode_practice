#include <limits.h>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
    // 类似往右下找最小值，简单思路：遍历两次，先往右下，再往左上
    if (mat.empty()) return {};
    int n = mat.size();     // row
    int m = mat[0].size();  // col
    vector<vector<int>> dp(n, vector<int>(m, INT_MAX - 1));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (!mat[i][j]) {
          dp[i][j] = 0;
        } else {
          if (j > 0) {
            dp[i][j] = std::min(dp[i][j - 1] + 1, dp[i][j]);
          }
          if (i > 0) {
            dp[i][j] = std::min(dp[i - 1][j] + 1, dp[i][j]);
          }
        }
      }
    }
    for (int i = n - 1; i >= 0; i--) {
      for (int j = m - 1; j >= 0; j--) {
        if (!mat[i][j]) {
          dp[i][j] = 0;
        } else {
          if (j < m - 1) {
            dp[i][j] = std::min(dp[i][j + 1] + 1, dp[i][j]);
          }
          if (i < n - 1) {
            dp[i][j] = std::min(dp[i + 1][j] + 1, dp[i][j]);
          }
        }
      }
    }
    return dp;
  }
};

int main() {
  vector<vector<int>> test = {{1, 0, 0}, {0, 0, 0}};
  Solution s;
  vector<vector<int>> res = s.updateMatrix(test);
  // std::cout << "Test result: " << s.updateMatrix(test) << std::endl;
  return 0;
}