## Ellipse-Ellipse overlap area:
This program calculats the overlaping area of two arbitrary ellipses. It implements
the algorithm published in this [paper](http://link.springer.com/article/10.1007%2Fs00791-013-0214-3)  [preprint](http://arxiv.org/abs/1106.3787).



### Usage: 
- compile the code:
`make`

This should produce an executable (overlap)
- run the executable with an inputfile:
> ./overlap inputfile

- This should produce two output-files:
	- **resultFile**: The naming is in this form `results_Day_Month_Year_Hour_Min_Second.txt`
	- **rootFile**: The naming is in this form `roots_Day_Month_Year_Hour_Min_Second.txt`

### Contents and Formats of files: 
- the **inputFile** should be in the following format

`id A1 B1 H1 K1 PHI_1 A2 B2 H2 K2 PHI_2`

(11 columns)

`id` is a running number, `Ax`  and `Bx` are semi-axes of the one ellipse with the center coordinates `(Hx, Kx)` and the inclination with respect to the x-axis `Phi_x` _(x in {1, 2})_

- **resultsFile** is in the following format: 

`id areaEllipse1 (=pi.A1.B1) areaEllipse2 (=pi.A2.B2) OverlapAreaAnalytical OverlapAreaPolynomial rel_err`

- **rootsFile** contains the coordinates of the intersection points (if any):

`id x0 y0 x1 y1 x2 y2 ...`

this file is used by the plot-script (`plot.py`)

### How to visualize the results: 
> python plot.py inputFile rootsFile

That would produce in the directory **./cases/** a couple of  png's

### Requirements:
- > [GSL](http://www.gnu.org/software/gsl/): to solve the quartic equations 
- _(optional)_ > [Boost.polygon](http://www.boost.org/doc/libs/1_54_0/libs/polygon/doc/index.htm): to compare the results of this code, 
the overlap-area of polygonized ellipses is calculated with Boost.polygon.


