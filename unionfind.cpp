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
        return (parent[p] == parent[q]);
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