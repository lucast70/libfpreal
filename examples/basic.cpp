// basic usage example of libfpreal

#include <fprealxx.h>

#include <iostream>
#include <algorithm>

using namespace fpreal;

int 
main () 
{
  // real number with two digits precision	
  fpreal2_t A, B = 12.12, C (13.13), D ("2342.1192"), E;
  
  // a native float
  float f = 123.8899;
  
  // assign from string
  E = "91.789";
  
  // assign from float
  E = 91.789f;
  
  
  // auto F = E + 0.001;
  
  // this works fine
  // std::cout << F.getDouble () << std::endl;
  
  // this doesn't work
  // std::cout << F << std::endl;
  
    
  // add 
  A = B + C + D + f; 
    
  std::cout 
    << "A = " << B.get () << " + " << C.get () << " + " <<  D.get () 
    << " + " << f << " = " << A.getString () << std::endl;
  
  // mix
  A = D - B + f - C;
  
  std::cout 
    << "A = " << D.get () << " - " << B.get () << " - " << f 
    << " + " << C.get () << " = " << A.getString () << std::endl;
    
  // mul
  A = D * D;
  
  std::cout 
    << "A = " << D.get () << " x " << D.get () << " = " << A.getString () << std::endl;
    
  // div
  C = 198.989;
  D = 12.11234;
  
  A = C / D;
  
  std::cout 
    << "A = " << C.get () << " / " << D.get () << " = " << A.getString () << std::endl;
  
  A = D / C;
  
  std::cout 
    << "A = " << D.get () << " / " << C.get () << " = " << A.getString () << std::endl << std::endl;
  
  // sort: test for cmp operators  
  fpreal4_t ARR[] = 
    {22.4f, 9.88128f, 15.7721f, 3.141592f, 11.1112f, 2.718181f, 16.384f}; 
  
  std::cout << "Array before sort:" << std::endl;  
  for (fpreal4_t ELEM : ARR)
    std::cout << ELEM.getString () << std::endl;
  
  std::sort (ARR, ARR + 7);
  
  std::cout << "Array after sort:" << std::endl;
  for (fpreal4_t ELEM : ARR)
    std::cout << ELEM.getString () << std::endl;
}	
