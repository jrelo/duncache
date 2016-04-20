#include <unistd.h>
#include <fcntl.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fts.h>
#include<string.h>
#include<errno.h>

/*
 * duncache.c 
 * quickly remove files in directory from linux page cache with POSIX_FADV_DONTNEED and fts() functions.
 * http://github.com/jrelo/duncache
 */

int compare (const FTSENT**, const FTSENT**);
int fd;

int main(int argc, char* const argv[])
{
    FTS* fs = NULL;
    FTSENT* child = NULL;
    FTSENT* parent = NULL;

    if (argc<2)
    {
        printf("Usage: %s <path-spec>\n", argv[0]);
        exit(255);
    }

    fs = fts_open(argv + 1,FTS_COMFOLLOW | FTS_NOCHDIR,&compare);

    if (NULL != fs)
    {
        while( (parent = fts_read(fs)) != NULL)
        {
            child = fts_children(fs,0);

            if (errno != 0)
            {
                perror("fts_children");
            }

            while ((NULL != child)
                && (NULL != child->fts_link))
            {
                child = child->fts_link;
                // char* s = concat(child->fts_path, child->fts_name);
                fd = open(child->fts_name, O_RDONLY);
                fdatasync(fd);
                posix_fadvise(fd, 0,0,POSIX_FADV_DONTNEED);
                printf("%s%s -> POSIX_FADV_DONTNEED\n", child->fts_path,child->fts_name);
				close(fd);

	    }
        }
        fts_close(fs);
    }
    return 0;
}

int compare(const FTSENT** one, const FTSENT** two)
{
    return (strcmp((*one)->fts_name, (*two)->fts_name));
}
