#include <bits/stdc++.h>
#define el '\n' 
#define ll long long
#define sz(x) ((int) (x).size())
#define all(x) (x).begin(), (x).end()
#define fi first
#define se second
#define vi vector<int>
#define pii pair<int, int>
#define rep(i, a, b) for(int i = (a); i < (b); i++)
using namespace std;
vector<vector<ll> > adj ;
const int N = 1e5+5 ;
vector<ll> depth , ans ;
vector<bool> visited ;
void dfs1(ll curr ){
    visited[curr] = 1 ;
    
    for(auto it : adj[curr] ){
        if(!visited[it]){
            dfs1(it);
            depth[curr] = max(depth[curr] , 1 + depth[it] );
        }
    }

}

void dfs2(ll curr , ll parent , ll par_ans ){
    visited[curr] = 1 ;
    vector<ll> pre , suff ; 
    for(auto it : adj[curr] ){
        if(!visited[it]){
            pre.push_back(depth[it]) ;
            suff.push_back(depth[it]) ; 
        }
    }
    int sz = pre.size() ;
    for(int i = 1 ; i < sz ; ++i ){
        pre[i] = max(pre[i] , pre[i-1] ) ;
    }
    for(int i = sz-2 ; i >=0 ; --i ){
        suff[i] = max(suff[i] , suff[i+1] ) ;
    }

    int idx = 0  ;
    for(auto it : adj[curr] ){
        if(!visited[it]){
            ll prefix = (idx > 0 )?pre[idx-1] : -1 ;
            ll suffix = (idx < sz-1 )?suff[idx+1] : -1 ;
            ll partial_ans = 1 + max(par_ans , max(prefix  , suffix) ) ;
            dfs2(it , curr , partial_ans ) ;
            // if(it == 2)
            // cout<<ans[it]<<" : 2 "<<endl;
            // cout<<" hi "<<prefix<<" "<<suffix<<endl;
            ++idx ;
        }
    }
    // cout<<endl;
    ans[curr] = 1 + max( (pre.size() > 0 )?pre[sz-1]:-1 , par_ans )  ;
}

void solve() {
    ll n , k ;
    cin>>n;
    adj.resize(n) ;
    rep(i , 0 , n-1 ){
        ll u , v ; 
        cin>>u>>v ;
        --u;
        --v ;
        adj[u].push_back(v) ;
        adj[v].push_back(u) ;
    }   
    // for(int i = 0 ; i< n ; ++i ){
    //     cout<<i<<" : ";
    //     for(auto it : adj[i] ){
    //         cout<<it<<" ";
    //     }
    //     cout<<endl;
    // }
    depth.clear() ;
    depth.resize(n , 0 ) ;
    visited.clear() ;
    visited.resize(n , 0 ) ;
    dfs1(0) ;
    // for(auto it : depth )cout<<it<<" ";
    // cout<<endl;
    visited.clear() ;
    visited.resize(n , 0 ) ;
    ans.clear() ;
    ans.resize(n , 0 ) ;
    dfs2(0 , 0 , -1 ) ;
    for(auto it : ans ) cout<<it<<" ";
    cout<<endl;
    // for(auto it : depth ) cout<<it<<" " ;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    solve();
}