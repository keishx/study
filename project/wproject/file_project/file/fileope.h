#ifndef FILEOPE_H
#define FILEOPE_H

#include "public.h"
#include "link.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>

#define FILE_DIR "shared_file"

int openFile(const char *pathname, int flags);
uint getFileSize(const char *pathname);
void scanFile(const char *dir, FileLink *link);

#endif // FILEOPE_H

