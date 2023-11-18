#include "headers/includes.h"
#include "headers/philosophes.h"

// Pas pour tout de suite
/*
typedef struct
{
    FILE *input_file;
    FILE *output_stream;
} args_t;


void usage(char *prog_name)
{
    return;
}

int parse_args(args_t *args, int argc, char const **argv)
{
    memset(args, 0, sizeof(args_t));

    args->output_stream = stdout;
    args->input_file = NULL;
    int opt;
    while ((opt = getopt(argc, argv, "hn:vf:")) != -1)
    {
        switch (opt)
        {
        case '?':
        case 'h':
            usage(argv[0]);
            return 1;
        }
    }

    return 0;
}

int main(int argc, char const **argv)
{
    args_t args;
    int err = parse_args(&args, argc, argv);
    if (err == -1)
    {
        exit(EXIT_FAILURE);
    }
    else if (err == 1)
    {
        exit(EXIT_SUCCESS);
    }
    return 0;
}
*/

int main(int argc, char const *argv[])
{
    if (argc >= 2)
    {
        int nbr_philosophes = atoi(argv[1]);
        run_philosophes(nbr_philosophes);
    } else
    {
        printf("No argument\n");
    }

    return 0;
}
