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

/* Copyright © 2020 - 2021 Lucas Tsatiris. All rights reserved. */

#ifndef _FPREAL_H
#define _FPREAL_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{ 
  CFPREAL_0_DIG = 0,		/* integer */
  CFPREAL_1_DIG,			/* real with 1 digit  right of the floating point */
  CFPREAL_2_DIG,			/* real with 2 digits right of the floating point */
  CFPREAL_3_DIG,			/* real with 3 digits right of the floating point */
  CFPREAL_4_DIG,			/* real with 4 digits right of the floating point */
  CFPREAL_5_DIG,			/* real with 5 digits right of the floating point */
  CFPREAL_6_DIG,			/* real with 6 digits right of the floating point */
  CFPREAL_7_DIG,			/* real with 7 digits right of the floating point */
  CFPREAL_8_DIG,			/* real with 8 digits right of the floating point */
  CFPREAL_9_DIG				/* real with 9 digits right of the floating point */
} CFPREAL_PRECISION;

typedef void * cfpreal_t;

/* initialize a fixed point real number, on failure returns NULL.
   internally, we use c++ new so don't use free(3) over this */
extern cfpreal_t cfpreal_init (const CFPREAL_PRECISION p);

/* set value from string to fixed point real number,
   on invalid string sets real = 0.0 */
extern void cfpreal_setString (cfpreal_t real, const char *);

/* set value from double to fixed point real number */
extern void cfpreal_setDouble (cfpreal_t real, const double d);

/* get value of fixed point real number into string */
extern void cfpreal_getString (cfpreal_t real, char *str);

/* get value of fixed point real number into double */
extern double cfpreal_getDouble (cfpreal_t real);

/* destroy a fixed point real number */
extern void cfpreal_destroy (cfpreal_t real);

/* add a and b returning double */
extern double cfpreal_add (cfpreal_t a, cfpreal_t b);

/* returns a + b */
extern double cfpreal_add (cfpreal_t a, cfpreal_t b);

/* adds a and b into s, returning s */
extern char * cfpreal_add_str (cfpreal_t a, cfpreal_t b, char *s);

/* returns a - b */
extern double cfpreal_sub (cfpreal_t a, cfpreal_t b);

/* subtracts b from a into s, returning s */
extern char * cfpreal_sub_str (cfpreal_t a, cfpreal_t b, char *s);

/* returns a * b */
extern double cfpreal_mul (cfpreal_t a, cfpreal_t b);

/* multiplies a by b into s, returning s */
extern char * cfpreal_mul_str (cfpreal_t a, cfpreal_t b, char *s);

/* returns a / b, no fdiv check */
extern double cfpreal_div (cfpreal_t a, cfpreal_t b);

/* divides b by a into s, returning s, no fdiv check */
extern char * cfpreal_div_str (cfpreal_t a, cfpreal_t b, char *s);

/* returns -1 for a < b, 1 for a > b and 0 for a==b */
extern int cfpreal_cmp (cfpreal_t a, cfpreal_t b);

#ifdef __cplusplus
}
#endif

#endif 	/* _FPREAL_H */
