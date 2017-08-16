#include "server.h"

extern FileLink *g_pFileLink;
int main(void)
{
    g_pFileLink = makeFileLink();
    scanFile(FILE_DIR, g_pFileLink);
	showFileLink(g_pFileLink);

    int sockfd = makeSocket();
    makeBind(sockfd);
    makeListen(sockfd);
    acceptClient(sockfd);

    printf("Hello World!\n");
    return 0;
}

