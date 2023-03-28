// C++ Headers
#include <string>
#include <getopt.h>

// Application headers
#include "utils/mathutils.h"
#include "ds/list.h"
#include "algo/sort.h"
#include "net/client/redis_client.h"
#include "net/server/redis_server.h"

int main(int argc, char *argv[])
{
    /* code */
    std::cout << "*** Starting App ***" << std::endl;
    std::cout << "File: " << argv[0] << "; ARGC: " << argc << std::endl;

    // auto i = generate_total(v);
    // std::cout << "Number of 3: " << std::count(std::begin(v), std::end(v), 3) << std::endl;

    int opt;
    struct option longopts[] = {
        {"server", 0, NULL, 's'},
        {"client", 0, NULL, 'c'},
        {0, 0, 0, 0}
    };

    // https://build-your-own.org/redis/03_hello_cs
    int port = 1234;

    while ((opt = getopt_long(argc, argv, ":cs", longopts, NULL)) != -1)
    {
        switch(opt) 
        {
            case 'c':
                client_connect(&port);
                break;
            case 's':
                server_listen(&port);
                break;
            case ':':
                printf("Option nneds a value\n");
                break;
            case '?':
                printf("Unknown option: %c\n", opt);
                break;
        }
    }


    return 0;
}
