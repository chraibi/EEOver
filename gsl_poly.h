#include <gsl/gsl_math.h>
#include <gsl/gsl_test.h>
#include <gsl/gsl_ieee_utils.h>
#include <gsl/gsl_poly.h>


/* Solve for real or complex roots of the quartic equation
 * x^4 + a x^3 + b x^2 + c x + d = 0,
 * returning the number of such roots.
 *
 * Roots are returned ordered.
 */
int
gsl_poly_solve_quartic (double a, double b, double c, double d,
			double * x0, double * x1,
			double * x2, double * x3);

int
gsl_poly_complex_solve_quartic(double a, double b, double c, double d,
			       gsl_complex * z0, gsl_complex * z1,
			       gsl_complex * z2, gsl_complex * z3);

 /* Solve for the complex roots of a general real polynomial */
 
 // typedef struct 
