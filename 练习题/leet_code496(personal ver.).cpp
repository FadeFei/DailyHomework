class Solution {
public:
    int findMaxNum(vector<int>& num) {
        int max = num[0];
        for (int i = 0; i < num.size(); i++) {
            if (num[i] > max) max = num[i];
        }
        return max;
    }
    vector<int> nextGreaterElement(vector<int>& findNums, vector<int>& nums) {
        vector<int> validNums;
        if (findNums.size() == 0 || nums.size() == 0) {
            return validNums; 
        }
        int maxNum = findMaxNum(nums);
        for (int i = 0; i < findNums.size(); i++) {
            if (findNums[i] == maxNum) {
                validNums.push_back(-1);
                continue;
            }
            int flag = 0;
            for (int j = 0; j < nums.size(); j++) {
                if (nums[j] == findNums[i]) flag = j;
            }
            while (flag < nums.size()) {
                flag++;
                if (flag == nums.size()) {
                    validNums.push_back(-1);
                    break;
                } 
                if (nums[flag] > findNums[i]) {
                    validNums.push_back(nums[flag]);
                    break;
                }
            }
        }
        return validNums;
    }
};