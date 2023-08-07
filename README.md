# ft_ls
Recode the system’s command ls

## Flags
- l - use a long listing format
- R - list subdirectories recursively
- a - do not ignore entries starting with .
- r - reverse order while sorting
- t - sort by modification time, newest first

## Bonus
- f - do not sort, enable -aU, disable -ls --color
- Management of ACL and extended attributes.
- Management of the columns without the option -l. (man 4 tty)

## Use this project
- git clone --recursive ....this_project
- or git clone ....this_project + git submodule update --init external/libft

## Within your mandatory part you are allowed to use the following functions:
- opendir
- readdir
- closedir
- stat
- lstat
- getpwuid
- getgrgid
- listxattr
- getxattr
- time
- ctime
- readlink
- perror
- strerror
- ===IN USE=====
- malloc
- free
- write
