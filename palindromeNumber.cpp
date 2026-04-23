#include <cmath>
#include <stack>

class Solution {
public:
    // double pointer integer version
    bool isPalindrome(const int& x) {
        if (x < 0) return false;
        char digitCount = 0;
        while (x / static_cast<long>(std::pow(10, digitCount)) > 0) {
            digitCount++;
        }

        char leftPointer = 0;
        char rightPointer = digitCount - 1;
        while (leftPointer < rightPointer) {
            char leftDigit = grabDigit(x, leftPointer);
            char rightDigit = grabDigit(x, rightPointer);
            if (leftDigit != rightDigit) { return false; }
            leftPointer++;
            rightPointer--;
        }
        return true;
    }

    static inline char grabDigit(const int& source, const char& index) {
        return static_cast<char>((source / static_cast<long>(std::pow(10, index))) % 10);
    }

    // integer version
    // bool isPalindrome(const int& x) {
    //     if (x < 0) return false;
    //     if (x == 0) return true;
    //
    //     int digitCount = 0;
    //     while (x / static_cast<long>(std::pow(10, digitCount)) > 0) {
    //         digitCount++;
    //     }
    //
    //     std::stack<int> digitStack;
    //     int expIndex = 0;
    //     for (; expIndex < digitCount / 2; expIndex++) {
    //         digitStack.emplace((x / static_cast<long>(std::pow(10, expIndex))) % 10);
    //     }
    //
    //     if (digitCount % 2) { expIndex += 1; }
    //
    //     for (; expIndex < digitCount; expIndex++) {
    //         if (((x / static_cast<long>(std::pow(10, expIndex))) % 10) != digitStack.top()) {
    //             return false;
    //         }
    //         digitStack.pop();
    //     }
    //
    //     return true;
    // }

    // String version
    // bool isPalindromeString(const int& x) {
    //     if (x < 0) return false;
    //     if (x == 0) return true;
    //
    //     std::string xString = std::to_string(x);
    //     int digitCount = xString.length();
    //     std::stack<char> digitStack;
    //
    //     int expIndex = 0;
    //     for (; expIndex < digitCount / 2; expIndex++) {
    //         digitStack.emplace(xString[expIndex]);
    //     }
    //     if (digitCount % 2) { expIndex += 1; }
    //
    //     for (; expIndex < digitCount; expIndex++) {
    //         if (xString[expIndex] != digitStack.top()) {
    //             return false;
    //         }
    //         digitStack.pop();
    //     }
    //
    //     return true;
    // }
};

int main() {
    Solution s;
    printf("%d ", s.isPalindrome(10));
}
