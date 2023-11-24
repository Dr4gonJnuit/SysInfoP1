import matplotlib.pyplot as plt
import pandas as pd

data = pd.read_csv('temps_execution.csv')

# Calculate the time taken for each code execution
time_philo = data['temps_philo']

# Plot the time taken on the y-axis, starting from 0
plt.plot(range(len(time_philo)), time_philo)
plt.ylim(0, max(time_philo))  # Set the y-axis limits

# Display the mean and standard deviation
mean_time = time_philo.mean()
std_dev = time_philo.std()
plt.axhline(mean_time, color='r', linestyle='--', label='Mean')
plt.axhline(mean_time + std_dev, color='g', linestyle='--', label='Mean + Std Dev')
plt.axhline(mean_time - std_dev, color='g', linestyle='--', label='Mean - Std Dev')

# Add labels and legend
plt.xlabel('Execution')
plt.ylabel('Time Taken')
plt.legend()

# Show the plot
plt.show()
