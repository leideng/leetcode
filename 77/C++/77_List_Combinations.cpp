/** Problem Description:

Given two integers n and k, return all possible combinations of k numbers out of 1 ... n.

For example,
If n = 4 and k = 2, a solution is:

[
  [2,4],
  [3,4],
  [2,3],
  [1,2],
  [1,3],
  [1,4],
]

*/

/** Algorithm Outline
    
    1. Use recursive DFS to print all possible combinations
    
*/

class Solution 
{
    public:
    
    vector< vector<int> > combine(int n, int k) 
    {
        n_ = n;
        current_combination_index_ = 0;
        //get the number of all combinations
        long num_combinations = getNumOfCombiantions(n, k);
        combinations_ = vector< vector<int> >(num_combinations, vector<int>(k,0));
        dfs(1, k);
        return combinations_;
    }
    
    long getNumOfCombiantions(int n, int k)
    {
        long nominator = 1;
        long denominator = 1;
        for(int i=1; i <= k; i++)
        {
            nominator *= (n-(i-1));
            denominator *= i;
        } 
        return nominator/denominator;
    }
    
    void dfs(int depth, int k)
    { 
        if(k == 0) ///come to the end of this branch
        {
            combinations_[current_combination_index_] = current_combination_;
            current_combination_index_++;
        }
        else // k > 0
        {
            for(int i=depth; i <= n_; ++i)
            {
                current_combination_.push_back(i);
                dfs(i+1,k-1);
                current_combination_.pop_back(); 
            }
        } 
    }
    
    private:
    
    int n_;
    vector< vector<int> > combinations_;
    int current_combination_index_;
    vector<int> current_combination_;
};