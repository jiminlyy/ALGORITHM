#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <cstdlib>
#include <ctime>

using namespace std;


long long comparison_cnt = 0;

// DNA 만들기
string generateDNA(int len) {
    string dna = "";
    char base[4] = { 'A', 'C', 'G', 'T' };
    for (int i = 0; i < len; i++) {
        dna += base[rand() % 4];
    }
    return dna;
}

//미스 매치를 두개 이하로 만들기 위함
int countMismatches(const string& text, int startIdx, const string& pattern, int max_err) {
    int errors = 0;
    int m = pattern.length();

    for (int i = 0; i < m; i++) {
        if (startIdx + i >= text.length()) return max_err + 1;
        comparison_cnt++;
        if (text[startIdx + i] != pattern[i]) errors++;
        if (errors > max_err) return errors;
    }
    return errors;
}

int main() {
    srand(time(0));

   
    int n = 10000;
    int m = 18; 
    int k = 6; 

    string text = generateDNA(n);


    int true_pos = rand() % (n - m);
    string original_pattern = text.substr(true_pos, m);
    string target_pattern = original_pattern;

    int p1 = rand() % m;
    int p2 = rand() % m;
    while (p1 == p2) { p2 = rand() % m; }
    target_pattern[p1] = (target_pattern[p1] == 'A') ? 'T' : 'A';
    target_pattern[p2] = (target_pattern[p2] == 'A') ? 'T' : 'A';

    cout << "Target Pattern 길이: " << m << endl;
    cout << "Sequence 길이      : " << k << endl; 
 
    cout << "Target Pattern (Error 2개 이하): " << target_pattern << endl;
    cout <<  endl;


    map<string, vector<int>> phoneBook;
    for (int i = 0; i <= n - k; i++) {
        phoneBook[text.substr(i, k)].push_back(i);
    }

  
    comparison_cnt = 0;
    vector<int> perfect_matches;
    set<int> candidates;

    for (int i = 0; i < 3; i++) {
        string seq = target_pattern.substr(i * k, k);
        if (phoneBook.find(seq) != phoneBook.end()) {
            for (int idx : phoneBook[seq]) {
                int start = idx - (i * k);
                if (start >= 0 && start <= n - m) candidates.insert(start);
            }
        }
    }

    for (int start : candidates) {
        if (countMismatches(text, start, target_pattern, 2) <= 2) {
            perfect_matches.push_back(start);
        }
    }
    long long perfect_comparison_result = comparison_cnt;

    comparison_cnt = 0;
    vector<int> trivial_matches;
    for (int i = 0; i <= n - m; i++) {
        if (countMismatches(text, i, target_pattern, 2) <= 2) {
            trivial_matches.push_back(i);
        }
    }
    long long trivial_comparison_result = comparison_cnt;

    cout << "Perfect Match" << endl;
    cout << "비교 횟수: " << perfect_comparison_result << endl;
    if (perfect_matches.empty()) cout << "찾지 못함" << endl;
    for (int p : perfect_matches) {
        cout << "찾은 위치: " << p << endl;
        cout << "찾으려는 READ : " << text.substr(p, k) << endl;
    }
    cout << endl;

    cout << "Trivial Match" << endl;
    cout << "비교 횟수: " << trivial_comparison_result << endl;
    if (trivial_matches.empty()) cout << "찾지 못함" << endl;
    for (int p : trivial_matches) {
        cout << "찾은 위치: " << p << endl;
        cout << "찾으려는 READ : " << text.substr(p, m) << endl;
    }
    
    return 0;
}