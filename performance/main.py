import matplotlib.pyplot as plt
import pandas as pd

# Read the .csv file
data = pd.read_csv('your_file.csv')

# Calculate the time taken for each code execution
time_taken = data['time_taken']

# Plot the time taken on the y-axis, starting from 0
plt.plot(range(len(time_taken)), time_taken)
plt.ylim(0, max(time_taken))  # Set the y-axis limits

# Display the mean and standard deviation
mean_time = time_taken.mean()
std_dev = time_taken.std()
plt.axhline(mean_time, color='r', linestyle='--', label='Mean')
plt.axhline(mean_time + std_dev, color='g', linestyle='--', label='Mean + Std Dev')
plt.axhline(mean_time - std_dev, color='g', linestyle='--', label='Mean - Std Dev')

# Add labels and legend
plt.xlabel('Execution')
plt.ylabel('Time Taken')
plt.legend()

# Show the plot
plt.show()
