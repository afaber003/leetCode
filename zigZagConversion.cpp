#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    string convert(string s, int numRows) {
        if (numRows == 1) {
            return s;
        }
        string finalAns;
        for (short i = 0; i < numRows; i++) {
            printRow(s, finalAns, i, static_cast<short>(numRows));
        }
        return finalAns;
    }

    static void printRow(const string& s, string& ans, const short thisRow, const short totalRows) {
        short offset = (totalRows - 1) * 2;
        auto stringLength = static_cast<short>(s.length());

        if (thisRow == 0 || thisRow == totalRows - 1) { // first or last row
            for (int i = thisRow; i < stringLength; i += offset) {
                ans.push_back(s[i]);
            }
        } else { // interior row
            int indexOfFirstOne = thisRow;
            int indexOfSecondOne = thisRow + ((totalRows - 1 - thisRow) * 2);
            for (; indexOfFirstOne < stringLength; indexOfFirstOne += offset) {
                ans.push_back(s[indexOfFirstOne]);
                if (indexOfSecondOne < stringLength) {
                    ans.push_back(s[indexOfSecondOne]);
                }
                indexOfSecondOne += offset;
            }
        }
    }
};

int main() {
    Solution s;
    printf("%s", s.convert("PAYPALISHIRING", 4).c_str());
}