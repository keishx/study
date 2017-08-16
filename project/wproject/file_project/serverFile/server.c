#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#include "server.h"
#include "protocol.h"

FileLink *g_pFileLink;

static void handleClientSearchRequest(int sockfd)
{
    PDU *pdu = NULL;
    pdu = makePDU(NAME_LEN*g_pFileLink->uiLen);//把所有文件名字传过去，每个名字长度*名字个数
	printf("file num = %d\n", g_pFileLink->uiLen);
    pdu->uiMsgType = ENUM_MSG_TYPE_SEARCH_RESPOND;
    int i = 0;
    FileNode *fileNode = g_pFileLink->pFirstNode;
    for (; NULL != fileNode; i++)//把文件存放在caMsg
    {
        memcpy(pdu->caMsg+i*NAME_LEN, fileNode->caFileName, NAME_LEN);
        fileNode = fileNode->next;
    }
    write(sockfd, pdu, pdu->uiPDULen);
    freePDU(pdu);
}
static void handleClientUploadFileRequest(int sockfd, PDU *pdu)
{
	char caPathname[160] = {'\0'};//把路径加到文件前
	strcpy(caPathname, FILE_DIR);
	strcat(caPathname, "/");
	strcat(caPathname, pdu->caName);

	char caFileName[NAME_LEN] = {'\0'};
	strcpy(caFileName, pdu->caName);	//文件名放入caName

	int fd = openFile(caPathname, O_RDWR);
	int recvSize = pdu->uiMsgLen;
	write(fd, pdu->caMsg, pdu->uiMsgLen);//读取第一个PDU，每个PDU放一部分，放总长度大小
	
	PDU *filepdu = NULL;
	if (recvSize != pdu->uiFileSize)
	{
		while (1)
		{
			filepdu = readPDU(sockfd);
			if (NULL == filepdu)
			{
				printf("client disconnected\n");
				freePDU(filepdu);
				return;
			}
			write(fd, filepdu->caMsg, filepdu->uiMsgLen);
			recvSize += filepdu->uiMsgLen;
			freePDU(filepdu);
			if (recvSize == pdu->uiFileSize)
			{
				break;
			}
		}
	}
	filepdu = makePDU(strlen(UPLOAD_OK));
	filepdu->uiMsgType = ENUM_MSG_TYPE_UPLOAD_RESPOND;
	memcpy(filepdu->caMsg, UPLOAD_OK, strlen(UPLOAD_OK));
	write(sockfd, filepdu, filepdu->uiPDULen);
	freePDU(filepdu);
	
	FileNode *fileNode = makeFileNode();
	strcpy(fileNode->caFileName, caFileName);
	insertFileLink(g_pFileLink, fileNode);
}
static void handleClientDownloadFileRequest(int sockfd, PDU *pdu)
{
	char caPathname[160] = {'\0'};
	strcpy(caPathname, FILE_DIR);
	strcat(caPathname, "/");
	strcat(caPathname, pdu->caName);
	printf("人%s\n",caPathname);

	int fd=openFile(caPathname,O_RDWR);
	
	PDU *filepdu=makePDU(PER_MAX_IO_BYTES);
	uint size=getFileSize(caPathname);
	uint fileSize=size;
	int ret=-1;
	int recvSize=filepdu->uiMsgLen;
	filepdu->uiFileSize=fileSize;
	strcpy(filepdu->caName,pdu->caName);
//	read(fd,filepdu->caMsg,filepdu->uiMsgLen);
//	freePDU(pdu);

	while(1)
	{
		
		printf("开始下载\n");
		if(PER_MAX_IO_BYTES<size)
		{
			printf("很快就借口\n");
			ret=read(fd,filepdu->caMsg,PER_MAX_IO_BYTES);
			printf("猪%d\n",ret);
		}
		else
		{
			ret=read(fd,filepdu->caMsg,size);
			printf("22猪%d\n",ret);
		}
		printf("就会得到的-----\n");
		if(-1==ret)
		{
			perror("read");
			exit(EXIT_FAILURE);
		}
		else if(0==ret)
		{
			printf("鲁迅\n");
			break;
		}
		filepdu->uiMsgLen=ret;
		printf("e健康来了\n");
		write(sockfd,filepdu,filepdu->uiPDULen);
		size-=ret;
	}
	freePDU(filepdu);
	
	

	
}
static void handleClientDeleteFileRequest(int sockfd, PDU *pdu)
{
	char caPathname[64] = {'\0'};
	strcpy(caPathname, FILE_DIR);
	strcat(caPathname, "/");
	strcat(caPathname, pdu->caName);
	
	int ret = remove(caPathname);
	PDU *respdu = NULL;
	if (0 == ret)
	{
		respdu = makePDU(strlen(DELETE_OK));
		memcpy(respdu->caMsg, DELETE_OK, strlen(DELETE_OK));
		delFileNodeByName(g_pFileLink, pdu->caName);
	}
	else
	{
		perror("delete file");
		memcpy(respdu->caMsg, DELETE_FAILED, strlen(DELETE_FAILED));
		respdu = makePDU(strlen(DELETE_FAILED));
	}
	respdu->uiMsgType = ENUM_MSG_TYPE_DELETE_RESPOND;
	write(sockfd, respdu, respdu->uiPDULen);
	freePDU(respdu);
}
static void handleClientRenameFileRequest(int sockfd, PDU *pdu)
{
	char caOldPathname[64] = {'\0'};
	strcpy(caOldPathname, FILE_DIR);
	strcat(caOldPathname, "/");
	strcat(caOldPathname, pdu->caName);
	
	char caNewPathname[64] = {'\0'};
	strcpy(caNewPathname, FILE_DIR);
	strcat(caNewPathname, "/");
	strcat(caNewPathname, pdu->caMsg);
	
	int ret = rename(caOldPathname, caNewPathname);
	PDU *respdu = NULL;
	if (0 == ret)
	{
		FileNode *fileNode = findFileNodeByName(g_pFileLink, pdu->caName);
		memset(fileNode->caFileName, '\0', NAME_LEN);
		strcpy(fileNode->caFileName, pdu->caMsg);

		respdu = makePDU(strlen(RENAME_OK));
		memcpy(respdu->caMsg, RENAME_OK, strlen(RENAME_OK));
	}
	else
	{
		perror("rename file");
		respdu = makePDU(strlen(RENAME_FAILED));
		memcpy(respdu->caMsg, RENAME_FAILED, strlen(RENAME_FAILED));
	}
	respdu->uiMsgType = ENUM_MSG_TYPE_REANME_RESPOND;
	write(sockfd, respdu, respdu->uiPDULen);
	freePDU(respdu);
}

static void *handleClient(void *arg)
{
    int sockfd = (int)arg;
    PDU *pdu = NULL;
    while (1)
    {
        pdu = readPDU(sockfd);
        if (NULL == pdu)
        {
            printf("client disconnected\n");
            pthread_exit(NULL);
        }
        switch (pdu->uiMsgType)
        {
        case ENUM_MSG_TYPE_SEARCH_REQUEST:
            handleClientSearchRequest(sockfd);
            break;
        case ENUM_MSG_TYPE_UPLOAD_REQUEST:
			handleClientUploadFileRequest(sockfd, pdu);
            break;
        case ENUM_MSG_TYPE_DOWNLOAD_REQUEST:
			handleClientDownloadFileRequest(sockfd, pdu);
            break;
        case ENUM_MSG_TYPE_REANME_REQUEST:
			handleClientRenameFileRequest(sockfd, pdu);
            break;
        case ENUM_MSG_TYPE_DELETE_REQUEST:
			handleClientDeleteFileRequest(sockfd, pdu);
            break;
        default:
            break;
        }
        freePDU(pdu);
    }

    return NULL;
}

int makeSocket()
{
	int sockfd = -1;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (-1 == sockfd)
	{
		perror("socket");
		exit(EXIT_FAILURE);
	}
    return sockfd;
}

void makeBind(int sockfd)
{
	int ret = -1;
	struct sockaddr_in servAddr;
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(8080);
	servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	bzero(&(servAddr.sin_zero), 8);
	//将socket和指定的地址绑定：表示在这个绑定的ip上进行监听和接收处理客户端的连接
	ret = bind(sockfd
			, (struct sockaddr *)&servAddr
			, sizeof(servAddr));
	if (-1 == ret)
	{
		perror("bind");
		exit(EXIT_FAILURE);
	}
}

void makeListen(int sockfd)
{
	//设置该socket每次能够处理的最大客户端数
    int ret = listen(sockfd, 10);
	if (-1 == ret)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}
}

static void makeThreadForHandleClient(int sockfd)
{
    //每来一个客户端都创建一个线程来专门处理
    pthread_t thread;
    int ret = pthread_create(&thread, NULL
                , handleClient
                , (void*)sockfd);
    if (0 != ret)
    {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }
}

void acceptClient(int sockfd)
{
	int clientSockfd = -1;
	struct sockaddr_in clientAddr;
	int iAddrLen = sizeof(clientAddr);
	while (1)
	{
		//阻塞等待接收客户端的连接
		//每来一个客户端的连接，
		//都会创建一个socket，
		//返回该socket的描述符
		//用于服务器和客户端通信
		printf("accept client...\n");
		clientSockfd = accept(sockfd
			, (struct sockaddr *)&clientAddr
			, &iAddrLen);
		if (-1 == clientSockfd)
		{
			perror("accept");
			exit(EXIT_FAILURE);
		}
        makeThreadForHandleClient(clientSockfd);
	}	
}
