class Solution {
public:
    vector<string> findWords(vector<string>& words) {
        unordered_set<char> row1 {'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p'};
        unordered_set<char> row2 {'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l'};
        unordered_set<char> row3 {'z', 'x', 'c', 'v', 'b', 'n', 'm'};
        vector<unordered_set<char>> rowset = {row1, row2, row3};

        vector<string> rightWords;
        for (int i = 0; i < words.size(); i++) {
        	int row = 0;
        	for (int k = 0; k < 3; k++) 
        		if (rowset[k].count((char)tolower(words[i][0])) > 0) 
        			row = k;	//测出这个words[i]是第几个row

        	rightWords.push_back(words[i]);
        	for (int j = 1; j < words[i].size(); j++) {
        		if (rowset[row].count((char)tolower(words[i][j])) == 0) { // 说明这个words[i]中第j个字母不在rows[row]中
        			rightWords.pop_back();	// 不符合要求，舍去这个words
        			break;
        		}
        	}
        }
        return rightWords;
    }
};