import matplotlib.pyplot as plt
import pandas as pd

def graph_window(size, name):
    plt.figure(figsize=size)
    for i in range(0, len(name)):
        graph_plot(name[i], len(name) * 100 + 10 + i + 1)
    plt.show()

def graph_plot(name, subplot_position=111):
    plt.subplot(subplot_position)
    
    data_read = pd.read_csv(name, index_col='n')
    
    nbr_threads = data_read.index
    
    data_means = data_read.mean(axis=1)
    data_std = data_read.std(axis=1)
    
    plt.plot(data_means.index, data_means, label='Mean Time')
    plt.fill_between(data_means.index, data_means - data_std, data_means + data_std, alpha=0.2, label='Standard Deviation')
    plt.xticks(data_means.index, nbr_threads)
    plt.ylim(0, max(data_means) + max(data_std))
    plt.xlabel('Number of Threads')
    plt.ylabel('Time Taken')
    plt.legend()
    plt.title(name.split('/')[1].split('.')[0])
    
    plt.grid(True)
    
    # Remove the duplicate plt.show() call
    # plt.show()

if __name__ == '__main__':
    file_to_graph = ['csv/ingi_temps_philo.csv', 'csv/ingi_temps_rw.csv']
    graph_window((100, 50), file_to_graph)
