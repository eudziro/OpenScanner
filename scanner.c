#include "scanner.h"


//void createPortList (int *low, int *high, char **result) {
//	result = (char**) malloc (sizeof (char*) * (*high - *low));
//	*result = (char*) malloc (sizeof (char) * *(high));
//	int temp_low = *low;
//	for (int i = 0; i <= *high; i++)
//      		*(result + i) = (char) temp_low++;
//}

void createPortList (int *low, int *high, char ***result) {
	*result = (char**) malloc (sizeof (char*) * (*high - *low + 1));
	if (*result == NULL) {
		perror ("malloc");
		exit (EXIT_FAILURE);
	}
	for (int i = 0; i <= *high - *low; i++) {
      		(*result)[i] = (char*) malloc(sizeof(char) * 6);
		if (*(result)[i] == NULL) {
			perror ("malloc");
			exit (EXIT_FAILURE);
		}
		sprintf((*result)[i], "%d", *low + 1);
	}
}



void scan (int argc, char *argv[]) {
	if (argc < 4) {
		usage();
		exit (EXIT_FAILURE);
	}

	struct protoent *protocol = getprotobyname("IP");
	if (protocol < 0) { 
		perror ("getprotobyname");
		exit (EXIT_FAILURE);
	}

	struct addrinfo *result;
	struct addrinfo hints = {
		.ai_family = AF_UNSPEC,
		.ai_socktype = SOCK_STREAM,
		.ai_flags = 0,
		.ai_protocol = protocol->p_proto };

	const char* host = argv[1];
	int port1i = atoi(argv[2]);
	int port2i = atoi(argv[3]);

	if (port1i == 0 || port2i == 0 || port2i < port1i) {
		usage();
		exit (EXIT_FAILURE);
	}
	char **array;

      	createPortList (&port1i, &port2i, &array); // todo: Add error handling;

	for (int i = 0; i <= port2i - port1i; i++) {
      		int s = getaddrinfo(host, array[i], &hints, &result);
      		if (s < 0) {
      			perror ("getaddrinfo");
			free (array[i]);
      			continue;
      		}

      		int sockfd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
      		if (sockfd < 0) {
      			perror ("socket");
			freeaddrinfo(result);
			free (array[i]);
			continue;
      		}

      		if (connect (sockfd, result->ai_addr, result->ai_addrlen) < 0) {
      			perror ("connect");
			close(sockfd);
      		} else {
			printf("Port %s is open", port1i + i);
			close(sockfd);
		}
		freeaddrinfo(result);
		free (array[i]);
      	}
	free (array);
}


void usage() { printf ("Usage: ./scan <host> <FROM> <TO>\n"); }

