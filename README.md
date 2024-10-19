# Shell

## overview
In this I implemented POSIX Shell using cpp

## How to run the program
- make clean
- make
- make run


## Commands Implemented
- echo
- cd
- pwd
- ls
- history
- foreground and background
- pinfo
- search
- pipeline

## Assumptions 
- In echo only "---" string is printed
- In cd ~ is treated as home path
- In pwd starting path is treated as home path
- In history only 20 recent commands is shown
- In pipeline all commands are executed using execvp

