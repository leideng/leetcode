/* Problem Description:

Given a string s, partition s such that every substring of the partition is a palindrome.

Return all possible palindrome partitioning of s.

For example, given s = "aab",
Return

[
  ["aa","b"],
  ["a","a","b"]
]

*/

/* Algorithm Pseudocode: recursive implementation

   1. Use recursive DFS to print all possible partitions
   2. Store the isPalindrome_ matrix for every possible substring to save time

*/ 

class Solution 
{
    public:
    
    vector< vector<string> > partition(string s) 
    {
        s_ = s;
        constructIsPalindromeMatrix();
        dfs(0);
        return partitions_;
    }
    

    void dfs(int depth)
    { 
        if(depth == s_.size()) ///come to the end of this branch
        {
            partitions_.push_back(current_partition_);
        }
        
        if(depth < s_.size())
        {
            for(int i=depth; i < s_.size(); ++i)
            {
                if(isPalindrome_[depth][i])
                {
                    current_partition_.push_back(s_.substr(depth, i-depth+1));
                    dfs(i+1);
                    current_partition_.pop_back(); 
                }
            }
        }
        
    }
   
    ///use dynamic programming to construct the matrix isPalindrome_
    ///isPalindrome_[i][j]=true if s_[i] = s_[j] and isPalindrome_[i+1][j-1] = true 
    void constructIsPalindromeMatrix()
    {
        int n = s_.size();
        isPalindrome_ = vector< vector<bool> >(n, vector<bool>(n,false));
        
        for(int i=n-1; i >= 0; --i)
        {
            for(int j=i; j < n; ++j)
            {
                if((s_[i] == s_[j]) && ( (j <= i+2) || isPalindrome_[i+1][j-1]))
                {
                    isPalindrome_[i][j] = true;
                }
            }
        }
        
    }
   
   
    private:
   
    ///the original input string 
    string s_;
    
    ///store the matrix about whether the substring s_[i,j] is a palindrome
    vector< vector<bool> > isPalindrome_;
    
    ///the set of all partitions
    vector< vector<string> > partitions_;
   
    ///the current partition during dfs
    vector< string > current_partition_;
};