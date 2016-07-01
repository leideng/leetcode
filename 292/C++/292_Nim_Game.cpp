/** Problem

You are playing the following Nim Game with your friend: There is a heap of stones on the table, each time one of you take turns to remove 1 to 3 stones. The one who removes the last stone will be the winner. You will take the first turn to remove the stones.

Both of you are very clever and have optimal strategies for the game. Write a function to determine whether you can win the game given the number of stones in the heap.

For example, if there are 4 stones in the heap, then you will never win the game: no matter 1, 2, or 3 stones you remove, the last stone will always be removed by your friend.

*/

/** Algorithm Outline

    1 The original idea is to use dynamic programming
    2 However, it turns out that this problem has a very special pattern:
      you will fail only when n is a multiplier of 4, i.e., n=4,8,12,...
*/


///loop
/** Time limit exceeded
class Solution 
{
    public:
    
    bool canWinNim(int n) 
    {
        vector<bool> can_win_v(n+1, false);
        
        for(int i=1; i <= n; ++i)
        {
            if(i <= 3) 
            {
                can_win_v[i] = true;
            }
            else
            {
                can_win_v[i] = ((!can_win_v[i-1]) || (!can_win_v[i-2]) || (!can_win_v[i-3]));
            }
        }
        
        return can_win_v[n];
    }
};
*/

///try to find the following pattern
class Solution 
{
    public:      
    
    bool canWinNim(int n) 
    {
        return n % 4 != 0;
    }
};