#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;


// for no reapeat element   
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>



//  for elements repeated 
typedef tree<long long, null_type, less_equal<long long>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;