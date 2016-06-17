/** Problem

Write a function to find the longest common prefix string amongst an array of strings.

*/


/** Algorithm Outline

    loop from the beginning until find the non-common position
    
*/

class Solution 
{
    public:
    
    string longestCommonPrefix(vector<string>& strs) 
    {
        
        //empty strings
        if(strs.empty())
        {
            return string();
        }
        
        //when only one string
        if(strs.size() == 1)
        {
            return strs[0];
        }
        
     
        for(int i=0; i < strs[0].size() ; ++i)
        {
            char letter = strs[0][i];
            for(int j=0; j < strs.size(); ++j)
            {
                if(i == strs[j].size() || //come to the end of strs[j]
                   strs[j][i] != letter) //it is not common prefix now
                {
                    if(i == 0) //return empty string
                    {
                        return string();
                    }
                    else
                    {
                        return strs[0].substr(0, i);
                    }
                    
                }
            }
        }

        
        return strs[0];
        
    }
};