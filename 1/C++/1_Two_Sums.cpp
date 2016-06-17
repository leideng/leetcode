/** Problem

Given an array of integers, return indices of the two numbers such that they add up to a specific target.

You may assume that each input would have exactly one solution.

Example:
Given nums = [2, 7, 11, 15], target = 9,

Because nums[0] + nums[1] = 2 + 7 = 9,
return [0, 1].

*/

/** Algorithm Outline
    
    1. First sort the vector in an ascending order  and store it in another vector
    2. Loop for each element from the smallest to the largest, and loop again for another element
    3. After finding the two elements, find its position in the original vector (must be unique)
       However, note that if the two elements are the same, we should find their positions different

*/

class Solution 
{
    public:
    
    vector<int> twoSum(vector<int>& nums, int target) 
    {
        vector<int> nums_sroted = nums;
        sort(nums_sroted.begin(), nums_sroted.end());
        
        int a;
        int b;
        vector<int> result;
        for(int i=0; i < nums_sroted.size(); ++i)
        {
            a = nums_sroted[i];
            for(int j=i+1; j < nums_sroted.size(); ++j)
            {
                b=nums_sroted[j];
                if(a+b == target)
                {
                    //have found the two elements;
                    vector<int>::iterator a_iter = find(nums.begin(), nums.end(), a);
                    int a_idx = a_iter - nums.begin();
                    int b_idx;
                    if(a == b) // a==b, find another a/b from the next elements of a_iter
                    { 
                        b_idx = find(a_iter+1, nums.end(), b) - nums.begin();
                    }
                    else
                    {
                        b_idx = find(nums.begin(), nums.end(), b) - nums.begin();
                    }
                    result.push_back(a_idx);
                    result.push_back(b_idx);
                    return result;
                }
                else if(a+b > target) //terminate the inner loop, this can save much time as we have sorted the vector
                {
                    break;
                }
            }
        }
        
        //fake return
        return result;   
    }
};