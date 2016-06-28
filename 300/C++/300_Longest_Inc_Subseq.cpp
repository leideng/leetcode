/** Problem 

Given an unsorted array of integers, find the length of longest increasing subsequence.

For example,
Given [10, 9, 2, 5, 3, 7, 101, 18],
The longest increasing subsequence is [2, 3, 7, 101], therefore the length is 4. Note that there may be more than one LIS combination, it is only necessary for you to return the length.

Your algorithm should run in O(n2) complexity.

Follow up: Could you improve it to O(n log n) time complexity?

*/

/** Algorithm Outline

    1. Find all (effective) increasing subsequences, where each time add a new element of the array
    2. We keep that all subsequences have different length, because, 
       for the same-length subsequences, we only need to keep the one with the smallest tail.
    3. When we add a new element, we add it to the longest possible subsequence as a new subsequence
    4. We keep the set of subsequences in the order of increasing length
    
    Example: [10, 9, 2, 5, 3, 7, 101, 18]
    
    Step 1: Add 10
    Subseq 0: [10] 
    
    Step 2: Add 9
    Subseq 0: [9]
    
    Step 3: Add 2 
    Subseq 0: [2]
    
    Step 4: Add 5 (to [2])
    Subseq 0: [2]
    Subseq 1: [2,5]
    
    Step 5: Add 3 (to [2])
    Subseq 0: [2]
    Subseq 1: [2,3]
    
    Step 6: Add 7 (to [2,3])
    Subseq 0: [2]
    Subseq 1: [2,3]
    Subseq 2: [2,3,7]
    
    Step 7: Add 101 (to [2,3,7])
    Subseq 0: [2]
    Subseq 1: [2,3]
    Subseq 2: [2,3,7]
    Subseq 3: [2,3,7,101]
    
    Step 8: Add 18 (to [2,3,7])
    Subseq 0: [2]
    Subseq 1: [2,3]
    Subseq 2: [2,3,7]
    Subseq 3: [2,3,7,18]
*/

class Solution 
{
    public:
    
    int lengthOfLIS(vector<int>& nums) 
    {
        if(nums.empty())
        {
            return 0;
        }
        
        //the set of all increasing subsequences, all of which have different length.
        //For the same-length subsequences, we only need to keep the one with the smallest tail.
        //We assume the size is increasing, i.e., subseq[0] has the smallest size
        vector< vector<int> > subseq;
        subseq.push_back( vector<int>(1, nums[0]) );
        
       // printSubseq(subseq);
        
        for(int i=1; i < nums.size(); ++i)
        {
            int s;
            for(s=subseq.size()-1; s >= 0; --s)
            {
                if(subseq[s].back() < nums[i])
                {
                    vector<int> new_sub = subseq[s];
                    new_sub.push_back(nums[i]);
                                 
                    if(s == subseq.size()-1) //this is the last subsequence
                    {
                        subseq.push_back(new_sub); //we just push back it
                    }
                    else
                    {
                        if(subseq[s+1].size() == new_sub.size()) //the next subsequence has the same size of the new subsequence
                        {
                            if(subseq[s+1].back() > new_sub.back()) //the new subsequence ends with smaller tail
                            {
                                subseq[s+1] = new_sub; //we then replace the next subsequence with the new subsequence
                            }
                        }
                    }           
                    break;
                }
            }
            
            if(s == -1) //come to the end of all subsequence
            {
                if(subseq[0].size() == 1)
                {
                    if(subseq[0][0] > nums[i])
                    {
                        subseq[0][0] = nums[i];
                    }
                }
                else
                {
                    subseq.insert(subseq.begin(), vector<int>(1, nums[i]) ); //we put this element as a single-element subsequence
                }
            }
            
         //   printSubseq(subseq);
        }            
        
        return subseq.back().size();
    }
    
    void printSubseq(const vector< vector<int> >& subseq)
    {
        for(int i=0; i < subseq.size(); ++i)
        {
            cout << "Subseq " << i << ": ";
            for(int j=0; j < subseq[i].size(); ++j)
            {
                cout << subseq[i][j] << ",";
            }
            cout << endl;
        }
    }
};