/** Problem

Given preorder and inorder traversal of a tree, construct the binary tree.

Note:
You may assume that duplicates do not exist in the tree.

*/

/** Algorithm Outline

    1 Use recursion
    2 We should not input a new vector for sub-tree's preorder or inorder. This 
      consumes a lot of time to pass arguments.
      Instead, we note that the preoder and inorder will not be changed and the 
      sub-tree's preoder and inorder are just consecutive sub-vector. So we only
      need to input the begin index and end index of the sub-tree.
    3 We should take care some special case where there is no left/right sub-tree.  
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution 
{
    public:
    
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) 
    {
        if(preorder.empty())
        {
            return NULL;
        }
        
        return buildTree_idx(preorder, inorder,  
                             0, preorder.size()-1,
                             0, inorder.size()-1);
    }
    
    // [preoder_idx_1, preoder_idx_2] is the preorder of the current sub-tree
    // [inorder_idx_1, inorder_idx_2] is the inorder of the current sub-tree
    TreeNode* buildTree_idx(vector<int>& preorder, vector<int>& inorder,
                            int preoder_idx_1, int preoder_idx_2,
                            int inorder_idx_1, int inorder_idx_2)
    {
        int root = preorder[preoder_idx_1];
        TreeNode* root_node = new TreeNode(root);
        if(preoder_idx_1 == preoder_idx_2) //only one node, this is redundant 
        {
            return root_node;
        }
        
        //find the position in the inoder of the root node
        int root_pos_inorder = find(inorder.begin()+inorder_idx_1, inorder.begin()+inorder_idx_2+1, root) - inorder.begin();
        
        if(root_pos_inorder == inorder_idx_1) //no left sub-tree now
        {
            root_node->left = NULL;
        }
        else
        {
            int left_preoder_idx_1 = preoder_idx_1 + 1;
            int left_preoder_idx_2 = preoder_idx_1 + (root_pos_inorder-inorder_idx_1);
            int left_inorder_idx_1 = inorder_idx_1;
            int left_inorder_idx_2 = root_pos_inorder - 1;
            root_node->left = buildTree_idx(preorder, inorder, 
                                            left_preoder_idx_1, left_preoder_idx_2, 
                                            left_inorder_idx_1, left_inorder_idx_2);
        }
        
        if(root_pos_inorder == inorder_idx_2) //no right sub-tree now
        {
            root_node->right = NULL;
        }
        else
        {
            int right_preoder_idx_1 = preoder_idx_1 + (root_pos_inorder-inorder_idx_1) + 1;
            int right_preoder_idx_2 = preoder_idx_2;
            int right_inorder_idx_1 = root_pos_inorder + 1;
            int right_inorder_idx_2 = inorder_idx_2; 
            root_node->right = buildTree_idx(preorder, inorder, 
                                             right_preoder_idx_1, right_preoder_idx_2, 
                                             right_inorder_idx_1, right_inorder_idx_2);
        }

        return  root_node;                               
    }        
    
};