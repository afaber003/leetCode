#include <cstdio>
#include <vector>

/* Definition for singly-linked list. */
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

using namespace std;

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode* resultHead = nullptr;
        ListNode* resultTail = nullptr;

        ListNode* nextNodeToOperateOn = getNextNodeToUse(lists);
        for (; nextNodeToOperateOn != nullptr; nextNodeToOperateOn = getNextNodeToUse(lists)) {
            if (resultHead == nullptr) {
                resultHead = nextNodeToOperateOn;
                resultTail = nextNodeToOperateOn;
                continue;
            }
            resultTail->next = nextNodeToOperateOn;
            resultTail = resultTail->next;
        }

        return resultHead;
    }

    ~Solution() {
        delete smallestNextNodeDEFAULT;
    }

private:
    ListNode* smallestNextNodeDEFAULT = new ListNode(10000);

    ListNode* getNextNodeToUse(vector<ListNode*>& lists) {
        auto smallestNextNode = smallestNextNodeDEFAULT;
        int indexToStep = -1;
        for (int i = 0; i < lists.size(); i++) {
            ListNode* listHead = lists[i];
            if (listHead != nullptr && listHead->val < smallestNextNode->val) {
                smallestNextNode = listHead;
                indexToStep = i;
            }
        }

        if (indexToStep != -1) {
            lists[indexToStep] = smallestNextNode->next;
        }
        // case where there is no next one (also known as done lmao)
        if (smallestNextNode == smallestNextNodeDEFAULT) {
            return nullptr;
        }
        return smallestNextNode;
    }
};

int main() {
    Solution s;
    ListNode* list1 = new ListNode(1, new ListNode(4, new ListNode(5)));
    ListNode* list2 = new ListNode(1, new ListNode(3, new ListNode(4)));
    ListNode* list3 = new ListNode(2, new ListNode(6));
    vector lists = {
        list1, list2, list3
    };

    ListNode* result = s.mergeKLists(lists);
    for (; result != nullptr; result = result->next) {
        printf("%d\n", result->val);
    }
}