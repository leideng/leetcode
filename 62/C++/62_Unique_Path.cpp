/** Problem

A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).

The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).

How many possible unique paths are there?

*/

/** Algorithm Outline

    1 Use dynamic programming
    
*/


/**  Recursion, time limit exceeded 
class Solution 
{
    public:
    
    int uniquePaths(int m, int n) 
    {
        if(m==1 || n == 1) 
        {
            return 1;
        }
        else
        {
            return uniquePaths(m,n-1) + uniquePaths(m-1,n);
        }
    }
};

*/

class Solution 
{
    public:
    
    int uniquePaths(int m, int n) 
    {
        vector< vector<int> > nums(m, vector<int>(n, 0));
        
        for(int i=0; i<m; ++i)
        {
            for(int j=0; j<n; j++)
            {
                if(i==0 || j == 0)
                {
                    nums[i][j] = 1;
                }
                else
                {
                    nums[i][j] = nums[i-1][j] + nums[i][j-1];
                }                    
            }
        }
        
        return nums[m-1][n-1];
    }
};