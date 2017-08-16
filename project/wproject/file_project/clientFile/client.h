#ifndef CLIENT_H
#define CLIENT_H

#include "public.h"

enum ENUM_OPERATE
{
    ENUM_OPERATE_MIN = -1,
    ENUM_OPERATE_SEARCH_FILE = 1,
    ENUM_OPERATE_UPLOAD_FILE = 2,
    ENUM_OPERATE_DOWNLOAD_FILE = 3,
    ENUM_OPERATE_DELETE_FILE = 4,
    ENUM_OPERATE_RENAME_FILE = 5,
    ENUM_OPERATE_EXIT = 0,
    ENUM_OPERATE_MAX = 0x00ffffff
};

int makeSocket();
void connectToServer(int sockfd);
void handle(int sockfd);

#endif
