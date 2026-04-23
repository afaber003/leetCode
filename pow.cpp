#include <cstdio>
#include <cmath>

class Solution {
public:
    double myPow(double x, int n) {
        if (n == 0) return 1.0;
        if (n == 1 || x == 1) return x;

    }
};

int main() {
    Solution s;
    std::printf("%lf\n", s.myPow(2, -4));
}