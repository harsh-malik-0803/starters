class trienode{
    public:
    trienode * left , * right ;
    int data;
    trienode(){
        left = NULL;
        right = NULL;
        data = 0 ;
    }
};

class trie{
    trienode * root = NULL ;
    public:
    trie(){
        root = new trienode();
    }
    void insert(int num ){
        trienode * t = root ;
        
        for(int i = 31 ; i>=0 ; --i ){
            int curr = num>>i & 1 ;
            if(curr == 0 ){
                if(t->left == NULL){
                    trienode * newnode = new trienode();
                    t->left = newnode ;
                }
                t = t->left ;
            }
            else{
                if(t->right == NULL){
                    trienode * newnode = new trienode();
                    t->right = newnode ;
                }
                t = t->right ;
            }
            
        }
    }
    int find_max(int num ){
        
        int ans = 0 ;
        trienode * t = root ;
        if(root == NULL || (root->left == NULL && root->right == NULL )) return -1;
        for(int i= 31 ; i>=0 ; --i ){
            int curr = num>>i & 1 ;
            if(curr == 0 ){
                // it will go to opposite direction 
                
                if( t->right ){
                    t = t->right;
                    ans = ans + (1<<i);
                }
                else{
                    t = t->left;
                }
            }
            else{
                if(t->left ) {
                    t = t->left ;
                    ans = ans + (1<<i) ;
                }
                else{
                    t = t->right;
                }
            }
        }
        return ans ;
    }
};


// -----------------------------
//     count node going through that -------------------

// class trienode{
//     public:
//     trienode * left , *right  ;
//     int cnt ;
//     trienode(){
//         left = NULL;
//         right = NULL;
//         cnt = 0 ;
//     }
// };

// class trie{
//     trienode * root = NULL ;
//     public:
//     trie(){
//         root = new trienode();
//     }
//     void insert(int num ){
//         trienode * t = root ;
        
//         for(int i = 31 ; i>=0 ; --i ){
//             int curr = num>>i & 1 ;
//             if(curr == 0 ){
//                 if(t->left == NULL){
//                     trienode * newnode = new trienode();
//                     t->left = newnode ;
//                 }
//                 t = t->left ;
//             }
//             else{
//                 if(t->right == NULL){
//                     trienode * newnode = new trienode();
//                     t->right = newnode ;
//                 }
//                 t = t->right ;
//             }
//             t->cnt++; 
//         }
//     }
//     int find_max(int num ){
        
//         int ans = 0 ;
//         trienode * t = root ;
//         if(root == NULL || (root->left == NULL && root->right == NULL )) return -1;
//         for(int i= 31 ; i>=0 ; --i ){
//             int curr = num>>i & 1 ;
//             if(curr == 0 ){
//                 // it will go to opposite direction 
                
//                 if( t->right && t->right->cnt > 0 ){
//                     t = t->right;
//                     ans = ans + (1<<i);
//                 }
//                 else{
//                     t = t->left;
//                 }
//             }
//             else{
//                 if(t->left && t->left->cnt > 0) {
//                     t = t->left ;
//                     ans = ans + (1<<i) ;
//                 }
//                 else{
//                     t = t->right;
//                 }
//             }
//         }
//         return ans ;
//     }
//     void remove_node(int num ){
//         trienode * t = root ;
        
//         for(int i = 31 ; i>=0 ; --i ){
//             int curr = num>>i & 1 ;
//             if(curr == 0 ){
//                 t = t->left ;
//             }
//             else{
//                 t = t->right ;
//             }
//             (t->cnt)--; 
//         }
//     }
// };
