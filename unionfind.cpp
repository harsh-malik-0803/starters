// https://codeforces.com/contest/356/problem/A   == trick1 (store index of next term to show that the next term is alive )

class union_find{
    
    public:
    vector<int> parent ;
    vector<int> sz ;    // having size of tree 

    union_find(int n ){
        parent.resize(n ) ;
        sz.resize(n , 1 ) ;
        for(int i = 0 ; i< n ; ++i ){
            parent[i] = i;
        }
    }

    int root( int v ){
        if( v == parent[v] ) return  v ;
        return parent[v] = root( parent[v] ) ;   // this is improvement
    } 


    bool connected(int p, int q){
        return (root(p) == root(q) );
    }
    
    void merge_set( int p , int q ){
        int i = root(p);
        int j = root(q);

        if(i==j){
            return ;
        }
        if(sz[i] < sz[j] ){
            swap(i , j ) ;
        }
        parent[j] = i;
        sz[i] += sz[j];
    }
};


// Time Complexity - 
// Initialise = O(N)   
// Union = O(logN)
// Find Operation = O(logN)

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

const int N = 1e5+5 ;
class union_find{
    
    public:
    vector<int> parent ;
    vector<int> sz ;    // having size of tree 

    union_find(int n ){
        parent.resize(n ) ;
        sz.resize(n , 1 ) ;
        for(int i = 0 ; i< n ; ++i ){
            parent[i] = i;
        }
    }

    int root( int v ){
        if( v == parent[v] ) return  v ;
        return parent[v] = root( parent[v] ) ;   // this is improvement
    } 


    bool connected(int p, int q){
        return (root(p) == root(q) );
    }
    
    void merge_set( int p , int q , int wt ){
        int i = root(p);
        int j = root(q);

        if(i==j){
            return ;
        }
        if(sz[i] < wt ) return ;

        if(sz[i] < sz[j] ){
            swap(i , j ) ;
        }
        parent[j] = i;
        sz[i] += sz[j];
        for(auto it : v[q] ){
            for(auto itr : it ){
                pq.push_back({0 , it , itr }) ;
            }
        }
    }
};

void solve() {
    ll n , k , m ;
    cin>>n>>m;
    vector<ll> v(n) ;
    rep(i , 0 , n ){
        ll d;
        cin>>d ;
        v[d].push_back(i);
    } 

    vector<vector<ll>> adj ;
    adj.resize(n) ;
    rep(i , 0 , m ){
        ll a , b ;
        cin>>a>>b;
        --a;
        --b;
        adj[a].push_back(b) ;
        adj[b].push_back(a) ;
    }
    
    union_find uf(n) ;
    
    priority_queue< vector<int> , vector< vector<int> > , greater< vector<int> >  > pq ;
    for(auto it : v[0] ){
        for(auto itr : it ){
            pq.push_back({0 , it , itr }) ;
        }
    }

    while(!pq.empty()){
        auto f = pq.top() ;
        
        uf.merge_set(it , itr );
    }

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int te;
    cin >> te;
    while(te--) solve();
}