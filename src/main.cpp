// C++ Headers
#include <string>
#include <getopt.h>

// Application headers
#include "utils/utils.h"
#include "utils/mathutils.h"
#include "ds/list.h"
#include "algo/sort.h"
#include "net/client/redis_client.h"
#include "net/server/redis_server.h"

// Constants
const int PORT_NUM = 1234;
const char* PROGRAM_NAME = nullptr;


void usage(FILE* stream, int exit_code)
{
    fprintf(stream, "Usage: %s options [...]\n", PROGRAM_NAME);
    fprintf(stream,
                "   -h  --help          Display usage\n"
                "   -l  --logfile       LogFile file to write to\n"
                "   -v  --verbose       Print verbose message\n"
                "   -s  --server        Start server on this node\n"
                "   -c  --client        Start client on this node\n"
            );
    exit(exit_code);
    return;
}

// Flags for command line arguments
static int f_server = 0;
static int f_client = 0;
static int f_verbose = 0;
void parse_args(int* argc, char** argv)
{
    const char* const short_options = ":vhcsl:";
    const struct option long_options[] = {
        { "verbose",    no_argument,        &f_verbose,     1   },
        { "help",       no_argument,        NULL,           'h' },
        { "logfile",    required_argument,  NULL,           'l' },
        { "server",     no_argument,        &f_server,      1   },
        { "client",     no_argument,        &f_client,      1   },
        { NULL,         0,                  NULL,           0   }
    };

    const char* log_filename = nullptr;

    // Loop through options
    int next_option;
    do
    {
        // TODO: use getsubopt to parse suboptions when this grows
        next_option = getopt_long(*argc, argv, short_options, long_options, NULL);
        switch (next_option)
        {
            case 'v':
                f_verbose = 1;
                break;
            case 'h':
                usage(stdout, 0);
                break;
            case 'l':
                printf("Output option processed!\n");
                printf("=> [%s]\n", optarg);
                log_filename = optarg;
                break;
            case 's':
                printf("Server option processed!\n");
                f_server = 1;
                break;
            case 'c':
                printf("Client option processed!\n");
                f_client = 1;
                break;
            case '?':   // Invalid option
                printf("=> Invalid option\n");
                usage(stderr, 1);
                break;
            case -1:    // All options processed
                printf("All options processed!\n");
                break;
            case ':':   // Options without arguments
                printf("Missing argument for [%c]\n", optopt);
                usage(stderr, 1);
                break;
            // Use '-' in case you want to uncomment the below
            // case 1:   // Non-optional arguments passed at the end
            //     printf("Additional argument for [%s]\n", optarg);
            //     break;
            default:
                printf("Def\n");
                usage(stdout, 0);
                break;
        }
    } while (next_option != -1);

    printf("Captured all command line arguments for: %s\n", PROGRAM_NAME);

    // TODO: Check mandatory arguments and verify argument value

    // Run functions based on options
    printf("Using output file to %s\n", log_filename);
    printf("Using verbose setting to %d\n", f_verbose);

    // https://build-your-own.org/redis/03_hello_cs
    if (f_server)
    {
        server_listen(&PORT_NUM);
    }
    if (f_client)
    {
        client_connect(&PORT_NUM);
    }
    return;
}

int main(int argc, char *argv[])
{
    /* code */
    std::cout << "*** Starting App ***" << std::endl;
    PROGRAM_NAME = argv[0];

    // auto i = generate_total(v);
    // std::cout << "Number of 3: " << std::count(std::begin(v), std::end(v), 3) << std::endl;

    parse_args(&argc, argv);

    return 0;
}
