/** Problem 

Given an unsorted array of integers, find the length of the longest consecutive elements sequence.

For example,
Given [100, 4, 200, 1, 3, 2],
The longest consecutive elements sequence is [1, 2, 3, 4]. Return its length: 4.

Your algorithm should run in O(n) complexity.

*/

/** Algorithm Outline
    
    1. Use hash table to determine whether a number is in the array
    2. Keep reducing the hash table size to avoid the redundant check.

*/

class Solution 
{
    public:
    
    int longestConsecutive(vector<int>& nums) 
    {
        unordered_map<int, bool> hash;
        for(int i=0; i < nums.size(); ++i)
        {
            hash[nums[i]] = true;
        }
        
        int max = -1;
        //for each element, we check the longest consecutive sequence, [down+1, up-1] (or (down, up)), that contains it
        for(int i=0; i < nums.size(); ++i)
        {
            //we find the up  
            int up = nums[i];
            while (hash.find(up) != hash.end()) 
            { 
                hash.erase(up);
                up++;
            }
            
            //we find the down  
            int down = nums[i] - 1;
            while (hash.find(down) != hash.end()) 
            {
                //we can remove this value in the hash, because we no longer need to check this value now
                hash.erase(down);
                down--;
            }
            
            if(up - down - 1 > max)
            {
                max = up - down - 1;
            }
        }
        
        return max;
    }
};    