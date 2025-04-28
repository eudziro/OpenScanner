
#include "webseeker.h"

/* This function creates list of ports specified by user */
int
create_port_list(int *low, int *high, char ***result) 
{
    /* Allocate enough space for all ports */
    *result = malloc(sizeof(char*) * (*high - *low + 1));
    if (*result == NULL) {
        perror("malloc");
        return -1;
    }

    /* Allocate enough space for the 10^4 base number */
    for (int i = 0; i <= *high - *low; i++) 
    {
        (*result)[i] = malloc(sizeof(char) * 6);
        if ((*result)[i] == NULL) {
            perror("malloc");
            return -1;
        }
        sprintf((*result)[i], "%d", *low + i);
    }
    return 0;

}

struct ping_pkt {
    struct icmphdr hdr;
    char msg[PING_PKT_S - sizeof(struct icmphdr)];
};

unsigned short checksum(void *b, int len) {
    unsigned short *buf = b;
    unsigned int sum = 0;
    unsigned short result;

    for (sum = 0; len > 1; len -= 2)
        sum += *buf++;
    if (len == 1)
        sum += *(unsigned char *)buf;
    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    result = ~sum;
    return result;
}

/* Going through the actual scan (non-anonymous) */
int
normal_scan(struct wseeker* pointer) 
{
    /* Getting protocol number by simply specifying "tcp" */
    struct protoent *protocol = getprotobyname("tcp");
    if (protocol == NULL) {
        perror("getprotobyname");
        return -1;
    }


    struct addrinfo *result = NULL;
    struct addrinfo hints = {
        .ai_family = AF_UNSPEC,
        .ai_socktype = SOCK_STREAM,
        .ai_flags = 0,
        .ai_protocol = protocol->p_proto
    };

    /* Initialize our list of ports */
    char **array = NULL; 
    create_port_list(&pointer->port_from, &pointer->port_to, &array);

    for (int i = 0; i <= pointer->port_to - pointer->port_from; i++) {
        int s = getaddrinfo(pointer->host, array[i], &hints, &result);
        if (s != 0) {
            perror("getaddrinfo"); /* Debug goals */
            free(array[i]); 
            continue; 
        }

        /* Get the socket file descriptor */
        int sockfd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
        if (sockfd < 0) {
            perror("socket");
            freeaddrinfo(result);
            free(array[i]);
            continue;
        }

        /* Set the timeout for the connection */
        struct timeval timeout;
        timeout.tv_sec = 1; // 1 second timeout
        timeout.tv_usec = 0;
        setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, (const char*)&timeout, sizeof(timeout));

        if (connect(sockfd, result->ai_addr, result->ai_addrlen) < 0) 
        {
            close(sockfd);
        } 
        else 
        {
            printf("Port %d is open\n", pointer->port_from + i);
            close(sockfd);
        }
        freeaddrinfo(result); // Free the memory for avoiding segfault;
        free(array[i]);
    }
    free(array); // Free the array in the end
    return 0;
}


int
ping(struct wseeker* pointer) 
{
    struct sockaddr_in addr_ping;
    struct ping_pkt pkt;
    struct timeval timeout;
    int addr_len = sizeof(addr_ping);
    int sent, received;

    int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (sockfd < 0) {
        perror("Socket creation failed");
        return -1;
    }

    memset(&addr_ping, 0, sizeof(addr_ping));
    addr_ping.sin_family = AF_INET;
    addr_ping.sin_addr.s_addr = inet_addr(pointer->host);

    memset(&pkt, 0, sizeof(pkt));
    pkt.hdr.type = ICMP_ECHO;
    pkt.hdr.un.echo.id = getpid();
    pkt.hdr.un.echo.sequence = 1;
    pkt.hdr.checksum = checksum(&pkt, sizeof(pkt));

    /* Set timeout for receiving */
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));

    /* Send the packet */
    sent = sendto(sockfd, &pkt, sizeof(pkt), 0, (struct sockaddr*)&addr_ping, sizeof(addr_ping));
    if (sent <= 0) {
        perror("Send failed");
        close(sockfd);
        return -1;
    }

    /* Receive the packet */
    received = recvfrom(sockfd, &pkt, sizeof(pkt), 0, (struct sockaddr*)&addr_ping, &addr_len);
    if (received < 0) {
        perror("Receive failed");
    } else {
        printf("Received reply from %s: bytes=%d seq=%d\n", pointer->host, received, pkt.hdr.un.echo.sequence);
    }

    close(sockfd);
    return 0;
}


