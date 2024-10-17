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

#include <cstdlib>
#include <stdexcept>

#ifdef FPREAL_DEBUG
#include <iostream>
#endif // DEBUG

using namespace fpreal;

// fast and furious ANSI C89 implementation
static bool
isValidNumber (const char *val)
{
  if (*val == 0)
    return true;

  if (!isdigit (*val))
    if (!((*val == '+') | (*val == '-') | (*val == '.')))
      return false;

  int decimal_point_counter = 0;
  if (*val == '.')
    decimal_point_counter ++;

  val ++;
  while (*val != 0)
  {
    if (!isdigit (*val) && *val != '.')
      return false;

    if (*val == '.')
      decimal_point_counter ++;

    if (decimal_point_counter > 1)
      return false;

    val ++;
  }

  return true;
}

// fix the real number
void
fpreal_t::fix (void)
{
  const char *n = string_before_fixing;

  if (numberValidation)
    if (!isValidNumber (n))
      throw std::runtime_error ("libfpreal: string contains invalid number");

  numberValidation = false;

  double temp1 = std::strtod (n, nullptr) * pow10 (precision ());

  sign = (temp1 < 0.0) ? -1.0 : 1.0;

  temp1 *= sign;

  if (temp1 > absolute_range ())
    throw std::range_error ("libfpreal: out of range");

  data = static_cast<uint_t> (temp1);

  // round the last digit
  temp1 -= data;
  temp1 *= 10;
  if (temp1 > 5)
    data += 1;

  double_after_fixing =
    static_cast <double> (data) *  rpow10 (precision ()) * sign;

  double_to_string (precision (), double_after_fixing, string_after_fixing);
}

// initialize
void
fpreal_t::initialize (const double &value)
{
  numberValidation = false;
  set (value);
  fix ();
}

void
fpreal_t::initialize (const std::string &value)
{
  numberValidation = true;
  set (value);
  fix ();
}

// initializer for assignment with automatic casting (copy constructor)
void
fpreal_t::initialize (const fpreal_t &real)
{
  numberValidation = false;
  set (real.string_before_fixing);
  fix ();
}

// compare a and b, returns -1 for (a<b), 0 for (a==b), 1 for (a>b)
int_t
fpreal_t::compare (const fpreal_t &a, const fpreal_t &b) const
{
  if (a.precision () == b.precision ())
    return (a.data * a.sign) - (b.data * b.sign);

  const PRECISION ap = a.precision (), bp = b.precision ();

  const uint_t temp =
    (ap < bp) 						?
    a.data * pow10 (bp - ap) 		:
    b.data * pow10 (ap - bp);

  return
    (ap < bp)								?
    (temp * a.sign) - (b.data * b.sign)		:
    (a.data * a.sign) - (temp * b.sign);
}
