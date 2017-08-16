#ifndef LINK_H
#define LINK_H

#include"public.h"

typedef struct FileNode
{
    char caFileName[NAME_LEN];
    struct FileNode *next;
}FileNode;

typedef struct FileLink
{
    FileNode *pFirstNode;
    uint uiLen;
}FileLink;

FileNode *makeFileNode();
FileLink *makeFileLink();
void insertFileLink(FileLink *link, FileNode *node);
void showFileLink(const FileLink *link);
void delFileNodeByName(FileLink *link, const char *pathname);
FileNode *findFileNodeByName(const FileLink *link, const char *pathname);

#endif // LINK_H

