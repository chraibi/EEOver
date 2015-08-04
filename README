Ellipse-Ellipse overlap area: Calculte the overlaping area of two arbitrary ellipses. This code implements
the algorithm published here
http://arxiv.org/abs/1106.3787


Usage: 
1) compile the code: make. This should produce an executable (overlap) 
2) run the executable with an inputfile: ./overlap inputfile 
3) two output files are produced: 
   3.1) resultFile: results_Day_Month_Year_Hour_Min_Second.txt 
   3.2) rootFile: roots_Day_Month_Year_Hour_Min_Second.txt

Formats of files: 
1) the inputFile should be in the following format id A1 B1 H1 K1 PHI_1 A2 B2 H2 K2 PHI_2 (11 columns)
2) resultsFile: id areaEllipse1 (=pi.A.B) areaEllipse2 (=pi.A.B) OverlapAreaAnalytical OverlapAreaPolynomial err 
3) rootsFile: #roots: id x0 y0 x1 y1 x2 y2 ... 
this file is used by the plot-script (plot.py)

How to plot the results: 
python plot.py inputFile rootsFile
That would produce in the directory ./cases/ a couple of  png's

Requirements: 
1) GSL: to solve the quartic equations 
2) (optional) Boost.polygon: to compare the results of this code, 
the overlap-area of polygonized ellipses is calculated with Boost.polygon.


