/** Problem 

Given a sorted linked list, delete all nodes that have duplicate numbers, leaving only distinct numbers from the original list.

For example,
Given 1->2->3->3->4->4->5, return 1->2->5.
Given 1->1->1->2->3, return 2->3.

*/

/** Algorithm Outline

    1. Add a fake node to be the prenode of the head
    2. Keep changing the prenode->next and current node 
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution 
{
    public:
    
    ListNode* deleteDuplicates(ListNode* head) 
    {
        if(head == NULL)
        {
            return NULL;
        }
        
        ListNode* fake_node = new ListNode(0);
        fake_node->next = head;
        ListNode* current = head;
        ListNode* prev = fake_node; //prev is the prenode of the current node
        while(current != NULL)
        {     
            int current_val = current->val;
            ListNode* next = current->next;
            if(next != NULL && next->val == current_val) //we need change the current pointer
            {
                while(next != NULL && next->val == current_val)
                {
                    next = next->next;
                }
                prev->next = next;
                current = next;
            }
            else
            {
                prev = current;
                current = current->next;
            }
        }
        
        return fake_node->next;
    }
};