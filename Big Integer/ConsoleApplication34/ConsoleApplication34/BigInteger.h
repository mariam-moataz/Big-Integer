#pragma once
#include <string>
#include <utility>

using namespace std;
class BigInteger
{
	
public:
	string multiply(string, string);
	int equalize(string&, string&);

	string subtracte(string, string);
	string add(string, string);
	string stpow(string, int);
	bool smaller(string , string );
	pair<string, string>divide(string , string );
	string ModOfPower(string, string, string);
	string Encrypt(string, string, string);
	string Decrypt(string, string, string);


	BigInteger();
	~BigInteger();
};

