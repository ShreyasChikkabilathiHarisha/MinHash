#include "minhash.hpp"

using namespace std;

template <typename T>
CountEstimator<T>::CountEstimator(T& object, std::list<long> hash_list, int n, long max_prime, int ksize, std::string input_file_name, char save_kmers, bool rev_comp)
{
	if(n == 0)
	{
		cout<<"n=0 exception\n";
		exit(0);
	}
	if(ksize == 0)
	{
		cout<<"ksize=0 exception\n";
		exit(0);
	}
	if((ksize % 2) == 0)
	{
		cout<<"Due to an issue with khmer, only odd ksizes are allowed\n";
		exit(0);
	}
	this->_ksize = ksize;
	this->_hash_list = hash_list;
	// get a prime to use for hashing
	long p = get_prime_lt_x(max_prime);
	this->p = p;
	// initialize sketch to size n
	


}

template <typename T>
void CountEstimator<T>::parse_file()
{

}

template <typename T>
void CountEstimator<T>::down_sample()
{

}

template <typename T>
void CountEstimator<T>::add()
{

}

template <typename T>
void CountEstimator<T>::add_sequence()
{

}

template <typename T>
void CountEstimator<T>::jaccard_count()
{

}

template <typename T>
void CountEstimator<T>::common_count()
{

}

template <typename T>
void CountEstimator<T>::common()
{

}

template <typename T>
void CountEstimator<T>::_truncate()
{

}

template <typename T>
void CountEstimator<T>::_export()
{

}

template <typename T>
void CountEstimator<T>::count_vector()
{

}

template <typename T>
void CountEstimator<T>::jaccard_vector()
{

}

bool is_prime(int number)
{
	if(number < 2)
	{
		return false;
	}
	if(number == 2)
	{
		return true;
	}
	if((number % 2) == 0)
	{
		return false;
	}
	for(int i =3; i<(int(pow(number,0.5))+1); i+=2)
	{
		if((number%i) == 0)
		{
			return false;
		}
	}
	return true;
}

long get_prime_lt_x(long target)
{
	if(target == 1)
	{
		return 1;
	}
	int i = int(target);
	if( (i%2) == 0 )
	{
		i -= 1;
	}
	while(i > 0)
	{
		if(is_prime(i))
		{
			return i;
		}
		i -=2;
	}
	if(i <= 0)
	{
		cout<<"unable to find a prime number < "<< target <<endl;
		exit(0);
	}
}

int main()
{
    cout<<"success\n";

    return 0;
}
