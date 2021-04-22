// libfpreal benchmarks

#include "fprealxx.h"

#include <cstdio>
#include <iostream>
#include <vector>
#include <functional>
#include <random>
#include <string>

class Rand_double
{
public:
    Rand_double(double low, double high)
    :r(std::bind(std::uniform_real_distribution<>(low,high),std::default_random_engine())){}

    double operator()(){ return r(); }

private:
    std::function<double()> r;
};

using namespace fpreal;

int 
main ()
{
  static constexpr int N = 100000;
  Rand_double rd {-999999999999.99999999f,999999999999.99999999f};
  std::vector <fpreal6_t> A, B, C;
  fpreal6_t r;
  
  // generate dataset
  for (int counter = 0; counter < N; counter ++)
  {
	r = rd (); 
	B.push_back (r);
	
	r = rd ();
	C.push_back (r);
	
	r = 0;
	A.push_back (0);  
  }	    
  
  // perform operations
  for (int n = 0; n < N; n ++)
  {
	// add
	A[n] = B[n] + C[n];
    
    
	// sub  
	A[n] = B[n] - C[n];
	
	// mul
	A[n] = B[n] * C[n];
	
	// div
	A[n] = B[n] / C[n];
	
	
	// cmp
	bool b = (A[n] == B[n]);
	b = (A[n] > B[n]);
	b = (A[n] >= B[n]);
	b = (A[n] < B[n]);
	b = (A[n] <= B[n]);
	
	// convert to std:string
	std::string s = A[n].getString ();
	
	// const to double
	double d = A[n].getDouble ();
  }	  
  	
}	
