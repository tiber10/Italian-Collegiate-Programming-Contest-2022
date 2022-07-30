// NOTE: it is recommended to use this even if you don't understand the
// following code.

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// input data
int N;
string S;

int main() {


    cin >> N;
    cin >> S;
    string cod = {"qwertyuiopasdfghjklzxcvbnm"};
    for(int i=0;i<N;i++){
        for(int j=0;j<26;j++){
            if(S[i]==cod[j]){
                S[i] = cod[j+1];
                break;
            }
        }
    }

    cout << S << endl; // print the result
    return 0;
}
