/** Problem

You are given coins of different denominations and a total amount of money amount. Write a function to compute the fewest number of coins that you need to make up that amount. If that amount of money cannot be made up by any combination of the coins, return -1.

Example 1:
coins = [1, 2, 5], amount = 11
return 3 (11 = 5 + 5 + 1)

Example 2:
coins = [2], amount = 3
return -1.

*/

/** Algorithm Outline

    1 Use dynamic programming
    
*/

class Solution 
{
    public:
    
    int coinChange(vector<int>& coins, int amount) 
    {
        if(amount == 0)
        {
            return 0;
        }
        
        if(amount < 0)
        {
            return -1;
        }
        
        //change_v[i] is the fewest number of coins that you need to make up amount i
        //We thus need to get change_v[amount]
        vector<int> change_v(amount+1, -1);
        
        //initialize change_v
        for(int i=0; i < coins.size(); ++i)
        {
            if(coins[i] <= amount)
            {
                change_v[coins[i]] = 1;
            }
        }
        
        //build change_v
        for(int a=1; a <= amount; ++a)
        {
            if(change_v[a] == 1)
            {
                continue;
            }
            
            //change_v[a] == -1 or change_v[a] > 1
            for(int i=0; i < coins.size(); ++i)
            {
                if(coins[i] < a)
                {
                    if(change_v[a] == -1) //change_v[a] == -1
                    {
                        if(change_v[a-coins[i]] > 0)
                        {
                            change_v[a] = 1 + change_v[a-coins[i]];
                        }
                    }
                    else //change_v[a] > 1
                    {
                        if(change_v[a-coins[i]] > 0)
                        {
                            change_v[a] = min(change_v[a], 1+change_v[a-coins[i]]);
                        }
                    }
                }
            }
        }
        
        return change_v[amount];
    }
};