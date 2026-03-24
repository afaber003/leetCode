#include <string>
#include <unordered_map>

class Solution {
public:
    int lengthOfLongestSubstring(std::string s) {
        int finalAnswer = 0;
        auto map = std::unordered_map<char, int>{};

        for (int index = 0; index < s.size(); ++index) {
            char c = s[index];
            if (map.contains(c)) {
                finalAnswer = std::max(static_cast<int>(map.size()), finalAnswer);
                index = map.at(c);
                map.clear();
            } else {
                map.insert(std::pair(c, index));
            }
        }

        return std::max(static_cast<int>(map.size()), finalAnswer);
    }
};

int main() {
    std::string s = "abcabcbb";
    printf("%d", Solution().lengthOfLongestSubstring(s));
}
