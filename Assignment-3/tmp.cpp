#include <iostream>
#include <cstring>

#define N 10001

using namespace std;

void charToInt();
void offset();
void calc();
void borrow();
void print();

string input1, input2;
int output[N];

int main()
{
    int n;
    while(cin >> n)
    while(n--)
    {
        cin >> input1 >> input2;
        offset();
        charToInt();
        calc();
        print();
    }
}

void charToInt()
{
    for(int i = 0; i<input1.length(); i++)
        input1[i] -= '0';

    for(int i = 0; i<input2.length(); i++)
        input2[i] -= '0';
}

void offset()
{
    if(input1.length() > input2.length())
        for(int i = input2.length(); i<input1.length(); i++)
            input2 = "0" + input2;

    else if(input1.length() < input2.length())
        for(int i = input1.length(); i<input2.length(); i++)
            input1 = "0" + input1;
}

void calc()
{
    memset(output, 0, sizeof(output));

    bool negative;

    negative = false;

    for(int i = 0; i<input1.length(); i--)
        if(input1[i] < input2[i]){
            negative = true;
            break;
        }


    if(!negative)
        for(int i = input1.length() - 1, digit = N-1 ; i >= 0; i--, digit--)
            output[digit] += input1[i] - input2[i];

    else{
        cout << "-";
        for(int i = input1.length() - 1, digit = N-1 ; i >= 0; i--, digit--)
            output[digit] += input2[i] - input1[i];
    }

    borrow();
}

void borrow()
{
    for(int i = 0, digit = N-1; i<input1.length(); i++, digit--)
        if(output[digit] < 0){
            output[digit] += 10;
            output[digit-1]--;
        }

}

void print()
{
    int i;

    //找出最高位的位置
    for(i = 0; i <= N-1 && output[i] == 0; i++);

    if(i >= N){cout << "0" << endl;return;}

    for(; i<=N-1; i++)
        cout << output[i];

    cout << endl;
}