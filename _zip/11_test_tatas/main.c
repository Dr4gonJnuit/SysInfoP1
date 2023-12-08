#include "headers/includes.h"
#include "headers/algorithmes/philosophes.h"
#include "headers/algorithmes/reader_writer.h"
#include "headers/algorithmes/produc_conso.h"

typedef struct args_p
{
    char *name;          // name of the program to run
    int nbr_threads[2];  // number of threads to run
    bool attente_active; // if true then use our personal mutexes and semaphores
} args_p;

void usage(char *prog_name) // Need to be updated
{
    if (strcmp(prog_name, "main") == 0)
    {
        printf("Usage: ./%s [OPTION]...\n", prog_name);
        printf("Options:\n");
        printf("  -f <name>      name of the program to run\n");
        printf("  -h             display this help and exit\n");
        printf("\n");
        printf("Examples:\n");
        printf("./main -f philo -h\n");
        printf("./main -f read_write -h\n");
        printf("./main -f prod_cons -h\n");
        printf("\n");
        return;
    }

    printf("Usage: ./main -f %s [OPTION]...\n", prog_name);
    printf("Run the program with the specified option\n");
    printf("\n");
    if (strcmp(prog_name, "philo") == 0)
    {
        printf("Options:\n");
        printf("  -n <number>    number of philosophers\n");
        printf("  -h             display this help and exit\n");
        printf("\n");
        printf("Examples:\n");
        printf("./main -f philo -n 5\n");
        printf("This will run the philosophe algorithm with 5 philosophers\n");
        printf("\n");
        return;
    }
    else if (strcmp(prog_name, "read_write") == 0)
    {
        printf("Options:\n");
        printf("  -n <number>    number of readers and writers\n");
        printf("  -h             display this help and exit\n");
        printf("\n");
        printf("Examples:\n");
        printf("./main -f read_write -n 4\n");
        printf("This will run the readers-writers algorithm with 4 readers and 4 writers\n");
        printf("\n");
        return;
    }
    else if (strcmp(prog_name, "prod_cons") == 0)
    {
        printf("Options:\n");
        printf("  -n <number>    number of producers and consumers\n");
        printf("  -h             display this help and exit\n");
        printf("\n");
        printf("Examples:\n");
        printf("./main -f prod_cons -n 8\n");
        printf("This will run the producers-consumers algorithm with 8 producers and 8 consumers\n");
        printf("\n");
        return;
    }
    else
    {
        printf("Error in showing help\n");
        return;
    }
}

int parse_args(args_p *args, int argc, char *argv[])
{
    memset(args, 0, sizeof(args_p));

    args->name = "main";
    args->nbr_threads[0] = 0;
    args->nbr_threads[1] = 0;
    args->attente_active = false;

    int opt;
    while ((opt = getopt(argc, argv, ":f:a:n:h")) != -1)
    {
        switch (opt)
        {
        case 'f':
            args->name = optarg;
            break;
        case 'a':
            args->attente_active = true;
            break;
        case 'n':
            if (strcmp(args->name, "philo") == 0)
            {
                args->nbr_threads[0] = atoi(optarg);
                if (args->nbr_threads[0] <= 0)
                {
                    printf("Invalid argument\n");
                    return -1;
                }
            }
            else if (strcmp(args->name, "prod_cons") == 0)
            {
                args->nbr_threads[0] = atoi(optarg);
                args->nbr_threads[1] = atoi(optarg);
                if (args->nbr_threads[0] <= 0 || args->nbr_threads[1] <= 0)
                {
                    printf("Invalid argument\n");
                    return -1;
                }
            }

            else if (strcmp(args->name, "read_write") == 0) // Can't chose the number of readers and writers -> need to be fixed
            {
                args->nbr_threads[0] = atoi(optarg);
                args->nbr_threads[1] = atoi(optarg);
                if (args->nbr_threads[0] <= 0 || args->nbr_threads[1] <= 0)
                {
                    printf("Invalid argument\n");
                    return -1;
                }
            }
            else
            {
                printf("Invalid name\n");
                return -1;
            }
            break;
        case '?':
        case 'h':
            usage(args->name);
            return 1;
        default:
            usage(argv[0]);
            return 1;
        }
    }

    return 0;
}

int main(int argc, char *argv[])
{
    if (argc >= 2)
    {
        args_p args;
        int err = parse_args(&args, argc, argv);
        if (err == -1)
        {
            exit(EXIT_FAILURE);
        }
        else if (err == 1)
        {
            exit(EXIT_SUCCESS);
        }

        if (strcmp(args.name, "philo") == 0)
        {
            run_philosophes(args.nbr_threads[0]);
        }
        else if (strcmp(args.name, "read_write") == 0)
        {
            run_reader_writer(args.nbr_threads[1], args.nbr_threads[1]);
        }
        else if (strcmp(args.name, "prod_cons") == 0)
        {
            run_produc_conso(args.nbr_threads[0], args.nbr_threads[1]);
        }
        else
        {
            printf("Invalid argument\n");
        }
    }
    else
    {
        printf("No argument\n");
    }

    return EXIT_SUCCESS;
}
