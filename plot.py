from matplotlib.pyplot import *
from numpy import *
import pylab
from matplotlib.patches import Ellipse
from math import pi

from sys import argv


if len(argv)< 3:
    print "Usage: python %s ellipseDataFile rootsFile"%argv[0]
    exit()
    
filename = argv[1]  # testcases.txt
rootsfile = argv[2]  #roots.txt

print "got input",filename
print "got roots",rootsfile

f = open (rootsfile)
data = loadtxt(filename)
data = np.atleast_2d(data)
roots = [line.split() for line in f if not line.startswith("#")]
print "roots ", roots
ids = range(data.shape[0]) #unique(data[:,0]).astype(int)
print "ids=",ids
for Id in ids:
    #PHI should be in radian
    #d = data[ data[:,0] == Id ] # Id should start with 0. So this is not save, since some users dont care too much
    d = data[Id, :]

    print "Id=",Id
    print "d",d
    A1 = d[1]
    B1 = d[2]
    H1 = d[3]
    K1 = d[4]
    PHI_1 = d[5]
    A2 = d[6]
    B2 = d[7]
    H2 = d[8]
    K2 = d[9]
    PHI_2 = d[10]
    
    print "A1=", A1, "B1=", B1, "H1=", H1, "K1=", K1, "PhI_1=",PHI_1 
    print "A2=", A2, "B2=", B2, "H2=", H2, "K2=", K2, "PhI_2=",PHI_2 
    while PHI_1 >=pi:  #fmod is not so acurate. I prefere doing a simple substraction
        PHI_1 -= pi
        print " >> PhI_1=",PHI_1 
    while PHI_2 >=pi:
        PHI_2 -= pi
        print " >> PhI_2=",PHI_2
    # get the roots
    #
    r = roots[Id]#roots[roots[:,0]==Id]
    length = len(r) - 1
    # if not length:
    #   continue
    print "Id", Id
    print "nroots ", length 
    #print "roots ", roots


    pylab.axes()
    #pylab.subplot(211)

    ms=9
    
    cir = Ellipse(xy=(H1,K1), width=2*A1, height=2*B1, angle=PHI_1*180/pi,  alpha = .2, fc='r', lw=3)
    plot(H1, K1, "or", ms=ms)
    plot(H2, K2, "ob", ms=ms)
    print "plot red line"
    print [H1+ A1*cos(PHI_1+pi), H1 + A1*cos(PHI_1)]
    print [K1+ A1*sin(PHI_1+pi), K1 + A1*sin(PHI_1)]
    #plot([H1+ A1*cos(PHI_1+pi), H1 + A1*cos(PHI_1)], [K1+ A1*sin(PHI_1+pi), K1 + A1*sin(PHI_1)], "--r", lw=2)
    #plot([H1+ B1*cos(PHI_1+pi+pi/2), H1 + B1*cos(PHI_1+pi/2)], [K1+ B1*sin(PHI_1+pi+pi/2), K1 + B1*sin(PHI_1+pi/2)], "--r", lw=2)
    pylab.gca().add_patch(cir)


    #plot roots
    
    if length:
        R = array([float(i) for i in r[1:]])
        rx_TR = (R[0::2])*cos(-PHI_1) + (R[1::2])*sin(-PHI_1)  + H1;
        ry_TR = -(R[0::2])*sin(-PHI_1) + (R[1::2])*cos(-PHI_1) + K1;

        print "rx_TR=", rx_TR
        print "ry_TR=", ry_TR
        plot(rx_TR, ry_TR, "og", ms=ms, lw=2)
    
    cir = Ellipse(xy=(H2,K2), width=2*A2, height=2*B2, angle=PHI_2*180/pi,  alpha =.2, fc='b', lw=3)
    #plot([H2+ A2*cos(PHI_2 + pi), H2 + A2*cos(PHI_2)], [K2+ A2*sin(PHI_2+pi), K2 + A2*sin(PHI_2)], "--b", lw=2)
    #plot([H2+ B2*cos(PHI_2+pi+pi/2), H2 + B2*cos(PHI_2+pi/2)], [K2+ B2*sin(PHI_2+pi+pi/2), K2 + B2*sin(PHI_2+pi/2)], "--b", lw=2)
    #plot(H2, K2, "ob", ms=ms)
    pylab.gca().add_patch(cir)
    pylab.axis('scaled')
    pylab.title("case %d"%(Id))

    pylab.grid()
    
    figname = "cases/case%.3d.png"%(Id)
     
    pylab.savefig(figname)
    print "---> ", figname
    #pylab.show()
    pylab.clf()







