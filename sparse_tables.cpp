// it is used for range sum query but here array is immutable . means not changing its value 
// so we store  ( 2^0 , 2^1 , 2^2 , ........., 2^ 32 ) for every index . 
// now we can return the query in o(32) constant time 

#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
#include<utility>
#include<climits>

using namespace std;

class sparse_table{
    int N = 28 ;
    int n ;
    vector<vector<int>> dp ; 
    public:
    sparse_table(int n , vector<int>& arr ){
        this->n = n ;
        dp.resize(n , vector<int>( N+1 , -1 )) ;
        for(int i = 0 ; i< n ; ++i ){
            dp[i][0] = arr[i] ;
        }
        for(int j = 1 ; j< N ; ++j ){
            for(int i = 0 ; i< n ; ++i ){
                int u = i + (1<<(j-1)) ; 
                dp[i][j] = min( dp[i][j-1] ,  dp[min(n-1 , u )][j-1] ) ; 
            }
        }
        // for(int i = 0 ; i < n ; ++i ){
        //     for(int j = 0 ; j< N ; ++j ){
        //         cout<<dp[i][j]<<" " ;
        //     }
        //     cout<<endl;
        // }
    }
    int query(int l , int r ){
        if(r < l ) return INT_MAX ; 
        if( r == l ){
            return dp[l][0] ;
        }
        int k = log2(r-l+1) ;
        int a1 = query(l , r - (1 << k) ) ;
        int a2 = dp[min( r - (1 << k) + 1 , n-1 ) ][k] ;
        return min(a1 , a2 ) ;
    }
};

int main(){
    int n ; 
    cin>>n ;
    vector<int> v(n ) ;
    for(int i = 0 ; i< n ; ++i ) cin>>v[i] ;

    sparse_table * st = new sparse_table(n , v ) ; 


    int q ; 
    cin>>q;
    for(int i = 0 ; i< q ; ++i ){
        int l , r ; 
        cin>>l>>r ; 
        int ans = st->query(l , r ) ;
        cout<<ans<<endl;
    }

    // cout<<" hi "<<endl;
    return 0 ; 
}