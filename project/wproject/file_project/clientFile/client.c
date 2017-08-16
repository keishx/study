#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#include "client.h"
#include "protocol.h"
#include "fileope.h"

int makeSocket()
{
    //AF_INET:ipv4
    //SOCK_STREAM:tcp(基于连接的可靠通信方式)
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == sockfd)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    return sockfd;
}

void connectToServer(int sockfd)
{
    struct sockaddr_in servAddr;
    servAddr.sin_family = AF_INET;
    //htons:将本地字节序转化成网络字节序
    servAddr.sin_port = htons(8080);
    //inet_addr：将字符串表示的地址转换成整形
    //127.0.0.1:表示本地环回的一个地址
    //消息不会往外发送，自己发送给自己
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    bzero(&(servAddr.sin_zero), 8);
    int ret = -1;
    //连接服务器
    ret = connect(sockfd
                , (struct sockaddr *)&servAddr
                , sizeof(servAddr));
    if (0 != ret)
    {
        perror("connect");
        exit(EXIT_FAILURE);
    }
}

static int operateFace()
{
    printf("\twelcome\n");
    printf("1,查看文件\n");
    printf("2,上传文件\n");
    printf("3,下载文件\n");
    printf("4,删除文件\n");
    printf("5,文件重命名\n");
    printf("0,退出\n");
    printf("输入操作选项:\n");
    int num = -1;
    scanf("%d", &num);
    return num;
}

static void searchFile(int sockfd)
{
    PDU *pdu = makePDU(0);
    pdu->uiMsgType = ENUM_MSG_TYPE_SEARCH_REQUEST;
    write(sockfd, pdu, pdu->uiPDULen);
    freePDU(pdu);

    pdu = readPDU(sockfd);
    if (NULL == pdu)
    {
        printf("disconnect to server\n");
        return;
    }
    if (ENUM_MSG_TYPE_SEARCH_RESPOND == pdu->uiMsgType)
    {
        int num = pdu->uiMsgLen;
        if (0 == num)
        {
            return;
        }
        int i = 0;
        char file[NAME_LEN] = {'\0'};
        for (; i < num/NAME_LEN; i++)
        {
            memset(file, '\0', NAME_LEN);
            memcpy(file, pdu->caMsg+i*NAME_LEN, NAME_LEN);
            printf("%s\n", file);
        }
    }
    free(pdu);
}

char *getFileName(const char *pathname)
{
	char *filename = NULL;
	if (NULL != pathname)
	{
		filename = strrchr(pathname, '/');
		filename++;
	}
	return filename;
}

static void uploadFile(int sockfd)
{
	char caPathname[128] = {'\0'};
	printf("请输入要上传的文件：");
	scanf("%s", caPathname);
	while(getchar()!='\n');
	uint size = getFileSize(caPathname);
	uint fileSize = size;
	int fd = openFile(caPathname, O_RDONLY);
	int ret = -1;
	
	PDU *pdu = makePDU(PER_MAX_IO_BYTES);
	strcpy(pdu->caName, getFileName(caPathname));
	pdu->uiFileSize = fileSize;
	pdu->uiMsgType = ENUM_MSG_TYPE_UPLOAD_REQUEST;
	
	while (1)
	{
		printf("开始上传\n");
		if (PER_MAX_IO_BYTES < size)
		{
			ret = read(fd, pdu->caMsg, PER_MAX_IO_BYTES);
		}
		else
		{
			ret = read(fd, pdu->caMsg, size);
		}
		if (-1 == ret)
		{
			perror("read");
			exit(EXIT_FAILURE);
		}
		else if (0 == ret)
		{
			break;
		}
		pdu->uiMsgLen = ret;
		write(sockfd, pdu, pdu->uiPDULen);
		size -= ret;
	}
	freePDU(pdu);
	pdu = readPDU(sockfd);
	if (ENUM_MSG_TYPE_UPLOAD_RESPOND == pdu->uiMsgType
		&& 0 == strncmp(UPLOAD_OK, pdu->caMsg, pdu->uiMsgLen))
	{
		printf("upload ok\n");
	}
	else
	{
		printf("upload failed\n");
	}
	freePDU(pdu);
}
static void downloadFile(int sockfd)
{
	PDU *pdu = makePDU(0);
	printf("请输入要下载的文件名：");
	scanf("%s",pdu->caName);
	pdu->uiMsgType=ENUM_MSG_TYPE_DOWNLOAD_REQUEST;
	write(sockfd,pdu,pdu->uiPDULen);
	freePDU(pdu);

	pdu = readPDU(sockfd);
	char caPathname[60]="\0";
	strcpy(caPathname,pdu->caName);

	int fd =openFile(caPathname,O_RDWR);
	int recvSize=pdu->uiMsgLen;
	write(fd,pdu->caMsg,pdu->uiMsgLen);

	PDU	*filepdu=NULL;
	if(recvSize!=pdu->uiFileSize)
	{
		while(1)
		{
			printf("123\n");
			filepdu=readPDU(sockfd);
			if(NULL==filepdu)
			{
				printf("client disconnected");
				freePDU(filepdu);
				return;
			}
			write(fd,filepdu->caMsg,filepdu->uiMsgLen);
			recvSize+=filepdu->uiMsgLen;
			freePDU(filepdu);
			if(recvSize==pdu->uiFileSize)
			{
				break;
			}
		}
	}
	printf("下载成功！\n");
}
static void deleteFile(int sockfd)
{
	PDU *pdu = makePDU(0);
	printf("请输入要删除的文件名:");
	scanf("%s", pdu->caName);
	pdu->uiMsgType = ENUM_MSG_TYPE_DELETE_REQUEST;
	write(sockfd, pdu, pdu->uiPDULen);
	freePDU(pdu);



	pdu = readPDU(sockfd);
	if (ENUM_MSG_TYPE_DELETE_RESPOND == pdu->uiMsgType
		&& 0 == strncmp(pdu->caMsg, DELETE_OK
				        , strlen(DELETE_OK)))
	{
		printf("delete file ok\n");
	}
	else
	{
		printf("delete file failed\n");
	}
	freePDU(pdu);
}
static void renameFile(int sockfd)
{
	PDU *pdu = makePDU(NAME_LEN);
	printf("请输入要命名的文件:");
	scanf("%s", pdu->caName);
	printf("请输入新文件名:");
	scanf("%s", pdu->caMsg);
	pdu->uiMsgType = ENUM_MSG_TYPE_REANME_REQUEST;
	write(sockfd, pdu, pdu->uiPDULen);
	freePDU(pdu);

	pdu = readPDU(sockfd);
	if (ENUM_MSG_TYPE_REANME_RESPOND == pdu->uiMsgType
	    && 0 == strncmp(RENAME_OK, pdu->caMsg
			            , strlen(RENAME_OK)))
	{
		printf("重命名文件成功\n");
	}
	else
	{
		printf("重命名文件失败\n");
	}
	freePDU(pdu);
}

void handle(int sockfd)
{
    int ret = -1;
    while (1)
    {
        ret = operateFace();
        switch (ret)
        {
        case ENUM_OPERATE_SEARCH_FILE:
            searchFile(sockfd);
            break;
        case ENUM_OPERATE_UPLOAD_FILE:
			uploadFile(sockfd);
            break;
        case ENUM_OPERATE_DOWNLOAD_FILE:
			downloadFile(sockfd);
            break;
        case ENUM_OPERATE_DELETE_FILE:
			deleteFile(sockfd);
            break;
        case ENUM_OPERATE_RENAME_FILE:
			renameFile(sockfd);
            break;
        case ENUM_OPERATE_EXIT:
            return;
        default:
            break;
        }
    }
}
