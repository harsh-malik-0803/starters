#include <bits/stdc++.h>
#define el '\n' 
#define ll long long
#define rep(i, a, b) for(int i = (a); i < (b); i++)
using namespace std;

int MAX_LEN = 0 ;
const int N = 1e5+5 ;
int n , m ;
int sqn = N ;
const int len = sqrt(1e5+5) + 1 ;

// segment tree
int a[N] ;
int b[len+2];


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
        b[ix/len]-- ;
        // upd(1 , 0 , N-1 , ix , ix , -1 ) ;
        fcolor[color[num]]++;
        a[fcolor[color[num]]]++;
        b[(ix+1)/len]++ ;
        // upd(1 , 0 , N-1 , ix + 1 , ix+1 , 1 ) ;
    }
}
void remove(int idx ){
    int num = ft[idx] ;
    fTempcolor[color[num]]--;
    if(fTempcolor[color[num]] % 2 ){
        int ix = fcolor[color[num]] ;
        a[fcolor[color[num]]]--;
        b[ix/len]-- ;
        // upd(1 , 0 , N-1 , ix , ix , -1 ) ;
        fcolor[color[num]]--;
        a[fcolor[color[num]]]++;
        b[(ix-1)/len]++ ;
        // upd(1 , 0 , N-1 , ix-1 , ix-1 , 1 ) ;
    }
}
int get_answer(int l , int r = N-2 ){
    ll sum = 0 ;
    ll c_l = l / len,   c_r = r / len;
    if (c_l == c_r)
        for (int i=l; i<=r; ++i)
            sum += a[i];
    else {
        for (int i=l, end=(c_l+1)*len-1; i<=end; ++i)
            sum += a[i];
        for (int i=c_l+1; i<=c_r-1; ++i)
            sum += b[i];
        for (int i=c_r*len; i<=r; ++i)
            sum += a[i];
    }
    return sum ;
}

void solve() {
    
    cin>>n>>m; 
    sqn = sqrt(n) ;
    memset(a , 0 , sizeof(a)) ;
    memset(b , 0 , sizeof(b)) ;
    memset(color , 0 , sizeof(color) ) ;
    adj.resize(n+1 ) ;
    query.resize(m) ;
    unordered_set<int> st ;
    
    rep(i , 0 , n ){
        cin>>color[i+1] ;
        MAX_LEN = max(MAX_LEN , color[i+1] );
        st.insert(color[i+1]) ;
    }     
    a[0] = st.size() ;
    b[0] = a[0] ;
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