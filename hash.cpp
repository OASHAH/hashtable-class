#include "hash.h"

hash::hash()
{
	hash_table = new std::list<unsigned long long int>[20];
	this->table_size = 20;
	this->items = 0;
}
hash::hash(unsigned long long int size)
{
	hash_table = new std::list<unsigned long long int>[size];
	this->table_size = size;
	this->items = 0;

}
void hash::insert_hash(unsigned long long int k)
{
	if (table_size + 1 == items)  double_size();
	insert(k);

}

void hash::insert(unsigned long long int k)// hash key
{
	unsigned long long int index = hash_function(k, table_size);
	hash_table[index].push_back(k);
	this->items++;

}
void hash::delete_hash(unsigned long long int k)
{
	
	if (table_size - 1 == (items / 4)) halve_size();
	// get the hash index of key
	unsigned long long int index = hash_function(k, table_size);

	// find the key in (inex)th std::list 
	std::list <unsigned long long int> ::iterator i;
	for (i = hash_table[index].begin();
		i != hash_table[index].end(); i++) {
		if (*i == k)
		{
			break;
		}
	}

	// if key is found in hash table, remove it 
	if (i != hash_table[index].end())
	{

		hash_table[index].erase(i);

		this->items--;
	}
}

unsigned long long int hash::search_hash(unsigned long long int k)
{
	unsigned long long int index = hash_function(k, table_size);
	// find the key in (inex)th std::list 
	std::list <unsigned long long int> ::iterator i;
	for (i = hash_table[index].begin();
		i != hash_table[index].end(); i++) {
		if (*i == k)
			break;
	}

	

	if (i == hash_table[index].end())
		return 666;
	else
		return hash_function(*i,this->table_size);
}

void hash::show_hash()
{
	for (int i = 0; i < table_size; i++) {
		std::cout << i;
		for (auto x : hash_table[i])
			std::cout << " --> " << x;
		std::cout << std::endl;
	}
}

unsigned long long int hash::hash_function(unsigned long long int k, unsigned long long int ts)
{
	unsigned long long int p = get_next_prime(table_size);
	unsigned long long int r = (double)rand() / RAND_MAX;
	unsigned long long int a = (p - 1) * r + 1;
	unsigned long long int b = (p - 1) * r;

	std::string a1 = std::to_string(a);
	std::string k1 = std::to_string(k);
	std::string ans = multiply(a1, k1);
	
	std::string::size_type sz = 0;   // alias of size_t

	unsigned long long y;
	while (!ans.empty()) {
		y = std::stoull(ans, &sz, 0);
		ans = ans.substr(sz);
	}

	//unsigned long long int y = std::stoll(ans);
	//unsigned long long int y = a * k;
	

	return ((y + b) % p) % ts; //here, m is the table size
}

void hash::double_size()
{
	std::list<unsigned long long int>* temp = new std::list<unsigned long long int>[table_size];
	unsigned long long int gt = table_size;
	for (int i = 0; i < table_size; i++)
	{
		for (auto x : hash_table[i])
		{
			temp[i].push_back(x);
		}
	}

	
	delete[] hash_table;

	this->table_size *= 2;
	hash_table = new std::list<unsigned long long int>[table_size];
	

	// this is rehashing on the hash_table.
	for (int i = 0; i < gt; i++)
	{
		for (auto x : temp[i])
		{
			insert(x);
		}
	}
	
	
	delete[] temp; // need to delete the chains.

}

void hash::halve_size()
{

	std::list<unsigned long long int>* temp = new std::list<unsigned long long int>[table_size/2];
	for (int i = 0; i < table_size; i++)
	{
		for (auto x : hash_table[i])
		{
			unsigned long long int k = hash_function(x, table_size/2);
			temp[i].push_back(k);
		}
	}

	delete[] hash_table;
	hash_table = new std::list<unsigned long long int>[table_size / 2];
	
	this->table_size /= 2;
	for (int i = 0; i < table_size; i++)
	{
		for (auto x : temp[i])
		{
			insert(x);
		}
	}

	
	delete[] temp; // need to delete the chained portion.
}

void hash::displayHash() {
	for (int i = 0; i < this->table_size; i++) {
		std::cout <<"|| " << i << " ||";
		for (auto x : hash_table[i])
		{
			std::cout << " --> " << x;
		}


		std::cout << std::endl;
	}
}

int hash::count_collisons()
{
	int collisons = 0;
	for (int i = 0; i < table_size; i++)
	{
		if (hash_table[i].size() > 1)
		{
			collisons += hash_table[i].size() -1;
		}
	}

	return collisons;
}

bool hash::is_prime(int p)
{
	int i;
	bool isPrime = true;
	for (i = 2; i <= p / 2; ++i)
	{
		if (p % i == 0)
		{
			isPrime = false;
			break;
		}
	}
	if (isPrime)
		return 1;
	else
		return 0;
}
int hash::get_next_prime(unsigned long long int t)
{
	for (int i = t; i < (2*t);i++)
	{
		if (is_prime(i)) return i;
	}


	return -1;
}
int hash::get_next_prime2(unsigned long long int t)
{
	for (int i = (2*t) -1; i >= 0;i--)
	{
		if (is_prime(i)) return i;
	}

}

std::string hash::multiply(std::string num1, std::string num2)
{
	int len1 = num1.size();
	int len2 = num2.size();
	if (len1 == 0 || len2 == 0)
		return "0";

	// will keep the result number in std::vector 
	// in reverse order 
	std::vector<int> result(len1 + len2, 0);

	// Below two indexes are used to find positions 
	// in result.  
	int i_n1 = 0;
	int i_n2 = 0;

	// Go from right to left in num1 
	for (int i = len1 - 1; i >= 0; i--)
	{
		int carry = 0;
		int n1 = num1[i] - '0';

		// To shift position to left after every 
		// multiplication of a digit in num2 
		i_n2 = 0;

		// Go from right to left in num2              
		for (int j = len2 - 1; j >= 0; j--)
		{
			// Take current digit of second number 
			int n2 = num2[j] - '0';

			// Multiply with current digit of first number 
			// and add result to previously stored result 
			// at current position.  
			int sum = n1 * n2 + result[i_n1 + i_n2] + carry;

			// Carry for next iteration 
			carry = sum / 10;

			// Store result 
			result[i_n1 + i_n2] = sum % 10;

			i_n2++;
		}

		// store carry in next cell 
		if (carry > 0)
			result[i_n1 + i_n2] += carry;

		// To shift position to left after every 
		// multiplication of a digit in num1. 
		i_n1++;
	}

	// ignore '0's from the right 
	int i = result.size() - 1;
	while (i >= 0 && result[i] == 0)
		i--;

	// If all were '0's - means either both or 
	// one of num1 or num2 were '0' 
	if (i == -1)
		return "0";

	// generate the result std::string 
	std::string s = "";

	while (i >= 0)
		s += std::to_string(result[i--]);

	return s;
}

unsigned long long int hash::hash_function2(unsigned long long int k, unsigned long long int ts)
{
	unsigned long long int p = get_next_prime2(table_size);
	unsigned long long int r = (double)rand() / RAND_MAX;
	unsigned long long int a = (p - 1) * r + 1;
	unsigned long long int b = (p - 1) * r;

	std::string a1 = std::to_string(a);
	std::string k1 = std::to_string(k);
	std::string ans = multiply(a1, k1);

	std::string::size_type sz = 0;   // alias of size_t

	unsigned long long y;
	while (!ans.empty()) {
		y = std::stoull(ans, &sz, 0);
		ans = ans.substr(sz);
	}

	//unsigned long long int y = std::stoll(ans);
	//unsigned long long int y = a * k;


	return ((y + b) % p) % ts; //here, m is the table size
}


void hash::insert_double_hashing(unsigned long long int k, int total_keys)
{
	unsigned long long int index1 = hash_function(k, table_size);
	if (items == table_size) double_size2(); //function for if table is full.

	if (hash_table[index1].empty())
	{
		this->items++;
		hash_table[index1].push_back(k);
	}
	else
	{
		unsigned long long int index2 = hash_function2(k, table_size);
		unsigned long long int index3;
		int i;

		for (i = 1; i < total_keys; i++)
		{
			
			index3 = (index1 + (i * index2)) % table_size;
			if (hash_table[index3].empty())
			{
				this->items++;
				hash_table[index3].push_back(k);
				break;
			}
		}
	}
}


void hash::double_size2()
{


	std::list<unsigned long long int>* temp = new std::list<unsigned long long int>[table_size];
	unsigned long long int gt = table_size;
	for (int i = 0; i < table_size; i++)
	{
		for (auto x : hash_table[i])
		{
			temp[i].push_back(x);
		}
	}
	delete[] hash_table;

	int y = table_size;
	this->table_size *= 2;
	hash_table = new std::list<unsigned long long int>[table_size];


	// this is rehashing on the hash_table.
	for (int i = 0; i < y; i++)
	{
		for (auto x : temp[i])
		{
			hash_table[i].push_back(x);
		}
	}

	delete[] temp; // need to delete the chains.

}

void hash::build_perfect_hashing()
{

	
	unsigned long long int index, index1;
	p_hash_table = new unsigned long long int* [table_size] {0};
	for (int i = 0; i < table_size; i++)
	{
		if (hash_table[i].size() == 1)
		{
			
			index = hash_function(hash_table[i].front(), table_size);

			p_hash_table[index] = new unsigned long long int[2]{ 0 };
			p_hash_table[index][0] = 2;

			p_hash_table[index][1] = hash_table[i].front();
		}
		else if (hash_table[i].size() > 1)
		{

			index = hash_function(hash_table[i].front(), table_size);
			p_hash_table[index] = new unsigned long long int[1 + square(hash_table[i].size()) + 1]{0}; // square of the keys.
			p_hash_table[index][0] = hash_table[i].size() + 2;

			for (auto j : hash_table[i])
			{
				
				index1 = hash_function3(j, square(hash_table[i].size())) + 1;
				if (p_hash_table[index][index1] != 0) std::cout << "collision" << std::endl;
				p_hash_table[index][index1] = j;
			}

		}
		else if (hash_table[i].empty())
		{
			p_hash_table[i] = new unsigned long long int[1]{ 0 };
			
		}
	}



}
void hash::search_perfect_hashing(unsigned long long int k)
{
	unsigned long long int index2;
	unsigned long long int index1 = hash_function(k, table_size);
	if (p_hash_table[index1][0] == 1)
	{
		index2 = 1;
		std::cout << "this key is located at perfect_hash_table[" << index1 << "]" << index2 << std::endl;
		return;
	}
	else if (p_hash_table[index1][0] == 0)
	{
		std::cout << "key not present" << std::endl;
		return;
	}
	else
	{
		index2 = hash_function2(k, square(p_hash_table[index1][0])  ) + 1;
		std::cout << "this key is located at index: table[" << index1 << "][" << index2 << "]"<< std::endl;
		return;
	}
	
	std::cout << "key not present" << std::endl;
	return;
}

unsigned long long int hash::square(unsigned long long int s)
{
	return s * s;
}

void hash::display_perfect_hashing()
{
	for (int i = 0; i < table_size; i++)
	{
		std::cout << "|| " << i << " || --> ";
		
			for (int j = 1; j < p_hash_table[i][0]; j++)
			{
				std::cout << "| " << p_hash_table[i][j];
			}

		std::cout << " |" << std::endl;
		
	}
}

unsigned long long int hash::hash_function3(unsigned long long int k, unsigned long long int ts)
{

	unsigned long long int p = get_next_prime2(table_size*6757 + 31);
	unsigned long long int r = (double)rand() / RAND_MAX;
	unsigned long long int a = (p - 1) * r + 1;
	unsigned long long int b = (p - 1) * r;

	std::string a1 = std::to_string(a);
	std::string k1 = std::to_string(k);
	std::string ans = multiply(a1, k1);

	std::string::size_type sz = 0;   // alias of size_t

	unsigned long long y;
	while (!ans.empty()) {
		y = std::stoull(ans, &sz, 0);
		ans = ans.substr(sz);
	}

	//unsigned long long int y = std::stoll(ans);
	//unsigned long long int y = a * k;


	return ((y + b) % p) % ts; //here, m is the table size
}