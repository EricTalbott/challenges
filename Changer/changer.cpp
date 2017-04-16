//Created by Eric Talbott

#include <iostream>

using namespace std;

//Declaring Contant values for Quarters, Dimes, Nickels, and Pennies
//Q = Quarters = 25
//D = Dimes = 10
//N = Nickels = 5
//P = Pennies = 1
#define Q 25
#define D 10
#define N 5
#define P 1


int* changer(int amount);
void printResults(int * arr, int quarters, int dimes, int nickels, int pennies, int arr_size);

//Main takes in 1 command line argument. An Integer Value which is
//sent to the changer function. An Int Array receives the results from changer
int main(int argc, char const *argv[]){
	int* arr;
	int input = atoi(argv[1]);
	arr = changer(input);

	return 0;
}

//Changer is passed an integer value and creates an array based on the 
//total number of coins needed to create that value 
//(ie. 99 = 3 Quarters, 2 Dimes, and 4 pennies. Array of size 9 is created)
//The array is then populated with the correct values, and returned after being 
//sent to the printResults function
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

	for(int i = 0; i < arr_size; i++){
		if(i < quarters)
			arr[i] = Q;
		else if (i < quarters + dimes)
			arr[i] = D;
		else if(i < quarters + dimes + nickels)
			arr[i] = N;
		else
			arr[i] = P;
	}

	printResults(arr, quarters, dimes, nickels, pennies, arr_size);

	return arr;
}

//Outputs the resulting array to the console
void printResults(int* arr, int quarters, int dimes, int nickels, int pennies, int arr_size){
cout << "An Array of size [" << arr_size << "] was created containing:" 
	<< endl << quarters << " Quarter(s)" 
	<< endl << dimes << " Dime(s)"
	<< endl << nickels << " Nickel(s)"
	<< endl << pennies << " Pennie(s)" << endl;

for(int i = 0; i < arr_size; i++)
	cout << arr[i] << " ";
cout << endl;

}