#ifndef FT_NM_H
#define FT_NM_H
#define t_stat struct stat

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>

#include "libft.h"

typedef struct s_file {
    char    *name;
    char    *error;
    int     fd;
}   t_file;

typedef struct s_nm {
    t_list  *files;
}   t_nm;


#endif