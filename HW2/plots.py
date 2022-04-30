import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

N = [10, 20, 50, 100, 200, 500, 1000, 1500, 2500, 5000, 10000, 12345 ]

algos = {"Linear\
          (Iterative)":{"a": [4, 8, 10, 20, 40, 100, 200, 300, 500, 1000, 2000, 2469],
                        "b": [10, 16, 50, 100, 200, 400, 1000, 1200, 2500, 5000, 10000, 12345],
                        "c": [18, 40, 90, 180, 360, 900, 1800, 2700, 4500, 9000, 18000, 22222],
                        "d": [16, 40, 100, 180, 360, 900, 1800, 2700, 4500, 9000, 18000, 22222]},
         "Linear\
          (Recursive)":{"a": [6, 8, 20, 40, 80, 300, 600, 900, 2000, 3000, 6000, 7407],
                        "b": [20, 36, 140, 320, 600, 1600, 3200, 4500, 8000, 17000, 36000, 44444],
                        "c": [30, 64, 280, 540, 1120, 2900, 6000, 8700, 14500, 29000, 58000, 74074],
                        "d": [30, 72, 300, 580, 1240, 3100, 6200, 9300, 16000, 32000, 66000, 81481]},
         "Binary":     {"a": [8.16, 13.28, 10.6, 22, 19.2, 28, 24, 24, 40, 60, 40, 49.3],
                        "b": [9.96, 12.8, 15.8, 52, 22.4, 28, 28, 30, 30, 40, 40, 40],
                        "c": [12.28, 12.32, 17.4, 15.2, 15.2, 26, 32, 24, 30, 20, 40, 49.3],
                        "d": [11.2, 14, 16.6, 19.6, 22.4, 26, 28, 36, 40, 40, 40, 49.38]},
         "Jump":       {"a": [36, 39, 45, 70, 80, 150, 100, 150, 250, 500, 1000, 1200],
                        "b": [67, 94, 130, 180, 260, 400, 500, 600, 750, 1500, 2000, 2469],
                        "c": [118, 164, 225, 300, 420, 600, 900, 1050, 1250, 2000, 3000, 3703],
                        "d": [143, 182, 260, 320, 460, 700, 1000, 1050, 1500, 2000, 3000, 3703]}}

plt.plot(N, algos["Linear          (Iterative)"]["a"], "o-", label="Scenario A")
plt.plot(N, algos["Linear          (Iterative)"]["b"], "o-", label="Scenario B")
plt.plot(N, algos["Linear          (Iterative)"]["c"], "o-", label="Scenario C")
plt.plot(N, algos["Linear          (Iterative)"]["d"], "o-", label="Scenario D")

plt.title("Linear Iterative")
plt.xlabel("N")
plt.ylabel("Time")

plt.legend()

plt.show()

plt.plot(N, algos["Linear          (Recursive)"]["a"], "o-", label="Scenario A")
plt.plot(N, algos["Linear          (Recursive)"]["b"], "o-", label="Scenario B")
plt.plot(N, algos["Linear          (Recursive)"]["c"], "o-", label="Scenario C")
plt.plot(N, algos["Linear          (Recursive)"]["d"], "o-", label="Scenario D")

plt.title("Linear Recursive")
plt.xlabel("N")
plt.ylabel("Time")

plt.legend()

plt.show()

plt.plot(N, algos["Binary"]["a"], "o-", label="Scenario A")
plt.plot(N, algos["Binary"]["b"], "o-", label="Scenario B")
plt.plot(N, algos["Binary"]["c"], "o-", label="Scenario C")
plt.plot(N, algos["Binary"]["d"], "o-", label="Scenario D")

plt.title("Binary")
plt.xlabel("N (Logarithmic)")
plt.ylabel("Time")
plt.xscale("log")

plt.legend()

plt.show()

plt.plot(N, algos["Jump"]["a"], "o-", label="Scenario A")
plt.plot(N, algos["Jump"]["b"], "o-", label="Scenario B")
plt.plot(N, algos["Jump"]["c"], "o-", label="Scenario C")
plt.plot(N, algos["Jump"]["d"], "o-", label="Scenario D")


plt.title("Jump")
plt.xlabel("N (Logarithmic)")
plt.ylabel("Time")
plt.xscale("log")

plt.legend()

plt.show()
