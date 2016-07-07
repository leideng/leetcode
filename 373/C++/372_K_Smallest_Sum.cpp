/** Problem 

You are given two integer arrays nums1 and nums2 sorted in ascending order and an integer k.

Define a pair (u,v) which consists of one element from the first array and one element from the second array.

Find the k pairs (u1,v1),(u2,v2) ...(uk,vk) with the smallest sums.

Example 1:
Given nums1 = [1,7,11], nums2 = [2,4,6],  k = 3
Return: [1,2],[1,4],[1,6]
The first 3 pairs are returned from the sequence:
[1,2],[1,4],[1,6],[7,2],[7,4],[11,2],[7,6],[11,4],[11,6]

Example 2:
Given nums1 = [1,1,2], nums2 = [1,2,3],  k = 2
Return: [1,1],[1,1]
The first 2 pairs are returned from the sequence:
[1,1],[1,1],[1,2],[2,1],[1,2],[2,2],[1,3],[1,3],[2,3]

Example 3:
Given nums1 = [1,2], nums2 = [3],  k = 3 
Return: [1,3],[2,3]
All possible pairs are returned from the sequence:
[1,3],[2,3]

*/

/** Algorithm outline
   
   Let m = nums1.size(), n = nums2.size()
   
   1. We consider the following 2-D matrix, say M, M[i][j] = nums1[i] + nums2[j]
   
      column 0   column 1         column n-1
      [0,0]      [1,0]     ...    [n-1,0]
      [0,1]      [1,1]     ...    [n-1,1]
      ...        ...       ...    ... 
      [0,m-1]    [1,m-1]   ...    [n-1,m-1]
  
   2. We should find the index of the k smallest elements in this matrix
   3. For each column, we know that it is sorted. If [i,j] has been selected, then
      [i-1, j], [i-2, j] .. [0,j] must also have been selected.
   4. Therefore, for each column, we maintain an index to record until which row is selected
   5. For those unselected elements, the smallest one must be the top un-visited element of one column (we have n columns in totol)
   6. After selecting the smallest element, we update the index of that column and continue  
   7. The complexity is O(k*n)

   Note: In this algorithm, I only use the property that each column of M is sorted. However,
   we did not use the property that each row of M is sorted.   
*/

class Solution 
{
    public:
    
    vector< pair<int, int> > kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) 
    {      

        vector< pair<int, int> > k_pairs;
        
        if(nums1.empty() || nums2.empty())
        {
            //return empty
            return k_pairs;
        }
        
        
        //int idx = vistied_col[i] is the index of the i-th column that has been visited, that is
        // For nums2[i], nums1[0,1,..., idx] has been added to k_paris        
        vector< int > visited_col(nums2.size(), -1);
        
        for(int i=0; i < k; ++i) //i means the i-th smallest pair
        {
            int sum = numeric_limits<int>::max();
            int m=-1;
            int n=-1;
            for(int col=0; col < nums2.size(); ++col)
            {
                int row_temp = visited_col[col];
                if( row_temp < ((int) nums1.size()) - 1 && nums1[row_temp+1] + nums2[col] < sum)
                {
                    sum = nums1[row_temp+1] + nums2[col];
                    m = row_temp+1;
                    n=col;
                }
            }
            
            if(m == -1 || n == -1)
            {
                break;
            }
            
            k_pairs.push_back( pair<int,int>(nums1[m], nums2[n]) ); 
            visited_col[n] = m;
        }
        
        return k_pairs;
    }
};