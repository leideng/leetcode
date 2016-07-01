/** Problem

Write a function that takes a string as input and returns the string reversed.

Example:
Given s = "hello", return "olleh".

*/ 

class Solution 
{
    public:
    
    string reverseString(string s) 
    {
        string result(s.size(), 0);
        for(int i=0; i < s.size(); ++i)
        {
            result[i] = s[s.size()-i-1]; 
        }
        
        return result;
    }
};