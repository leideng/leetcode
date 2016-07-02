/** Problem

Given a string array words, find the maximum value of length(word[i]) * length(word[j]) where the two words do not share common letters. You may assume that each word will contain only lower case letters. If no such two words exist, return 0.

Example 1:
Given ["abcw", "baz", "foo", "bar", "xtfn", "abcdef"]
Return 16
The two words can be "abcw", "xtfn".

Example 2:
Given ["a", "ab", "abc", "d", "cd", "bcd", "abcd"]
Return 4
The two words can be "ab", "cd".

Example 3:
Given ["a", "aa", "aaa", "aaaa"]
Return 0
No such pair of words.

*/

/** Algorithm Outline
    
    1. Loop for each word, and construct the following two data structures:
        
        letter_str_vv[0]: is the index set of strings that includes letter 'a'
        letter_str_vv[1]: is the index set of strings that includes letter 'b'
        ...
        letter_str_vv[25]: is the index set of strings that includes letter 'z'
        
        
        
        hasCommon_vv[i][j] = 1 means that string i and string j have a common letter.
    
    2. A double loop for hasCommon_vv to get the result
    
    3. For each word, it could have multiple same letter, e.g., "qqqqqqqq", make sure
       that we only need to consider the first 'q', and ignore all later 'q's.
     
    4. Improvement for item 1: we can use bit manipulation to check whether string 
       i and string j have a common letter.  
       
       "abb", we can use integer x = 3  = 0b00..000011 to represent it  
       "bcd", we can use integer y = 14 = 0b00..001110 to represnet it
        Then we see if x & y == 0, then string i and string j do not have a common letter,
        otherwise, like here x&y = 0b00..000010 = 2, string i and string j have a common letter.
*/

/** Simple loop, time limit exceeded
class Solution 
{
    public:
    
    int maxProduct(vector<string>& words) 
    {
        int max = 0;
        for(int i=0; i < words.size(); ++i)
        {
            //create a hash table for the current string 
            unordered_map<char, bool> hash;
            for(int s=0; s < words[i].size(); ++s)
            {
                hash[words[i][s]] = true;
            }
            
            for(int j=i+1; j < words.size(); ++j)
            {
                bool hasCommon = false;
                for(int s=0; s < words[j].size(); ++s)
                {
                    if(hash.find(words[j][s]) != hash.end())
                    {
                        hasCommon = true;
                        break;
                    }
                }
                
                if(!hasCommon)
                {
                    if(words[i].size() * words[j].size() > max)
                    {
                        max = words[i].size() * words[j].size();
                    }
                }
            }
        }
        
        return max;
    }
};
*/

/** Accepted but still too slow
class Solution 
{
    public:
    
    int maxProduct(vector<string>& words) 
    {
        //we build the following data structure
        //letter_str_vv[0]: is the index set of strings that includes letter 'a'
        //letter_str_vv[1]: is the index set of strings that includes letter 'b'
        //...
        //letter_str_vv[25]: is the index set of strings that includes letter 'z'
        vector< vector<int> > letter_str_vv(26);
        
        //we also build the following data structure
        // hasCommon_vv[i][j] = 1 means that string i and string j have a common letter.
        vector< vector<int> > hasCommon_vv(words.size(), vector<int>(words.size(), 0));
        
        for(int i=0; i < words.size(); ++i)
        {
            for(int s=0; s < words[i].size(); ++s)
            {
                int letter_idx = words[i][s] - 'a';
                
                if(letter_str_vv[letter_idx].empty() ||
                   letter_str_vv[letter_idx].back() != i) // string i has not been handled
                {
                    for(int t=0; t < letter_str_vv[letter_idx].size(); ++t)
                    {
                        int string_idx = letter_str_vv[letter_idx][t];
                        hasCommon_vv[string_idx][i] = 1;
                        hasCommon_vv[i][string_idx] = 1;
                    }
                    letter_str_vv[letter_idx].push_back(i);
                }    
            }
        }
       
        int max = 0;
        for(int i=0; i < words.size(); ++i)
        {
            for(int j=i+1; j < words.size(); ++j)
            {
                if(hasCommon_vv[i][j] == 1)
                {
                    continue;
                }
                else
                {
                    int prod = words[i].size() * words[j].size();
                    if(prod > max)
                    {
                        max = prod;
                    }
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
    
    int maxProduct(vector<string>& words) 
    {
        vector<int> words_int_v(words.size(), 0);
        
        for(int i=0; i < words.size(); ++i)
        {
            for(int s=0; s < words[i].size(); ++s)
            {
                int letter_idx = words[i][s] - 'a';
                int mask = 1 << letter_idx;
                words_int_v[i] = (words_int_v[i] | mask);
            }
        }
       
        int max = 0;
        for(int i=0; i < words.size(); ++i)
        {
            for(int j=i+1; j < words.size(); ++j)
            {
                //note that the bitwise "&" has lower priority than "=="
                if( (words_int_v[i] & words_int_v[j]) == 0) //strings i and j have no common letters
                {
                    int prod = words[i].size() * words[j].size();
                    if(prod > max)
                    {
                        max = prod;
                    }
                }
            }
        }
        
        return max;
    }
};
