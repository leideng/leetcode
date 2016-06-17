/** Problem 

Implement next permutation, which rearranges numbers into the lexicographically next greater permutation of numbers.

If such arrangement is not possible, it must rearrange it as the lowest possible order (ie, sorted in ascending order).

The replacement must be in-place, do not allocate extra memory.

Here are some examples. Inputs are in the left-hand column and its corresponding outputs are in the right-hand column.
1,2,3 ¡ú 1,3,2
3,2,1 ¡ú 1,2,3
1,1,5 ¡ú 1,5,1

*/

/** Algorithm Outline

    1 From the last element to the first element, find the position that we want to increase 
      The condition is the first time we find  an i such that nums[i+1] > nums[i]. 
    2 If we can find the position, we increase nums[i-1] and sort the remaining elements
    3 If we cannot find the position, we come to the last permutation, and we just sort to come to the first permutation
    4 We should make use of the fact [i+1,i+2, ..., n-1] has already been in a descending order. 
      We can then just reverse the sub-vector to do sorting.

*/


class Solution 
{
    public:
    
    void nextPermutation(vector<int>& nums) 
    {
        int n = nums.size();
        if(n <= 1)
        {
            return;
        }
        
        //find the position that we want to increase
        int position = -1;
        for(int i = n-2; i >= 0; --i)
        {
            if(nums[i+1] > nums[i])
            {
                position = i;
                break;
            }
        }

        
        if(position == -1) //we cannot find the position to increase
        {
            //revert the vector to get the first elements
            reverse(nums.begin(),nums.end());
            return;
        }
        else //we can find the position
        {
            //we find the smallest element in [position+1,position+2, ..., n-1] that is larger than nums[position]
            for(int i=n-1; i > position; --i)
            {
                if(nums[i] > nums[position])
                {
                    //swap nums[i] and nums[position]
                    int temp = nums[position];
                    nums[position] = nums[i];
                    nums[i] = temp;
                    
                    //then we revert the remaining elements, i.e., [position+1,position+2, ..., n-1]
                    reverse(nums.begin()+position+1, nums.end());
                    
                    return;
                }
            }                
        }
    }
};