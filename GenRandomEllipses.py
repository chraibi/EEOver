#produce randomly <num> cases to test the overlaping-routing
#id A1 B1 H1 K1 PHI_1 A2 B2 H2 K2 PHI_2

import numpy as np

num = int(1e6) # num of random cases
ampl = 10.
offset = -5


filename = "testcases_1M.txt"
print ">>%s (num=%d)"%(filename, num)
f = open(filename, "w")


A1 = 1 + np.random.random_sample( (num, ) ) * ampl # [1, amp+1)
B1 = A1 - np.random.random_sample( (num, ) ) # [A1-1, A1)

H1 = -offset + np.random.random_sample( (num, ) ) * ampl # [-offset, ampl+1 -pffset)
K1 = -offset + np.random.random_sample( (num, ) ) * ampl # [-offset, ampl+1 -pffset)

PHI_1 = -np.pi + np.random.random_sample( (num, ) ) * 2* np.pi # [-pi, pi)


A2 = 1 + np.random.random_sample( (num, ) ) * ampl # [1, amp+1)
B2 = A2 - np.random.random_sample( (num, ) ) # [A1-1, A1)

H2 = -offset + np.random.random_sample( (num, ) ) * ampl # [-offset, ampl+1 -pffset)
K2 = -offset + np.random.random_sample( (num, ) ) * ampl # [-offset, ampl+1 -pffset)

PHI_2 = -np.pi + np.random.random_sample( (num, ) ) * 2* np.pi # [-pi, pi)


for i in range(num):
    #id A1 B1 H1 K1 PHI_1 A2 B2 H2 K2 PHI_2
    print >>f, "%d\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f"%(i,A1[i], B1[i], H1[i], K1[i], PHI_1[i], A2[i], B2[i], H2[i], K2[i], PHI_2[i])

f.close()
