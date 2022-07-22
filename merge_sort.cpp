class node{
    public:
    int val , idx , cnt ;
    node(){
        val = 0 , idx = 0 , cnt = 0 ;   
    }
    node(int v ,int i ){
        val = v , idx = i ;
        cnt = 0 ;
    }
};

class Solution {
public:
    void merge_arr(int  l, int mid , int r , vector<node>&arr ){
        int len1 = mid - l +1 ;
        int len2 = r-mid  ;
        node arr1[len1];
        node arr2[len2];
        
        for(int i = l ; i<= mid ; ++i ){
            arr1[i-l] = arr[i];
        }
        for(int i = mid+1 ; i<= r ; ++i ){
            arr2[i-mid-1] = arr[i];
        }
        
        int i = 0 , j = 0  , cnt = 0 ;
        
        int k = l ;
        while(i<len1 && j< len2 ){
            if(arr1[i].val <= arr2[j].val ){
                arr1[i].cnt += cnt ;
                arr[k] = arr1[i];
                ++i;
                ++k;
            }
            else{
                ++cnt;
                arr[k] = arr2[j];
                ++j;
                ++k;
            }
        }
        while(i<len1){
            arr1[i].cnt += cnt ;
            arr[k] = arr1[i];
            ++i;
            ++k;
        }
        while(j<len2){
            arr[k] = arr2[j];
            ++j;
            ++k;
        }
    }
    void merge_sort(int l , int r , vector<node>&arr ){
        if(r <= l) return ;
        int mid = (l+r)/2 ;
        //cout<<l <<" "<<mid<<" "<<r<<endl;
        merge_sort(l , mid , arr ) ;
        merge_sort(mid+1 , r , arr);
        merge_arr(l , mid , r , arr ) ;
    }
    vector<int> countSmaller(vector<int>& nu) {
        vector<node> nums ;
        for(int i = 0 ; i< nu.size() ; ++i ){
            node n1(nu[i] , i ) ;
            nums.push_back(n1);
        }
        merge_sort(0 , nums.size()-1  , nums );
        vector<int> ans(nums.size() , 0 );
        for(auto it : nums ){
            ans[it.idx] = it.cnt ;
        }
        return ans ;
    }
};