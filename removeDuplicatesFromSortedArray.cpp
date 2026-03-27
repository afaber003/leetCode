#include <vector>

using namespace std;
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        vector<int> uniques;
        for (auto number : nums) {
            if (uniques.empty() || uniques.back() != number) uniques.push_back(number);
        }
        for (int i = 0; i < uniques.size(); i++) {
            nums[i] = uniques[i];
        }
        return (int) uniques.size();
    }
};