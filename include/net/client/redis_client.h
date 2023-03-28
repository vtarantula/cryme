#ifndef REDIS_CLIENT_H__
#define REDIS_CLIENT_H__

// C++ Headers
#include <string.h>
#include <unistd.h>
#include <stdexcept>

// Network headers
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>

// Application Headers

void client_connect(const int* port)
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0)
    {
        throw std::runtime_error("Unable to get socket()");
    }

    struct sockaddr_in addr = {};
    addr.sin_family = AF_INET;
    addr.sin_port = ntohs(*port);
    addr.sin_addr.s_addr = ntohl(INADDR_LOOPBACK);  // 127.0.0.1

    int rv = connect(fd, (const sockaddr*) &addr, sizeof(addr));
    if (rv)
    {
        throw std::runtime_error("Unable to connect()");
    }
    // Do some work
    char msg[] = "hello";
    write(fd, msg, strlen(msg));

    char rbuf[64] = {};
    ssize_t n = read(fd, rbuf, sizeof(rbuf) - 1);
    if (n < 0)
    {
        throw std::runtime_error("Unable to read()");
    }
    printf("Server: %s\n", rbuf);

    close(fd);
    return;
}

#endif    // REDIS_CLIENT_H__