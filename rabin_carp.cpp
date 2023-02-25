#include<iostream>
#include<vector>

using namespace std;
int add(int a , int b  , int mod = 1e9 + 7 ){
    int res = ( a + b ) % mod ;
    if(res < 0 ) 
        res += mod ;
    return res ;      
}
int mult(int a , int b , int mod = 1e9 + 7 ){
    int res = ( a * 1LL * b ) % mod ;
    if(res < 0 ) 
        res += mod ;
    return res ;      
}
int power(int a , int b , int mod = 1e9 + 7 ){   // a^b 
    int res = 1 ;
    while(b){
        if( (b%2) == 1 ) res = mult(res , a , mod ) ;
        a = mult(a , a , mod ) ;
        b = b/2 ;
    }
    return res ;      
}

class Rabin_carp{
    int N , mod , base ;
    int * hash , * inv , * pw ;
    public:
    Rabin_carp(int m , int b , string s ){
        mod = m ; 
        base = b ; 
        N = 1e6 + 6 ;
        hash = new int[N] ;
        inv = new int[N] ;
        pw = new int[N] ;

        init() ;
        build(s) ;
    }
    void init(){
        pw[0] = 1 ;
        for(int i = 1 ; i< N ; ++i ){
            pw[i] = mult(pw[i-1] , base , mod ) ;
        }
        int inv_pw = power(base , mod-2 , mod ) ;
        inv[0] = 1 ;
        for(int i = 1 ; i< N ; ++i ){
            inv[i] = mult( inv[i-1] , inv_pw , mod ) ;
        }
    }
    void build(string s ){
        int n = s.length() ;
        for(int i = 0 ; i< n ; ++i ){
            hash[i] = add( (i == 0)? 0 : hash[i-1] , mult( s[i] - 'a' + 1 ,  pw[i] , mod ) , mod ) ;  
        }
    }
    int getHash(int x , int y ){
        int hs = add ( hash[y] , (x == 0)? 0 : -hash[x-1] , mod ) ;
        hs = mult(hs , inv[x] , mod ) ;
        return hs ;    
    }
} ;

int main(){
    string t , p ;
    cin>>p>>t ;
    int n = t.size() , m = p.size() ;
    Rabin_carp * r1 = new Rabin_carp( (int)1e9 + 7 , 31 , t) ;
    Rabin_carp * r2 = new Rabin_carp( (int)1e9 + 9 , 31 , t) ;
    Rabin_carp * r3 = new Rabin_carp( (int)1e9 + 7 , 31 , p) ;
    Rabin_carp * r4 = new Rabin_carp( (int)1e9 + 9 , 31 , p) ;

    pair<int,int> hash = {r3->getHash(0 , m-1) , r4->getHash(0 , m-1 ) } ;
    vector<int> ans ; 
    for(int i = 0 ; i< n ; ++i ){
        int l = i , r = i + m -1 ;
        if( r >= n )  break ; 
        pair<int,int> new_hash = {r1->getHash( l , r ) , r2->getHash( l , r ) } ;

        if(new_hash == hash ){
            ans.push_back(i) ;
        }
    }
    for(auto it : ans ) {
        cout<<it<<" ";
    }
}