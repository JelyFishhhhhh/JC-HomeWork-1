#include <iostream>

using namespace std;

int main(){

    int a, b, times, sum;                              // a: 下限值; b: 上限值; times: case數量; sum: 奇數和;

    cin>> times;                                       // 輸入times 數
    for(int i= 0; i< times; i++){                      // 執行times 次

        sum= 0;                                        // sum 歸零
        cin>> a>> b;                                   // 輸入下限值及上限值
        for(int j= a; j<= b; j++){                     // 從a 遍歷至b

            if(j% 2== 1){                              // 如果是奇數

                sum+= j;                               // sum 加上此時的數
            }
        }

        cout<< "Case "<< i+ 1<< ": "<< sum<< "\n";     // 輸出結果
    }
}