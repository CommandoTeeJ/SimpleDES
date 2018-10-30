#include <iostream>
#include <vector>
#include <cassert>
#include <string>

using namespace std;

//Function to change string of binary into vector of binary
void setVec(string temp,vector<bool> &bitset) {
	for (int i = 0; i < temp.length(); i++) {
		bitset.push_back(temp[i] - 48);
	}
}

//Displays binary vector into console
void displayVec(vector<bool> &bitset) {
	for (int i = 0; i < bitset.size(); i++) {
		cout << bitset[i];
	}
}

//Does a single circular shift
void shiftFive(vector<bool> &bitset) {
	vector<bool> temp(10, 0);

	for (int i = 0; i < 5; i++) {
		temp[i] = bitset[(i + 1) % 5];
	}

	for (int i = 0; i < 5; i++) {
		temp[i + 5] = bitset[5+((i + 1) % 5) ];
	}

	bitset = temp;
}

//F is also Fk()
vector<bool> F(vector<bool> n, vector<bool> k) {
	//EP is the vector of permutated plaintext
	vector<bool> EP(8, 0);

	//expand plaintext
	short ep[8] = { 4,1,2,3,2,3,4,1 };

	//permutate the plaintext
	for (int i = 0; i < 8; i++) {
		EP[i] = n[ep[i] - 1];
	}

	//xor the text with the key
	for (int i = 0; i < 8; i++) {
		EP[i] = EP[i] ^ k[i];
	}

	//4 digit Fk output (pre permutation)
	vector<bool> output(4,0);

	//S0 box
	if (EP[0]) {
		if (EP[3]) {
			if (EP[1]) {
				if (EP[2]) {
					output[0] = 1;
					output[1] = 0;
				}
				else {
					output[0] = 1;
					output[1] = 1;
				}
			}
			else {
				if (EP[2]) {
					output[0] = 0;
					output[1] = 1;
				}
				else {
					output[0] = 1;
					output[1] = 1;
				}
			}
		}
		else {
			if (EP[1]) {
				if (EP[2]) {
					output[0] = 1;
					output[1] = 1;
				}
				else {
					output[0] = 0;
					output[1] = 1;
				}
			}
			else {
				if (EP[2]) {
					output[0] = 1;
					output[1] = 0;
				}
				else {
					output[0] = 0;
					output[1] = 0;
				}
			}
		}
	}
	else {
		if (EP[3]) {
			if (EP[1]) {
				if (EP[2]) {
					output[0] = 0;
					output[1] = 0;
				}
				else {
					output[0] = 0;
					output[1] = 1;
				}
			}
			else {
				if (EP[2]) {
					output[0] = 1;
					output[1] = 0;
				}
				else {
					output[0] = 1;
					output[1] = 1;
				}
			}
		}
		else {
			if (EP[1]) {
				if (EP[2]) {
					output[0] = 1;
					output[1] = 0;
				}
				else {
					output[0] = 1;
					output[1] = 1;
				}
			}
			else {
				if (EP[2]) {
					output[0] = 0;
					output[1] = 0;
				}
				else {
					output[0] = 0;
					output[1] = 1;
				}
			}
		}
	}

	//S1
	if (EP[4]) {
		if (EP[7]) {
			if (EP[5]) {
				if (EP[6]) {
					output[2] = 1;
					output[3] = 1;
				}
				else {
					output[2] = 0;
					output[3] = 0;
				}
			}
			else {
				if (EP[6]) {
					output[2] = 0;
					output[3] = 1;
				}
				else {
					output[2] = 1;
					output[3] = 0;
				}
			}
		}
		else {
			if (EP[5]) {
				if (EP[6]) {
					output[2] = 0;
					output[3] = 0;
				}
				else {
					output[2] = 0;
					output[3] = 1;
				}
			}
			else {
				if (EP[6]) {
					output[2] = 0;
					output[3] = 0;
				}
				else {
					output[2] = 1;
					output[3] = 1;
				}
			}
		}
	}
	else {
		if (EP[7]) {
			if (EP[5]) {
				if (EP[6]) {
					output[2] = 1;
					output[3] = 1;
				}
				else {
					output[2] = 0;
					output[3] = 1;
				}
			}
			else {
				if (EP[6]) {
					output[2] = 0;
					output[3] = 0;
				}
				else {
					output[2] = 1;
					output[3] = 0;
				}
			}
		}
		else {
			if (EP[5]) {
				if (EP[6]) {
					output[2] = 1;
					output[3] = 0;
				}
				else {
					output[2] = 1;
					output[3] = 0;
				}
			}
			else {
				if (EP[6]) {
					output[2] = 0;
					output[3] = 1;
				}
				else {
					output[2] = 0;
					output[3] = 0;
				}
			}
		}
	}

	//opp4 is the permutation of the plaintext
	short opp4[4] = { 2,4,3,1 };

	//p4 is the vector that holds the permutated output
	vector<bool> p4;

	//permutate output
	for (int i = 0; i < 4; i++) {
		p4.push_back(output[opp4[i] - 1]);
	}

	//return
	return p4;
}

//xor makes it easy to xor two vectors
vector<bool> xor (vector<bool> ls, vector<bool> rs) {
	//assert the vectors are the same size
	assert(ls.size() == rs.size());

	//the output
	vector<bool> output;

	//xor every member of both vectors
	for (int i = 0; i < ls.size(); i++) {
		output.push_back(ls[i] ^ rs[i]);
	}

	//return
	return output;
}

//circular shift of 2
void shiftFive2(vector<bool> &bitset) {
	//temp holds the shift temporarily
	vector<bool> temp(10, 0);

	//circular shift left side
	for (int i = 0; i < 5; i++) {
		temp[i] = bitset[(i + 2) % 5];
	}

	//circular shift right side
	for (int i = 0; i < 5; i++) {
		temp[i + 5] = bitset[5 + ((i +2) % 5)];
	}

	//set original vector to the shifted value
	bitset = temp;
}

//Main encryption function that can also be used to decrypt values
vector<bool> encrypt(string tempKey, string tempPlain) {
	//various arrays of bools to be used across functions
	vector<bool> key;
	vector<bool> p10Key(10, 0);
	vector<bool> k1(8, 0);
	vector<bool> k2(8, 0);
	vector<bool> plain;
	vector<bool> IP(8, 0);

	//change key and plain text into vectors of bool
	setVec(tempPlain, plain);
	setVec(tempKey, key);
	
	//the various specifications of permutations; perm10 is the first key permutation,perm8 is the secondary key permutations(to split them into 8 bit keys)
	//ip is the first permutation of the plaintext, ipneg is the revers of ip
	short permutation10[10] = { 3, 5, 2, 7, 4, 10, 1, 9, 8, 6 };
	short permutation8[8] = { 6, 3, 7, 4 ,8 ,5 ,10 ,9 };
	short ip[8] = { 2, 6 ,3 ,1 ,4, 8 ,5 ,7 };
	short ipNeg[8] = { 4, 1 ,3, 5 ,7 ,2 ,8 ,6 };

	//Permutate key first time
	for (int i = 0; i < 10; i++) {
		p10Key[i] = key[permutation10[i] - 1];
	}

	//Circular shift of 1
	shiftFive(p10Key);

	//P8 for k1
	for (int i = 0; i < 8; i++) {
		k1[i] = p10Key[permutation8[i] - 1];
	}

	//Circular shift of 2
	shiftFive2(p10Key);

	//P8 for k2
	for (int i = 0; i < 8; i++) {
		k2[i] = p10Key[permutation8[i] - 1];
	}

	//do the initial permutation of the plaintext
	for (int i = 0; i < 8; i++) {
		IP[i] = plain[ip[i] - 1];
	}

	//left side and right side of the plain text (for fk ops)
	vector<bool> rs;
	vector<bool> ls;

	//set left side array
	for (int i = 0; i < 4; i++) {
		ls.push_back(IP[i]);
	}

	//set right side array
	for (int i = 4; i < 8; i++) {
		rs.push_back(IP[i]);
	}

	//xor left side with Fk of right side
	vector<bool> Fk = xor (ls, F(rs, k1));

	//add the right side back to the text and flip 
	for (int i = 0; i < 4; i++) {
		rs.push_back(Fk[i]);
	}

	//reset the vars
	IP = rs;
	ls = vector<bool>(); rs = vector<bool>();

	//splitting the text (Left side)
	for (int i = 0; i < 4; i++) {
		ls.push_back(IP[i]);
	}

	//splitting the text (Right side)
	for (int i = 4; i < 8; i++) {
		rs.push_back(IP[i]);
	}

	//xor left side and Fk2 right side
	Fk = xor (ls, F(rs, k2));

	//combine the plaintext back together
	for (int i = 0; i < 4; i++) {
		Fk.push_back(rs[i]);
	}

	//prepare final permutation vector
	vector<bool> cipherT(8, 0);

	//final permutation using inverse of ip
	for (int i = 0; i < 8; i++) {
		cipherT[i] = Fk[ipNeg[i] - 1];
	}

	//return
	return cipherT;
}

//main
int main() {
	//main loop
	while (1) {
		//string version of key and plaintext
		string tempKey;
		string tempPlain;

		//IO
		cout << endl << endl;
		cout << "Enter 8 digit binary Plaintext: ";
		cin >> tempPlain;
		cout << "Enter 10 digit binary key: ";
		cin >> tempKey;
		cout << endl << "Encrypted text: ";

		//directly display the output of the encryption, set to a var if it is to be used
		displayVec(encrypt(tempKey, tempPlain));
	}

}
