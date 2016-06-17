/** Problem

Given an array of integers, return indices of the two numbers such that they add up to a specific target.

You may assume that each input would have exactly one solution.

Example:
Given nums = [2, 7, 11, 15], target = 9,

Because nums[0] + nums[1] = 2 + 7 = 9,
return [0, 1].

*/

/** Algorithm Outline
    
    1. We create a map/hash table for  <value, index>
    2. Loop for each element nums[i], we then try to find the complement target-nums[i] in the map
    3. Note that it is possible that target = a + a, and there are two a's in the vector. We take it as a special case.

*/

class Solution 
{
    public:
    
    vector<int> twoSum(vector<int>& nums, int target) 
    {
        int a;
        int b;
        vector<int> result;
        //take care of the special case target = a + a
        if(target % 2 == 0) //target is an even number
        {
            a=target/2;
            vector<int>::iterator a_iter = find(nums.begin(), nums.end(), a);
            if(a_iter != nums.end())//we have found a, and we try to find another a
            {
                vector<int>::iterator b_iter = find(a_iter+1, nums.end(), a);
                if(b_iter != nums.end()) // indeed we find another a
                {
                    result.push_back(a_iter - nums.begin());
                    result.push_back(b_iter - nums.begin());
                    return result;
                }
            }
        }
        
        
        //build the map
        map<int, int> value_idx_map;
        for(int i=0; i < nums.size(); ++i)
        {
            value_idx_map[nums[i]] = i;
        }
        
        //find the two elements
        for(int i=0; i < nums.size(); ++i)
        {
            a = nums[i];
            b = target - a;
            
            if(b == a) //we do not need to handle special case, but it affects the later serach for b
            {
                continue;
            }
            
            map<int, int>::iterator mi = value_idx_map.find(b);
            if(mi != value_idx_map.end()) //we find b
            {                
                result.push_back(i);
                result.push_back(mi->second);
                return result;
            }
        }
        
        //fake return
        return result;
       
    }
};