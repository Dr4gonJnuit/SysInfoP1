#include "headers/includes.h"
#include "headers/philosophes.h"
#include "headers/reader_writer.h"

typedef struct args_p
{
    char *name;
    int nbr_philosophes;
    int reader;
    int writer;
} args_p;

void usage(char *prog_name)
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
        printf("./main -f reader_writer -h\n");
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
        printf("\n");
        return;
    }
    else if (strcmp(prog_name, "reader_writer") == 0)
    {
        printf("Options:\n");
        printf("  -i <number>    number of readers\n");
        printf("  -j <number>    number of writers\n");
        printf("  -h             display this help and exit\n");
        printf("\n");
        printf("Examples:\n");
        printf("./main -f reader_writer -i 5 -j 5\n");
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

    args->name = strrchr(argv[0], '/');
    if (args->name)
    {
        args->name++;
    }
    else
    {
        args->name = argv[0];
    }
    args->nbr_philosophes = 0;
    args->reader = 0;
    args->writer = 0;
    
    int opt;
    while ((opt = getopt(argc, argv, ":n:i:j:f:h")) != -1)
    {
        switch (opt)
        {
        case 'n':
            args->nbr_philosophes = atoi(optarg);
            if (args->nbr_philosophes <= 0)
            {
                printf("Invalid argument\n");
                return -1;
            }
            break;
        case 'i':
            args->reader = atoi(optarg);
            if (args->reader <= 0)
            {
                printf("Invalid argument\n");
                return -1;
            }
            break;
        case 'j':         
            args->writer = atoi(optarg);
            if (args->writer <= 0)
            {
                printf("Invalid argument\n");
                return -1;
            }
            break;
        case 'f':
            args->name = optarg;
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
            run_philosophes(args.nbr_philosophes);
        }
        else if (strcmp(args.name, "reader_writer") == 0)
        {
            run_reader_writer(args.reader, args.writer);
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

    return 0;
}
