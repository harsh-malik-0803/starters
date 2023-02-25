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
template<typename T>
using minpq = priority_queue<T, vector<T>, greater<T>>;

vector<int> kmp ( string pattern ){
    int n = pattern.size() ;
    vector<int> lps(n , 0 ) ;
    int j = 0 ;
    for(int i = 1 ; i< n ; ++i ){
        j = lps[i-1] ;
        while(j > 0 && pattern[i] != pattern[j] ){
            j = lps[j-1] ;
        }
        if( pattern[i] == pattern[j] ) ++j ; 
        lps[i] = j ;
    }
    
    return lps ; 
}

void solve() {
    int n ;
    cin>>n;
    string pattern , text ;
    cin>>pattern>>text ; 

    vector<int> ans ; 
    vector<int> lps = kmp(pattern) ;
    int m = text.size() ;
    int i = 0 , j = 0 ; // i == text , j = pattern 
    while( i<m && j<n ){
        if(pattern[j] == text[i] ){
            ++j ;
            ++i ; 
        }
        else{
            if( j != 0 ) j = lps[j-1] ;
            else ++i ;
        }
        if(j == n ){
            ans.push_back( i-n );   
            j = lps[j-1] ;
        }
        
    }
    for(auto it : ans ){
        cout<<it<<" ";
    }
    cout<<endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int te;
    cin >> te;
    while(te--) 
    solve();
}