import matplotlib.pyplot as plt
import seaborn as sns
import numpy as np
import pandas as pd
# Sample Data
x = np.linspace(0, 10, 50)
y = np.sin(x)

# 1. Line Plot (Matplotlib)
plt.plot(x, y, label="sin(x)", color="blue", marker="o")
plt.title("Line Plot - Sine Function")
plt.xlabel("X-axis")
plt.ylabel("Y-axis")
plt.legend()
plt.show()
