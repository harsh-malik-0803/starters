#include<bits/stdc++.h>
using namespace std;
#define ll long long

//  kth ancestor -- binory lifting -----------------------------

// class TreeAncestor {
//     vector<int> parent ;
//     int n ;
//     vector<vector<int>> dp;
// public:
//     TreeAncestor(int n, vector<int>& parent) {
//         this->n = n ;
//         this->parent = parent ;
//         init();
//     }
//     void init(){
//         dp.resize(n , vector<int>(20 , -1 ) );
//         for(int i = 0 ; i< n ; ++i ){
//             dp[i][0] = parent[i] ;
//         }
        
//         for(int j = 1 ; j<20 ; ++j ){
//             for(int i = 1 ; i< n ; ++i ){
//                 dp[i][j] = getKthAncestor( dp[i][j-1] ,  1<<(j-1) ) ;
//             }
//         }
//     }
//     int getKthAncestor(int node, int k) {
//         if(k == 0 || node == -1 ){
//             return node ;
//         }
//         int lev = log2(k) ;
//         return getKthAncestor( dp[node][lev] , k-(1<<lev) ) ;
//     }
// };

// ----------------------------------------------------------------------





vector<vector<int>> adj ;
//vector<int> dist; 
vector<ll> arr ;

vector<ll> ans ;
vector<bool> visited ;


// ------------------------bridge in a graph ---------------------//

// vector<bool> visited ;
// vector<ll> tim , low ;
// int timer ;
// vector<pair<ll,ll>> bridges;
// void dfs( ll src , ll p = -1 ){
// 	visited[src] = 1 ;
// 	low[src] = tin[src] = timer++;

// 	for(auto to : adj[src] ){
// 		if(to == parent ) continue ;
// 		if(visited[to] ) {
// 			low[src] = min(low[src] , tin[to] );
// 		}
// 		else{
// 			dfs(to , src );
// 			low[src] = min(low[src] , low[to] ) ;
// 			if(low[to] > tin[src] ) {
// 				bridges.push_back({to , src }) ;
// 			}
// 		}
// 	}
// }

// ------------------------end ---------------------//
void dfs(ll src , ll dest , vector<ll>& path ){
    visited[src] = 1 ;
    path.push_back(src);
    if(src == dest ){
        
        ans = path ;
        return ;
    }
    for(auto it :  adj[src] ){
        if(!visited[it] ){
            dfs(it , dest , path ) ;
        }
    }
    path.pop_back();
}

void solve(){
	ll n , q ;
	cin>>n>>q;
    adj.clear();
    arr.resize( n ) ;
    for(int i= 0 ; i< n ; ++i ){
        cin>>arr[i];
    }
    adj.resize(n) ;
    
    for(int i= 0 ; i< n-1 ; ++i ){
        ll l , r;
        cin>>l>>r;
        --l;
        --r;
        adj[l].push_back(r);
        adj[r].push_back(l);
    }
    

	while(q>0){
		ll  a , b ;
		cin>>a>>b;
		--a;
        --b;
        
        vector<ll> ans1 ;
        ans.clear() ;
        visited.clear();

        visited.resize(n , 0 );
        dfs(a , b , ans1 );
        ll len = ans.size();
        vector<int> v;
        for(int i = 0 ; i< len ; ++i ){
            v.push_back(arr[ans[i]]);
            // cout<<v[i]<<" ";
        }
        sort(v.begin() , v.end() ) ;
        cout<<v[0] + v[v.size()-1] + v[(len+1)/2 -1 ] <<" ";
        // for(int i = 0 ; i< len ; ++i ){
        //     cout<<v[i]<<" ";
        // }
		--q;
	}
}

int main(){
	solve();
}