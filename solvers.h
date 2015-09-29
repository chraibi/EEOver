#include <gsl/gsl_math.h>
#include <gsl/gsl_test.h>
#include <gsl/gsl_ieee_utils.h>
#include <gsl/gsl_poly.h>


/* Solve for real or complex roots of the quartic equation
 * x^4 + a x^3 + b x^2 + c x + d = 0,
 * returning the number of such roots.
 *
 * Roots are returned ordered.
 * Author: Andrew Steiner
 */
int gsl_poly_solve_quartic (double a, double b, double c, double d,
			double * x0, double * x1,
			double * x2, double * x3);

 /* Solve for the complex roots of a general real polynomial */
int gsl_poly_complex_solve_quartic(double a, double b, double c, double d,
			       gsl_complex * z0, gsl_complex * z1,
			       gsl_complex * z2, gsl_complex * z3);
//---------------------------------------------------------------------------

int SolveQuadric(double c[ 3 ], double s[ 2 ] );
int SolveCubic( double c[ 4 ], double s[ 3 ] );
int SolveQuartic(double c[ 5 ], double s[ 4 ] );

//---------------------------------------------------------------------------
//-- functions for solving the quartic equation from Netlib/TOMS
void BIQUADROOTS (double p[], double r[][5]);
void CUBICROOTS (double p[], double r[][5]);
void QUADROOTS (double p[], double r[][5]);
//---------------------------------------------------------------------------

double nointpts (double A1, double B1, double A2, double B2, double H1, 
                 double K1, double H2, double K2, double PHI_1, double PHI_2,
                 double H2_TR, double K2_TR, double AA, double BB, 
                 double CC, double DD, double EE, double FF, int *rtnCode);

double twointpts (double xint[], double yint[], double A1, double B1, 
                  double PHI_1, double A2, double B2, double H2_TR, 
                  double K2_TR, double PHI_2, double AA, double BB, 
                  double CC, double DD, double EE, double FF, int *rtnCode);

double threeintpts (double xint[], double yint[], double A1, double B1, 
                    double PHI_1, double A2, double B2, double H2_TR, 
                    double K2_TR, double PHI_2, double AA, double BB, 
                    double CC, double DD, double EE, double FF,
                    int *rtnCode);

double fourintpts (double xint[], double yint[], double A1, double B1, 
                   double PHI_1, double A2, double B2, double H2_TR, 
                   double K2_TR, double PHI_2, double AA, double BB, 
                   double CC, double DD, double EE, double FF, int *rtnCode);

int istanpt (double x, double y, double A1, double B1, double AA, double BB,
             double CC, double DD, double EE, double FF);

double ellipse2tr (double x, double y, double AA, double BB, 
                   double CC, double DD, double EE, double FF);

//===========================================================================
//== ELLIPSE-ELLIPSE OVERLAP ================================================
//===========================================================================
//choice=1: use gsl_poly_complex_solve()
//choice=2: use Andrew Steiner's gsl_poly_complex_solve_quartic()
double ellipse_ellipse_overlap_gsl(double PHI_1, double A1, double B1, 
                                double H1, double K1, double PHI_2, 
                                double A2, double B2, double H2, double K2,
                                double X[4], double Y[4], int * NROOTS,
                                int *rtnCode, int choice);


double ellipse_ellipse_overlap_netlibs(double PHI_1, double A1, double B1, 
                                double H1, double K1, double PHI_2, 
                                double A2, double B2, double H2, double K2,
                                double X[4], double Y[4], int * NROOTS,
                                int *rtnCode);

double ellipse_ellipse_overlap_gems(double PHI_1, double A1, double B1, 
                                double H1, double K1, double PHI_2, 
                                double A2, double B2, double H2, double K2,
                                double X[4], double Y[4], int * NROOTS,
                                int *rtnCode);


int double_cmp(const void *a, const void *b) ;
