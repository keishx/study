#include "protocol.h"

PDU *makePDU(uint uiMsgLen)
{
	uint uiPDULen = 0;
	uiPDULen = sizeof(PDU) - 4*sizeof(char)
			   + uiMsgLen;
	PDU *pdu = (PDU *)malloc(uiPDULen);
	if (NULL == pdu)
	{
		printf("malloc pdu failed\n");
		exit(EXIT_FAILURE);
	}
	memset(pdu, 0, uiPDULen);
	pdu->uiPDULen = uiPDULen;
	pdu->uiMsgLen = uiMsgLen;
	return pdu;
}
void freePDU(PDU *pdu)
{
	if (NULL != pdu)
	{
		free(pdu);
	}
}

PDU *readPDU(int sockfd)
{
	uint uiPDULen = 0;
	int ret = -1;
	ret = read(sockfd, &uiPDULen, sizeof(uint));//读取总大小数值
	if (-1 == ret)
	{
		perror("read 1");
		exit(EXIT_FAILURE);
	}

    if (0 == ret)
    {
        return NULL;
    }

	uint uiMsgLen = 
		uiPDULen-(sizeof(PDU)-4*sizeof(char));
	PDU *pdu = makePDU(uiMsgLen);
	ret = read(sockfd, (char*)pdu+sizeof(uint)//读取剩下的部分
			   , uiPDULen-sizeof(uint));
	if (-1 == ret)
	{
		perror("read 2");
		exit(EXIT_FAILURE);
	}
	return pdu;
}





