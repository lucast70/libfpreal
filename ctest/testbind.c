#include "fpreal.h"
#include <stdio.h>

int
main ()
{
  cfpreal_t a, b;	
  char s[32];
  
  a = cfpreal_init (5);
  b = cfpreal_init (5);
  
  fprintf (stdout, "for number: 787.99878998 with precision 5\n");
  
  fprintf (stdout, "testing cfpreal_setString\n"); 
  cfpreal_setString (a, "787.99878998");
  
  fprintf (stdout, "testing cfpreal_getString: "); 
  cfpreal_getString (a, s);
  fprintf (stdout, "%s\n", s);
  
  fprintf (stdout, "testing cfpreal_setDouble\n"); 
  cfpreal_setDouble (a, 787.99878998);
  
  fprintf (stdout, "testing cfpreal_getDouble: "); 
  fprintf (stdout, "%f\n", cfpreal_getDouble (a));
  
  cfpreal_setDouble (a, 7.99878);
  cfpreal_setDouble (b, 1.28981);
  
  fprintf (stdout, "testing cfpreal_add: 7.99878 + 1.28981 = "); 
  fprintf (stdout, "%f\n", cfpreal_add (a, b));
  
  fprintf (stdout, "testing cfpreal_sub: 7.99878 - 1.28981 = "); 
  fprintf (stdout, "%f\n", cfpreal_sub (a, b));
  
  fprintf (stdout, "testing cfpreal_mul: 7.99878 * 1.28981 = "); 
  fprintf (stdout, "%f\n", cfpreal_mul (a, b));
  
  fprintf (stdout, "testing cfpreal_div: 7.99878 / 1.28981 = "); 
  fprintf (stdout, "%f\n", cfpreal_div (a, b));
}	
