
#include "scanner.h"

void createPortList(int *low, int *high, char ***result) {
    *result = (char**) malloc(sizeof(char*) * (*high - *low + 1));
    if (*result == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i <= *high - *low; i++) {
        (*result)[i] = (char*) malloc(sizeof(char) * 6); // Enough space for port number as string
        if ((*result)[i] == NULL) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
        sprintf((*result)[i], "%d", *low + i); // Correctly format the port number
    }
}

void scan(int argc, char *argv[]) {
    if (argc < 4) {
        usage();
        exit(EXIT_FAILURE);
    }

    struct protoent *protocol = getprotobyname("tcp"); // Use "tcp" instead of "IP"
    if (protocol == NULL) { 
        perror("getprotobyname");
        exit(EXIT_FAILURE);
    }

    struct addrinfo *result;
    struct addrinfo hints = {
        .ai_family = AF_UNSPEC,
        .ai_socktype = SOCK_STREAM,
        .ai_flags = 0,
        .ai_protocol = protocol->p_proto
    };

    const char* host = argv[1];
    int port1i = atoi(argv[2]); 
    int port2i = atoi(argv[3]);

    if (port1i <= 0 || port2i <= 0 || port1i > port2i) { // Validate port range
        usage();
        exit(EXIT_FAILURE);
    }

    char **array;
    createPortList(&port1i, &port2i, &array); // Pass the address of array

    for (int i = 0; i <= port2i - port1i; i++) {
        int s = getaddrinfo(host, array[i], &hints, &result);
        if (s != 0) {
            perror("getaddrinfo");
            free(array[i]); // Free allocated memory before exiting
            continue; // Skip to the next port
        }

        int sockfd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
        if (sockfd < 0) {
            perror("socket");
            freeaddrinfo(result); // Free addrinfo before continuing
            free(array[i]); // Free allocated memory before continuing
            continue; // Skip to the next port
        }

        if (connect(sockfd, result->ai_addr, result->ai_addrlen) < 0) {
            perror("connect");
            close(sockfd);
        } else {
            printf("Port %d is open\n", port1i + i); // Print the correct port number
            close(sockfd);
        }
        freeaddrinfo(result); // Free addrinfo after use
        free(array[i]); // Free the allocated port string
    }
    free(array); // Free the array of port strings
}

void usage() { 
    printf("Usage: ./scan <host> <FROM> <TO>\n"); 
}

