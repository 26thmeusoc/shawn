#! /bin/bash

# (c) 2011 Dirk Braun

if [ "$1" = "debug" ] ; then
	gcc main.c builtin.c log.c -o shawn -DDEBUG=1 -Wall -std=c99 -I/usr/include/readline
else
	gcc main.c builtin.c log.c -o shawn -Wall -std=c99
fi
