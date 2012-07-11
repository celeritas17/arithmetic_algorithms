/*
 Ryan Koven 7/1/2012
 div_and_mult.h: c++ header file that defines several functions that implement several new and old algorithms for multiplying and dividing integers. 
 References: Dasgupta, Papadimitriou, Vazirani: Algorithms. 2008.
*/



#ifndef DIV_AND_MULT_H_
#define DIV_AND_MULT_H_


#include<iostream> // Will be necessary later
#include<cmath>



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


#endif