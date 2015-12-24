from matplotlib.pyplot import *
from numpy import *
import pylab
from matplotlib.patches import Ellipse
from math import pi
import os, shutil
from sys import argv

import imp
try:
    imp.find_module('tqdm')
    from tqdm import tqdm
    found_tqdm = True
except ImportError:
    found_tqdm = False

if len(argv) < 4:
    print ("Usage: python %s ellipseDataFile rootsFile resultsFile"%argv[0])
    sys.exit()


DIR = "cases" # put the figs here
ms = 9
if os.path.exists(DIR):
    print ("Delete directory <%s>"%DIR)
    shutil.rmtree(DIR)
    print ("Create directory <%s>"%DIR)
    os.makedirs(DIR)
else:
    os.makedirs(DIR)
    print ("Directory <%s> does not exist. Create one .."%DIR)

filename = argv[1]  # testcases.txt
rootsfile = argv[2]  # roots
resultsfile = argv[3]  # areas

print("got input", filename)
print("got roots", rootsfile)
print("got roots", resultsfile)

f = open(rootsfile)
data = loadtxt(filename)
data = np.atleast_2d(data) # for the case that we have only one case

areas = loadtxt(resultsfile)
areas = np.atleast_2d(areas)
roots = [line.split() for line in f if not line.startswith("#")]

ids = range(data.shape[0]) #unique(data[:,0]).astype(int)
if found_tqdm:
    ids = tqdm(ids)

for Id in ids:
    #PHI should be in radian
    d = data[Id, :]
    area = areas[Id, :]
    index = d[0]
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

    while PHI_1 >= pi:  #fmod is not so acurate. I prefere doing a simple substraction
        PHI_1 -= pi

    while PHI_2 >= pi:
        PHI_2 -= pi

    # get the roots
    #
    r = roots[Id]
    length = len(r) - 1

    pylab.axes()

    cir = Ellipse(xy=(H1, K1), width=2*A1, height=2*B1, angle=PHI_1*180/pi, alpha=.2, fc='r', lw=3)
    plot(H1, K1, "or", ms=ms)
    plot(H2, K2, "ob", ms=ms)
    pylab.gca().add_patch(cir)

    #plot roots
    if length:
        R = array([float(i) for i in r[1:]])
        rx_TR = (R[0::2])*cos(-PHI_1) + (R[1::2])*sin(-PHI_1)  + H1
        ry_TR = -(R[0::2])*sin(-PHI_1) + (R[1::2])*cos(-PHI_1) + K1
        plot(rx_TR, ry_TR, "og", ms=ms, lw=2)

    cir = Ellipse(xy=(H2, K2), width=2*A2, height=2*B2, angle=PHI_2*180/pi, alpha=.2, fc='b', lw=3)

    pylab.gca().add_patch(cir)
    pylab.axis('scaled')
    pylab.title(r"$%d,\; A_1= %.3f,\; A_2= %.3f,\;A_{12}= %.3f,\; \epsilon=%.3f$"%(
        index, area[1], area[2], area[3], area[5]))

    pylab.grid()

    figname = os.path.join(DIR, "case%.3d.png"%(Id))
    pylab.savefig(figname)
    # sys.stdout.write("---> %s"%figname)
    #pylab.show()
    pylab.clf()
