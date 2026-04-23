#include <cstdio>
/**
* Definition for singly-linked list. */
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* current = head;
        ListNode* beforeRemoval = head;

        unsigned int iterationsBehind = 0;
        bool removeFirstOne = true;
        while (current != nullptr) {
            current = current->next;
            if (iterationsBehind++ >= n) {
                if (!removeFirstOne)
                    beforeRemoval = beforeRemoval->next;
                removeFirstOne = false;
            }
        }

        if (removeFirstOne) {
            head = head->next;
            delete beforeRemoval;
        } else {
            const auto oneToRemove = beforeRemoval->next;
            beforeRemoval->next = oneToRemove ? oneToRemove->next : nullptr;
            delete oneToRemove;
        }
        return head;
    }
};

int main() {
    Solution s;
    ListNode *head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);
    s.removeNthFromEnd(head, 2);

    auto temp = head;
    do {
        printf("%d,", temp->val);
        temp = temp->next;
    } while (temp != nullptr);

    return 0;
}