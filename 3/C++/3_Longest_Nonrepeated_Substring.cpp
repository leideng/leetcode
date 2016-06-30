/** Problem

Given a string, find the length of the longest substring without repeating characters.

Examples:

Given "abcabcbb", the answer is "abc", which the length is 3.

Given "bbbbb", the answer is "b", with the length of 1.

Given "pwwkew", the answer is "wke", with the length of 3. Note that the answer must be a substring, "pwke" is a subsequence and not a substring.

*/


/** Algorithm Outline
    
    1 Loop for each letter in the string
    2 We maintain the current substring (cur_str) and the length (max) of longest substring without repeating characters until the current letter
    3 If the current letter is in the current substring, we should remove the subsubstring of the current substring, from the beginning to the     
      repeated current letter
    4 If the current letter is not in the current substring, we just insert the current letter into the current substring
    
    Example "pwwkewka"
    
    Initialize: cur_str=""     max=0  
    For "p":    cur_str="p"    max=1
    For "w":    cur_str="pw"   max=2
    For "w":    cur_str=""     max=2
    For "k":    cur_str="k"    max=1
    For "e":    cur_str="ke"   max=2
    For "w":    cur_str="kew"  max=3
    For "k":    cur_str="ewk"  max=3
    For "a":    cur_str="ewka" max=4
    
    Reduce Complexity: 
    The complexity comes from two parts:
    (i) Find if the current letter is in the current substr
    (ii) Remove the subsubstring of the current substring, from the beginning to the     
      repeated current letter
      
    Both of them can be done in constant time: We maintain a hashtable (cur_map) of <letter, position> and a current index (cur_idx) of the beginning of the current substring 
    
    Initialize: cur_str=""     max=0  cur_idx=0 cur_map=""             
    For "p":    cur_str="p"    max=1  cur_idx=0 cur_map={<'p',0>}      
    For "w":    cur_str="pw"   max=2  cur_idx=0 cur_map={<'p',0>, <'w',1>} 
    For "w":    cur_str="w"    max=2  cur_idx=2 cur_map={<'p',0>, <'w',2>} //we find cur_map['w']-1>cur_idx, thus 'w' is in the current substring
                                                                           //we only need to update cur_map['w'] to be 2 (do not need to remove)
    For "k":    cur_str="wk"   max=2  cur_idx=2 cur_map={<'p',0>, <'w',2>, <'k',3>} 
    For "e":    cur_str="wke"  max=3  cur_idx=2 cur_map={<'p',0>, <'w',2>, <'k',3>, <'e', 4>}
    For "w":    cur_str="kew"  max=3  cur_idx=3 cur_map={<'p',0>, <'w',5>, <'k',3>, <'e', 4>}
    For "k":    cur_str="ewk"  max=3  cur_idx=3 cur_map={<'p',0>, <'w',5>, <'k',6>, <'e', 4>}
    For "a":    cur_str="ewka" max=4  cur_idx=3 cur_map={<'p',0>, <'w',5>, <'k',6>, <'e', 4>, <'a',7>} 
    
    
    Further Improvement:
    cur_map can be implemented by a hash table, e.g., unordered_map in C++
    However, since the letter set is given, we can use an array to further reduce the complexity

*/ 

/** Use hash table
class Solution 
{
    public:
    
    int lengthOfLongestSubstring(string s) 
    {
        // cur_map[c]=k, means the current position for character c is k
        unordered_map<char, int> cur_map;
        int cur_idx = 0; //the current index for the beginning of the current substring
        int max = 0;
        
        for(int i=0; i < s.size(); ++i)
        {
            unordered_map<char, int>::iterator miter = cur_map.find(s[i]);
            if(miter != cur_map.end() && miter->second >= cur_idx) //we have found this in current substring, 
                                                                   //e.g., s[i]=c   current substring = abcd
            {
                cur_idx = miter->second+1; //we replace the current subsubstring, e.g., abcd =>  dc (remove abc)
                                           //this is equivalent to update cur_idx
                cur_map[s[i]] = i;         //also remember to update cur_map[s[i]], i.e., cur_map[c]=2 =>  cur_map[c]=4       
            }
            else //this character is not in the current substring
            {
                cur_map[s[i]] = i; //we then insert the current character
                if(i-cur_idx+1 > max)
                {
                    max = i-cur_idx+1; //we also update max if possible
                }
            } 
        }
        
        return max;
    }
};

*/


class Solution 
{
    public:
    
    int lengthOfLongestSubstring(string s) 
    {
        // cur_map[c]=k, means the current position for character c is k
        //unordered_map<char, int> cur_map;
        vector<int> cur_map(128,-1);
        int cur_idx = 0; //the current index for the beginning of the current substring
        int max = 0;
        
        for(int i=0; i < s.size(); ++i)
        {
            //unordered_map<char, int>::iterator miter = cur_map.find(s[i]);
            //if(miter != cur_map.end() && miter->second >= cur_idx) //we have found this in current substring, 
                                                                   //e.g., s[i]=c   current substring = abcd
            if(cur_map[s[i]] >= cur_idx)                                                          
            {
                cur_idx = cur_map[s[i]]+1; //we replace the current subsubstring, e.g., abcd =>  dc (remove abc)
                                           //this is equivalent to update cur_idx
                cur_map[s[i]] = i;         //also remember to update cur_map[s[i]], i.e., cur_map[c]=2 =>  cur_map[c]=4       
            }
            else //this character is not in the current substring
            {
                cur_map[s[i]] = i; //we then insert the current character
                if(i-cur_idx+1 > max)
                {
                    max = i-cur_idx+1; //we also update max if possible
                }
            } 
        }
        
        return max;
    }
};