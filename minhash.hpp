#include <iostream>
#include <string>
#include <list>
#include <cmath>
#include <inttypes.h>
#include <algorithm>  
#include <functional>
#include <cctype>
#include <cstring>

//template <typename T >
class CountEstimator
{
	/* A simple bottom n-sketch MinHash implementation.
    n is the number of sketches to keep
    Still don't know what max_prime is */
private:
	int n;
	long max_prime = 9999999999971;
	int ksize = 0;
	long p;
	std::string input_file_name = "";
	char save_kmers = 'n';
	std::list<long> hash_list ;
	bool rev_comp=false;
	std::list<long> _mins ;
	std::list<long> _counts ;
	std::list<std::string> _kmers ;
	long _true_num_kmers;

public:
	CountEstimator();
	CountEstimator(std::list<long> hash_list, int n, long max_prime, int ksize, std::string input_file_name, char save_kmers, bool rev_comp);
	void parse_file(bool rev_comp);
	void down_sample(long h);
	void add(std::string kmer, bool rev_comp);
	void add_sequence(std::string seq, bool rev_comp);
	void jaccard_count();
	void jaccard();
	void common_count();
	void common();
	void _truncate();
	void _export();
	void count_vector();
	void jaccard_vector();
};

uint64_t MurmurHash64A ( const void * key, int len, unsigned int seed );
bool is_prime(int number);
long get_prime_lt_x(long t);
//int main();
