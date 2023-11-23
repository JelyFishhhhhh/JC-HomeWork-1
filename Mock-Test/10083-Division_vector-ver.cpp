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
    if (hugeInt1.size() < hugeInt2.size()) {
        return true;
    }
    if (hugeInt1.size() > hugeInt2.size()) {
        return false;
    }
    for (int i = hugeInt1.size() - 1; i >= 0; i--) {
        if (hugeInt1[i] < hugeInt2[i]) {
            return true;
        }
        if (hugeInt1[i] > hugeInt2[i]) {
            return false;
        }
    }
    return false;
}

void decrement(vector<int> &hugeInt) {
    hugeInt[0]--;
    for (size_t i = 0; i < hugeInt.size(); i++) {
        if (hugeInt[i] < 0) {
            hugeInt[i + 1]--;
            hugeInt[i] += 10;
        }
    }
    while (!hugeInt.empty() && !hugeInt.back()) {
        hugeInt.pop_back();
    }
}

void subtraction(vector<int> &minuend, vector<int> &subtrahend) {
    for (size_t i = 0; i < minuend.size(); i++) {
        minuend[i] -= (i < subtrahend.size() ? subtrahend[i] : 0);
        if (minuend[i] < 0) {
            minuend[i] += 10;
            minuend[i + 1]--;
        }
    }
    while (!minuend.empty() && !minuend.back()) {
        minuend.pop_back();
    }
}

void multiplication(vector<int> &multiplicand, vector<int> &multiplier) {
    vector<int> product(multiplicand.size() + multiplier.size(), 0);

    for (size_t ix = 0; ix < multiplicand.size(); ix++) {
        for (size_t iy = 0; iy < multiplier.size(); iy++) {
            product[ix + iy] += multiplicand[ix] * multiplier[iy];
            product[ix + iy + 1] += product[ix + iy] / 10;
            product[ix + iy] %= 10;
        }
    }

    while (!product.empty() && !product.back()) {
        product.pop_back();
    }

    multiplicand = product;
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
    remainder = dividend;
    quotient = vector<int>(dividend.size() - divisor.size() + 1, 0);
    vector<int> buffer(divisor.size() + quotient.size(), 0);

    for (size_t i = 0; i < buffer.size(); i++) {
        if (i < quotient.size()) {
            buffer[i] = 0;
            continue;
        }
        buffer[i] = divisor[i - quotient.size()];
    }

    if (isLess(remainder, buffer)) {
        divideBy10(buffer);
    } else {
        quotient.push_back(0);
    }

    quotient = vector<int>(quotient.size(), 0);
    for (int i = quotient.size() - 1; i >= 0; i--) {
        while (!isLess(remainder, buffer)) {
            subtraction(remainder, buffer);
            quotient[i]++;
            if (isZero(remainder)) {
                break;
            }
        }
        divideBy10(buffer);
    }

    // Remove leading zeros in the quotient
    while (!quotient.empty() && quotient.back() == 0) {
        quotient.pop_back();
    }
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
