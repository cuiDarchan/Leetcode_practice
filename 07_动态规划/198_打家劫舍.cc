#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
 public:
  int rob(vector<int>& nums) {
    int size = nums.size();
    if (size < 0) return 0;
    if (size == 1) return nums[0];
    int pre_max2 = 0, pre_max1 = 0, cur = 0;
    // 从第1个屋子开始, 从第3个屋子开始会出错
    for (int i = 0; i < size; i++) {
      cur = max(pre_max2 + nums[i], pre_max1);
      pre_max2 = pre_max1;
      pre_max1 = cur;
    }
    return cur;
  }
};

int main() {
  vector<int> test = {2, 1, 1, 2};
  Solution s;
  std::cout << "Test result: " << s.rob(test) << std::endl;
  return 0;
}