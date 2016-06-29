/** Problem

Given a sorted array of integers, find the starting and ending position of a given target value.

Your algorithm's runtime complexity must be in the order of O(log n).

If the target is not found in the array, return [-1, -1].

For example,
Given [5, 7, 7, 8, 8, 10] and target value 8,
return [3, 4].

*/

/** Algorithm Outline

    1. First binary algorithm for a position (pos) of the target value
    2. Then for the left interval [0,pos], find the first element of the target value, serving as the left index (left)
    3. And for the right interval [pos, n], find the last element of the target value, serving as the right index (right)
    
*/

class Solution 
{
    public:
    
    vector<int> searchRange(vector<int>& nums, int target) 
    {
        //first binary search for a position for the target
        int min=0;
        int max=nums.size()-1;
        int pos = -1;
        while(min <= max)
        {
            int mid = (min+max)/2;
            if(nums[mid] == target)
            {
                pos = mid;
                break;
            }
            else if(nums[mid] < target)
            {
                min=mid+1;
            }
            else //nums[mid] > target
            {
                max=mid-1;
            }
        }
        
        if(pos == -1) //we did not find any position of the target value
        {
            return vector<int>(2,-1);
        }
        
        //now for [0, pos], we need to find the first position of the target value
        int left=pos;
        min=0;
        while(min < left)
        {
            int mid = (min+left)/2;
            if(nums[mid] < target)
            {
                min = mid + 1;
            }
            else //nums[mid] = target
            {
                left = mid;
            }
        }
        
        //now for [pos, nums.size()-1], we need to find the last position of the target value
        int right=pos;
        max=nums.size()-1;
        while(right < max)
        {
            int mid = (right+max+1)/2; //note that here we have mid=(right+max+1)/2
                                       //This is for the case that right=max-1. 
                                       //e.g., nums=[2,2]
                                       //we find pos=0
                                       //then the original right=0, max=1
                                       //then mid=1, and we can set right=1, and then terminate
            if(nums[mid] > target)
            {
                max = mid - 1;
            }
            else //nums[mid] = target
            {
                right = mid;
            }
        }
        
        vector<int> result;
        result.push_back(left);
        result.push_back(right);
        
        return result;
    }
};