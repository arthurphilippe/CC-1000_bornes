/*
** EPITECH PROJECT, 2018
** Untitled (Workspace)
** File description:
** connect
*/

#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include "game.h"
#include "stolist.h"

static int extract_port(list_t *args)
{
	const char *str_port = list_get_back(args);

	return (atoi(str_port));
}

int socket_create_and_connect(char *host, int port)
{
	struct sockaddr_in addr;
	struct protoent *pt = getprotobyname("TCP");
	struct hostent *ip = NULL;
	struct in_addr **serv_char_ip = NULL;
	int fd;

	memset(&addr, 0, sizeof(struct sockaddr_in));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	if ((ip = gethostbyname(host)) == NULL) return (-1);
	serv_char_ip = (struct in_addr **) ip->h_addr_list;
	inet_pton(AF_INET, inet_ntoa(*serv_char_ip[0]), &addr.sin_addr);
	fd = socket(AF_INET, SOCK_STREAM, pt->p_proto);
	if (fd == -1) return (-1);
	if (connect(fd, (struct sockaddr *) &addr, sizeof(addr)) == -1)
		return (-1);
	return (fd);
}

int game_connect(game_t *ga, const char *arg_str)
{
	list_t *args = stolist(arg_str, ":");
	char *host;
	int port;

	if (list_get_size(args) < 2) {
		dprintf(2, "%s\n",
			"game_connect: argument format must be \"IP:PORT\"");
		ga->ga_live = false;
		list_destroy(args);
		return (-1);
	}
	host = list_get_front(args);
	port = extract_port(args);
	if (!port) {
		dprintf(2, "%s\n",
			"game_connect: port is either not formed of digits "
			"or is not set\nformat: \"IP:PORT\"");
		ga->ga_live = false;
		list_destroy(args);
		return (-1);
	}
	ga->ga_socketfd = socket_create_and_connect(host, port);
	if (ga->ga_socketfd == -1) {
		perror("game_connect");
		ga->ga_live = false;
		list_destroy(args);
		return (-1);
	}
	list_destroy(args);
	return (0);
}
