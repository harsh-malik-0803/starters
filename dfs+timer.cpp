class Solution {
public:
    vector<vector<int>> adj ;
    vector<vector<int>> radj ;
    int ans  ;
    vector<bool> visited;
    int timer ;
    vector<int> st;
    vector<int> sizeof2 ;
    
    void dfs(int s , int p = -1 ){
        visited[s] = 1 ;
        st[s] = timer++ ;
        
        for(auto to : adj[s] ){ 
            if( st[to] > 0 ){
                ans = max(ans , timer - st[to] );
                if(timer - st[to] == 2 ){
                    sizeof2.push_back(to);
                }
                continue ;
            }
            if(visited[to]  ) continue ;
            else{
                dfs(to , s );
            }               
        }
        st[s] = 0 ;
        --timer ;
    }
    
    int dfs2(int s , int except ){
        int temp = 0 ;
        for(auto to : radj[s] ){
            if(to != except ){
                temp =max(temp , dfs2(to , except ) ) ;
            }
        }
        return 1 + temp ; 
    }
    
    int maximumInvitations(vector<int>& favorite) {
        int n = favorite.size();
        adj.clear();
        adj.resize(n  );
        radj.clear();
        radj.resize(n  );
        for(int i = 0 ; i< n ; ++i ){
            adj[i].push_back(favorite[i] ) ;
            radj[favorite[i]].push_back(i) ;
        }
        ans = 0 ;
        visited.clear();
        visited.resize(n , 0 );
        timer = 1 ;
        st.clear();
        st.resize(n , 0 );
        sizeof2.clear();
        
        for(int i = 0 ; i< n ; ++i ){
            
            if(!visited[i]){
                dfs(i );
            }
        }
          
        int temp = 0 ;
        for(auto s : sizeof2 ){
            auto to = favorite[s];
            temp += dfs2(s , to );
            temp += dfs2(to ,  s ) ;
            ans = max(ans , temp );
        }
        return ans ;
    }
};