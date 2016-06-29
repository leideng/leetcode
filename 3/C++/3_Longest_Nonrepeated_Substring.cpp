/** Problem

Given a string, find the length of the longest substring without repeating characters.

Examples:

Given "abcabcbb", the answer is "abc", which the length is 3.

Given "bbbbb", the answer is "b", with the length of 1.

Given "pwwkew", the answer is "wke", with the length of 3. Note that the answer must be a substring, "pwke" is a subsequence and not a substring.

*/


/** Algorithm Outline

*/ 

class Solution 
{
    public:
    
    int lengthOfLongestSubstring(string s) 
    {
        // cur_map[c]=k, means the current position for character c is k
        unordered_map<char, int> cur_map;
        int max = 0;
        
        for(int i=0; i < s.size(); ++i)
        {
            unordered_map<char, int>::iterator miter = cur_map.find(s[i]);
            if( miter == cur_map.end()) //this character is not in the current substring
            {
                cur_map[s[i]] = i;
                
                if(cur_map.size() > max)
                {
                    max = cur_map.size();
                }
            }
            else //we have found this in current substring, e.g., s[i]=c   current substring = abcd
            {
                //we remove the subsubstring that is before this repeated character, e.g., abcd =>  dc (remove abc)
                int idx = miter->second;
                for(unordered_map<char, int>::iterator mi_temp=cur_map.begin(); mi_temp != cur_map.end();)
                {
                    if(mi_temp->second <= idx)
                    {
                        cur_map.erase(mi_temp++);  // advance before iterator become invalid
                    }
                    else
                    {
                        mi_temp++;
                    }
                }
                //we then insert the current character
                cur_map[s[i]] = i;
            }
            
        }
        
        return max;
    }
};