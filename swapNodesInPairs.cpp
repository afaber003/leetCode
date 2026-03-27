

/*Definition for singly-linked list. */
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }

        ListNode* finalHead = swapWithNext(head);
        ListNode* current = finalHead->next;
        while (current != nullptr && current->next != nullptr) {
            ListNode* newNext = swapWithNext(current->next);
            current->next = newNext;
            current = newNext->next;
        }
        return finalHead;
    }

private:
    // Returns the new start one
    ListNode* swapWithNext(ListNode* start) {
        if (start == nullptr) {
            return nullptr;
        }
        if (start->next == nullptr) {
            return start;
        }

        ListNode* nextOne = start->next;
        ListNode* oneAfterAll = nextOne->next;
        start->next = oneAfterAll;
        nextOne->next = start;
        return nextOne;
    }
};