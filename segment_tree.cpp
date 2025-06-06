#include<bits/stdc++.h>
using namespace std ; 
const int N = 1e5 + 5 ; 
int a[N] , st[4*N] ;
void build(int v , int l , int r ){
    if(l == r ){
        st[v] = a[l];
        return ;
    }
    else{
        build(2*v , l , (l+r) / 2 ) ;
        build(2*v +1 , (l+r) / 2 + 1 , r ) ;
        st[v] = st[2*v] + st[2*v+1] ;
    }
}


void upd(int v , int l , int r , int tl , int tr , int val ){
    if(l == tl && r == tr ){
        st[v] = val ; 
        return ;
    }
    else if( tr < l || tl > r ) return ;

    else{
        upd(2*v , l , (l+r) / 2 , tl , min(tr , (l+r) /2 ) , val ) ;
        upd(2*v + 1 , (l+r) / 2 + 1 , r , max(tl , (l+r) /2 +1 ) , tr , val ) ;
        st[v] = st[ v*2 ] + st[ 2*v + 1 ] ;
    }
}

int query(int v , int l , int r , int tl , int tr ){
    if( l == tl && r == tr ){
        return st[v] ;
    }
    else if( tr < l || tl > r ) return 0 ; 
    else{
        return query(2*v , l , (l+r)/2 , tl , min(tr , (l+r) /2 )  ) 
        + query(2*v+1 , (l+r)/2+1 , r , max(tl , (l+r) /2 +1 ) , tr  ) ;
    }
}

int main(){
    int n ; cin>>n ; 
    for(int i = 0 ; i< n ; ++i ) cin>>a[i] ;
    build(1 , 0 , n-1 ) ;

    int q ;  cin>>q ;
    for(int i = 0 ; i< q ; ++i ){
        int tp ;  cin>>tp ; 
        if(tp == 1 ){
            int l , r , val ;  
            cin>>l>>r>>val ; 
            upd(1 , 0 , n-1 , l-1 , r-1 , val ) ;
        }
        else{
            int l , r  ;  
            cin>>l>>r ; 
            cout<<query(1 , 0 , n-1 , l-1 , r-1 )<<endl ;
        }
    }
}