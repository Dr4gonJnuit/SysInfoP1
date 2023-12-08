import matplotlib.pyplot as plt
import pandas as pd

def graph_window(size, name, title, f, show=True):
    plt.figure(figsize=size)
    for i in range(0, len(name)):
        f(name[i], len(name) * 100 + 10 + i + 1, title[i])
    if show:
        plt.show()

def graph_plot(name, subplot_position=111, title='', show=False):
    data = pd.read_csv(name, index_col='n')
    
    plt.subplot(subplot_position)
    plt.boxplot(data.T.values, meanline=True, showmeans=True, vert=True, patch_artist=True, labels=data.index)
    
    plt.xlabel('Nombres de Threads')
    plt.ylabel('Temps (s)')
    plt.title(title)
    plt.grid(True)
    
    if show:
        plt.show()

def graph_line(name, subplot_position=111, title='', show=False):
    data = pd.read_csv(name, index_col='n')
    
    plt.subplot(subplot_position)
    mean_values = data.mean()
    std_values = data.std()
    
    plt.axhline(mean_values, color='r', linestyle='--', label='Mean')
    plt.axhline(mean_values + std_values, color='g', linestyle='--', label='Mean + Std Dev')
    plt.axhline(mean_values - std_values, color='g', linestyle='--', label='Mean - Std Dev')
    
    plt.xlabel('Index')
    plt.ylabel('Temps (s)')
    plt.title(title)
    plt.grid(True)
    
    if show:
        plt.show()

if __name__ == '__main__':
    # file_to_graph = ['csv/ingi_temps_philo.csv', 'csv/ingi_temps_pc.csv','csv/ingi_temps_rw.csv']
    # title_names = ['Temps d\'exécution du problème des philosophes', 'Temps d\'exécution du problème des producteurs-consomateurs','Temps d\'exécution du problème des lecteurs-écrivains']
    
    g = ["performance/csv/Ingi_temps_philo_POSIX.csv"]
    n = ["Temps d'exécution du problème des philosophes"]
    #graph_window((90, 40), tas, tas_title, graph_plot)
    graph_window((90, 40), g, n, graph_line)
