#define Q 25
#define D 10
#define N 5
#define P 1

#include<iostream>
using namespace std;

int* arr;
int* changer(int num);
int quarters, dimes, nickels, pennies, arr_size;

int main(int argc, char const *argv[])
{
	int number = atoi(argv[1]);
	arr = changer(number);

	for(int i = 0; i < arr_size; i++){
		cout << arr[i] << " " ;
	}
	cout << endl;

	return 0;
}



int* changer(int num){
	quarters = num / Q;
	num = num % Q;
	dimes = num / D;
	num = num % D;
	nickels = num / N;
	num = num % N;
	pennies = num / P;
	num = num % P;

	arr_size = quarters + dimes + nickels + pennies;

	arr = new int[arr_size];

	for(int i = 0; i < quarters; i++){
		arr[i] = Q;
	}
	for(int i = quarters; i < (quarters + dimes); i++){
		arr[i] = D;
	}
	for(int i = (quarters + dimes); i < (quarters + dimes + nickels); i++){
		arr[i] = N;
	}
	for(int i = (quarters + dimes + nickels); i < (quarters + dimes + nickels + pennies); i++){
		arr[i] = P;
	}

	return arr;
}