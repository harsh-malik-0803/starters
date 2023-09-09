#include <bits/stdc++.h>
#define el '\n' 
#define int int
#define rep(i, a, b) for(int i = (a); i < (b); i++)
using namespace std;

int MAX_LEN = 0 ;
const int N = 1e5+5 ;
int n , m ;
int sqn = N ;

// segment tree
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
        st[v] += val ; 
        return ;
    }
    else if( tr < l || tl > r ) return ;

    else{
        upd(2*v , l , (l+r) / 2 , tl , min(tr , (l+r) /2 ) , val ) ;
        upd(2*v + 1 , (l+r) / 2 + 1 , r , max(tl , (l+r) /2 +1 ) , tr , val ) ;
        st[v] = st[ v*2 ] + st[ 2*v + 1 ] ;
    }
}

int que(int v , int l , int r , int tl , int tr ){
    if( l == tl && r == tr ){
        return st[v] ;
    }
    else if( tr < l || tl > r ) return 0 ; 
    else{
        return que(2*v , l , (l+r)/2 , tl , min(tr , (l+r) /2 )  ) 
        + que(2*v+1 , (l+r)/2+1 , r , max(tl , (l+r) /2 +1 ) , tr  ) ;
    }
}
// segment tree end 

vector<vector<int>> adj ;

class Query{
    public:
    int l , r , k , idx ;
};

vector<Query> query ;

int timer = 1 ;
int inTime[N] , outTime[N] , fcolor[N] , fTempcolor[N] , color[N] ;
vector<int> ft ;
bool visited[N] ;

void dfs(int curr ){
    visited[curr] = 1 ;
    ft.push_back(curr) ;
    inTime[curr] = timer++ ;

    for(auto it : adj[curr] ){
        if(!visited[it] ){
            dfs(it) ;
        }
    }
    ft.push_back(curr) ;
    outTime[curr] = timer++ ;
}

bool cmp(Query &q1 , Query &q2 ){
    int c1 = q1.l / sqn ;
    int c2 = q2.l / sqn ;
    if(c1 != c2 ) return c1 < c2 ;

    if(c1 %2 == 0 ){
        return q1.r > q2.r ;
    }
    return q1.r < q2.r ;
}

void add(int idx ){
    int num = ft[idx] ;
    fTempcolor[color[num]]++;
    if(fTempcolor[color[num]] % 2 == 0 ){
        int ix = fcolor[color[num]] ;

        a[fcolor[color[num]]]--;
        upd(1 , 0 , N-1 , ix , ix , -1 ) ;
        fcolor[color[num]]++;
        a[fcolor[color[num]]]++;
        upd(1 , 0 , N-1 , ix + 1 , ix+1 , 1 ) ;
    }
}
void remove(int idx ){
    int num = ft[idx] ;
    fTempcolor[color[num]]--;
    if(fTempcolor[color[num]] % 2 ){
        int ix = fcolor[color[num]] ;
        a[fcolor[color[num]]]--;
        upd(1 , 0 , N-1 , ix , ix , -1 ) ;
        fcolor[color[num]]--;
        a[fcolor[color[num]]]++;
        upd(1 , 0 , N-1 , ix-1 , ix-1 , 1 ) ;
    }
}
int get_answer(int k ){
    int ans = que( 1 , 0 , N-1 , k , N-1) ;
    return ans ;
}

void solve() {
    
    cin>>n>>m; 
    sqn = sqrt(n) ;
    memset(a , 0 , sizeof(a)) ;
    memset(color , 0 , sizeof(color) ) ;
    adj.resize(n+1 ) ;
    query.resize(m) ;
    unordered_set<int> st ;
    build(1 , 0 , N-1 ) ;
    rep(i , 0 , n ){
        cin>>color[i+1] ;
        MAX_LEN = max(MAX_LEN , color[i+1] );
        st.insert(color[i+1]) ;
    }     
    a[0] = st.size() ;
    ++MAX_LEN ;
    rep(i , 0 , n-1 ){
        int l , r ;
        cin>>l>>r ;
        adj[l].push_back(r) ;
        adj[r].push_back(l) ;
    }

    // flatten a tree first then took query
    timer = 1 ;
    memset(inTime , 0 , sizeof(inTime) ) ;
    memset(outTime , 0 , sizeof(outTime) ) ;
    ft.push_back(0);
    memset(visited , 0 , sizeof(visited) ) ;
    dfs(1) ;

    
    rep(i ,0 , m ){
        int vj , kj ;
        cin>>vj>>kj;
        query[i].l = inTime[vj];
        query[i].r = outTime[vj];
        query[i].idx = i+1 ;
        query[i].k = kj ; 
    }

    // now apply mo's algorithm 
    sort(query.begin() , query.end() , cmp ) ;
    int answers[m+1] ;
    memset(fcolor , 0 , sizeof(fcolor) ) ;
    memset(fTempcolor , 0 , sizeof(fTempcolor) ) ;
    int cur_l = 1;
    int cur_r = 0;
    // invariant: data structure will always reflect the range [cur_l, cur_r]
    for (Query q : query ) {
        
        while (cur_l > q.l) {
            cur_l--;
            add(cur_l);
        }
        while (cur_r < q.r) {
            cur_r++;
            add(cur_r);
        }
        while (cur_l < q.l) {
            remove(cur_l);
            cur_l++;
        }
        while (cur_r > q.r) {
            remove(cur_r);
            cur_r--;
        }
        answers[q.idx] = get_answer(q.k);
        // cout<<q.l<<" : "<<q.r<<" : "<<q.k<<" : "<<q.idx<<" : "<<cur_l<<" :"<<cur_r <<endl;
    }
    for(int i  = 1 ; i<= m ; ++i )
        cout<<answers[i]<<endl;
    
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    solve();
}