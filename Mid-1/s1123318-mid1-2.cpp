#include <iostream>
using namespace std;

// a, b are odds
int oddSum( int a, int b )
{
	if (a == b) {
		
		return a;
	}
	if (a > b) {

		return 0;
	}
	return a + b + oddSum(a + 2, b - 2);
}

int main()
{
	int testCase, a, b;
	cin >> testCase;
	for (int n = 1; n <= testCase; n++) {
		cin >> a >> b;
		
		// assign 2 the closest odd number;
		if (a % 2== 0) {
			a++;
		}
		if (b % 2== 0) {
			b--;
		}
		// output
		cout << "Case "<< n<<": " << oddSum(a, b) << '\n';
	}
	return 0;

}
