/** Problem

Write a program to find the n-th ugly number.

Ugly numbers are positive numbers whose prime factors only include 2, 3, 5. For example, 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 is the sequence of the first 10 ugly numbers.

Note that 1 is typically treated as an ugly number.

*/

/* Algorithm Outline

   1. We try to find all ugly numbers, from the first to the n-th.
   2. The difficulty is how to find the i-th ugly number based on all found ugly numbers (from the first to the (i-1)-th).
   3. The key observation is that the i-th ugly number must be  
   
           (j-th ugly number)*2 for some j in [1,i-1], or 
           (j-th ugly number)*3 for some j in [1,i-1], or 
           (j-th ugly number)*5 for some j in [1,i-1].
      
      For example, 1, 2=1*2
                   1, 2, 3=1*3
                   1, 2, 3, 4=2*2
                   1, 2, 3, 4, 5=1*5
                   1, 2, 3, 4, 5, 6=2*3 
                   1, 2, 3, 4, 5, 6, 8=4*2
                   1, 2, 3, 4, 5, 6, 8, 9=3*3
   
   4. Now we only need to find such a j for any factor (2,3, or 5). This can be done by binary search. 
      
      For example, given 1,2,3,4,5,6,8,9,10, we want to find the next ugly number
      1) For factor 2: We should find the smallest ugly number such that it times 2 is larger than 10 
                 1*2=2, 2*2=4, 3*2=6, 4*2=8, 5*2=10, 6*2=12>10, 8*2=16, 9*2=16, 10*2=20. 
         We can find the 6-th ugly number 6 such that 6*2=12>10
      2) For factor 3: We should find the smallest ugly number such that it times 3 is larger than 10
         We can find the 4-th ugly number 4 such that 4*3=12>10
      3) For factor 5: We should find the smallest ugly number such that it times 5 is larger than 10
         We can find the 3-th ugly number 3 such that 3*5=15>10
      4) Then, among 12, 12, 15, we choose the smallest, i.e., 12 as the next ugly number
      
      Note that 1) 2) and 3) can be done by binary search.
    
   5. The complexity is O(nlog(n))
   
   Further improvement
   To get 1),2) and 3) in the step 4, we can keep three pointers/indices, p2, p3, and p5. Each time we only need to find 
   a j that is larger than p2, p3, or p5. We should keep updating p2, p3 and p5.
*/

/** Accepted by still too slow
class Solution 
{
    public:
    
    int nthUglyNumber(int n) 
    {
        if(n == 1)
        {
            return 1;
        }
        
        vector<int> ugly_number_v(n+1, -1);      
        ugly_number_v[1] = 1;
        
        for(int i=2; i <= n; ++i)
        {
            int min = std::numeric_limits<int>::max();
            
            int temp = findNextSmallest(ugly_number_v, i, 2);
            
            if( temp < min)
            {
                min = temp;
            }

            temp = findNextSmallest(ugly_number_v, i, 3);
            if( temp < min)
            {
                min = temp;
            }
            
            temp = findNextSmallest(ugly_number_v, i, 5);
            if( temp < min)
            {
                min = temp;
            }
            
            ugly_number_v[i] = min;
        }
        
        return ugly_number_v[n];
    }
    
    int findNextSmallest(const vector<int>& ugly_number_v, int i, long long factor) //use long long factor to avoid overflow
    {
        //find one of the previous ugly numbers, which times 2 can larger than ugly_number_v[i-1]
        int n_min = 1; 
        int n_max = i-1;
        while(n_min <= n_max)
        {
            int mid = (n_min+n_max)/2;
            
            if(ugly_number_v[mid]*factor > ugly_number_v[i-1] )
            {
                if(ugly_number_v[mid-1]*factor <= ugly_number_v[i-1])
                {
                    return ugly_number_v[mid]*factor;
                }
                
                n_max = mid - 1;
                continue;
            }
            
            if( ugly_number_v[mid]*factor <= ugly_number_v[i-1] )
            {
                if( ugly_number_v[mid+1]*factor > ugly_number_v[i-1])
                {
                    return ugly_number_v[mid+1]*factor;
                }
                
                n_min = mid + 1;
                continue;
            }
        }
        
        return 0; //fake return
    }
};

*/


/// Using the further improvement, must faster 
class Solution 
{
    public:
    
    int nthUglyNumber(int n) 
    {
        vector<long> ugly_number_v(n+1, -1);      
        ugly_number_v[1] = 1;
     
        int p2 = 1;
        int p3 = 1;
        int p5 = 1;
        
        for (int i = 2; i <= n; ++i)
        {
            int m = min(min(ugly_number_v[p2] * 2, ugly_number_v[p3] * 3), ugly_number_v[p5] * 5);
            ugly_number_v[i] = m;
            while (ugly_number_v[p2] * 2 <= ugly_number_v[i])
            {
                p2++;
            }
            while (ugly_number_v[p3] * 3 <= ugly_number_v[i])
            {
                p3++;
            }
            while (ugly_number_v[p5] * 5 <= ugly_number_v[i])
            {
                p5++;
            }
        }
        return ugly_number_v[n];
    }
};