/** Problem 


Given two words word1 and word2, find the minimum number of steps required to convert word1 to word2. (each operation is counted as 1 step.)

You have the following 3 operations permitted on a word:

a) Insert a character
b) Delete a character
c) Replace a character

*/

/** Algorithm Outline
   
  1. It is also called Levenshtein distance, see https://en.wikipedia.org/wiki/Levenshtein_distance
  2. We define dist_vv[i][j] as the minimal number of steps from word1[0,1,...,i-1] (the first i letters of word1)
     to word2[0,1,...,j-1] (the first j letters of word2)
  3. We want to compute dist_vv[m][n], m = word1.size(), n = word2.size()
  4. We should dynamically compute dist_vv[i][j] through dist_vv[s][t], s=i-1 or i, t=j-1 or j
*/

class Solution 
{
    public:
    
    int minDistance(string word1, string word2) 
    {        
        if(word1.empty())
        {
            return word2.size();
        }
        
        if(word2.empty())
        {
            return word1.size();
        }

        int m = word1.size();
        int n = word2.size();
        vector< vector<int> > dist_vv(m+1, vector<int>(n+1, 0));
        
        for(int i=0; i <= m; ++i)
        {
            dist_vv[i][0] = i;
        }
        
        for(int j=0; j <=n; ++j)
        {
            dist_vv[0][j] = j;
        }
        
        for(int i=1; i<=m; ++i)
        {
            for(int j=1; j<=n; ++j)
            {
                if(word1[i-1] == word2[j-1])
                {
                    dist_vv[i][j] = dist_vv[i-1][j-1];
                }
                else
                {
                    //insert a letter in the back of word1, this letter is word2[j]
                    int n_insert = dist_vv[i][j-1]+1;
                    //delete the last letter of word1
                    int n_delete = dist_vv[i-1][j]+1;
                    //replace the last letter of word1 to be word2[j]
                    int n_replace = dist_vv[i-1][j-1]+1;
                    
                    dist_vv[i][j] = min(n_insert, min(n_delete, n_replace));
                }
            }
        }
        
        return dist_vv[m][n];
    }
};