/** Problem Description

You are given two linked lists representing two non-negative numbers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.

Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 0 -> 8

*/

/** Algorithm outline
   
   1. Use one carry number
   2. The input list could have different length

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
    
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) 
    {
        if(l1 == NULL && l2 == NULL)
        {
            return NULL;
        }
        
        //not both l1 and l2 are empty
        ListNode* result = new ListNode(-1);
        
        ListNode* l1_idx = l1;
        ListNode* l2_idx = l2;
        ListNode* result_idx = result;
        
        int last_carry = 0;
        while(1)
        {
            int sum =  last_carry;
            if(l1_idx != NULL)
            {
                sum += l1_idx->val;
            }
            if(l2_idx != NULL)
            {
                sum += l2_idx->val;
            }
            
            if(sum < 10)
            {
                last_carry = 0;
                result_idx->val = sum;    
            }
            else
            {
                last_carry = 1;
                result_idx->val = sum - 10;
            }
            
            if(l1_idx == NULL || l1_idx->next == NULL)
            {
                l1_idx = NULL;
            }
            else
            {
                l1_idx = l1_idx->next;
            }
            
            if(l2_idx == NULL || l2_idx->next == NULL)
            {
                l2_idx = NULL;
            }
            else
            {
                l2_idx = l2_idx->next;
            }
            
            if(l1_idx == NULL && l2_idx == NULL && last_carry==0)
            {
                break;
            }
            else 
            {
                result_idx->next = new ListNode(-1);
                result_idx = result_idx->next; 
            }
        }

        return result;
    }
};