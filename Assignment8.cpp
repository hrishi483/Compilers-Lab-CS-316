
#include <bits/stdc++.h>
using namespace std;

set<char> ss;

bool dfs(char i, char org, char last, map<char,vector<vector<char>>> &mp, map<char,set<char>> &fmp) {
    bool rtake = false;
    for(auto r : mp[i]) {
        bool take = true;
        for(auto s : r) {
            if(s == i) break;
            if(!take) break;
            if(!(s >= 'A' && s <= 'Z') && s != 'e') {
                ss.insert(s);
                break;
            }
            else if(s == 'e') {
                if(org == i || i == last)
                    ss.insert(s);
                rtake = true;
                break;
            }
            else {
                take &= dfs(s, org, r[r.size() - 1], mp, fmp);
                rtake |= take;
            }
        }
    }
    return rtake;
}

void calculateFirstSets(map<char,vector<vector<char>>> &mp, map<char,set<char>> &fmp) {
    for(auto q : mp) {
        ss.clear();
        dfs(q.first, q.first, q.first, mp, fmp);
        for(auto g : ss) 
            fmp[q.first].insert(g);
    }
}

void calculateFollowSets(map<char,vector<vector<char>>> &mp, map<char,set<char>> &fmp, map<char,set<char>> &gmp, char start) {
    gmp[start].insert('$');
    int count = 10;
    while(count--) {
        for(auto q : mp) {
            for(auto r : q.second) {
                for(size_t i = 0; i < r.size(); i++) {
                    if(r[i] >= 'A' && r[i] <= 'Z') {
                        if(i == r.size() - 1) {
                            for(auto g : gmp[q.first]) 
                                gmp[r[i]].insert(g);
                        }
                        if(i < r.size() - 1 && !(r[i + 1] >= 'A' && r[i + 1] <= 'Z')) 
                            gmp[r[i]].insert(r[i + 1]);
                        else {
                            char temp = r[i + 1];
                            size_t j = i + 1;
                            while(temp >= 'A' && temp <= 'Z') {
                                if(!fmp[temp].empty() && *fmp[temp].begin() == 'e') {
                                    for(auto g : fmp[temp]) {
                                        if(g == 'e') continue;
                                        gmp[r[i]].insert(g);
                                    }
                                    j++;
                                    if(j < r.size()) {
                                        temp = r[j];
                                        if(!(temp >= 'A' && temp <= 'Z')) {
                                            gmp[r[i]].insert(temp);
                                            break;
                                        }
                                    }
                                    else {
                                        for(auto g : gmp[q.first]) 
                                            gmp[r[i]].insert(g);
                                        break;
                                    }
                                }
                                else {
                                    for(auto g : fmp[temp]) {
                                        gmp[r[i]].insert(g);
                                    }
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void printSets(map<char,set<char>> &fmp, map<char,set<char>> &gmp) {
    cout << "FIRST: " << endl;
    for(auto q : fmp) {
        string ans = "";
        ans += q.first;
        ans += " = {";
        for(char r : q.second) {
            ans += r;
            ans += ',';
        }
        ans.pop_back();
        ans += "}";
        cout << ans << endl;
    }

    cout << endl;
    cout << "FOLLOW: " << endl;
    for(auto q : gmp) {
        string ans = "";
        ans += q.first;
        ans += " = {";
        for(char r : q.second) {
            ans += r;
            ans += ',';
        }
        ans.pop_back();
        ans += "}";
        cout << ans << endl;
    }
}

int main(){
    // map<char,vector<vector<char>>> mp = {
    //     {'S', {{'A', 'C', 'B'}, {'C', 'b', 'B'}, {'B', 'a'}}},
    //     {'A', {{'d', 'a'}, {'B', 'C'}}},
    //     {'B', {{'g'}, {'e'}}},
    //     {'C', {{'h'}, {'e'}}}
    // };
    map<char,vector<vector<char>>> mp = {
        {'E', {{'E', '+', 'T'}, {'T'}}},
        {'T', {{'T','*','F'}, {'F'}}},
        {'F', {{'d'}}}
    };
    
    char start = 'E';

    map<char,set<char>> fmp, gmp;

    calculateFirstSets(mp, fmp);
    calculateFollowSets(mp, fmp, gmp, start);
    printSets(fmp, gmp);

    return 0;
}
