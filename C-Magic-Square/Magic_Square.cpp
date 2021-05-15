#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> GetMagicOddSquare(int n) {
	vector<vector<int>> numbers(n  * 2 - 1, vector<int>(n * 2 - 1));
	vector<vector<int>> square(n, vector<int>(n));

	// Filling numbers with zeros
	for (int i = 0; i < n * 2 - 2; i++) {
		for (int j = 0; j < n * 2 - 1; j++) {
			numbers[i][j] = 0;
		}
	}

	// Filling numbers with numbers
	for (int i = n - 1; i > -1; i--) {
		int x = i;
		int y = i + n * 2 / 2 - 1;
		int value = (x) * (n) + 1;
		int counter = 0;

		while (counter < n) {
			numbers[y][x] = value;
			value++;
			x++;
			y--;
			counter++;
		}
	}

	// Moving numbers to the center and writing them into the square vector
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int y = i + n / 2;
			int x = j + n / 2;

			if (numbers[y][x] == 0) {
				if (y < x) {
					if (x + y > (n - 1) * 2) {	// right
						x -= n;
					}
					else {	// top
						y += n;
					}
				}
				else {
					if (x + y > (n - 1) * 2) {	// bottom
						y -= n;
					}
					else {	// left
						x += n;
					}
				}
			}
			square[i][j] = numbers[y][x];
		}
	}

	return square;
}
vector<vector<int>> GetMagicEvenOddSquare(int n) {
	vector<vector<int>> quarter_square = GetMagicOddSquare(n / 2);
	vector<vector<int>> square(n, vector<int>(n));

	// Filling big square with 4 small ones
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int x = j % (n / 2);
			int y = i % (n / 2);
			int buffer = 0;

			if (x != j) {
				if (y != i) buffer = n * n * 1 / 4;
				else buffer = n * n * 2 / 4;
			}
			else {
				if (y != i) buffer = n * n * 3 / 4;
				else buffer = n * n * 0 / 4;
			}

			square[i][j] = quarter_square[y][x] + buffer;
		}
	}

	// Doing changes to perfect the big magic square
	// Swapping middle columns
	for (int i = n / 2 - (n / 2 - 3) / 2; i < n / 2 + (n / 2 - 3) / 2; i++) {
		for (int j = 0; j < n / 2; j++) {
			int temp = square[j][i];
			square[j][i] = square[n / 2 + j][i];
			square[n / 2 + j][i] = temp;
		}
	}
	// Swapping first line symbols
	for (int i = 0; i < n / 2; i++) {
		int j = 1;

		if (i == 0 || i == n / 2 - 1) j = 0;

		int temp = square[i + n / 2][j];
		square[i + n / 2][j] = square[i][j];
		square[i][j] = temp;
	}

	return square;
}
vector<vector<int>> GetMagicEvenEvenSquare(int n) {
	vector<vector<int>> square(n, vector<int>(n));

	// Filling square with numbers
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			square[i][j] = i * n + j + 1;
		}
	}

	// Swaping numbers in square
	// Swaping top left and bottom right squares
	for (int i = 0; i < n / 2; i++) {
		for (int j = 0; j < n / 2; j++) {
			if ((i + j) % 2 == 1) {
				int temp = square[i][j];
				square[i][j] = square[n - i - 1][n - j - 1];
				square[n - i - 1][n - j - 1] = temp;
			}
		}
	}
	// Swapping bottom left and top right squares
	for (int i = n / 2; i < n; i++) {
		for (int j = 0; j < n / 2; j++) {
			if ((i + j) % 2 == 0) {
				int temp = square[i][j];
				square[i][j] = square[n - i - 1][n - j - 1];
				square[n - i - 1][n - j - 1] = temp;
			}
		}
	}

	return square;
}

vector<vector<int>> GetMagicSquare(int n) {
	if (n % 2 == 1) return GetMagicOddSquare(n);
	else if ((n / 2) % 2 == 1) return GetMagicEvenOddSquare(n);
	else return GetMagicEvenEvenSquare(n);
}

void DebugInfo(vector<vector<int>> square) {
	int n = square.size();
	cout << endl;

	for (int i = 0; i < n; i++) {
		int s = 0;
		for (int j = 0; j < n; j++) {
			s += square[i][j];
		}
		cout << "summ line " << i + 1 << " = " << s << endl;
	}
	cout << endl;

	for (int i = 0; i < n; i++) {
		int s = 0;
		for (int j = 0; j < n; j++) {
			s += square[j][i];
		}
		cout << "summ column " << i + 1<< " = " << s << endl;;
	}

	cout << endl;

	int s = 0;
	for (int i = 0; i < n; i++) {
		s += square[i][i];
	}
	cout << "summ diag 1 (top-left >> right-bottom) = " << s << endl;

	s = 0;
	for (int i = 0; i < n; i++) {
		s += square[n - i - 1][i];
	}
	cout << "summ diag 2 (bottom-left >> right-top) = " << s << endl;
}

int main() {
	int n;
	cin >> n;

	vector<vector<int>> square = GetMagicSquare(n);

	for (auto line : square) {
		for (auto number : line) {
			cout << number << "\t";
		}
		cout << endl;
	}

	DebugInfo(square);
}