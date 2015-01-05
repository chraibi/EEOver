//===========================================================================
//== INCLUDE ANSI C SYSTEM HEADER FILES =====================================
//===========================================================================
#include <math.h>	//-- for calls to trig, sqrt and power functions
// #include <iostream>

//#include <math>	//-- for calls to trig, sqrt and power functions

//==========================================================================
//== DEFINE PROGRAM CONSTANTS ==============================================
//==========================================================================
#define NORMAL_TERMINATION		     	      0
#define NO_INTERSECTION_POINTS				100
#define ONE_INTERSECTION_POINT				101
#define LINE_TANGENT_TO_ELLIPSE				102
#define DISJOINT_ELLIPSES	    			103
#define ELLIPSE2_OUTSIDETANGENT_ELLIPSE1	104
#define ELLIPSE2_INSIDETANGENT_ELLIPSE1 	105
#define ELLIPSES_INTERSECT	    			106
#define TWO_INTERSECTION_POINTS				107
#define THREE_INTERSECTION_POINTS  			108
#define FOUR_INTERSECTION_POINTS  			109
#define ELLIPSE1_INSIDE_ELLIPSE2  			110
#define ELLIPSE2_INSIDE_ELLIPSE1  			111
#define ELLIPSES_ARE_IDENTICAL    			112
#define INTERSECTION_POINT					113
#define TANGENT_POINT						114

#define ERROR_ELLIPSE_PARAMETERS     	   -100
#define ERROR_DEGENERATE_ELLIPSE		   -101
#define ERROR_POINTS_NOT_ON_ELLIPSE   	   -102
#define ERROR_INVERSE_TRIG                 -103
#define ERROR_LINE_POINTS                  -104
#define ERROR_QUARTIC_CASE		   		   -105
#define ERROR_POLYNOMIAL_DEGREE  		   -107
#define ERROR_POLYNOMIAL_ROOTS   		   -108
#define ERROR_INTERSECTION_PTS   		   -109
#define ERROR_CALCULATIONS				   -112

#define EPS     	   				   +1.0E-05
#define pi     (2.0*asin (1.0))	//-- a maximum-precision value of pi
#define twopi  (2.0*pi)     	//-- a maximum-precision value of 2*pi
