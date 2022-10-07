// #include <iostream>

// using namespace std;

// int main()
// {
//     int N, K, M;
//     cin >> N >> K >> M;
//     int res = 0;
//     while (N >= K)
//     {
//         N -= K;
//         res += K / M;
//         N += K % M;
//     }
//     cout << res << endl;
// }

// #include <iostream>
// #include <string>
// #include <cstring>
// #include <vector>
// #include <chrono>
// using namespace std;

// int isInterleave(
//     string A, string B, string C)
// {
//     int M = A.length(), N = B.length();
//     int IL[M + 1][N + 1];
//     memset(IL, 0, (M + 1) * (N + 1) * sizeof(int));
//     vector<int> vec(N + 1);
//     bool flag = true;
//     for (int i = 0; i <= M; ++i)
//     {
//         for (int j = 0; j <= N; ++j)
//         {
//             if (i == 0 && j == 0)
//             {
//                 IL[i][j] = 1;
//             }
//             else if (i == 0)
//             {
//                 if (B[j - 1] == C[j - 1])
//                 {
//                     IL[i][j] = IL[i][j - 1];
//                 }
//             }
//             else if (j == 0)
//             {
//                 if (A[i - 1] == C[i - 1])
//                 {
//                     IL[i][j] = IL[i - 1][j];
//                 }
//             }
//             else if (A[i - 1] == C[i + j - 1] && B[j - 1] != C[i + j - 1])
//             {
//                 if (IL[i - 1][j] > 0 && vec[j] == 1)
//                 {
//                     IL[i][j] = IL[i - 1][j] + 1;
//                 }

//                 else
//                 {
//                     IL[i][j] = IL[i - 1][j];
//                 }
//                 flag = true;
//             }

//             else if (A[i - 1] != C[i + j - 1] && B[j - 1] == C[i + j - 1])
//             {
//                 if (IL[i][j - 1] > 0 && flag)
//                 {
//                     IL[i][j] = IL[i][j - 1] + 1;
//                     flag = false;
//                 }

//                 else
//                     IL[i][j] = IL[i][j - 1];
//             }

//             else if (
//                 A[i - 1] == C[i + j - 1] && B[j - 1] == C[i + j - 1])
//             {
//                 if (((IL[i - 1][j] <= IL[i][j - 1]) && IL[i - 1][j] > 0) || (IL[i][j - 1] == 0))
//                 {
//                     if (IL[i - 1][j])
//                     {
//                         IL[i][j] = IL[i - 1][j] + (vec[j] == 1);
//                         flag = true;
//                     }
//                 }
//                 else if (((IL[i - 1][j] > IL[i][j - 1]) && IL[i][j - 1] > 0) || (IL[i - 1][j] == 0))
//                 {
//                     if (IL[i][j - 1])
//                     {
//                         IL[i][j] = IL[i][j - 1] + (flag ==true);
//                         flag = false;
//                     }
//                 }
//             }
//             if (IL[i][j] > 0)
//             {
//                 vec[j] += 1;
//             }
//             else
//             {
//                 vec[j] = 0;
//             }
//         }
//         flag = true;
//     }
//     return IL[M][N] - 1;
// }
// int main()
// {
//     string t1, t2, s;
//     cin >> s >> t1 >> t2;
//     cout << isInterleave(t1, t2, s) << endl;
//     return 0;
// }

// #include <iostream>
// using namespace std;

// int main()
// {
//     int n;
//     cin >> n;
//     int count = 0;
//     if (n > 27)
//     {
//         cout << 0 << endl;
//         return 0;
//     }
//     for (int a = 0; a < 10; a++)
//     {
//         for (int b = 0; b < 10; b++)
//         {
//             for (int d = 0; d < 10; d++)
//             {
//                 for (int e = 0; e < 10; e++)
//                 {
//                     if ((a + b <= n) && (n - a - b <= 9) && (a + d <= n) && (n - a - d <= 9) && (e + b <= n) && (n - e - b <= 9) && (d + e <= n) && (n - d - e <= 9) && (a + b + d + e >= n) && (a + b + d + e <= 2 * n) && (a + b + d + e - n <= 9))
//                         count++;
//                 }
//             }
//         }
//     }
//     cout << count << endl;
// }

// def func(arr_cola):
//     cola_mean = sum(arr_cola) / len(arr_cola)
//     res = 0
//     for cola in arr_cola:
//         if cola > cola_mean:
//             res += 1
//     return res

// arr_cola = []
// for _ in range(10):
//     arr_cola.append(int(input()))
// print(func(arr_cola))

#include <iostream>
#include <vector>
using namespace std;
int main() {
    int c;
    vector<int> arr_cola;
    int sum=0;
    for (int i =0;i<10;i++) {
        cin>>c;
        arr_cola.push_back(c);
        sum+=c;
    }
    int cola_mean=sum/10;
    int res = 0;
    for (const auto &cola :arr_cola) {
        if (cola>cola_mean) res+=1;
    }
    cout<<res<<endl;
}