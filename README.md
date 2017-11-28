# CSE549 - 

BZ2 files contain kmers
HDF5 files contain CE's structures

TO DO's
=======
write a fastq reader from code in createVirusesMinHashSketches.cpp - populate all kmers in a list/vector.. pass one kmer to caller on each call.

write code for import, export to hdf5 files in minhash.cpp 

add code to dump minhash sketches to hdf5 file in createVirusesMinHashSketches.cpp

some observations:
==================
python
time python CreateVirusesMinHashSketches.py (without writing to hdf5 file)
real	40m36.332s
user	44m59.964s
sys	6m10.315s

c++
time ./createVirusesMinHashSketches (without writing to hdf5 file)
real	8m11.709s
user	28m34.043s
sys	0m53.912s

