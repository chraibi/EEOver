from matplotlib.pyplot import *
from numpy import *

d = loadtxt("log.txt")

n = d[:,0]
te = d[:,1]
tp = d[:,2]
err = d[:,3]

s = tp/te
ms = 9
ts=20
subplot(211)

plot(n, s, "bD-",lw=2, ms=ms)
xlabel(r"$n$", size=18)
ylabel(r"$t_p/t_e$", size=ts)
xlim([min(n)-0.3, max(n)+0.3])
ds=10
ylim([min(s)-ds, max(s)+ds])
grid()

ax = subplot(212)
plot(n, err, "bo-",lw=2, ms=ms)
xlabel(r"$n$", size=18)
ylabel(r"$\epsilon_{rel}$", size=ts)
xlim([min(n)-0.3, max(n)+0.3])
de=0.05
#ylim([min(err)-de, max(err)+de])
ax.set_yscale('log')
grid()
savefig("performance.png")
savefig("performance.pdf")
show()
