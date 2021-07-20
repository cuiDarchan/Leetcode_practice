#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

class Solution {
 public:
  int candy(vector<int>& ratings) {
    if (ratings.size() < 2) return 1;
    vector<int> child(ratings.size(), 1);
    // 从左到右
    for (int i = 1; i < ratings.size(); i++) {
      if (ratings[i] > ratings[i - 1]) child[i] = child[i - 1] + 1;
    }
    // 从右到左
    for (int i = ratings.size() - 1; i >= 1; i--) {
      if (ratings[i - 1] > ratings[i])
        child[i - 1] = std::max(child[i] + 1, child[i - 1]);
    }
    return std::accumulate(child.begin(), child.end(), 0);
  }
};

int main() {
  vector<int> candy = {1, 0, 2, 3, 4, 7, 6, 4, 3, 1};
  Solution s;
  std::cout << "candy: " << s.candy(candy) << std::endl;
  return 0;
}