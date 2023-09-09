#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 2e5 + 5 ;
int dp[N][22] ;
int v[N] ;
vector<int> adj[N] ; 
ll n , q ;
int depth[N] ;
int query(int node , int level ){

    for(int i = 19 ; i>=0 ; --i ){
        if( level == 0 || node == -1 ) return node ;
        if( level >= (1<<i)){
            level -= (1<<i) ;
            node = dp[node][i] ;
        }
    }
    return node ; 
}
void init(){
    memset(dp , -1 , sizeof(dp) ) ;
    for(int i = 1 ; i<= n ; ++i ){
        dp[i][0] = v[i] ;
    }
    for(int j = 1 ; j<= 19 ; ++j ){
        for(int i = 2; i<= n ; ++i ){
            if(dp[i][j-1] == -1 ) dp[i][j] = -1 ;
            else dp[i][j] = dp[dp[i][j-1]][j-1] ; 
        }
    }
}

int lca(int u , int v ){
    if(depth[u] < depth[v] ) return lca(v , u ) ;
    u = query(u , depth[u] - depth[v] ) ;
    if( u == v ) return u ; 
    for(int j = 19 ; j>=0 ; --j ){
        int parU = dp[u][j] ;
        int parV = dp[v][j] ;
        if(parU != parV ){
            u = parU ;
            v = parV ;
        }
    }
    if( u == v ) return u ;
    return dp[u][0] ;
}

bool vis[N] ;
void dfs(int src ){
    vis[src] = 1 ;
    for(auto it : adj[src] ){
        if( !vis[it]){
            depth[it] = depth[src] + 1 ;
            v[it] = src ;
            dfs(it) ;
        }
    }
}
void solve(){
    
    cin>>n>>q ;   
    memset(v , -1 , sizeof(v) ) ;   
    for(int i = 0 ; i< n-1 ; ++i ){  
        int u , v ; 
        cin>>u>>v ;
        adj[u].push_back(v) ;
        adj[v].push_back(u) ;
    }
    memset(depth , 0 , sizeof(depth) ) ; 
    memset(vis , 0 , sizeof(vis) ) ; 
    dfs(1) ;
    init() ; 
    

    while( q > 0 ){

        ll u , v ;
        cin>>u>>v ;
        int lc = lca(u , v ) ;
        int ans = depth[u] + depth[v] - 2* depth[lc]  ;
        cout<<ans<<endl;

        --q ;
    }

}

int main(){
    solve() ;
}