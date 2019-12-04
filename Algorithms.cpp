#include "pch.h"
#include<vector>
#include <iostream>
#include"Algorithms.h"

struct binary{
  LongModInt order;
  int bit;
};

LongModInt pow(const LongModInt& number1, const LongModInt& number2){

	if(number1.getField()->mod != number2.getField()->mod)
		throw std::invalid_argument("Moduli must be equal.");

    LongModInt result(LongInt("1"), number1.getField()),temp=number1,number=number2;
    const int bits=8;
    LongInt mod=number1.getField()->mod;
    int length=mod.getSize()*bits;
    std::vector<binary>number2bin; number2bin.resize(length);
    LongModInt order("2",number1.getField()),degree("1",number1.getField());
    int breakpoint=0;

    for(int i(length-1);i>=0;i--){
        number2bin[i].order=degree;
        degree=degree*order;
        number2bin[i].bit=0;
    }

    for(int i(length-1);i>0;i--){
        if(number2bin[i].order>number2bin[i-1].order){
            breakpoint=i;
                break;}
        }

    for(int i(breakpoint);i<length;i++)
        if(number2bin[i].order<=number){
            number2bin[i].bit++;
            number=number-number2bin[i].order;
    }
    for(int i(length-1);i>=breakpoint;i--){
        if(number2bin[i].bit) result=result*temp;
            temp=temp*temp;
    }
    return result;
}




//////////////////////////



int euler(int n){ // returns maximum count of simple numbers lesser than n
	int ret = 1;
	for (int i = 2; i * i <= n; ++i)
	{
		int p = 1;
		while (n % i == 0)
		{
			p *= i;
			n /= i;
		}
		p /= i;
		if (p >= 1) ret *= (p * (i - 1));
	}
	return --n ? n * ret : ret;
}

int gcd(int a, int b) // returns greatest common divisor
{
	if (a < b)
		return gcd(b, a);
	if (a % b == 0)
		return b;
	return gcd(b, a % b);
}

bool is_prime(int n) { // check if number is prime
	if (n <= 1)
		return true;
	if (n == 2)
		return true;
	if (n%2==0)
		return false;
	for (int j = 3; j * j <= n; j+=2)
		if (n % j == 0) return false;

	return true;
}

int power(int x, int y, int mod) { // recursive function that returns special power using mod
	if (y == 0)
		return 1;
	int temp = power(x, y / 2, mod) % mod;
	temp = (temp * temp) % mod;
	if (y % 2 == 1)
		temp = (temp * x) % mod;
	return temp;
}

bool isCarmichaelNumber(int n) { // checks if given number is Charmichael number
	for (int b = 2; b < n; b++) {
		// If "b" is relatively prime to n
		if (gcd(b, n) == 1) {

			// And pow(b, n-1)%n is not 1,
			// return false.
			if (power(b, n - 1, n) != 1){
				return false;
			}
		}
	}
	return true;
}

void eulerCarmichaelTest(){ // test case for above program
	std::cout << "euler(10) = " << euler(10) << std::endl;
	std::cout << "euler(1) = " << euler(1) << std::endl;
	std::cout << "euler(2) = " << euler(2) << std::endl;
	std::cout << "euler(5) = " << euler(5) << std::endl;
	if(isCarmichaelNumber(561) && !is_prime(561)) std::cout << "561 is Charmichael number" << std::endl;
	else std::cout << "Number is not Charmichael" << std::endl;
	if(isCarmichaelNumber(1105) && !is_prime(1105)) std::cout << "1105 is Charmichael number" << std::endl;
	else std::cout << "Number is not Charmichael" << std::endl;
	if(isCarmichaelNumber(2000) && !is_prime(2000)) std::cout << "2000 is Charmichael number" << std::endl;
	else std::cout << "Number is not Charmichael" << std::endl;
}
