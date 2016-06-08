/*
  There are a total of n courses you have to take, labeled from 0 to n - 1.
  Some courses may have prerequisites, for example to take course 0 you have to first take course 1, which is expressed as a pair: [0,1]
  Given the total number of courses and a list of prerequisite pairs, is it possible for you to finish all courses?
  For example:
      2, [[1,0]]
  There are a total of 2 courses to take. To take course 1 you should have finished course 0. So it is possible.
      2, [[1,0],[0,1]]
  There are a total of 2 courses to take. To take course 1 you should have finished course 0, and to take course 0 you should also have finished course 1. So it is impossible.
*/

/* 
   We largely follow the Kahn's algorithm algorithm for topological sorting, 
   see https://en.wikipedia.org/wiki/Topological_sorting#Algorithms
   
    L ← Empty list that will contain the sorted elements
    S ← Set of all nodes with no incoming edges
    while S is non-empty do
        remove a node n from S
        add n to tail of L
        for each node m with an edge e from n to m do
            remove edge e from the graph
            if m has no other incoming edges then
                insert m into S
    if graph has edges then
        return error (graph has at least one cycle)
    else 
        return L (a topologically sorted order)
*/

class Solution 
{
    public:
    
    bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) 
    {
        //the indegree of all nodes   indegree_v[n] is the indegree of node n
        vector<int> indegree_v(numCourses, 0);
        
        //the node queue with zero indegree
        list<int> zero_indegree_l;
        
        //construct the outgoing edge set of each node, this is critical for saving time!!
        vector< list<int> > outgoing_edge_list_v(numCourses);
        
        //initialize outgoing edge set of each node, and indegree of each node
        for(int i=0; i < prerequisites.size(); ++i)
        {
            pair<int, int> edge = prerequisites[i];
            int src = edge.first;
            int dest = edge.second;
            outgoing_edge_list_v[src].push_back(i);
            ++indegree_v[dest];
        }
        
        //initialize zero_indegree_v
        for(int i=0; i < numCourses; ++i)
        {
            if(indegree_v[i] == 0)
            {
                zero_indegree_l.push_back(i);
            }
        }
        
        //there is a loop in the graph, return false
        if(zero_indegree_l.empty())
        {
            return false;
        }
        
        while(!zero_indegree_l.empty())
        {
            //pop the last elements in zero_indegree_l
            int n = zero_indegree_l.front();
            zero_indegree_l.pop_front();
            for(list< int >::iterator liter=outgoing_edge_list_v[n].begin(); liter != outgoing_edge_list_v[n].end(); ++liter)
            {
                pair<int, int> edge = prerequisites[*liter];
                //remove this edge from the outgoing edge set of node n
                liter = outgoing_edge_list_v[n].erase(liter);
                //decrease liter such that we can check the next edge of the removed edge
                --liter;
                int dest = edge.second;
                --indegree_v[dest];
                if(indegree_v[dest] == 0)
                {
                    zero_indegree_l.push_back(dest);
                }
            }
        }
        
        //return false if not all edges are removed
        for(int i=0; i < numCourses; ++i)
        {
            if(!outgoing_edge_list_v[i].empty())
            {
                return false;
            }    
        }
        return true;        
    }
};