#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
 public:
  int numberOfArithmeticSlices(vector<int>& nums) {
    /*
        原本的等差子列，多了一个新满足条件的数字，依旧是等差子列，个数不变;
        只是多了一个最长的子列
        dp[i] = dp[i-1]+1;
    */
    vector<int> dp(nums.size(), 0);
    int ans = 0;
    for (int i = 2; i < nums.size(); i++) {
      if (nums[i] - nums[i - 1] == nums[i - 1] - nums[i - 2]) {
        dp[i] = dp[i - 1] + 1;
      }
      ans += dp[i];
    }
    return ans;
  }
};

int main() {
  vector<int> test = {1, 2, 3, 4};
  Solution s;
  std::cout << "Test result: " << s.numberOfArithmeticSlices(test) << std::endl;
  return 0;
}