#include <limits.h>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int maximalSquare(vector<vector<char>>& matrix) {
    if (matrix.empty() || matrix[0].empty()) {
      return 0;
    }
    int row = matrix.size();
    int col = matrix[0].size();
    vector<vector<int>> dp(row, vector<int>(col, 0));
    int res = 0;
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < col; j++) {
        if (!(matrix[i][j] - '0')) {
          dp[i][j] = 0;
        } else if (i == 0 || j == 0) {
          dp[i][j] = matrix[i][j] - '0';
        } else {
          int tmp = std::min(dp[i - 1][j - 1], dp[i - 1][j]);
          dp[i][j] = std::min(tmp, dp[i][j - 1]) + 1;
        }
        res = std::max(res, dp[i][j]);
      }
    }
    return res * res;
  }
};

int main() {
  vector<vector<char>> test = {{'1', '0', '1', '0', '0'},
                               {'1', '0', '1', '1', '1'},
                               {'1', '1', '1', '1', '1'},
                               {'1', '0', '0', '1', '0'}};
  Solution s;
  std::cout << "Test result: " << s.maximalSquare(test) << std::endl;
  return 0;
}