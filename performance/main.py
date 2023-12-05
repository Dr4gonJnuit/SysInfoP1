import matplotlib.pyplot as plt
import pandas as pd

def graph_window(size, name, title, show=True):
    plt.figure(figsize=size)
    for i in range(0, len(name)):
        graph_plot(name[i], len(name) * 100 + 10 + i + 1, title[i])
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

if __name__ == '__main__':
    # file_to_graph = ['csv/ingi_temps_philo.csv', 'csv/ingi_temps_pc.csv','csv/ingi_temps_rw.csv']
    # title_names = ['Temps d\'exécution du problème des philosophes', 'Temps d\'exécution du problème des producteurs-consomateurs','Temps d\'exécution du problème des lecteurs-écrivains']
    tas = ['csv/temps_TAS.csv']
    tas_title = ['Temps d\'exécution du TAS simple']
    graph_window((90, 40), tas, tas_title)
