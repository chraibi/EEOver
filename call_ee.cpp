
#include <stdio.h>
#include <iostream>
#include <string.h>


#define USING_BOOST 1   // change this to 0 if boost is not installed


#if defined(_WIN64) || defined(_WIN32)
    #include<time.h>
#else
    #include <sys/time.h>
#endif


#if USING_BOOST 
  #include <boost/geometry.hpp>
  #include <boost/geometry/geometries/point_xy.hpp>
  #include <boost/geometry/geometries/polygon.hpp>
  #include <boost/foreach.hpp>
  #include <boost/geometry/geometries/adapted/c_array.hpp>
  typedef boost::geometry::model::d2::point_xy<double,        
                                             boost::geometry::cs::cartesian> point_2d;
  typedef boost::geometry::model::polygon<point_2d> polygon_2d;
  using namespace boost::geometry;
  const int n = 20;
#endif

#include "solvers.h"
#include "program_constants.h"	//-- error message codes and constants

int output = GSL; //output only GSL or TOMS

//putting current date in a filename
//http://stackoverflow.com/questions/5138913/c-putting-current-date-in-a-filename
void  setFileName(char * name)
{  
    // time_t now;
    // struct tm *today;  
    // char date[9];
    // //get current date  
    // time(&now);  
    // today = localtime(&now);
    //print it in DD_MM_YY_H_M_S format.
   
    // strftime(date, 25, "%d_%m_%Y_%H_%M_%S", today);
    // strcat(name, "_");
    // strcat(name, date);
    strcat(name, ".txt");
    printf("name: %s\n", name);
}

//convert ellipse to polygon
#if USING_BOOST
int ellipse2poly(float PHI_1, float A1, float B1, float H1, float K1, polygon_2d * po)
{
    //using namespace boost::geometry;
    polygon_2d  poly;
    
    float xc = H1;
    float yc = K1;
    float a = A1;
    float b = B1;
    float w = PHI_1;
    //	----
    if(!n)
    {
        std::cout << "error ellipse(): nshould be >0\n" <<std::endl;
        return 0;
    }
    float t = 0;
    int i = 0;
    double coor[n*2+1][2];
  
    double x, y;
    float step = pi/n;
    float sinphi = sin(w);
    float cosphi = cos(w);
    // std::cout << "step: " << step << "  sin=  " << sinphi << "  cos= " << cosphi << std::endl;
    for(i=0; i<2*n+1; i++)
    {   
        x = xc + a*cos(t)*cosphi - b*sin(t)*sinphi;
        y = yc + a*cos(t)*sinphi + b*sin(t)*cosphi;
        if(fabs(x) < 1e-4) x = 0;
        if(fabs(y) < 1e-4) y = 0;

        coor[i][0] = x;
        coor[i][1] = y;
        t += step;
        // std::cout << "x=  " << x << " | y= " << y << std::endl;
    }

    assign_points(poly, coor);
    correct(poly);
    *po = poly;
    return 1;
}

// overlaping area of two polygons
float getOverlapingAreaPoly(polygon_2d poly, polygon_2d poly2)
{
    float overAreaPoly = 0.0;    
    std::deque<polygon_2d> output;
    bool ret = boost::geometry::intersection(poly, poly2, output);
    if(!ret) {
         std::cout << "Could not calculate the overlap of the polygons\n";
         exit(-1);
    }
    // int i = 0;
    BOOST_FOREACH(polygon_2d const& p, output)
    {
        overAreaPoly = boost::geometry::area(p);
        // std::cout << i++ << ": " << std::endl;
    }
    return overAreaPoly;
}
#endif

// real timestamping
double get_time(void)
{
    struct timeval stime;
    gettimeofday (&stime, (struct timezone*)0);
    return (stime.tv_sec+((double)stime.tv_usec)/1000000);
}

int main (int argc, char ** argv) 
{
    double A1, B1, H1, K1, PHI_1;
    double A2, B2, H2, K2, PHI_2;
    double area[5] = {0,0,0,0,0}; 
    int rtn[5] = {0,0,0,0,0};
    if (argc < 3)
    {
        printf("Usage: %s inputfile choice (1 || 2)\n exit...\n", argv[0]);
        exit(-1);
    }
    int choice;
    // choice = 1 -> use gsl_poly_complex_solve()
    // choice = 2 -> gsl_poly_complex_solve_quartic()
    choice = atoi(argv[2]);
    printf ("Calling ellipse_ellipse_overlap.c\n\n");

    int MAXITER = 1, i; //MAXITER: to compare the run-time of poly- and analytical solution.
    double t_end[5] = {0,0,0,0,0}; 
    double t_start[5] = {0,0,0,0,0};
    float times[5] = {0,0,0,0,0};
#if USING_BOOST
    polygon_2d poly, poly2;
    float eps = 0.0001, err[5] = {0,0,0,0,0};
    float meanErr[5] = {0,0,0,0,0};
#endif


    //float Re, Rp, Oe, Op;	

    char inputFile[100] = "";
    strcpy(inputFile,argv[1]);//"testcases.txt"; 
    char resultFile[100] = "results";
    setFileName(resultFile);
    printf("resultFile = <%s>\n", resultFile);

    char rootsFile[100] = "roots";
    setFileName(rootsFile);
    printf("rootsFile = <%s>\n", rootsFile);

    FILE * f;  // inputFile
    FILE * gf; // resultFile
    FILE * hf; // rootsFile
    int isc, id;
    int counter = 0;

    for(i=0;i<MAXITER;i++)
    {
        f = fopen(inputFile, "r");
        gf = fopen(resultFile, "w");
        fprintf(gf, "# id  areaEllipse1(pi.A.B)  areaEllipse2(pi.A.B)  OverlapAreaAnalytical  OverlapAreaPolynomial  err\n");
        hf = fopen(rootsFile, "w");
        if(f == NULL)
        {
            printf(">>>>>>>>> can not open file %s <<<<<<<<<<<\n", inputFile);
            exit(0);
        }
        if(gf == NULL)
        {
            printf(">>>>>>>>> can not open file %s <<<<<<<<<<<\n", resultFile);
            exit(0);
        }       
        if(hf == NULL)
        {
            printf(">>>>>>>>> can not open file %s <<<<<<<<<<<\n", rootsFile);
            exit(0);
        }
        int convert_to_radian = 0;
        //char dummy[255];
        // the file starts with this line: #id A1 B1 H1 K1 PHI_1 A2 B2 H2 K2 PHI_2
        //fgets(dummy, 255, f); //ignore first line. depends on file      
        fprintf(hf, "#roots: id x0 \ty0 \tx1 \ty1  x2 \ty2 ...\n");
        //fprintf(gf, "#no\t area_1\t\t area_2\t\t area_ellipse\t area_polygon\t err\n");
        double x_gsl[4], y_gsl[4];
        double x_toms[4], y_toms[4];
        double x_gems[4], y_gems[4];
        int nroots_gsl, nroots_toms, nroots_gems;

        
        while (1){
            isc = fscanf(f,"%d %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf",&id, &A1, &B1, &H1, &K1, &PHI_1, &A2, &B2, &H2, &K2, &PHI_2); 
            
            if(isc != 11){
                  printf("read end of line (isc=%d | counter=%d)\n", isc, counter);
                break;
            }
            // printf("id=%d,  A1=%f,  B1=%f,  H1=%f,  K1=%f,  PHI_1=%f,  A2=%f,  B2=%f,  H2=%f,  K2=%f,  PHI_2=%f\n",id, A1, B1, H1, K1, PHI_1, A2, B2, H2, K2, PHI_2);
            /////////////////////////////////////////////////////////////////////////
            if(convert_to_radian)
            {
                PHI_1 = PHI_1 *180.0/pi;
                PHI_2 = PHI_2 *180.0/pi;
            }

//======================== Using GSL ====================
            t_start[GSL] = get_time();
            area[GSL] = ellipse_ellipse_overlap_gsl (PHI_1, A1, B1, H1, K1,
                                            PHI_2, A2, B2, H2, K2, x_gsl, y_gsl, &nroots_gsl, &rtn[GSL], choice);
            t_end[GSL] = get_time();
            times[GSL] += (t_end[GSL] - t_start[GSL])*1000;
//======================== Using TOMS ====================
            t_start[TOMS] = get_time();
            area[TOMS] = ellipse_ellipse_overlap_netlibs (PHI_1, A1, B1, H1, K1,
                                            PHI_2, A2, B2, H2, K2, x_toms, y_toms, &nroots_toms, &rtn[TOMS]);
            t_end[TOMS] = get_time();
            times[TOMS] += (t_end[TOMS] - t_start[TOMS])*1000;
//======================== Using GEMS ====================
            t_start[GEMS] = get_time();
            area[GEMS] = ellipse_ellipse_overlap_gems (PHI_1, A1, B1, H1, K1,
                                            PHI_2, A2, B2, H2, K2, x_gems, y_gems, &nroots_gems, &rtn[GEMS]);
            t_end[GEMS] = get_time();
            times[GEMS] += (t_end[GEMS] - t_start[GEMS])*1000;
//========================================================


#if USING_BOOST
            ellipse2poly(PHI_1, A1, B1, H1, K1, &poly);
            ellipse2poly(PHI_2, A2, B2, H2, K2, &poly2);
            t_start[BOOST] = get_time();
            area[BOOST] = getOverlapingAreaPoly(poly, poly2);
            t_end[BOOST] = get_time();
            times[BOOST] += (t_end[BOOST] - t_start[BOOST])*1000;
//========================================================
            err[GSL] = (fabs(area[GSL])<eps)?fabs(area[BOOST]): fabs (area[BOOST]-area[GSL])/area[GSL];
            meanErr[GSL] += err[GSL];
//========================================================
            err[TOMS] = (fabs(area[TOMS])<eps)?fabs(area[BOOST]) : fabs(area[BOOST]-area[TOMS])/area[TOMS];
            meanErr[TOMS] += err[TOMS];
//========================================================
            err[GEMS] = (fabs(area[GEMS])<eps)?fabs(area[BOOST]) : fabs(area[BOOST]-area[GEMS])/area[GEMS];
            meanErr[GEMS] += err[GEMS];
//========================================================
#endif
            counter++;

            // output roots
            fprintf(hf, " %d ",id);
            if(output==GSL)
            {
                  for(i=0; i<nroots_gsl; i++)
                        fprintf(hf, "  %f  %f  ", x_gsl[i], y_gsl[i]);
                  fprintf(hf, "\n");

            }
            else if (output == TOMS){

                  for(i=0; i<nroots_toms; i++)
                        fprintf(hf, "  %f  %f  ", x_toms[i], y_toms[i]);
                  fprintf(hf, "\n");

            }



            //output results

#if USING_BOOST
            fprintf(gf, "%d    %10.4f    %10.4f    %10.4f    %10.4f    %10.4f\n", id, pi*A1*B1, pi*A2*B2, area[output], area[BOOST], err[output]);
#else
            fprintf(gf, "%d    %10.4f    %10.4f    %10.4f    %10.4f    %10.4f\n", id, pi*A1*B1, pi*A2*B2, area[output], -1., -1.);
#endif
            // printf("------------------------------------------\n");
            // printf ("Case %d: PolyArea  = %1.8f\n", id, area[BOOST]);
            // printf ("\tarea_gsl  = %8.8f, ret = %3d, err = %3f\n", area[GSL], rtn[GSL], err[GSL]);
            // printf ("\tarea_toms = %8.8f, ret = %3d, err = %3f\n", area[TOMS], rtn[TOMS], err[TOMS]);
            // printf ("\tarea_gems = %8.8f, ret = %3d, err = %3f\n", area[GEMS], rtn[GEMS], err[GEMS]);
            
            //printf("=====================================================================================\n");
                    
            ////////////////////////////////////////////////////////////////////////
                    
        }//while
		
	fclose(f);
        fclose(gf);
        fclose(hf);
    }//MAXITER
    printf("------------------------------------------\n");
    printf("run time for %d cases:\n", counter);
#if USING_BOOST
    printf("\tUsing GSL   = %8.4lf [ms], mean error = %.10f\n", times[GSL], meanErr[GSL]/counter); 
           printf("\tUsing TOMS  = %8.4lf [ms], mean error = %.10f\n", times[TOMS], meanErr[TOMS]/counter);
    printf("\tUsing GEMS  = %8.4lf [ms], mean error = %.10f\n", times[GEMS], meanErr[GEMS]/counter);
    printf("\tUsing Boost = %8.4lf [ms]\n", times[BOOST]);

#else
    printf("\tUsing GSL   = %8.4lf [ms]\n", times[GSL]);
    printf("\tUsing TOMS  = %8.4lf [ms]\n", times[TOMS]);
    printf("\tUsing GEMS  = %8.4lf [ms]\n", times[GEMS]);
#endif
    printf("------------------------------------------\n");
    printf("\tpython plot.py %s %s %s\n to plot the results\n", inputFile, rootsFile, resultFile);
    printf("------------------------------------------\n");
    printf("return %f\n", meanErr[GSL]/counter);
    
    if (meanErr[GSL]/counter < 0.01)
          return EXIT_SUCCESS;
    else
          return EXIT_FAILURE;
                

}
