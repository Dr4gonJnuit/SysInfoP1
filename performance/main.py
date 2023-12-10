import matplotlib.pyplot as plt
import pandas as pd


def convert_time(time_string):
    """Transforms a time string into a total time in milliseconds.

    Args:
        time_string (String): the time to convert

    Returns:
        Int: the total time in milliseconds
    """
    minutes, seconds = time_string.split(":")
    seconds, milliseconds = seconds.split(".")
    total_time = int(minutes) * 60 * 1000 + int(seconds) * 1000 + int(milliseconds)
    return total_time


def graph_line(files, names, show=False):
    """Constructs a line graph from the data in the csv files.

    Args:
        files (List of Strings): The paths to the csv files
        names (List of Strings): The names of the graphs
        show (bool, optional): Can decide to show the plot. Defaults to False.
    """
    for file in files:
        # Read data from csv file
        data = pd.read_csv(file, index_col="n").map(convert_time)

        # Calculate mean and standard deviation
        mean = data.mean(axis=1)
        std = data.std(axis=1)

        # Plot the graph
        plt.errorbar(
            data.index,
            mean,
            yerr=std,
            fmt="-o",
            label=names,
            markersize=3,
            linewidth=1,
            capsize=6,
        )
        plt.legend(names, loc="upper left")

    # Informations about the graph
    plt.title(names[-1])
    plt.xlabel("Number of Threads (n)")
    plt.ylabel("Execution Time (ms)")
    plt.grid(True)

    # Force y-axis to start at 0
    plt.ylim(bottom=0)

    # Force x-axis to display index values
    plt.xticks(data.index)

    if show:
        plt.show()


if __name__ == "__main__":
    # Paths to csv files
    csv_to_graph_philo = [
        "performance/csv/Ingi_temps_philo_POSIX.csv",
        "performance/csv/Ingi_temps_philo_TAS.csv",
        "performance/csv/Ingi_temps_philo_TATAS.csv",
    ]

    csv_to_graph_prod_cons = [
        "performance/csv/Ingi_temps_prod_cons_POSIX.csv",
        "performance/csv/Ingi_temps_prod_cons_TAS.csv",
        "performance/csv/Ingi_temps_prod_cons_TATAS.csv",
    ]

    csv_to_graph_read_write = [
        "performance/csv/Ingi_temps_read_write_POSIX.csv",
        "performance/csv/Ingi_temps_read_write_TAS.csv",
        "performance/csv/Ingi_temps_read_write_TATAS.csv",
    ]

    csv_to_graph_test_TAS_and_TATAS = [
        "performance/csv/Ingi_temps_test_TAS.csv",
        "performance/csv/Ingi_temps_test_TATAS.csv",
    ]

    # Names of the graphs
    name_of_graph_philo = [
        "Temps philo POSIX",
        "Temps philo TAS",
        "Temps philo TATAS",
        "Temps du problème des philosophes en fonction du nombre de threads",
    ]

    name_of_graph_prod_cons = [
        "Temps prod cons POSIX",
        "Temps prod cons TAS",
        "Temps prod cons TATAS",
        "Temps du problème des producteurs-consommateurs en fonction du nombre de threads",
    ]

    name_of_graph_read_write = [
        "Temps read write POSIX",
        "Temps read write TAS",
        "Temps read write TATAS",
        "Temps du problème des lecteurs-écrivains en fonction du nombre de threads",
    ]

    name_of_graph_test_TAS_and_TATAS = [
        "Temps test TAS",
        "Temps test TATAS",
        "Temps du test en fonction du nombre de threads",
    ]

    graph_line(csv_to_graph_philo, name_of_graph_philo, True)
    graph_line(csv_to_graph_prod_cons, name_of_graph_prod_cons, True)
    graph_line(csv_to_graph_read_write, name_of_graph_read_write, True)
    graph_line(csv_to_graph_test_TAS_and_TATAS, name_of_graph_test_TAS_and_TATAS, True)
