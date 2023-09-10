import matplotlib.pyplot as plt

# Read the values from output.out
with open('ChuaFinitePrecision\\solution1\\csim\\build\output.txt', 'r') as f:
    values = [float(line.strip()) for line in f]

# Create the plot
plt.plot(values)
plt.title('Values from output.out')
plt.xlabel('Iteration')
plt.ylabel('dataui.f Value')
plt.grid(True)
plt.show()
