import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

cases = ["a", "b", "c", "d"]

times = [[1,50,100,100],[2,75,150,150],[1,6.64,6.64,6.64],[1,7,18,20]]
plt.plot(cases, times[0], "o-", label="Linear (Iterative)")
plt.plot(cases, times[1], "o-", label="Linear (Recursive)")
plt.plot(cases, times[2], "o-", label="Binary")
plt.plot(cases, times[3], "o-", label="Jump")

plt.title("Theoretical Plot")
plt.xlabel("Cases")
plt.ylabel("Time")

plt.legend()

plt.show()
