/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 */

// Copyright © 2020 - 2021 Lucas Tsatiris. All rights reserved.

#pragma once

// C++98
#if __cplusplus<=199711L

#ifndef noexcept
#define noexcept
#endif

#ifndef nullptr
#define nullptr		NULL
#endif

#endif	// __cplusplus<=199711L

// prior C++11
#if __cplusplus<201103L

#ifndef constexpr
#define constexpr	const
#endif

#endif	// __cplusplus<201103L

// prior C++20
#if __cplusplus<202002L

#ifndef consteval
#define consteval	constexpr
#endif

#endif	// __cplusplus<202002L

// check for c++11 compiler 
#ifdef FPREAL_USE_CONSTEXPR
#if __cplusplus<201103L
#undef FPREAL_USE_CONSTEXPR
#warning "Compiler does not support constexpr"
#endif	// __cplusplus<201103L
#endif	// FPREAL_USE_CONSTEXPR

// silly gcc 10.2 bug in C++11 mode, so we disable use of constexpr
#ifdef FPREAL_USE_CONSTEXPR
#if __GNUC__==10 && __GNUC_MINOR__==2
#if __cplusplus==201103L
#undef FPREAL_USE_CONSTEXPR
#warning "Buggy gcc compiler, constexpr usage disabled"
#endif
#endif
#endif

// use constexpr
#ifdef FPREAL_USE_CONSTEXPR
#define FPREAL_OPT_VAR		constexpr
#define FPREAL_OPT_FUNC		consteval
#else
#define FPREAL_OPT_VAR		const
#define FPREAL_OPT_FUNC		inline
#endif	// FPREAL_USE_CONSTEXPR

#if defined (__SIZEOF_INT128__)		// gcc, clang and icc 
#define FPREAL_UINT 		unsigned __int128
#define FPREAL_INT 			__int128
#endif	// __SIZEOF_INT128__

#if !defined (FPREAL_UINT)
#define FPREAL_UINT 		unsigned long long
#define FPREAL_INT 			long long
#endif	// FPREAL_UINT

#include <cstdio>
#include <cstring>
#include <string>

namespace fpreal
{
  // version number
  static FPREAL_OPT_VAR unsigned short version = 1;
  	
  // supported precisions
#if __cplusplus<=199711L
  enum PRECISION
#else  
  enum PRECISION : const unsigned short int
#endif	// __cplusplus<=199711L 
  { 
	NONE = 0,				// integer
	REAL_1_DIG,				// real with 1 digit  right of the floating point
	REAL_2_DIG,				// real with 2 digits right of the floating point
	REAL_3_DIG,				// real with 3 digits right of the floating point
	REAL_4_DIG,			    // real with 4 digits right of the floating point
	REAL_5_DIG,			    // real with 5 digits right of the floating point
	REAL_6_DIG,			    // real with 6 digits right of the floating point
	REAL_7_DIG,			    // real with 7 digits right of the floating point
	REAL_8_DIG,			    // real with 8 digits right of the floating point
	REAL_9_DIG			    // real with 9 digits right of the floating point
  };

  // int types used for fixing and
  // biggest supported number: abs (10^(max_pow - PRECISION)) - 1 
#if __cplusplus<=199711L
  typedef FPREAL_UINT uint_t;
  typedef FPREAL_INT  int_t;
#else  
  using uint_t = FPREAL_UINT;
  using int_t = FPREAL_INT;
#endif	// __cplusplus<=199711L
  
  // biggest supported number: abs (10^(max_pow - PRECISION)) - 1 
  // used by range
  static FPREAL_OPT_VAR 
    unsigned short int max_pow = sizeof (int_t) == 16 ? 19 : 9;
  
  // converts double to string with specific precision
  static FPREAL_OPT_FUNC const char *
  double_format (const unsigned short int exp) noexcept
  {
    return 
      (exp ==  0) ? "%.0lf" :
      (exp ==  1) ? "%.1lf" :
      (exp ==  2) ? "%.2lf" : 
      (exp ==  3) ? "%.3lf" :
      (exp ==  4) ? "%.4lf" : 
      (exp ==  5) ? "%.5lf" :
      (exp ==  6) ? "%.6lf" : 
      (exp ==  7) ? "%.7lf" :
      (exp ==  8) ? "%.8lf" : 
      (exp ==  9) ? "%.9lf" : "%.0lf";
  }	  
  
  // calculate 10^exp
  static FPREAL_OPT_FUNC uint_t
  pow10 (const unsigned short int exp) noexcept
  {
    return 
      (exp ==  0) ? 1 :
      (exp ==  1) ? 10 :
      (exp ==  2) ? 100 : 
      (exp ==  3) ? 1000 :
      (exp ==  4) ? 10000 : 
      (exp ==  5) ? 100000 :
      (exp ==  6) ? 1000000 : 
      (exp ==  7) ? 10000000 :
      (exp ==  8) ? 100000000 : 
      (exp ==  9) ? 1000000000 : 0;
  }  
  
  // calculate 1/(10^exp)
  static FPREAL_OPT_FUNC double
  rpow10 (const unsigned short int exp) noexcept
  {
    return 
      (exp ==  0) ? 1.0 :
      (exp ==  1) ? 0.1 :
      (exp ==  2) ? 0.01 : 
      (exp ==  3) ? 0.001 :
      (exp ==  4) ? 0.0001 : 
      (exp ==  5) ? 0.00001 :
      (exp ==  6) ? 0.000001 : 
      (exp ==  7) ? 0.0000001 :
      (exp ==  8) ? 0.00000001 : 
      (exp ==  9) ? 0.000000001 : 
      (exp == 10) ? 0.0000000001 :
      (exp == 11) ? 0.00000000001 :
      (exp == 12) ? 0.000000000001 :
      (exp == 13) ? 0.0000000000001 :
      (exp == 14) ? 0.00000000000001 :
      (exp == 15) ? 0.000000000000001 :
      (exp == 17) ? 0.0000000000000001 :
      (exp == 18) ? 0.00000000000000001 : 0;
  }
  
  // convert double to string
  static void
  double_to_string (const PRECISION p, const double value, char *cstr)
  {
    sprintf (cstr, double_format (p), value);
  }
     
  // base class	
  class fpreal_t
  {
	public:
	  // constructor
	  FPREAL_OPT_FUNC fpreal_t (const PRECISION p) : 
        data (0), 
        sign (1.0f), 
        double_after_fixing(0.0), 
        string_before_fixing(""),
        string_after_fixing(""),
        numberValidation (true),
        data_precision (p) { }
      
      // get the precision
	  FPREAL_OPT_FUNC PRECISION precision (void) const noexcept
	  { 
        return 
          (data_precision == 1) ? RD1 : 
          (data_precision == 2) ? RD2 : 
          (data_precision == 3) ? RD3 : 
          (data_precision == 4) ? RD4 : 
          (data_precision == 5) ? RD5 : 
          (data_precision == 6) ? RD6 : 
          (data_precision == 7) ? RD7 : 
          (data_precision == 8) ? RD8 : 
          (data_precision == 9) ? RD8 : NONE;
      }  
	  
	  // get the fix real number as double 
	  double getDouble (void) const noexcept
	  {
		return double_after_fixing;
	  }

	  // // get the fix real number as std::string
	  std::string getString (void) const
	  {
        return std::string (string_after_fixing);	
      }
	  
	  // get the fixed number
	  // warning: doesn't work with std::printf
	  // use getDouble() and getString () instead  
#if __cplusplus>=201402L	  
	  auto get (void)
	  {
		struct result
		{
		  operator double() { return base->getDouble ();  }
          operator std::string() { return base->getString (); }
          fpreal_t *base;
	    };
        
        return result { this };
	  }
#else	  
	  inline double get () { return getDouble ();  }
#endif	// __cplusplus>=201402L	
   
	  // the absolute range
      FPREAL_OPT_FUNC double absolute_range () const
      {
        return 
	      static_cast <double> (pow10 (max_pow) - 1) * rpow10 (precision ());
      } 
      
      // initialize 
	  void initialize (const double &value);
	  void initialize (const std::string &value);
	  void initialize (const fpreal_t &real);
            	  
	  // overloaded operators
	  bool operator==(const fpreal_t &b);		// eq
	  bool operator!=(const fpreal_t &b);		// ne
	  bool operator<(const fpreal_t &b);		// lt
	  bool operator<=(const fpreal_t &b);		// lte
	  bool operator>(const fpreal_t &b);		// gt
	  bool operator>=(const fpreal_t &b);		// gte
	  
	  fpreal_t operator+(const fpreal_t &b); 	// add
	  fpreal_t operator+(const double b);
	  fpreal_t operator+(const std::string &b);	
	  fpreal_t operator+(const char *b); 	
	  	  
	  template <typename T> fpreal_t operator+=(const T &b); // +=
	  
	  fpreal_t operator++();					// ++
	  fpreal_t operator+=(const double b);
	  	  
	  fpreal_t operator-(const fpreal_t &b); 	// sub
	  fpreal_t operator-(const double b);
	  fpreal_t operator-(const std::string &b);	
	  fpreal_t operator-(const char *b); 	
	  
	  template <typename T> fpreal_t operator-=(const T &b); // -=
	  
	  fpreal_t operator--();					// --
	  fpreal_t operator-=(const double b);
	  
	  fpreal_t operator*(const fpreal_t &b); 	// mul
	  fpreal_t operator*(const double b);
	  fpreal_t operator*(const std::string &b);	
	  fpreal_t operator*(const char *b); 
	  
	  template <typename T> fpreal_t operator*=(const T &b); // *=
	  
	  fpreal_t operator/(const fpreal_t &b); 	// div
	  fpreal_t operator/(const double b);
	  fpreal_t operator/(const std::string &b);	
	  fpreal_t operator/(const char *b); 
	  
	  template <typename T> fpreal_t operator/=(const T &b); // /=
	  
	  fpreal_t operator()(const double b);		// ()
	  fpreal_t operator()(const std::string &b);
	  fpreal_t operator()(const char *b);
	  	  
	protected:  
	  // get the data
	  inline uint_t getData () const noexcept { return data; }
	        
	  // set initial value as double: the real number to be fixed
	  void set (const double value)
	  { 
		double_to_string (precision (), value, string_before_fixing);
	  } 

	  // set initial value as string: the real number to be fixed
	  void set (const std::string &value)
	  {
		std::strcpy (string_before_fixing, value.c_str ());
	  } 

	private: 
      uint_t 		  data;							// data of fixed point real number
	  double     	  sign;							// 1 for positive, -1 for negative
	  double          double_after_fixing;			// the double after the point fixing
	  char			  string_before_fixing[32];		// the string before the point fixing
	  char			  string_after_fixing[32];		// the string after the point fixing
      bool			  numberValidation;				// true if we have to call isValidNumber ()													
	  PRECISION 	  data_precision;				// the precision
	  	  
	  static FPREAL_OPT_VAR PRECISION 
	  // static const PRECISION
	    RD0 = NONE,
	    RD1 = REAL_1_DIG,
	    RD2 = REAL_2_DIG,
	    RD3 = REAL_3_DIG,
	    RD4 = REAL_4_DIG,
	    RD5 = REAL_5_DIG,
	    RD6 = REAL_6_DIG,
	    RD7 = REAL_7_DIG,
	    RD8 = REAL_8_DIG,
	    RD9 = REAL_9_DIG;
	  
	  // adjust precision: returns b.data adjusted for p 
	  inline uint_t adjust_precision (const fpreal_t &b, 
							          const PRECISION p) const
	  {
		return (b.precision () < p)  						?
				b.getData () * pow10 (p - b.precision ()) 	:
				b.getData ();  	
      }                                
	  
	  // compare a and b, returns (a<b)=-1, (a==b)=0 , (a>b)=1 
	  int_t compare (const fpreal_t &a, const fpreal_t &b) const;
	  
	  // fix the number
	  void fix (void);

      // the absolute value of range
      FPREAL_OPT_FUNC uint_t range () const noexcept
      { 
		return (pow10 (max_pow - precision ()) - 1); 
	  }
  };
  
  inline fpreal_t operator+(const double b, fpreal_t &a) { return a + b; }
  inline fpreal_t operator+(const std::string b, fpreal_t &a) { return a + b; }
  inline fpreal_t operator+(const char *b, fpreal_t &a) { return a + b; }
  inline fpreal_t operator-(const double b, fpreal_t &a) { return a - b; }
  inline fpreal_t operator-(const std::string b, fpreal_t &a) { return a - b; }
  inline fpreal_t operator-(const char *b, fpreal_t &a) { return a - b; }
  inline fpreal_t operator*(const double b, fpreal_t &a) { return a * b; }
  inline fpreal_t operator*(const std::string b, fpreal_t &a) { return a * b; }
  inline fpreal_t operator*(const char *b, fpreal_t &a) { return a * b; }
  inline fpreal_t operator/(const double b, fpreal_t &a) { return a / b; }
  inline fpreal_t operator/(const std::string b, fpreal_t &a) { return a / b; }
  inline fpreal_t operator/(const char *b, fpreal_t &a) { return a / b; }

// type macro: fpreal1_t, fpreal2_t etc
#define FPTYPE(prec) \
  class fpreal##prec##_t : public fpreal_t\
  {\
	public:\
	  template <typename T> fpreal##prec##_t (const T initial_value) : fpreal_t (REAL_##prec##_DIG) \
	  {\
		initialize (initial_value);\
	  } \
	  fpreal##prec##_t (void) : fpreal_t (REAL_##prec##_DIG)\
	  {\
		initialize (0.0f);\
	  }\
  };

  FPTYPE(1);
  FPTYPE(2);
  FPTYPE(3);
  FPTYPE(4);
  FPTYPE(5);
  FPTYPE(6);
  FPTYPE(7);
  FPTYPE(8);
  FPTYPE(9);
  
} // fpreal	
