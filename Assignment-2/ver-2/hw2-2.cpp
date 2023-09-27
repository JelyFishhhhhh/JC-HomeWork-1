#include <iostream>

using namespace std;

int main(){

    int number, sum;                // number: 目前的數字; sum: 暫存非個位數number的各位數和

    while(cin>> number){
        
        if(number== 0){             // 如果是零就結束程式(類EOF)
            
            return 0;               // 傳送"結束"這個狀態碼給系統
        }
        
        while(number> 9){           // 如果number不只有個位數
            sum= 0;                 // sum 歸零

            while(number> 0){       // 用於計算各位數的和

                sum+= number% 10;   
                number/= 10;
            }
            

            number= sum;            // 將各位數之總和值傳回number
        }
        cout<< number<< "\n";       // 輸出number之值
    }
}