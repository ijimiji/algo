#include <cstdint>
#include <vector>
#define let const auto
#define var auto
#define fn auto

#include <fstream>
#include <queue>
#include <stack>

using namespace std;

int main(){
    ifstream input("huffman.in");
    ofstream output("huffman.out");
    int64_t buffer, left, right;
    input >> buffer;

    stack<int64_t> s;
    priority_queue<int64_t, vector<int64_t>, greater<int64_t>> q;

    while(input >> buffer){
        q.push(buffer);
    }

    buffer = 0;
    while(true){
        left = q.top();
        q.pop();
        if (q.empty()){
            while (!s.empty()){
                buffer += s.top();
                s.pop();
            }
            output << buffer;
            break;
        } else {
            right = q.top();
            q.pop();
            s.push(right + left);
            q.push(s.top());
        }
    }

    return 0;
}