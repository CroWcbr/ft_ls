# ft_ls
Recode the system’s command ls

## Flags
- l - use a long listing format
- R - list subdirectories recursively
- a - do not ignore entries starting with .
- r - reverse order while sorting
- t - sort by modification time, newest first

## Bonus
- Management of ACL and extended attributes.
- Management of the columns without the option -l. (man 4 tty)
- A - do not list implied . and ..
- d - list directories themselves, not their contents
- f - do not sort, enable -aU, disable -ls --color
- g - like -l, but do not list owner
- i - print the index number of each file
- m - fill width with a comma separated list of entries
- n - like -l, but list numeric user and group IDs
- o - like -l, but do not list group information
- s - print the allocated size of each file, in blocks
- S - sort by file size, largest first
- U - do not sort; list entries in directory order
--help - display this help and exit
--color - colorize the output

## Use this project
- git clone --recursive ....this_project
- or git clone ....this_project + git submodule update --init external/libft
