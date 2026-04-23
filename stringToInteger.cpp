#include <cmath>
#include <string>

class Solution {
public:
    int myAtoi(std::string s) {
        long long finalAnswer = 0;
        char mode = 0;
        bool isPos = true;
        unsigned int inputDigitCount = 0;

        unsigned int afterLastDigitIndex = 0;
        for (; afterLastDigitIndex < s.length(); afterLastDigitIndex++) {
            char& c = s[afterLastDigitIndex];
            switch (mode) {
                case 0: {
                    if (c == ' ') {
                        break;
                    }
                    mode = 1;
                }
                case 1: {
                    mode = 2;
                    if (c == '-') {isPos = false; break;}
                    if (c == '+') { break; }
                }
                case 2: {
                    if (c == '0') {
                        break;
                    }
                    mode = 3;
                }
                case 3: {
                    if (c < 48 || c > 57) {goto done;}
                    inputDigitCount++;
                    break;
                }
                default: {
                    printf("THis shoulkd not happen");
                    exit(1);
                }
            }
        }
        done:

        if (isPos) {
            if (inputDigitCount > 15) {
                return std::numeric_limits<int>::max();
            }
            for (int i = 0; i < inputDigitCount; i++) {
                finalAnswer += pullFromString(s, i, afterLastDigitIndex) * static_cast<unsigned long>(std::powl(10, i));
                if (finalAnswer > std::numeric_limits<int>::max()) {
                    return std::numeric_limits<int>::max();
                }
            }
        } else {
            if (inputDigitCount > 15) {
                return std::numeric_limits<int>::min();
            }
            for (int i = 0; i < inputDigitCount; i++) {
                finalAnswer -= pullFromString(s, i, afterLastDigitIndex) * static_cast<unsigned long>(std::powl(10, i));
                if (finalAnswer < std::numeric_limits<int>::min()) {
                    return std::numeric_limits<int>::min();
                }
            }
        }

        return static_cast<int>(finalAnswer);
    }

private:
    inline char pullFromString(const std::string& s, const int& i, const unsigned int& afterLastDigitIndex) {
        return s[afterLastDigitIndex - (i + 1)] - 48;
    }
};

int main() {
    printf("%d", Solution().myAtoi("20000000000000000000"));
}
