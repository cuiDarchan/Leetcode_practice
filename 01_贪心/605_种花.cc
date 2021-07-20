#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
 public:
  bool canPlaceFlowers(vector<int>& flowerbed, int n) {
    // own, 暴力解法
    // int size = flowerbed.size();
    // for (int i = 0; i < size; i++) {
    //   if (!flowerbed[i]) {
    //     // 普通情况
    //     if (i > 0 && i < size - 1) {
    //       if (flowerbed[i - 1] == 0 && flowerbed[i + 1] == 0) {
    //         flowerbed[i] = 1;
    //         n--;
    //       }
    //     }
    //     // 左边界,[0] 或者 [0,1,xx]
    //     else if (!i) {
    //       if (i + 1 == size || flowerbed[i + 1] == 0) {
    //         flowerbed[i] = 1;
    //         n--;
    //       }
    //     }
    //     // 右边界
    //     else {
    //       if (flowerbed[i - 1] == 0) {
    //         flowerbed[i] = 1;
    //         n--;
    //       }
    //     }
    //   }
    // }
    // return n <= 0;

    // 官方解法,根据（j-i-2）/2
    int prev = -1;
    int size = flowerbed.size();
    int m = 0;
    for (int i = 0; i < size; i++) {
      if (flowerbed[i] == 1) {
        // 左边界全是0
        if (prev < 0) {
          m += i / 2;
        } else {
          m += (i - prev - 2) / 2;
        }
        prev = i;
      }
    }
    // 全0的情况
    if (prev < 0) {
      m += (size + 1) / 2;  //[0] , 1
    } else {
      m += (size - prev - 1) / 2;
    }
    return m >= n;
  }
};

int main() {
  vector<int> test = {0, 0, 1, 0, 1};
  int n = 1;
  Solution s;
  std::cout << "Test result: " << s.canPlaceFlowers(test, n) << std::endl;
  return 0;
}