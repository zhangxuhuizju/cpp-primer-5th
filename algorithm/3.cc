#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// void slove(vector<int>& vec)
// {
//     int len = vec.size();
 
//     int sum = 0;
//     for (int i = 0; i < len; ++i) {
//         sum += vec[i];
//     }
 
//     vector<vector<int>> dp;
//     for (int i = 0; i <= len; i++) {
//         vector<int>tmp;
//         for (int j = 0; j <= sum / 2; ++j) {
//             tmp.push_back(0);
//         }
//         dp.push_back(tmp);
//     }
 
//     for (int i = 1; i <= len; ++i) {
//         for (int j = 1; j <= sum / 2; ++j) {
//             if(j>=vec[i-1])
//                 dp[i][j] = max(dp[i-1][j],dp[i-1][j-vec[i-1]]+vec[i-1]);
//             else 
//                 dp[i][j] = dp[i - 1][j];
//         }
//     }
    
//     cout << dp[len][sum/2] << ' ' << sum - dp[len][sum / 2] << endl;
// }


int main(int argc, char const *argv[])
{
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        int* battle = new int[n];
        for (int i = 0; i < n; ++i) {
            cin >> battle[i];
        }
        sort(battle, battle + n);
        int sum1 = battle[0], sum2 = battle[1];
        for (int i = 2; i < n; i += 2) {
            if (sum1 < sum2) {
                if(i+1 < n)
                    sum1 += battle[i+1];
                sum2 += battle[i];
            } else {
                sum1 += battle[i];
                if(i+1 < n)
                    sum2 += battle[i+1];
            }
        }
        if (sum1 > sum2)
            swap(sum1, sum2);
        cout << sum1 << ' ' << sum2 << endl;
    }
    return 0;
}
