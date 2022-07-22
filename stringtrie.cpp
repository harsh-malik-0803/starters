class node{
    public:
    bool ends_here ;
    node ** children ; 
    node(){
        ends_here = false ;
        children = new node*[26];
        for(int i = 0 ;i< 26 ; ++i ){
            children[i] = NULL ;
        }
    }
    
};

class Trie {
    node * head = NULL ;
public:
    Trie() {
        head = new node() ;
    }
    
    void insert(string word) {
        if(search(word)) return ; 
        
        int n = word.size();
        node * t = head ;
        for(int i = 0 ; i< n ; ++i ){
            int curr = word[i]-'a';
            if(t->children[curr] == NULL ){
                node * newnode = new node();
                t->children[curr] = newnode ;
            }
            
            t = t->children[curr] ;
            if(i == n-1  ){
                t->ends_here = true ;
            }
        }
        
    }
    
    bool search(string word) {
        
        int n = word.size();
        node * t = head ;
        for(int i = 0 ; i< n ; ++i ){
            int curr = word[i]-'a';
            if(t->children[curr] == NULL ){
                return false ;
            }
            t = t->children[curr] ;
            if(i == n-1 && t->ends_here ){
                return true;
            }
        }
        return false ;
    }
    
    bool startsWith(string prefix) {
        int n = prefix.size();
        node * t = head ;
        for(int i = 0 ; i< n ; ++i ){
            int curr = prefix[i]-'a';
            if(t->children[curr] == NULL ){
                return false ;
            }
            t = t->children[curr] ;
        }
        return true ;
    }
};



//  2nd implementation 



class trienode{
    public:
    bool ends ;
    trienode ** children;
    string word ;
    trienode(){
        word = "";
        ends = false ;
        children = new trienode*[26];
        for(int i = 0 ; i< 26 ; ++i )
            children[i] = NULL;   
    }
};

class trie{
    
    void insert(string word , trienode * t , int i ){
        int curr = word[i] - 'a' ;
        trienode * newnode ;
        if(t->children[curr] == NULL ){
            newnode = new trienode();
            t->children[curr] = newnode;
        }
        t->children[curr]->word = t->word + word[i];
        if( i == word.length()-1 ){
            t->children[curr]->ends = true;
            return ;
        }
        insert(word , t->children[curr] , i+1 );
    }
    public:
    trienode * root ;
    trie(){
        root = new trienode() ;
    }
    void insert(string word){
        insert(word , root , 0 );
    }
};
