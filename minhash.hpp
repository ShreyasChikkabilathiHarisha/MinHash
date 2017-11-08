#include <iostream>
#include <string>
#include <list>
#include <cmath>
#include <inttypes.h>
#include <algorithm>  
#include <functional>
#include <cctype>
#include <cstring>

template <typename T >
class CountEstimator
{
	/* A simple bottom n-sketch MinHash implementation.
    n is the number of sketches to keep
    Still don't know what max_prime is */
private:
	int n;
	long max_prime = 9999999999971;
	int ksize = 0;
	std::string input_file_name = NULL;
	char save_kmers = 'n';
	std::list<long> hash_list ;
	bool rev_comp=false;
	std::list<long> _mins ;
	std::list<long> _counts ;
	std::list<std::string> _kmers ;
	long _true_num_kmers;

public:
	CountEstimator(T& object, std::list<long> hash_list, int n = 0, long max_prime = 9999999999971, int ksize = 0, std::string input_file_name = NULL, char save_kmers = 'n', bool rev_comp = false);
	void parse_file(bool rev_comp=false);
	void down_sample(long h);
	void add(T& kmer, bool rev_comp=false);
	void add_sequence(std::string seq, bool rev_comp=false);
	void jaccard_count();
	void jaccard();
	void common_count();
	void common();
	void _truncate();
	void _export();
	void count_vector();
	void jaccard_vector();
	bool is_prime(int number);
	long get_prime_lt_x(long target);

};

uint64_t MurmurHash64A ( const void * key, int len, unsigned int seed );
int main();
