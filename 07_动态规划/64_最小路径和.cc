#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
 public:
  int minPathSum(vector<vector<int>>& grid) {
    int row = grid.size();
    int col = grid[0].size();
    vector<int> dp(col, 0);
    // dp(i,j) = min{dp(i-1,j),dp(i,j-1)}+ grid[i][j]
    // 空间压缩： 一层dp[i]; 上一层dp 依旧是dp[j]
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < col; j++) {
        if (i == 0 && j == 0) {
          dp[j] = grid[i][j];
        } else if (i == 0) {
          dp[j] = dp[j - 1] + grid[i][j];
        } else if (j == 0) {
          dp[j] = dp[j] + grid[i][j];
        } else {
          dp[j] = std::min(dp[j - 1], dp[j]) + grid[i][j];
        }
      }
    }
    return dp[col - 1];
  }
};

int main() {
  vector<vector<int>> test = {{1, 2, 3}, {4, 5, 6}};
  Solution s;
  std::cout << "Test result: " << s.minPathSum(test) << std::endl;
  return 0;
}