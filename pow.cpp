#include <cstdio>

class Solution {
public:
    double myPow(double x, int n) {
        if (n == 0) return 1.0;
        for (int i = 1; i < +n; i++) {
            x *= x;
        }
        return n > 0 ? x : (1/x);
    }
};

int main() {
    Solution s;
    std::printf("%lf\n", s.myPow(2, -2));
}