#include <stdio.h>
#include <math.h>
#include "timer.h"




double pi_leibniz (int n);                                                // calling on the functions that have been written elsewhere//
double pi_bbp (int n);                                                     
int adjust_rep_count (int count, double time, double tmin, double tmax);  // calling on supplies counter for timing the functions//

int
main (void)
{
  double pi;
  double minerr = 0.000001, abserr; // sets that minimum error allowed for the program//
  int i;
  int ileibniz, ibbp;

  i = 1;
  do
    {
      pi = pi_leibniz (i);
      abserr = fabs (pi - M_PI);                     //Loop is calculating the abs error of the leibniz function//
      printf ("%8d %20.15f %20.15f\n", i, pi, abserr);
      i *= 2;
    }
  while (abserr > minerr);
  ileibniz = i / 2;  // Since we double the iterations above we need to divide by 2//

  printf ("ileibniz = %8d\n", ileibniz);

  i = 1;
  do
    {
      pi = pi_bbp (i);
      abserr = fabs (pi - M_PI);              //Performs the same process as above for the BBP series//
      printf ("%8d %20.15f %20.15f\n", i, pi, abserr);
      i *= 2;
    }
  while (abserr > minerr);
  ibbp = i / 2;

  printf ("ibbp = %8d\n \n \n", ibbp);

  double time, time1, time2;
  int j;                      // initializing the variables that I need for the timer function//
  double tmax = 2.;
  double tmin = 1.;
  int count = 1000;

  printf ("Timing the BBP Series Method:\n\n");
  printf ("   Time/Iteration    Total Time      Iterations\n");

  do
    {
      timer_start ();

      for (j = 0; j < count; j++)                // Measure the time per function call of the BBP function//
	{
	  pi_bbp (ibbp);
	}
      time = timer_stop ();

      time1 = time / count;
      printf (" %10.2f usec         %10.6f sec      %10d\n", time1 * 1.e6,
	      time, count);
      count = adjust_rep_count (count, time, tmin, tmax);
    }
  while ((time > tmax) || (time < tmin));   // Loop will continue to run as long as the time per function call is within set limits//

  printf ("\n\n");

  count = 1000;

  printf ("Timing the Leibniz Series Method:\n\n");
  printf ("   Time/Iteration          Total Time           Iterations\n");

  do
    {
      timer_start ();

      for (j = 0; j < count; j++)     // Same as above but now for the leibniz function//
	{
	  pi_leibniz (ileibniz);
	}

      time = timer_stop ();

      time2 = time / count;
      printf (" %10.2f usec         %10.6f sec      %10d\n", time2 * 1.e6,
	      time, count);
      count = adjust_rep_count (count, time, tmin, tmax);
    }
  while ((time > tmax) || (time < tmin));
  printf ("\n\n");

  double trate = time2 / time1; // Lastly we want the time ration of the two functions//

  printf ("Ratio of Time: %10.2f\n\n", trate);

  return 0;
}
