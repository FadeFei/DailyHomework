class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& findNums, vector<int>& nums) {
        stack<int> s;
        unordered_map<int, int> m;

        //这一块其实是遍历nums，然后找到每一个数字右边第一个比它大的数字！然后放到map类型的m里面！
        for (int n : nums) {
            while (s.size() && s.top() < n) {
                m[s.top()] = n;
                s.pop();
            }
            s.push(n);
        }



        vector<int> ans;

        // 这一块也不难，遍历每个findNums，然后根据上面得到的map类型m，寻找每一个在m中是否有映射，有的话就把映射存到数组，没有就存-1！
        for (int n : findNums) ans.push_back(m.count(n) ? m[n] : -1);
        return ans;
    }
};