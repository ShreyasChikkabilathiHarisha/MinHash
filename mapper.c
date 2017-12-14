#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>
#include "minhash.hpp"
// #include "bloom_filter.hpp"
#include "containmentminhash.cpp"
using namespace std;

bool KmerCompare(string &str1, string &str2){
   return str1.compare(str2);
}

float trueJaccards(vector<string> *aKmerVectB, vector<string> *aKmerVectA) {
   std::vector<string> *v = new vector<string>;
   v->reserve(aKmerVectA->size() + aKmerVectB->size());
   std::vector<string>::iterator it, itEnd;

   sort(aKmerVectB->begin(), aKmerVectB->end());
   sort(aKmerVectA->begin(), aKmerVectA->end());
   /*
   cout << "sort A:" << endl;
   for(std::vector<std::string>::iterator i = aKmerVectA->begin(); i != aKmerVectA->end(); ++i)
   {
     cout << *i << ' ';
   }
   cout << endl;
   cout << "sort B:" << endl;
   for(std::vector<std::string>::iterator i = aKmerVectB->begin(); i != aKmerVectB->end(); ++i)
   {
     cout << *i << ' ';
   }
   cout << endl;
   */
   // bigger set has to go as first argument
   itEnd=std::set_intersection(aKmerVectB->begin(), aKmerVectB->end(), aKmerVectA->begin(), aKmerVectA->end(), v->begin(), KmerCompare);
   uint countIntersect = 0;
   if (itEnd-v->begin() > 0){
      countIntersect = itEnd-v->begin();
   }
   std::cout << "The intersection has " << countIntersect << " elements:\n";
   /*
   for (it=v->begin(); it!=itEnd; ++it){
      cout << ' ' << *it;
   }
   std::cout << '\n';
   */
   itEnd=std::set_union(aKmerVectB->begin(), aKmerVectB->end(), aKmerVectA->begin(), aKmerVectA->end(), v->begin(), KmerCompare);
   uint countUnion = 0;
   if (itEnd-v->begin() > 0){
      countUnion = itEnd-v->begin();
   }
   std::cout << "The union has " << countUnion << " elements:\n";
   /*
   for (it=v->begin(); it!=itEnd; ++it){
      cout << ' ' << *it;
   }
   std::cout << '\n';
   */
   float trueJaccard = countIntersect / (float)countUnion;
   //cout << "trueJaccard : " << trueJaccard << endl;
   delete v;
   return trueJaccard;
}

void generateKmers(string &aLargeString, const uint &aKmerSize, vector<string> *aKmerVect, const uint numKmers){
   vector<string>::iterator it = aKmerVect->begin();
   for (uint i=0;i < numKmers; i++){
      //cout << i << " : " << aLargeString.substr(i, aKmerSize) << endl;
      aKmerVect->insert(it, aLargeString.substr(i, aKmerSize));
      it++;
   }
}

void printKmers(vector<string> *aKmerVect){
   vector<string>::iterator it;
   for (it = aKmerVect->begin(); it < aKmerVect->end(); it++){
      cout << *it << ' ';
   }
   cout << endl;
}

int main()
{
   string small_string = "CTACGCAAGGGTACCGCGACCTCAATGCTTGCACGTTACTCCTCTGCCGTTAACATGTCTTCAGGTTGATCAAGCTGACTAGCACTTGATTTCCAGGATA";
   string base_names = "../data/Genomes/base_name.txt";
   // Kmer size
   const uint ksize = 11;
   // probability error rate for bloom filter
   const float prob_error_rate = 0.01;
   // max number of hashes to retain for each string
   const uint h = 10;
   // num kmers formed from each string
   uint size_A = small_string.length() - ksize + 1 ;
    uint size_A_est = 0;
   vector<string> *kmersA = new vector<string>;
   kmersA->reserve(size_A);
   generateKmers(small_string, ksize, kmersA, size_A);
   vector<float> *min_jaccards = new vector<float>;
   CountEstimator ch(10, 9999999999971, 11, "", 'y', NULL, false);
   ch.add_sequence(small_string, false);
   CountEstimator re();
   string line;
   while(getline("data.txt"),line){
     re._mins.insert(line);
   }
   float minestimate = re.jaccard(ch);

   ContainmentMinHash cmh(small_string.length(), prob_error_rate, 0xA5A5A5A5);
   for (size_t i = 0; i < size_B; ++i)
   {
      if (!cmh.contains(kmersA->at(i))){
         cmh.add(kmersA->at(i));
         size_A_est++;
      }
      else{
         cout << "string already present in bloom_filter : " << kmersA->at(i) << endl;
      }
   }
   long i=0;
   vector<float> *con_jaccards = new vector<float>;
   float containment_est_jaccard;
   for(list<CountEstimator>::iterator it = genome_sketches.begin(); it!= genome_sketches.end(); it++)
   {
      cout << "element count :" << cmh.element_count() << "\n";
      float int_est = 0;
      for (auto& kmer : ch.get_kmers_list()){
         if (!kmer.empty() && cmh.contains(kmer)){
            int_est++;
         }
         else{
            cout << "BF doesnot contain " << kmer << endl;
         }
      }
      cout << "MinHash" << minestimate << endl;
      containment_est = int_est / float(h)
      containment_est_jaccard = ((*it)->_true_num_kmers * containment_est)/((*it)->_true_num_kmers + kmersA.size() - ((*it)->_true_num_kmers * containment_est));
      con_jaccards.push_back(containment_est_jaccard);
      i++;
   }

   // to wrote the mean of min and containment hashes between the sample and the values in the hdf5 exports.

}
