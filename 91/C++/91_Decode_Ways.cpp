/** Problem

A message containing letters from A-Z is being encoded to numbers using the following mapping:

'A' -> 1
'B' -> 2
...
'Z' -> 26
Given an encoded message containing digits, determine the total number of ways to decode it.

For example,
Given encoded message "12", it could be decoded as "AB" (1 2) or "L" (12).

The number of ways decoding "12" is 2.

*/

/** Algorithm Outline
 
   1. It needs to handle the non-decodable input. e.g. "01" should return 0;
   2. Use dynamic programming 
*/


/** Recursion, time limit exceeded
class Solution 
{
    public:
    
    int numDecodings(string s) 
    {
        if(s.empty())
        {
            return 0;
        }
        
        if(s[0] == '0')
        {
            return 0; //something wrong happens
        }
        
        if(s.size() == 1)
        {
            return 1;
        }
        
        int sum = 0;
        
        //judge if the second letter is a valid single-letter code
        if(s[1] != '0')
        {
            int ret = numDecodings(s.substr(1));
            if(ret == 0) //something wrong happens
            {
                return 0;
            }
            else
            {
                sum += ret;
            }
        }
        
        //judge if the first two letters are a two-letter code
        //and the third letter is a single-letter code
        int two_letter_code = atoi(s.substr(0,2).c_str());
        if(two_letter_code >= 10 && two_letter_code <= 26)
        {
            if(s.size() >= 3)
            {
                if(s[2] != '0')
                {
                    int ret = numDecodings(s.substr(2));
                    if(ret == 0) //something wrong happens
                    {
                        return 0;
                    }
                    else
                    {
                        sum += ret;
                    }
                }
            }
            else //s.size() = 2
            {
                sum++;
            } 
        }

        return sum;
    }
};
*/

class Solution 
{
    public:
    
    int numDecodings(string s) 
    {
        if(s.empty())
        {
            return 0;
        }
        
        if(s[0] == '0')
        {
            return 0; //something wrong happens
        }
        
        if(s.size() == 1)
        {
            return 1;
        }
        
        //s.size() >= 2;
        
        //ways_v[i] is the number of decode ways of the substring s[0,...,i]
        vector<int> ways_v(s.size(), 0);
        ways_v[0] = 1;
        for(int i=1; i < s.size(); ++i)
        {
            if(s[i] == '0') //letter i cannot be a single-letter code, it must combine with letter i-1
            {
                int temp = atoi(s.substr(i-1,2).c_str());
                if(temp >=10 && temp <= 26)
                {
                    if(i == 1)
                    {
                        ways_v[i] = 1;
                    }
                    else if(ways_v[i-2] > 0) //i >= 2
                    {
                        ways_v[i] += ways_v[i-2];
                    }
                    else
                    {
                        ways_v[i] = 0;
                    }
                }
            }
            else //s[i] != '0', thus letter i can be a single-letter code 
            {
                if(ways_v[i-1] > 0)
                {
                    ways_v[i] += ways_v[i-1]; //decode letter i as a single-letter code
                }
                
                int temp = atoi(s.substr(i-1,2).c_str());
                if(temp >=10 && temp <= 26)
                {
                    if(i == 1)
                    {
                        ways_v[i] += 1;
                    }
                    else if(ways_v[i-2] > 0) //i >= 2
                    {
                        ways_v[i] += ways_v[i-2];
                    }
                    else
                    {
                        //do nothing
                    }
                }
            }  
        }
        
        return ways_v[s.size()-1];
    }
};