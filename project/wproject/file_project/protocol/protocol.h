#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "public.h"

#define UPLOAD_OK        "upload_ok"
#define DOWNLOAD_OK      "download_ok"
#define DELETE_OK        "delete_ok"
#define DELETE_FAILED    "delete_failed"
#define RENAME_OK        "rename_ok"
#define RENAME_FAILED    "rename_failed"

enum ENUM_MSG_TYPE
{
	ENUM_MSG_TYPE_MIN = 0,
    ENUM_MSG_TYPE_SEARCH_REQUEST,    //查看请求
    ENUM_MSG_TYPE_SEARCH_RESPOND,    //查看回复
    ENUM_MSG_TYPE_UPLOAD_REQUEST,    //上传请求
    ENUM_MSG_TYPE_UPLOAD_RESPOND,    //上传回复
    ENUM_MSG_TYPE_DOWNLOAD_REQUEST,  //下载请求
    ENUM_MSG_TYPE_DOWNLOAD_RESPOND,  //下载回复
    ENUM_MSG_TYPE_REANME_REQUEST,    //重命名请求
    ENUM_MSG_TYPE_REANME_RESPOND,    //重命名回复
    ENUM_MSG_TYPE_DELETE_REQUEST,    //删除请求
    ENUM_MSG_TYPE_DELETE_RESPOND,    //删除回复
	ENUM_MSG_TYPE_MAX = 0x00ffffff
};

//PDU:协议数据单元
typedef struct PDU
{
    uint uiPDULen;    //消息结构体总大小
    uint uiMsgType;   //消息类型
    char caName[64];  //文件名
    uint uiFileSize;  //总文件大小
    uint uiMsgLen;    //这个pdu存放文件的大小
    char caMsg[4];    //这个PDU文件
}PDU;

PDU *makePDU(uint uiMsgLen);
void freePDU(PDU *pdu);
PDU *readPDU(int sockfd);

#endif
