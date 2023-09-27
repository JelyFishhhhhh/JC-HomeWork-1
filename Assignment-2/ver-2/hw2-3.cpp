#include <iostream>

using namespace std;

int main(){

    int times, a, b, n, buff;           // times: case 數; a: 最近點; b: 最遠點; n: 商家數; buff: 暫存值
    cin>> times;                        // 輸入case 數

    for(int i= 0; i< times; i++){       // 執行times 次
        
        cin>> n;                        // 輸入商家數
        a= 99;                          // 暫時設定最近點之值
        b= 0;                           // 暫時設定最遠點之值
        for(int j= 0; j< n; j++){       // 執行n 次
            cin>> buff;                 // 輸入當前商家座標
            if(buff< a){                // 如果商家比目前最近點近
                
                a= buff;                // a 被取代
            }
            if(buff> b){                // 如果商家比目前最遠點遠
                
                b= buff;                // b 被取代
            }
        }

        cout<< 2* (b- a)<< "\n";        // 輸出距離
    }
}