#include<iostream>
using namespace std;

bool isprime [1000006];
void sieve_primes(){
    int N = 1000005 ;
    for(int i = 0 ; i <= n ; ++i){
        isprime[i] = true;
    }
    isprime[0] = false;
    isprime[1] = false;
    for( int i = 2 ; i*i <= n ; ++i ){
        for( int j = i*i ; j <=n ; j +=i ){
            if( isprime[j] ){
                isprime[j] = false;
            }
        }
    }
}

int main(){
    int n;
    cin>>n;
    sieve(n);
}