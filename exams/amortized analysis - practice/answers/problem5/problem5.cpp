#include <iostream>
#include <vector>

using namespace std;

string getCommonPrefix(string& word1, string &word2){
    auto size1 = word1.size(), size2 = word2.size();
    int i,j;
    string toBeReturned;
    for(i=0, j=0; i<size1 and j<size2; ++i,++j){
        if (word1[i] != word2[j])
            break;
        toBeReturned.push_back(word1[i]);
    }
    return toBeReturned;
}

string commonPrefix(vector<string>& words, int min, int max){
    if (min == max)
        return words[max];
    else{
        int mid = (max - min)/2;
        string dividedProblem1=commonPrefix(words, min, mid);
        string dividedProblem2=commonPrefix(words, mid+1, max);
        return getCommonPrefix(dividedProblem1, dividedProblem2);
    }
}

string problem5(vector<string>& words) {
    return commonPrefix(words,0,(int)words.size()-1);
}

int main() {
    std::cout << "Problem 5 - Prefix\n";
    std::vector<std::string> words = {"prefixHOLA", "prefixChau", "prefixPALABRA"};
    std::cout << problem5(words) << "\n";

    ///T(n) = 2T(n/2) + O(m), where m is length of the words
}
