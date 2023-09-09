#include <bits/stdc++.h>
#define el '\n' 
#define ll long long
using namespace std;

vector<ll> fact , ifact , inverseofi ;
const ll N = 1e6 + 1000;
const ll p = 1e9+ 7 ;


// used for finding inverse of natural number i using frmatts little theorem

void findinverse( ){
    for(int i = 2 ; i<= N ; ++i ){
        inverseofi[i] = (inverseofi[p%i] * (p - p/i) % p ) % p ;  
    }
}

void init(){
    fact.resize(N , 0 );
    ifact.resize(N , 0 );
    inverseofi.resize(N , 0 );

    fact[0] = fact[1] = ifact[0] = ifact[1] = inverseofi[0] = inverseofi[1] = 1 ;
    for(int i = 2 ; i<= N ; ++i ){
        fact[i] = (fact[i-1]*i) % p ;
    }

    findinverse();

    for(int i = 2 ; i<= N ; ++i ){
        ifact[i] =  (ifact[i-1] * inverseofi[i] ) % p ;
    }
}

ll ncr(ll n , ll r ){
    if(r > n ) return 0 ;
    return ( (fact[n] * ifact[n-r])%p * ifact[r])%p ;
    // ifact = inverse fact we calculate using fermattts little theormrem
}

int main() {
    init();
    cout<<ifact[2]<<endl;
    ll ans = ncr(6 , 3 );
    cout<<ans<<endl;
}