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
#include "fpreal.h"

#include <memory>
#include <iostream>

using namespace fpreal;

extern "C" cfpreal_t 
cfpreal_init (const CFPREAL_PRECISION p)
{
  fpreal_t *r = new (std::nothrow) fpreal_t (static_cast <PRECISION> (p));
  return static_cast <cfpreal_t> (r);
}	

extern "C" void 
cfpreal_setString (cfpreal_t real, const char *str)
{
  fpreal_t *r = reinterpret_cast <fpreal_t *> (real);
  
  try
  {
    r->initialize (std::string (str));
  }
  catch (const std::runtime_error &) 
  {
	r->initialize (std::string ("0"));    
  }	
}

extern "C" void 
cfpreal_setDouble (cfpreal_t real, const double d)
{
  fpreal_t *r = reinterpret_cast <fpreal_t *> (real);
  
  try
  {
    r->initialize (d);
  }
  catch (const std::runtime_error &) 
  {
	r->initialize (std::string ("0"));    
  }	
}	

extern "C" void
cfpreal_getString (cfpreal_t real, char *str)
{
  fpreal_t *r = reinterpret_cast <fpreal_t *> (real);
  std::strcpy (str, r->getString ().c_str ());	
}	

extern "C" double
cfpreal_getDouble (cfpreal_t real)
{
  fpreal_t *r = reinterpret_cast <fpreal_t *> (real);
  return r->getDouble ();
}

extern "C" void
cfpreal_destroy (cfpreal_t real)
{
  delete (static_cast<fpreal_t *> (real));
}

extern "C" double
cfpreal_add (cfpreal_t a, cfpreal_t b)
{
  return (*(static_cast<fpreal_t *> (a)) + *(static_cast<fpreal_t *> (b))).getDouble ();
}

extern "C" char *
cfpreal_add_str (cfpreal_t a, cfpreal_t b, char *s)
{
  strcpy (s, 
         (*(static_cast<fpreal_t *> (a)) + *(static_cast<fpreal_t *> (b))).getString ().c_str ());
  return s;       
}

extern "C" double
cfpreal_sub (cfpreal_t a, cfpreal_t b)
{
  return (*(static_cast<fpreal_t *> (a)) - *(static_cast<fpreal_t *> (b))).getDouble ();
}

extern "C" char *
cfpreal_sub_str (cfpreal_t a, cfpreal_t b, char *s)
{
  strcpy (s, 
         (*(static_cast<fpreal_t *> (a)) - *(static_cast<fpreal_t *> (b))).getString ().c_str ());
  return s;       
}

extern "C" double
cfpreal_mul (cfpreal_t a, cfpreal_t b)
{
  // return (*(static_cast<fpreal_t *> (a)) * *(static_cast<fpreal_t *> (b))).getDouble ();
  return (*(static_cast<fpreal_t *> (a)) * *(static_cast<fpreal_t *> (b))).getDouble ();
}

extern "C" char *
cfpreal_mul_str (cfpreal_t a, cfpreal_t b, char *s)
{
  strcpy (s, 
         (*(static_cast<fpreal_t *> (a)) * *(static_cast<fpreal_t *> (b))).getString ().c_str ());
  return s;       
}

extern "C" double
cfpreal_div (cfpreal_t a, cfpreal_t b)
{
  return (*(static_cast<fpreal_t *> (a)) / *(static_cast<fpreal_t *> (b))).getDouble ();
}

extern "C" char *
cfpreal_div_str (cfpreal_t a, cfpreal_t b, char *s)
{
  strcpy (s, 
         (*(static_cast<fpreal_t *> (a)) / *(static_cast<fpreal_t *> (b))).getString ().c_str ());
  return s;       
}

extern "C" int 
cfpreal_cmp (cfpreal_t a, cfpreal_t b)
{
  if (*(static_cast<fpreal_t *> (a)) < *(static_cast<fpreal_t *> (b))) 
    return -1;
  else
  if (*(static_cast<fpreal_t *> (a)) > *(static_cast<fpreal_t *> (b))) 
    return 1;
  
  return 0;  
}	

