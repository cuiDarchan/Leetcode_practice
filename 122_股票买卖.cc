#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
 public:
  int maxProfit(vector<int>& prices) {
    int res = 0;
    // 1.贪心： 长度为1区间 前后做差 加和
    for (int i = 1; i < prices.size(); i++) {
      int delt = prices[i] - prices[i - 1];
      if (delt > 0) res += delt;
    }
    return res;
    // 2.dp
  }
};

int main() {
  vector<int> prices = {7, 1, 5, 3, 6, 4};
  int n = 1;
  Solution s;
  std::cout << "Test result: " << s.maxProfit(prices) << std::endl;
  return 0;
}