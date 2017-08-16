 #include "fileope.h"

int openFile(const char *pathname, int flags)
{
    int fd = -1;
    fd = open(pathname, flags|O_CREAT, 0664);
    if (-1 == fd)
    {
        perror("open file");
        exit(EXIT_FAILURE);
    }
    return fd;
}


uint getFileSize(const char *pathname)
{
    int fd = -1;
    fd = openFile(pathname, O_RDWR);
    off_t off = -1;
    off = lseek(fd, 0, SEEK_END);
    if (-1 == off)
    {
        perror("lseek");
        exit(EXIT_FAILURE);
    }
    lseek(fd, 0, SEEK_SET);
    close(fd);
    return off;
}


void scanFile(const char *dir, FileLink *link)
{
    if (NULL == dir || NULL == link)
    {
        return;
    }
    DIR *pdir = opendir(dir);
    if (NULL == pdir)
    {
        perror("opendir");
        exit(EXIT_FAILURE);
    }
    FileNode *fileNode = NULL;
    struct dirent *pdirent = NULL;
    pdirent = readdir(pdir);
    while (NULL != pdirent)
    {
        fileNode = makeFileNode();
        if (0 != strcmp(".", pdirent->d_name)
            && 0 != strcmp("..", pdirent->d_name))
        {
            strcpy(fileNode->caFileName, pdirent->d_name);
            insertFileLink(link, fileNode);
        }
        pdirent = readdir(pdir);
    }
    closedir(pdir);
}
