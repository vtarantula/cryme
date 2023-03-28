// C++ Headers
#include <string>
#include <getopt.h>

// Application headers
#include "utils/mathutils.h"
#include "ds/list.h"
#include "algo/sort.h"
#include "net/client/redis_client.h"
#include "net/server/redis_server.h"

int main(int argc, char const *argv[])
{
    /* code */
    std::cout << "*** Starting App ***" << std::endl;
    std::cout << "File: " << argv[0] << "; ARGC: " << argc << std::endl;

    // auto i = generate_total(v);
    // std::cout << "Number of 3: " << std::count(std::begin(v), std::end(v), 3) << std::endl;

    // https://build-your-own.org/redis/03_hello_cs
    /*
    int port = 1234;
    if (argc == 2)
    {
        std::string action(argv[1]);
        if (action == "server")
        {
            server_listen(&port);
        } else if (action == "client")
        {
            client_connect(&port);
        }
    }
    */

    std::vector<long> v{3, 5, 4, -1, 2, 1, -2};
    merge_sort(v);
    for (const auto& i : v)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    return 0;
}
