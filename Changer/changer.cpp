#include <iostream>

using namespace std;

#define Q 25
#define D 10
#define N 5
#define P 1


int* changer(int amount);

int main(int argc, char const *argv[])
{
	int* arr;
	int input = atoi(argv[1]);
	arr = changer(input);

	return 0;
}



int* changer(int amount){

	int* arr;

	int quarters = amount / Q;
	amount = amount % Q;
	int dimes = amount / D;
	amount = amount % D;
	int nickels = amount / N;
	amount = amount % N;
	int pennies = amount / P;
	amount = amount % P;

	int arr_size = quarters + dimes + nickels + pennies;

	arr = new int[arr_size];

	arr_size = 0;
	for(int i = arr_size; i < (arr_size + quarters); i++)
		arr[i] = Q;

	arr_size += quarters;
	for(int i = arr_size; i < (arr_size + dimes); i++)
		arr[i] = D;

	arr_size += dimes;
	for(int i = arr_size; i < (arr_size + nickels); i++)
		arr[i] = N;

	arr_size += nickels;
	for(int i = arr_size; i < (arr_size + pennies); i++)
		arr[i] = P;

	arr_size += pennies;
	
	cout << "An Array of size [" << arr_size << "] was created containing:" 
		<< endl << quarters << " Quarter(s)" 
		<< endl << dimes << " Dime(s)"
		<< endl << nickels << " Nickel(s)"
		<< endl << pennies << " Pennie(s)" << endl;


	return arr;
}