## Ellipse-Ellipse overlap area:
This program calculates the overlapping area of two arbitrary ellipses. It implements
the algorithm published in this [paper](http://link.springer.com/article/10.1007%2Fs00791-013-0214-3). See also the available [preprint](http://arxiv.org/abs/1106.3787).



### Usage: 
- compile the code:
`make`

This should produce an executable (overlap)
- run the executable with an input-file:
> ./overlap inputfile id

(`id` is 1 or 2 to choose between two different quartic solversc)
- This should produce two output-files:
	- **result-File**: The naming is in this form `results_Day_Month_Year_Hour_Min_Second.txt`
	- **root-File**: The naming is in this form `roots_Day_Month_Year_Hour_Min_Second.txt`

### Contents and Formats of files: 
- the **input-File** should be in the following format

`id A1 B1 H1 K1 PHI_1 A2 B2 H2 K2 PHI_2`

(11 columns)

`id` is a running number, `Ax`  and `Bx` are semi-axes of the one ellipse with the center coordinates `(Hx, Kx)` and the inclination with respect to the x-axis `Phi_x` _(x in {1, 2})_

- **results-File** is in the following format: 

`id area-Ellipse1 (=pi.A1.B1) areaEllipse2 (=pi.A2.B2) OverlapAreaAnalytical OverlapAreaPolynomial rel_err`

- **roots-File** contains the coordinates of the intersection points (if any):

`id x0 y0 x1 y1 x2 y2 ...`

this file is used by the plot-script (`plot.py`)

### How to visualize the results: 
> python plot.py inputFile rootsFile resultsFile

That would produce in the directory **./cases/** a couple of  png's

### Requirements:
- > [GSL](http://www.gnu.org/software/gsl/): to solve the quartic equations 
- _(optional)_ > [Boost.polygon](http://www.boost.org/doc/libs/1_54_0/libs/polygon/doc/index.htm): to compare the results of this code, 
the overlap-area of polygonized ellipses is calculated with Boost.polygon.

###Remarks:

The solver of the quartic function is the central part of the code. Actually, two different solvers are used separatly: 
- [gsl_poly_complex_solve()](http://linux.math.tifr.res.in/manuals/html/gsl-ref-html/gsl-ref_6.html) from GSL,
- and [gsl_poly_complex_solve_quartic()](http://www.network-theory.co.uk/download/gslextras/Quartic/00README.txt) from Andrew Steiner.          

The second one is faster, however fails to calculate accuratly the roots of [test_5](test5.txt)..
