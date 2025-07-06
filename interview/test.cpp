#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1.0);
const double EPS = 1e-9;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int K;
    if (!(cin >> K)) return 0;

    struct Cam { double fov; double L; };
    vector<Cam> cams(K);
    for (int i = 0; i < K; ++i) {
        cin >> cams[i].L >> cams[i].fov;          // 题目顺序：感知距离 L  视场角 fov
    }

    int n;
    cin >> n;
    vector<pair<int,int>> pts(n);
    for (int i = 0; i < n; ++i) cin >> pts[i].first >> pts[i].second;

    // 原点障碍物数量
    int zeroCnt = 0;
    for (auto &p : pts) if (p.first == 0 && p.second == 0) ++zeroCnt;

    int answer = 0;                               // 最终结果

    for (const auto &cam : cams) {
        double L2 = cam.L * cam.L;
        double alpha = cam.fov * PI / 180.0;      // 弧度

        // 收集在距离范围内的点的极角
        vector<double> ang;
        ang.reserve(n);
        for (auto &p : pts) {
            long long x = p.first, y = p.second;
            if (x == 0 && y == 0) continue;       // 原点已单独统计
            if (1.0 * x * x + 1.0 * y * y - L2 <= EPS) {
                double a = atan2((double)y, (double)x);
                if (a < 0) a += 2 * PI;
                ang.push_back(a);
            }
        }

        int m = (int)ang.size();
        if (m == 0) {                             // 远处无点
            answer = max(answer, zeroCnt);
            continue;
        }

        // 若 FOV ≥ 360，直接全向
        if (cam.fov >= 360.0 - EPS) {
            answer = max(answer, m + zeroCnt);
            continue;
        }

        sort(ang.begin(), ang.end());
        ang.resize(2 * m);
        for (int i = 0; i < m; ++i) ang[i + m] = ang[i] + 2 * PI;

        int best = 0;
        for (int i = 0, j = 0; i < m; ++i) {
            while (j < i + m && ang[j] - ang[i] <= alpha + EPS) ++j;
            best = max(best, j - i);
        }

        answer = max(answer, best + zeroCnt);
    }

    cout << answer << '\n';
    return 0;
}
