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
    printf("Usage: %s -n <nbr_philosophes>\n", prog_name);
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
            usage(argv[0]);
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
