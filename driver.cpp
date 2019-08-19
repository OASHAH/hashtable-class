
#include "hash.h"
#include <algorithm>
struct Node
{
	Node* next;
	unsigned long long int val;
};

unsigned long long int* generateRandomKeys(int);
int removeDuplicates(unsigned long long int*, int);
int entry();

int main() {

	unsigned long long int* arr1 = generateRandomKeys(100);
	int size = removeDuplicates(arr1, 100); // size of arr1 after removing duplicates.
	


	hash h1(40);

	// uncomment this to check chained hashing
	for (int i = 0; i < size; i++)
	{
		int c = entry();
		switch (c)
		{
		case 1:
			h1.insert_hash(arr1[i]);
			break;

		case 2:
			h1.insert_hash(arr1[i]);
			//h1.delete_hash(arr1[i]);
			break;

		case 3:
			//std::cout << h1.search_hash(arr1[i]) << std::endl;
			break;

		default:
			continue;
		}
	}

	//h1.insert_hash(3345);
	h1.build_perfect_hashing();
	h1.display_perfect_hashing();
	//h1.search_perfect_hashing(3345);
	//h1.search_perfect_hashing(33457);


	//h1.displayHash();
	//std::cout << "\nTotal collisions = " << h1.count_collisons() << std::endl;

	return 0;
}


unsigned long long int* generateRandomKeys(int n)
{
	// 2^64 = 8 bytes. thus it is long long
	unsigned long long int max = ULLONG_MAX - 1; //LLONG_MAX
	unsigned long long int* arr = new unsigned long long int[n];

	for (int i = 0; i < n; i++)
	{
		arr[i] = round((((double)rand() / (RAND_MAX))) * max + 1);
		
	}

	/*for (int i = 0; i < n; i++)
	{
		std::cout << arr[i] << " --> " <<std::endl;
	}*/ //check the keys.

	return arr;



}

int entry()
{
	double r = (double)rand() / RAND_MAX;
	if (r < 0.33)
	{
		return 1;

	}
	else if (r > 0.33 && r < 0.66)
	{
		return 2;
	}
	else
	{
		return 3;
	}
}

int removeDuplicates(unsigned long long int* arr, int n)
{
	if (n == 0 || n == 1)
		return 0;

	int u = sizeof(arr) / sizeof(arr[0]);
	std::sort(arr, arr + u);

	// To store index of next unique element 
	int j = 0;

	// Doing same as done in Method 1 
	// Just maintaining another updated index i.e. j 
	for (int i = 0; i < n - 1; i++)
		if (arr[i] != arr[i + 1])
			arr[j++] = arr[i];

	arr[j++] = arr[n - 1];

	
	unsigned long long int* temp = new unsigned long long int[j];
	for (int i = 0; i < j; i++)
	{
		temp[i] = arr[i];
	}

	delete[] arr;

	arr = new unsigned long long int[j];
	for (int i = 0; i < j; i++)
	{
		arr[i] = temp[i];
	}

	return j;


}

