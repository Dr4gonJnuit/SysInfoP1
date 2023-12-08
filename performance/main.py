import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

def convert_time(time_string):
    minutes, seconds = time_string.split(':')
    seconds, milliseconds = seconds.split('.')
    total_time = int(minutes) * 60 * 1000 + int(seconds) * 1000 + int(milliseconds)
    return total_time

def graph_line(file, name, show=False):
    data = pd.read_csv(file, index_col='n').applymap(convert_time)
    
    print(data)
    
    plt.plot(data.T, data.index)
    
    if show:
        plt.show

if __name__ == '__main__':
    csv_to_graph = ['performance/csv/Ingi_temps_philo_POSIX.csv', \
                     'performance/csv/Ingi_temps_philo_TAS.csv', \
                     'performance/csv/Ingi_temps_philo_TATAS.csv']
    name_of_graph = ['Temps philo POSIX', 'Temps philo TAS', 'Temps philo TATAS']
    
    graph_line(csv_to_graph[0], name_of_graph[0], True)
