//  tc = O(n) . finding the largest palindrome centered at i SOME SIMILAR  concepot as Z Algo

#include<iostream>
#include<bits/stdc++.h>
using namespace std ;

auto manchter_odd(string s ){
    int n = s.size() ;
    s = "$" + s + "^" ;
    vector<int> p (n+2) ;
    int l = 1 , r = 1 ;
    for(int i = 1 ; i<= n ; ++i ){
        p[i] = max(0 , min(r-i , p[l + (r-i) ]) ) ;
        while( s[i-p[i]] == s[i+p[i]] ) p[i]++;
        if(i + p[i] > r ){
            l = i-p[i] , r = i + p[i] ;
        }
    }
    return vector<int> (begin(p) + 1 , end(p) -1 ) ;
}
vector<int> manchter(string s ){
    string t ;
    for(auto c : s ){
        t += string("#") + c ;
    }
    auto res = manchter_odd(t + "#") ;

    return vector<int> (begin(res) + 1 , end(res) - 1 ) ; 
}

int main(){
    string s = "abcbcba" ;
    auto ans = manchter(s) ;
    for(auto it : ans ) cout<<it<<" ";
}