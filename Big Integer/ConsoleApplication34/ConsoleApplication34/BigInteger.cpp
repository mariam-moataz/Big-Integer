#include "BigInteger.h"
#include<string>
#include<sstream>
#include <utility>
#include<cmath>
#define min(a,b) ((a) < (b) ? (a) : (b))
#define max(a,b) ((a) > (b) ? (a) : (b))

using namespace std;

BigInteger::BigInteger()
{
}




bool BigInteger::smaller(string s1, string s2){// if s1 is smaller than s2
	int index = 0;
	if (s1.size() < s2.size()){
		return true;
	}
	if (s1.size()> s2.size()){
		return false;
	}

	while (index < s2.size()){
		if (s1[index] - '0'<s2[index] - '0'){
			return true;
		}
		if (s1[index] - '0' == s2[index] - '0'){
			index++;
			continue;
		}
		if (s1[index] - '0'>s2[index] - '0'){
			return false;
		}
	}
	return false;

}



pair<string, string>BigInteger::divide(string a, string b)
{
	if (smaller(a, b)) {
		pair<string, string> tmp;
		tmp.first = '0';
		tmp.second = a;
		return tmp;
	}
	string ADD = add(b, b);
	pair<string, string> p = divide(a, ADD);
	string q = p.first;
	string r = p.second;

	string ADD2 = add(p.first, p.first);
	p.first = ADD2;

	if (smaller(r, b))
		return p;

	else {
		p.first = add(p.first, "1");
		p.second = subtracte(p.second, b);
		return p;
	}

}



string BigInteger::ModOfPower(string B, string P, string M)
{
	
	if (P.size() == 1 && P[0] == '1')
	{
		return divide(B, M).second;
	}
	if (P.size() == 1 && P[0] == '0')
	{
			return divide("1", M).second;	
	}
	pair<string, string> tmpst = divide(P, "2");
		string pow = ModOfPower(B, tmpst.first, M);
		string powxpow = multiply(pow, pow);
		
		if (tmpst.second.size() == 1 && tmpst.second[0] != '0'){
			string powxpowxB = multiply(powxpow, B);
			return divide(powxpowxB, M).second;
		}
		else{
			return divide(powxpow, M).second;
		}
}






string BigInteger::subtracte(string str1, string str2) {
	int sub;
	string result = "";
	int n = equalize(str1, str2);
	int carry = 0;
	for (int i = n - 1; i >= 0; i--) {

		sub = (str1[i] - '0') - (str2[i] - '0') - carry;
		if (sub < 0) {
			sub += 10;
			carry = 1;

		}
		else {
			carry = 0;
		}

		result.push_back(sub + '0');

	}
	
	
	reverse(result.begin(), result.end());
	return result.erase(0, min(result.find_first_not_of('0'), result.size() - 1));
}


string BigInteger::add(string str1, string str2) {
	int carry = 0;
	string result ="";
	int n = equalize(str1, str2);

	for (int i = n - 1; i >= 0; i--) {
		int sum = (str1[i] - '0') + (str2[i] - '0') + carry; //convert from string to int
		result.push_back(sum % 10 + '0'); //convert from int to string
		carry = sum / 10;

	}
	if (carry)
		result.push_back(carry + '0');
	reverse(result.begin(), result.end());
	return result;
}



string BigInteger::multiply(string number1, string number2){
	
	if (number1.size() == 1 && number1[0] == '1'){
		return number2;
	}
	if (number2.size() == 1 && number2[0] == '1'){
		return number1;
	}
	if (number1.size() == 1 && number1[0] == '0'){
		return "0";
	}
	if (number2.size() == 1 && number2[0] == '0'){
		return "0";
	}
	int n;

	if (number1.size() != number2.size()){
		n = equalize(number1, number2);
	}
	else{
		n = number1.size();
	}

	if (n == 1){
		int tmpnum = (number1[0] - '0') *(number2[0] - '0');
		string res = to_string(tmpnum);
		return res;
	}


	string b = number1.substr(0, (n / 2)), a = number1.substr(n / 2, n - (n / 2));
	string d = number2.substr(0, (n / 2)), c = number2.substr(n / 2, n - (n / 2));
	string m1 = multiply(a, c);
	string m2 = multiply(b, d);
	string z = multiply(add(a, b), add(c, d));
	string npad;
	string sub1;
	string nover2pad;
	string addfinal;

	npad = stpow(m2, 2 * (n - (n / 2)));
	sub1 = subtracte(z, add(m1, m2));
	nover2pad = stpow(sub1, n - (n / 2));
	addfinal = add(add(nover2pad, npad), m1);
	return addfinal.erase(0, min(addfinal.find_first_not_of('0'), addfinal.size() - 1));

}


int BigInteger::equalize(string &str1, string &str2)
{
	int n1 = str1.size();
	int n2 = str2.size();
	if (n1 < n2)
	{
		for (int i = 0; i < n2 - n1; i++)
			str1 = "0" + str1;
		return str2.size();
	}
	else if (n1 > n2)
	{
		for (int i = 0; i < n1 - n2; i++)
			str2 = "0" + str2;
	}
	return str1.size();
}


string BigInteger::stpow(string str, int n){
	string res = str;

	for (int i = 1; i <= n; i++){
		res = res  + '0';
	}
	return res;
}

string BigInteger::Encrypt(string n, string e, string M){
	return ModOfPower(M, e, n);
}

string BigInteger::Decrypt(string n, string d, string EM){
	return ModOfPower(EM, d, n);
}
BigInteger::~BigInteger()
{
}
