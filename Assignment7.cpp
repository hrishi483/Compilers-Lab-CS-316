#include <bits/stdc++.h>
#include <string.h>
using namespace std;

char getLowerCaseLetter(char A) {
    if (A >= 'A' && A <= 'Z') { // Check if A is a capital letter
        return static_cast<char>(A - 'A' + 'a'); // Convert to lowercase
    } else {
        return A; // If A is not a capital letter, return as it is
    }
}

bool check_left_recursion(vector<char> input)
{
    if(input[0]==input[1]){
        return true;
    }
    else{
        return false;
    }
}

vector<vector<char>> remove_left_recursion(vector<char> input){
    vector<char> alpha;
    vector<char> beta;
    char A = input[0];
    
    bool temp=false;
    for(int i=2;i<input.size();i++){
        if(input[i]=='|'){
            temp=true;
        }
        else{
            if(temp){
                beta.push_back(input[i]);
            }
            else{
                alpha.push_back(input[i]);
            }
        }
    }
    if(alpha.size()==0){
        alpha.push_back('e');
    }
    if(beta.size()==0){
        beta.push_back('e');
    }
    
    // cout<<"alpha ";
    // for(auto i:alpha){
    //     cout<<i<<" | ";
    // }
    // cout<<endl;
    // cout<<"beta ";    
    // for(auto i:beta){
    //     cout<<i<<" | ";
    // }
    // cout<<endl;
    // cout<<A<<endl;
    vector<vector<char>> ans;
    vector<char> rule1;
    // A' = a  && epsilon  = #
     // A->beta a  
     
    rule1.push_back(A);
    for(auto i:beta){
        rule1.push_back(i);
    }
    rule1.push_back(getLowerCaseLetter(A));
    ans.push_back(rule1);
    
    // a->alpha a|e
    vector<char> rule2;
    rule2.push_back(getLowerCaseLetter(A));
    for(auto i:alpha){
        rule2.push_back(i);
    }
    rule2.push_back(getLowerCaseLetter(A));
    rule2.push_back('|');
    rule2.push_back('#');
    
    ans.push_back(rule2);
    
    // for(auto i:ans){
    //     cout<<"RULE: ";
    //     for(auto j:i){
    //         cout<<j<<" | ";
    //     }
    //     cout<<endl;
    // }
    // cout<<endl;

    return ans;
}

int main(int argc, char *argv[]) 
{ 
    vector<vector<string>> rules;
    vector<vector<char>>new_rules;
    
    while (true) {
        cout << "Enter Left Part || Enter . to end: ";
        char left;
        cin >> left;

        if (left == '.'){
            break;
        }
        else{   
            vector<char>input;
            input.push_back(left);
            
            while (true){
                // one by one OR Enter . to end : OR Enter |"
                cout << "Enter Right side ";
                char right;
                cin >> right;
                if(right=='.'){
                    break;
                }
                else{
                    input.push_back(right);
                }
            } 
            for(int i=0;i<input.size();i++){
                if(i==0)
                    cout<<input[0]<<" -> ";
                else
                    cout<<input[i]<<" ";
            }
            cout<<endl;
            if(check_left_recursion(input)){
                cout<<"Left recursion exist:Remove it "<<endl;
                vector<vector<char>>no_lr = remove_left_recursion(input);
                for(int i=0; i<no_lr.size();i++){
                    new_rules.push_back(no_lr[i]);
                    }
                cout<<endl;
                }
            else{
                new_rules.push_back(input);
                cout<<"No Left recursion exist"<<endl;
            }
        } 
    }
    cout<<endl;
    for(int i=0; i<new_rules.size();i++){
        cout<<i<<": ";
        for(int j=0;j<new_rules[i].size();j++){
            if(j==0){
                cout<<new_rules[i][0]<<" -> ";
            }
            else{
                cout<<new_rules[i][j]<<" ";
            }
        }
        cout<<endl;
    }
    return 0;
}


// E
// E
// +
// T
// |
// F
// .
// T
// T
// *
// F
// |
// F
// .
// F
// i
// .