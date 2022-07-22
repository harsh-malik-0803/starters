const int p = 1e9 + 7 ;
#define ll long long
class Solution {
public:
    int totalStrength(vector<int>& s) {
        int n = s.size();
        int left[n];
        int right[n];
        memset(left , 0 , sizeof(left));
        memset(right , 0 , sizeof(right));
        stack<int> st ;
        st.push(-1) ;
        for(int i = 0 ; i< n ; ++i ){
            while(st.size()>1 && s[st.top()] > s[i] ) st.pop();
            left[i] = st.top() ;
            st.push(i);
        }
        while(st.size() > 0 ) st.pop() ;
        st.push(n);
        for(int i = n-1 ; i>=0 ; --i ){
            while(st.size()>1 && s[st.top()] >= s[i] ) st.pop();
            right[i] = st.top() ;
            st.push(i);
        }
        
        vector<long long> prefix(n + 1, 0L);
        for (int i = 0; i < n; ++i) {
            prefix[i + 1] = (prefix[i] + s[i]) % p;
        }
        // sum of first k prefix
        vector<long long> prefix_sum(n + 2, 0L);
        for (int i = 0; i <= n; ++i) {
            prefix_sum[i + 1] = (prefix_sum[i] + prefix[i]) % p;
        }
        
        long long res = 0 ;
        for(int i = 0 ; i< n ; ++i ){
            res += ((prefix_sum[right[i] + 1] - prefix_sum[i + 1]) * (i - left[i]) % p + p * 2 - 
               (prefix_sum[i + 1] - prefix_sum[left[i] + 1]) * (right[i] - i) % p) % p * s[i] % p;
            res %= p;
        }
        return res ;
    }
};