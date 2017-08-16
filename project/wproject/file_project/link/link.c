#include "link.h"


FileNode *makeFileNode()
{
    FileNode *node = (FileNode *)malloc(sizeof(FileNode));
    if (NULL == node)
    {
        printf("malloc file node failed\n");
        exit(EXIT_FAILURE);
    }
    memset(node, 0, sizeof(FileNode));
    node->next = NULL;
    return node;
}


FileLink *makeFileLink()
{
    FileLink *link = (FileLink *)malloc(sizeof(FileLink));
    if (NULL == link)
    {
        printf("malloc file link failed\n");
        exit(EXIT_FAILURE);
    }
    memset(link, 0, sizeof(FileLink));
    link->pFirstNode = NULL;
    link->uiLen = 0;
    return link;
}


void insertFileLink(FileLink *link, FileNode *node)
{
    if (NULL == link || NULL == node)
    {
        return;
    }
    node->next = link->pFirstNode;
    link->pFirstNode = node;
	link->uiLen++;
}


void showFileLink(const FileLink *link)
{
    if (NULL == link)
    {
        return;
    }
    FileNode *node = link->pFirstNode;
    while (NULL != node)
    {
        printf("%s\n", node->caFileName);
        node = node->next;
    }
}


void delFileNodeByName(FileLink *link, const char *pathname)
{
    if (NULL == link || NULL == pathname)
    {
        return;
    }
    FileNode *pre = link->pFirstNode;
    FileNode *cur= pre;
    while (NULL != cur)
    {
        if (0 == strcmp(pathname, cur->caFileName))
        {
            if (link->pFirstNode == cur)
            {
                link->pFirstNode = cur->next;
            }
            else
            {
                pre->next = cur->next;
            }
            break;
        }
        pre = cur;
        cur = cur->next;
    }
    free(cur);
    cur = NULL;
}


FileNode *findFileNodeByName(const FileLink *link, const char *pathname)
{
    if (NULL == link || NULL == pathname)
    {
        return NULL;
    }
    FileNode *node = link->pFirstNode;
    while (NULL != node)
    {
        if (0 == strcmp(pathname, node->caFileName))
        {
            break;
        }
        node = node->next;
    }
    return node;
}
