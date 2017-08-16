#include "client.h"

int main(void)
{
    int sockfd = makeSocket();
    connectToServer(sockfd);
    handle(sockfd);

    printf("Hello World!\n");
    return 0;
}

