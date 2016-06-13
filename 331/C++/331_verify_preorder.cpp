/** Problem Description:

One way to serialize a binary tree is to use pre-order traversal. When we encounter a non-null node, we record the node's value. If it is a null node, we record using a sentinel value such as #.

     _9_
    /   \
   3     2
  / \   / \
 4   1  #  6
/ \ / \   / \
# # # #   # #
For example, the above binary tree can be serialized to the string "9,3,4,#,#,1,#,#,2,#,6,#,#", where # represents a null node.

Given a string of comma separated values, verify whether it is a correct preorder traversal serialization of a binary tree. Find an algorithm without reconstructing the tree.

Each comma separated value in the string must be either an integer or a character '#' representing null pointer.

You may assume that the input format is always valid, for example it could never contain two consecutive commas such as "1,,3".

Example 1:
"9,3,4,#,#,1,#,#,2,#,6,#,#"
Return true

Example 2:
"1,#"
Return false

Example 3:
"9,#,#,1"
Return false

*/

/** Algorithm Outline
    
    1. Use Stack to store the node 
    2. Whenever two #'s occur, remove these two #'s and the top non-null node in the stack
    3. Remember to delete all non-null tree nodes cascade 
    
*/

class Solution 
{
    public:
    
    bool isValidSerialization(string preorder) 
    {
        //return true for the empty tree
        if(preorder == "#")
        {
            return true;
        }
        
        stack<string> tree_stack;
        //the current index to the beginning of the next element 
        int current_idx = 0;
        while(current_idx < preorder.size())
        {
            if(preorder[current_idx] == '#')
            {
                if(tree_stack.empty())
                {
                    return false;
                }
                
                if(tree_stack.top() == "#") //we use -1 to represent # in the stack
                {
                     //we need delete all non-null tree nodes cascade 
                     //let us find where should we stop
                     while(1)
                     {
                         tree_stack.pop(); //pop '#'
                         tree_stack.pop(); //pop the top non-null tree node 
                         if(tree_stack.empty()) //tree_stack is empty now, we are done
                         {
                             return (current_idx == (preorder.size() - 1));
                         }
                         else if(tree_stack.top() == "#") //if we find another '#', we do it again
                         {
                             continue;
                         }
                         else //otherwise, we stop it here and push '#' into the stack
                         {
                             tree_stack.push("#");
                             break;
                         }
                     }
                }
                else
                {
                    tree_stack.push("#");
                }
                
                //remember to update current_idx
                current_idx += 2;
            }
            else //preorder[current_idx] != '#'
            {
                int next_comma_idx = preorder.find(',',current_idx);
                if(next_comma_idx == string::npos) //we find the final word
                {
                    tree_stack.push(preorder.substr(current_idx));
                    current_idx = preorder.size();
                }
                else
                {
                    tree_stack.push(preorder.substr(current_idx, next_comma_idx-current_idx));
                    current_idx = next_comma_idx+1;
                }
            }
        }
        
        return tree_stack.empty();
        
    }
};