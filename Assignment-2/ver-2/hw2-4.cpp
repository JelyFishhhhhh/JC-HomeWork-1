#include <iostream>

using namespace std;

int main(){

    int a, b, c, d, L, count;                       // a: x^ 2係數; b: x^ 1係數; c: 常數項係數; d: 模除數; L: x 之上限值; count: 可被模除的x 總數 

    while (cin>> a>> b>> c>> d>> L){                // 類 EOF

        if(a== 0&& b== 0&& c== 0&& d== 0&& L== 0){  // 如果a, b, c, d, L 皆為零
            
            return 0;                               // 結束
        }
        
        count= 0;                                   // count 歸零
        for(int x= 0; x<= L; x++){                  // x 從0 遍歷至 L
            
            if((a* x* x+ b* x+ c)% d== 0){          // 如果 a* x^ 2+ b* x^ 1+ c 能被 d 模除

                count++;                            // count 累加
            }
        }

        cout<< count<< "\n";                        // 輸出 count
    }
    
}