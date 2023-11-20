#include "headers/includes.h"
#include "headers/philosophes.h"

typedef struct args_p
{
    char *name;
    int n;
} args_p;

void usage(char *prog_name)
{
    printf("Usage: %s -n <nbr_philosophes>\n", prog_name);
}

int parse_args(args_p *args, int argc, char *argv[])
{
    memset(args, 0, sizeof(args_p));

    int opt;
    while ((opt = getopt(argc, argv, "hn:f:")) != -1)
    {
        switch (opt)
        {
        case 'n':
            args->n = atoi(optarg);
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
            run_philosophes(args.n);
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
