#include <bits/stdc++.h>

using namespace std;

class BfsOpenLOck {
    public:
        string plusOne(string s, int i) {
            if (s[i] == '9') {
                s[i] = '0';
            }else{
                s[i] = s[i] + 1;
            }
            return s;
        }

        string minusOne(string s, int i) {
            if (s[i] == '0') {
                s[i] = '9';
            }else{
                s[i] = s[i] - 1;
            }
            return s;
        }

        vector<string> getNeighbors(string s) {
            vector<string> neighbors;
            int  n = s.size();
            for (int i = 0; i < n; i++) {
                neighbors.push_back(plusOne(s, i));
                neighbors.push_back(minusOne(s, i));
            }
            return neighbors;
        }

        int openLock(vector<string>& deadends,string target) {
            unordered_set<string> deads(deadends.begin(), deadends.end());
            if (deads.count("0000")) {
                return -1;
            }
            queue<string> q;
            unordered_set<string> visited;
            int steps = 0;
            q.push("0000");
            visited.insert("0000");
            while(!q.empty()) {
                int size = q.size();
                for (int i = 0; i < size; i++) {
                    string cur = q.front();
                    q.pop();
                    if (cur == target) {
                        return steps;
                    }
                    for(auto neighbor : getNeighbors(cur)){
                        if (deads.count(neighbor) || visited.count(neighbor)){
                            continue;
                        }else {
                            q.push(neighbor);
                            visited.insert(neighbor);
                        }
                    }
                }
                steps++;
            }
            return -1;
        }

};

int main() {
    vector<string> deadends = {"0201","0101","0102","1212","2002"};
    string target = "0202";
    BfsOpenLOck bfs;
    int res = bfs.openLock(deadends, target);
    cout << res << endl;
    return 0;
}