# ft_ls
Recode the system’s command ls

## Flags
- l - use a long listing format
- R - list subdirectories recursively
- a - do not ignore entries starting with .
- r - reverse order while sorting
- t - sort by modification time, newest first

## Use this project
- git clone --recursive ....

## Use external lib
- libft
	- git submodule add https://github.com/CroWcbr/libft.git external/libft

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