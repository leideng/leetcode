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
        current_idx_ = 0;
        //get the number of all combinations
        long num_combinations = getNumOfCombiantions(n, k);
        combinations_ = vector< vector<int> >(num_combinations, vector<int>(k,0));
        
        my_stack_.push(1);
        
        //the loop logic is based on, either the current stack is full or not full
        // 1. If not full, get the top element, add 1, and push into the stack
        // 2. If full, we should pop the stack, but we should decide to pop how many times
        //    Example, n=6, k=4
        //    (i) If the current stack is [1,2,5,6], we should pop 6,5,2 and get the stack to be [1]
        //    and then we should push 2+1=3 into the stack, so the stack is [1,3]
        //    (ii) If the current stack is [3,4,5,6], we should pop 6,5,4,3 and the stack is empty []
        //     and then the loop is terminated         
        while(1)
        {
            if(my_stack_.size() < k)
            {
                my_stack_.push(my_stack_.top()+1); 
            }
            else // my_stack_.size() == k, the stack is full now
            {
               //first put the current full stack into the combination set
               addCurrentCombination(my_stack_);
               //pop the stack
               for(int i=0; i < k; ++i)
               {
                   int temp = my_stack_.top();
                   my_stack_.pop();
                   if(temp < n - i)
                   {
                       my_stack_.push(temp+1);
                       break;
                   }
               }
               //cannot push any more
               if(my_stack_.empty())
               {
                   break;
               }
            }
        }
        return combinations_;
    }
    
    
    ///add the current combination in the full stack into combinations_
    void addCurrentCombination(stack<int> my_stack)
    {
        for(int i=my_stack.size()-1; i >= 0; --i)
        {
            combinations_[current_idx_][i] = my_stack.top();
            my_stack.pop();
        }
        current_idx_++;
    }
    
    ///get n choose k
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
    
    
    private:
    
    ///the set of all combinations
    vector< vector<int> > combinations_;
    
    ///the index of current combination
    int current_idx_;
    
    ///the working stack_
    stack<int> my_stack_;
};