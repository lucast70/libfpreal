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

#include "fprealxx.h"

using namespace fpreal;

// overloaded operators 
// eq
bool 
fpreal_t::operator==(const fpreal_t &b)
{
  return (compare (*this, b) == 0) ? true : false;
}

// ne
bool 
fpreal_t::operator!=(const fpreal_t &b)
{
  return (compare (*this, b) == 0) ? false : true;
}

// lt
bool 
fpreal_t::operator<(const fpreal_t &b)
{
  return (compare (*this, b) < 0)  ? true : false;
}

// lte
bool 
fpreal_t::operator<=(const fpreal_t &b)
{
  return (compare (*this, b) < 1)  ? true : false;
}

// gt
bool 
fpreal_t::operator>(const fpreal_t &b)
{
  return (compare (*this, b) > 0)  ? true : false;
}

//gte
bool 
fpreal_t::operator>=(const fpreal_t &b)
{
  return (compare (*this, b) > -1)  ? true : false;
}

// add
fpreal_t
fpreal_t::operator+(const fpreal_t &b)
{
  const PRECISION p = (precision () < b.precision ()) ? b.precision (): precision ();
  
  const uint_t 
    itemp1 = adjust_precision (*this, p),
    itemp2 = adjust_precision (b, p);
  
  const double dtemp = 
    ((itemp1 * sign) + (itemp2 * b.sign )) * rpow10 (p);
  
  fpreal_t real (p);
  
  char stemp[64];
  double_to_string (p, dtemp, stemp);
  real.initialize (stemp);
  
  return real;

}

fpreal_t
fpreal_t::operator+(const double b) 
{
  fpreal_t real (precision ());
  
  real.initialize (b);
  
  return *this + real;	
}	

fpreal_t
fpreal_t::operator+(const std::string &b) 
{
  fpreal_t real (precision ());
  
  real.initialize (b);
  
  return *this + real;	
}	

fpreal_t
fpreal_t::operator+(const char *b) 
{
  return *this + std::string (b);	
}	

// +=
template <typename T> fpreal_t 
fpreal_t::operator+=(const T &b) 
{
  *this = (*this + b);
  return *this;
}	

// ++
fpreal_t 
fpreal_t::operator++()
{
  *this += 1;
  return *this;	
}	

fpreal_t 
fpreal_t::operator+=(const double b)
{
  *this = (*this + b);
  return *this;	
}

// sub
fpreal_t
fpreal_t::operator-(const fpreal_t &b) 
{
  const PRECISION p = (precision () < b.precision ()) ? b.precision (): precision ();

  const uint_t 
    itemp1 = adjust_precision (*this, p),
    itemp2 = adjust_precision (b, p);
  
  const double dtemp = 
    ((itemp1 * sign) - (itemp2 * b.sign )) * rpow10 (p);
  
  fpreal_t real (p);
  
  char stemp[64]; 
  double_to_string (p, dtemp, stemp);
  real.initialize (stemp);
  
  return real;
}

fpreal_t
fpreal_t::operator-(const double b) 
{
  fpreal_t real (precision ());
  
  real.initialize (b);
  
  return *this - real;	
}	

fpreal_t
fpreal_t::operator-(const std::string &b) 
{
  fpreal_t real (precision ());
  
  real.initialize (b);
  
  return *this - real;	
}	

fpreal_t
fpreal_t::operator-(const char *b) 
{
  return *this - std::string (b);	
}	

// -=
template <typename T> fpreal_t 
fpreal_t::operator-=(const T &b) 
{
  *this = *this - b;
  return *this;
}

// --
fpreal_t 
fpreal_t::operator--()
{
  *this -= 1;
  return *this;	
}	

fpreal_t 
fpreal_t::operator-=(const double b)
{
  *this = *this - b;
  return *this;	
}

// mul
fpreal_t
fpreal_t::operator*(const fpreal_t &b) 
{
  const PRECISION p = (precision () < b.precision ()) ? b.precision (): precision ();
  
  const uint_t 
    itemp1 = adjust_precision (*this, p),
    itemp2 = adjust_precision (b, p);

  const double dtemp = 
    ((itemp1 * sign) * (itemp2 * b.sign )) * rpow10 (p*2);

  fpreal_t real (p);

  char stemp[64];
  double_to_string (p, dtemp, stemp);
  real.initialize (stemp);
    
  return real;
}

fpreal_t
fpreal_t::operator*(const double b) 
{
  fpreal_t real (precision ());
  
  real.initialize (b);
  
  return *this * real;	
}	

fpreal_t
fpreal_t::operator*(const std::string &b) 
{
  fpreal_t real (precision ());
  
  real.initialize (b);
  
  return *this * real;	
}	

fpreal_t
fpreal_t::operator*(const char *b) 
{
  return *this * std::string (b);	
}	

// *=
template <typename T> fpreal_t 
fpreal_t::operator*=(const T &b) 
{
  *this = *this * b;
  return *this;
}

// div
fpreal_t
fpreal_t::operator/(const fpreal_t &b) 
{
  const PRECISION p = (precision () < b.precision ()) ? b.precision (): precision ();

  const uint_t 
    itemp1 = adjust_precision (*this, p),
    itemp2 = adjust_precision (b, p);
  
  const double 
    dtemp1 = itemp1 * sign,
    dtemp2 = itemp2 * b.sign;
  
  const double dtemp = dtemp1 / dtemp2;
  fpreal_t real (p);
  
  char stemp[64];
  double_to_string (p, dtemp, stemp);
  real.initialize (stemp);
  
  return real;
}

fpreal_t
fpreal_t::operator/(const double b) 
{
  fpreal_t real (precision ());
  
  real.initialize (b);
  
  return *this / real;	
}	

fpreal_t
fpreal_t::operator/(const std::string &b) 
{
  fpreal_t real (precision ());
  
  real.initialize (b);
  
  return *this / real;	
}	

fpreal_t
fpreal_t::operator/(const char *b) 
{
  return *this / std::string (b);	
}	

// /=
template <typename T> fpreal_t 
fpreal_t::operator/=(const T &b) 
{
  *this = *this / b;
  return *this;
}

// ()
fpreal_t 
fpreal_t::operator()(const double b)
{
  fpreal_t real (precision ());
  
  real.initialize (b);
  return real;	
}	

fpreal_t 
fpreal_t::operator()(const std::string &b)
{
  fpreal_t real (precision ());
  
  real.initialize (b);
  return real;	
}

fpreal_t 
fpreal_t::operator()(const char *b)
{
  fpreal_t real (precision ());
  
  real.initialize (std::string (b));
  return real;	
}


