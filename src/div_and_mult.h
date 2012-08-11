/*
 Ryan Koven 2012
 div_and_mult.h: c++ header file that defines several functions that implement several new and old algorithms for multiplying and dividing integers,
 and other fun things. 
 References: Dasgupta, Papadimitriou, Vazirani: Algorithms. 2008.
*/



#ifndef DIV_AND_MULT_H_
#define DIV_AND_MULT_H_


#include<iostream> 
#include<cmath>

namespace arithmetic{


/* division: Implements an interesting (but not entirely fast-- O(n^2), n the number of bits in the representation of the integers) 
   method to divide x by y-- x, y nonnegative, y > 0. Returns quotient and remainder in an array with quotient in the first position 
   in the array, remainder in second. */
int* divide(int x, int y){

	assert(y > 0);

	int q_r[2];

	q_r[0] = 0;
	q_r[1] = 0;

	if (x > 0){
		q_r[0] = 2*divide(x/2, y)[0];
		q_r[1] = 2*divide(x/2, y)[1];

		if (x%2 != 0)
			q_r[1] += 1;
		
		if (q_r[1] >= y)
			q_r[1] -= y , q_r[0] += 1;
	}
	 
	return q_r;
}

/* multiply: An interesting method to multiply integers. Again, not entirely fast. */
int multiply(int x , int y){


	int product = 0;

	if (x >= 0 && y > 0){

		int z = multiply(x, y/2);

		if (y%2 == 0)
			product = 2*z;
		else
			product = x + 2*z;
	}

	return product;

}

/* modexp: Modular exponentiation-- returns x^y mod N for integers x, y, N. Returns 0 if any of x, y, N are negative. */
int modexp(int x, int y, int N){

	assert(N > 0);

	int exp = 0;

	if (x >= 0 && y >= 0 && N > 1){

		if (y == 0)
			exp = 1;
		else{
			int z = modexp(x, y/2, N);
			if (y%2 == 0)
				exp = z*z % N;
			else
				exp = x*z*z % N; 
	}

	}
	return exp;  

}

/* Implementation of Euclid's >2000 year old algorithm for finding the greatest common divisor of two integers a, b. 
   Returns gcd(a, b) if a>=b>=0, 0 otherwise. */
 int euclid_gcd(int a, int b){

	 int gcd = 0;

	 if (a >= b && b >= 0){
		 if (b == 0)
			 gcd = a;
		 else
			 gcd = euclid_gcd(b, a%b);
	 }

	 return gcd;
 }

 /* extended_euclid: Returns integers x, y, d such that d = gcd(a, b) (a >=b >= 0) and d = ax + by in an array. 
    The algorithm is an extension of Euclid's algorithm from euclid_gcd, made possible by the fact that gcd(a, b)
	can always be expressed as ax + by for some integers x, y. */
 int* extended_euclid_gcd(int a, int b){

	 int x_y_d[3];

	 for (int i = 0; i < 3; i++)
		 x_y_d[i] = 0;

	 if (b == 0)
		 x_y_d[0] = 1, x_y_d[1] = 0, x_y_d[2] = a;
	 else{
		x_y_d[0] = extended_euclid_gcd(b, a%b)[1]; 
		x_y_d[1] = extended_euclid_gcd(b, a%b)[0] - (a/b)*extended_euclid_gcd(b, a%b)[1];
		x_y_d[2] = extended_euclid_gcd(b, a%b)[2];
	 }
	 return x_y_d;
 }

//Calculate the product a x b of two n digit numbers a, b recursively 
long long Recursive_Mult(int x, int y){
	long long order_of_magnitude = 1;
	int num_digits = 0; //number of digits in a, b (need to verify that both a, b have same num of digits) 
	long long product = 0;
	while (x/order_of_magnitude > 0){
		order_of_magnitude*=10;
		num_digits++;
                                    }
	if (x == 0 || y ==0)
		product = 0;

	else if (num_digits == 1)
		product = x*y;
	
	else{
		for (int i = 0; i<num_digits/2; i++)
			order_of_magnitude = order_of_magnitude/10;

		int a = x/(order_of_magnitude);
		int b = x%(order_of_magnitude);

		int c = y/(order_of_magnitude);
		int d = y%(order_of_magnitude);

		product = pow((double)10, num_digits)*Recursive_Mult(a,c) + pow((double)10, num_digits/2)*(Recursive_Mult(a,d) + Recursive_Mult(b,c)) + Recursive_Mult(b,d);

	}
	
	return product;
}

//Calculate the product a x b of two n digit numbers a, b recursively using the Karatsuba algorithm
long long Karatsuba_Mult(int x, int y){
	long long order_of_magnitude = 1;
	int num_digits = 0; //number of digits in a, b (need to verify that both a, b have same num of digits) 
	long long product = 0;
	while (x/order_of_magnitude > 0){
		order_of_magnitude*=10;
		num_digits++;
                                    }
	if (x == 0 || y== 0)
		product = 0;

	else if (num_digits == 1)
		product = x*y;
	
	else{
		for (int i = 0; i<num_digits/2; i++)
			order_of_magnitude = order_of_magnitude/10;

		int a = x/(order_of_magnitude);
		int b = x%(order_of_magnitude);

		int c = y/(order_of_magnitude);
		int d = y%(order_of_magnitude);

		int quantity1 = Recursive_Mult(a,c);
		int quantity2 = Recursive_Mult(b,d);
		int quantity3 = Recursive_Mult(a+b,c+d);

		product = pow((double)10, num_digits)*quantity1 + pow((double)10, num_digits/2)*(quantity3 - quantity1 - quantity2) + quantity2;

	}
	
	
	return product;
}

}

/* htoi: converts hexadecimal numbers entered as a c-style string into integers */
int htoi(char s[]){
	int i, n;
	n = 0;

	if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X')){
		for (i = 2; (s[i] >= '0' && s[i] <='9') || (s[i]>='a' && s[i]<='f') || (s[i]>='A' && s[i]<='F'); i++ ){
			if (s[i] >= '0' && s[i] <='9')
				n = 16*n + (s[i] - '0');
			else if (s[i] >= 'A' && s[i] <= 'F') 
				n = 16*n + 10 + (s[i] - 'A');
			else 
				n = 16*n + 10 + (s[i] - 'a');
}

	}

	else{
		for (i = 0; (s[i] >= '0' && s[i] <='9') || (s[i]>='a' && s[i]<='f') || (s[i]>='A' && s[i]<='F'); i++ ){
			if (s[i] >= '0' && s[i] <='9')
				n = 16*n + (s[i] - '0');
			else if (s[i] >= 'A' && s[i] <= 'F') 
				n = 16*n + 10 + (s[i] - 'A');
			else 
				n = 16*n + 10 + (s[i] - 'a');
}
	    }

	return n;
}

bool isPrime(long long n){
	if ( n < 0) n*=-1;
	if (n == 1) return false;
	for (long long i = 2; i*i<=n; i++)
		if (n%i == 0) return false;

	return true;
}

bool primality(int N){
	 
	 bool prime = true;

	 int a;

	 for (int j = 0; j < 100; j++){
		 a = 1 + rand()%(N-1);
		 
		 if ((modexp(a, N-1, N) - 1) != 0){
			 prime = false;
			 break;
					}

	 }

	 return prime;
 }

#endif