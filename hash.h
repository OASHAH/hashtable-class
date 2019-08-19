#pragma once
#include<iostream>
#include <list> 
#include <iterator> 
#include<string>
#include<vector>

//#include "bigint-library-master/bigint.h"

class hash
{
private:
	unsigned long long int table_size;
	unsigned long long int items;
	std::list<unsigned long long int>* hash_table;
	unsigned long long int** p_hash_table;
public:
	
	hash();
	hash(unsigned long long int);
	void insert_hash(unsigned long long int); // this checks for loading factor while the one below doesn't.
	void insert(unsigned long long int);
	void delete_hash(unsigned long long int);
	bool is_prime(int);
	int get_next_prime(unsigned long long int); // for hash function 1
	int get_next_prime2(unsigned long long int); // for hash function 2
	std::string multiply(std::string, std::string); // for big number multiplication.
	unsigned long long int hash_function(unsigned long long int, unsigned long long int);// key, table_size
	unsigned long long int hash_function2(unsigned long long int, unsigned long long int); // same as above
	unsigned long long int hash_function3(unsigned long long int, unsigned long long int); // same as above
	void show_hash();
	void double_size();
	void double_size2(); // for double hashing.
	void halve_size();
	unsigned long long int search_hash(unsigned long long int);
	int count_collisons();
	void displayHash();
	void insert_double_hashing(unsigned long long int, int); // key, total keys

	void build_perfect_hashing();
	void search_perfect_hashing(unsigned long long int);
	unsigned long long int square(unsigned long long int);
	void display_perfect_hashing();
	

};

