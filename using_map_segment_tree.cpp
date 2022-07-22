class segment_tree {
    map<pair<int,int>,int> mp;
    int n ;
    void build_map(int l , int r ){
        if(l == r ){
            return ;
        }
        int m = (l+r)/2;
        build_map(l , m);
        build_map(m+1 , r);
        mp[{l,r}] = mp[{l,m}] + mp[{m+1,r}];
        return ;
    }
    void update(int index, int val , int l , int r ){
        if(l == r && l == index){
            mp[{l,r}] = val;
            return ;
        }
        int m = (l+r)/2 ;
        if( index<= m ){
            update(index , val , l , m);
        }
        else{
            update(index , val , m+1 , r );
        }
        mp[{l,r}] = mp[{l,m}] + mp[{m+1,r}];
        return ;
    }
    
    int find_sum(int l , int r , int cl , int cr ){
        if( l == cl && r == cr ){
            return mp[{cl , cr}];
        }
        
        int m = (cl + cr)/2 ;
        if(r <= m ){
            return find_sum(l , r , cl , m );
        }
        else if(l>m){
            return find_sum(l , r , m+1 , cr );
        }
        else {
            return find_sum(l , m , cl , m ) + find_sum( m+1 , r , m+1 , cr );
        }
    }
public:
    segment_tree(vector<int>& nums) {
        n = nums.size();
        for(int i = 0 ; i< nums.size() ; ++i ){
            mp[{i+1,i+1}] = nums[i] ;
        }
        build_map(1 , n );
        
    }
    
    void update(int index, int val) {
        update(index+1 , val , 1 , n );
        
    }
    
    int sumRange(int left, int right) {
        return find_sum(left+1 , right+1 , 1 , n );
    }
};