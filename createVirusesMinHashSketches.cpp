// # Here we will pre-compute the min hash sketches to speed the simulation. Could parallelize this
// # to make it go faster, but it only needs to be done once, so I don't really care
// import os
// import screed
// import khmer
// import MinHash as MH
// import bz2
// from multiprocessing.dummy import Pool
// import multiprocessing
// from itertools import *
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <list>
#include <linux/limits.h>
#include <experimental/filesystem>
#include <unordered_set>

#include "minhash.hpp"

using namespace std;
namespace fs = std::experimental::filesystem;

unsigned int num_threads = thread::hardware_concurrency();
long long prime = 9999999999971; // taking hashes mod this prime
unsigned int ksize = 21;  // k-mer length
unsigned int max_h = 500;  // max number of hashes in sketch
list<string> file_names; 

// string filename = "/fatfs/Fall2017Courses/ComputationalBiology/project/MinHashMetagenomics-master/data/Viruses/FileNames.txt";
string relativePath = "/../../../MinHashMetagenomics-master/data/Viruses/";
string filename = "FileNames.txt";

list<CountEstimator> make_minhash(string aFilepath, unsigned int amax_h, unsigned int prime, unsigned int ksize){
	unordered_set<string> kmers;
	

} 

void threadFunc(const string& filename){
	cout << this_thread::get_id() << " filename : " << filename << "\n";
}
void createThread(const string& filename){
	thread t1(threadFunc, filename);
	t1.detach();
}

int main(){
	ifstream fs;
	string line;
    fs::path p = fs::current_path();
    string absPath = p.string() + relativePath + filename; 
	cout << absPath << "\n";
	fs.open(absPath);
	if (fs.is_open()) {
		while ( getline (fs,line) ) {
			// cout << fs::path(line).filename().string() << "\n";
			file_names.push_back(fs::path(line).string());
		}
	}else {
		cout << "Unable to open file\n";
	}
	fs.close();

	
	cout << *file_names.begin() << "\n";
	// for_each(file_names.begin(), file_names.end(), [](string &filename){cout << filename << "\n";});
	for_each(file_names.begin(), file_names.end(), createThread);
	
	// t1.detach();
	//t1.join();

	cout << endl;
	return 0;
}


/*


def make_minhash(genome, max_h, prime, ksize):
	kmers = set()
	name = os.path.basename(genome)
	MHS = MH.CountEstimator(n=max_h, max_prime=prime, ksize=ksize, save_kmers='y')
	for record in screed.open(genome):
		seq = record.sequence
		for i in range(len(seq) - ksize + 1):
			kmer = seq[i:i+ksize]
			kmer_rev = khmer.reverse_complement(kmer)
			if kmer < kmer_rev:
				kmers.add(kmer)
				MHS.add(kmer)
			else:
				kmers.add(kmer_rev)
				MHS.add(kmer_rev)
	MHS._true_num_kmers = len(kmers)
	MHS.input_file_name = os.path.basename(genome)
	# Export the hash k-mers
	fid = open(os.path.abspath(os.path.join('../data/Viruses/', name + ".Hash21mers.fa")), 'w')
	for kmer in MHS._kmers:
		fid.write(">\n%s\n" % kmer)
	fid.close()


def make_minhash_star(arg):
return make_minhash(*arg)

pool = Pool(processes=num_threads)
genome_sketches = pool.map(make_minhash_star, zip(file_names, repeat(max_h), repeat(prime), repeat(ksize)))


# Export all the sketches
base_names = [os.path.basename(item) for item in file_names]
MH.export_multiple_to_single_hdf5(genome_sketches, os.path.abspath('../data/Viruses/AllSketches.h5'))
*/