#include <iostream>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

vector<int> CalculatingControlBits(int numberControlBits, string in) {
	vector<int> tempVec;
	for (int _powerOfTwo = 0; _powerOfTwo < numberControlBits; _powerOfTwo++) {
		int _twoToTheDegree = pow(2, _powerOfTwo);
		int controlBit = 0;
		for (int i = _twoToTheDegree - 1; i < in.size(); i += _twoToTheDegree) {
			for (int j = _twoToTheDegree; j > 0 && i < in.size(); j--, i++) {
				if (in[i] == '1') controlBit++;
			}
		}
		if (controlBit % 2 != 0) in[_twoToTheDegree - 1] = '1';
		tempVec.push_back(controlBit);
	}
	return tempVec;
}

int main() {
	string in;
	int numberControlBits = 0;
	int twoToTheDegree = 1;
	vector<int> firstArrControlBits, secondArrControlBits;
	srand(time(0));

	cout << "Enter a binary number: ";
	cin >> in;
	cout << "Initial size: " << in.size() << endl;
	cout << endl << "The preparation stage:" << endl;
	for (int i = 1; i < in.size(); i++) {
		if (i == twoToTheDegree) {
			in.insert(i, "0");
			numberControlBits += 1;
			twoToTheDegree = pow(2, numberControlBits);
			cout << i << " : " << in << endl;
		}
	}

	cout << endl << "The final size: " << in.size() << endl;
	cout << "Number of control bits: " << numberControlBits << endl;

	firstArrControlBits = CalculatingControlBits(numberControlBits, in);

	cout << "The result of the first stage: " << in << endl;
	cout << endl << "The values of the control bits: " << endl;

	for (int i = 0; i < firstArrControlBits.size(); i++) {
		cout << i + 1 << " : " << firstArrControlBits[i] << endl;
	}

	int randomIndex = rand() % in.size();
	in[randomIndex] = in[randomIndex] == '1' ? '0' : '1';
	cout << endl << "Made a change to the message: " << in << endl;

	secondArrControlBits = CalculatingControlBits(numberControlBits, in);

	cout << endl << "The values of the control bits: " << endl;

	for (int i = 0; i < secondArrControlBits.size(); i++) {
		cout << i + 1 << " : " << secondArrControlBits[i] << endl;
	}

	int index = 0;
	for (int i = 0; i < numberControlBits; i++)
		if (firstArrControlBits[i] != secondArrControlBits[i])
			index += pow(2, i);

	cout << endl << "The wrong bit is under the index: " << index - 1 << endl;

	return 0;
}
