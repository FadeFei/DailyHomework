
class Solution {
public:
    vector<string> fizzBuzz(int n) {
        vector<string> validString;
        for (int i = 1; i <= n; i++) {
        	if (i%3 == 0 && i%5 == 0) {
        		validString.push_back("FizzBuzz");
        	} else if (i%3 == 0) {
        		validString.push_back("Fizz");
        	} else if (i%5 == 0) {
        		validString.push_back("Buzz");
        	} else {
        		validString.push_back(to_string(i));
        	}
        }
        return validString;
    }
};