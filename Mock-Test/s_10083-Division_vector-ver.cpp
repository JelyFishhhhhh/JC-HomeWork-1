#include <iostream>
#include <vector>
using namespace std;

#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)

const int twoHundred = 200;
const int hundred = 100;

bool isZero(vector<int> &hugeInt) {
    for (int digit : hugeInt) {
        if (digit) {
            return false;
        }
    }
    return true;
}

bool isLess(vector<int> &hugeInt1, vector<int> &hugeInt2) {
    
    
}

void decrement(vector<int> &hugeInt) {
    
    
}

void subtraction(vector<int> &minuend, vector<int> &subtrahend) {
    

}

void multiplication(vector<int> &multiplicand, vector<int> &multiplier) {
    
    
}

void divideBy10(vector<int> &hugeInt) {
    if (hugeInt.size() == 1) {
        hugeInt[0] = 0;
    } else {
        for (size_t i = 1; i < hugeInt.size(); i++) {
            hugeInt[i - 1] = hugeInt[i];
        }
        hugeInt.pop_back();
    }
}

void division(vector<int> &dividend, const vector<int> &divisor, vector<int> &quotient, vector<int> &remainder) {
    

}


int main() {

    int t, a, b;
    while (cin >> t >> a >> b) {
        cout << "(" << t << "^" << a << "-1)/(" << t << "^" << b << "-1) ";
        if (t == 1) {
            cout << "is not an integer with less than 100 digits.\n";
            continue;
        }
        if (a == b) {
            cout << "1\n";
            continue;
        }
        if (a < b) {
            cout << "is not an integer with less than 100 digits.\n";
            continue;
        }

        vector<int> dividend = {1};
        vector<int> divisor = {1};
        vector<int> quotient, remainder;

        vector<int> base;
        for (int i = t; i > 0; i /= 10) {
            base.push_back(i % 10);
        }

        for (int i = 0; i < a; ++i) {
            multiplication(dividend, base);
            if (dividend.size() > twoHundred - base.size()) {
                break;
            }
        }

        if (dividend.size() > twoHundred - base.size()) {
            cout << "is not an integer with less than 100 digits.\n";
        } else {
            for (int i = 0; i < b; ++i) {
                multiplication(divisor, base);
                if (divisor.size() > hundred - base.size()) {
                    break;
                }
            }

            if (divisor.size() > hundred - base.size()) {
                cout << "is not an integer with less than 100 digits.\n";
            } else {
                decrement(dividend);
                decrement(divisor);

                division(dividend, divisor, quotient, remainder);

                if (quotient.size() < hundred && isZero(remainder)) {
                    for (int i = quotient.size() - 1; i >= 0; i--) {
                        cout << quotient[i];
                    }
                } else {
                    cout << "is not an integer with less than 100 digits.\n";
                    continue;
                }
                cout << '\n';
            }
        }
    }
    return 0;
}
