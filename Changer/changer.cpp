#include <iostream>

using namespace std;

#define Q 25
#define D 10
#define N 5
#define P 1


int* changer(int amount);
void printResults(int * arr, int quarters, int dimes, int nickels, int pennies, int arr_size);

int main(int argc, char const *argv[]){
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