#include<bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std ;

// for no reapeat element   
// #define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>



//  for elements repeated 
typedef tree<long long, null_type, less_equal<long long>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

int main(){
    ordered_set st ;
    st.insert(5) ;
    st.insert(5) ;
    st.insert(4) ;
    st.insert(4) ;
    st.insert(1) ;
    st.insert(2) ;
    st.insert(6) ;
    cout<<st.order_of_key(6) ;
    cout<<*(st.find_by_order(1))<<endl;
}