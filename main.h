/*
 shawn: SHell of AWesomeNess - A Demonstration of fork and exec
 Copyright (C) 2013  Dirk "26thmeusoc" Braun
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#define _BSD_SOURCE     // Required for Feature Test Macros

#include <stdlib.h>           // For EXIT_FAILURE/SUCCES
#include <stdio.h>            // For IO Operations
#include <errno.h>            // For errno
#include <unistd.h>           // For gethostname()
#include <readline/readline.h> // For readline()
#include <string.h>           // For sterror(), strtok()
#include <sys/types.h>        // For wait()
#include <sys/wait.h>         // For wait()
#include "builtin.h"          // For builtin Applications
#include "log.h"              // For message-Functions


/*!
 * shawn - SHell of AWesomeNess
 *
 * \author Dirk '26thmeusoc' Braun
 * \version 1.1
 */
 
 
/*!
 * Search for next part of Command.
 * 
 * Searches for next whitespace in cmd. It is then replaced by '\0'.
 * find_next_space() returns a pointer to next character, followed by whitespace.
 * 
 * General Idea for this code by Marco 'mhi' Hinz
 * 
 * \param cmd Commandlinetext, given by user
 * \return Pointer to next substring, NULL if end of String is reached 
 * or cmd starts with #, which means this section is comment!
 */
char *find_next_space(char *cmd);

/*!
 * Count number of parameters in cmd. We define this as number of
 * unescaped whitespaces.
 * 
 * \param cmd Commandlinearguments, given by user
 * \return Number of Parameters (unescaped whitespaces)
 */
int count_paramters(char *cmd);

/*!
 * Searches for first occurerence of charac.
 * Then moves every character following it one letter back.
 * 
 * \param str String where character should be deleted
 * \param charc Character to be removed
 * \return 1 if a character was deleted, 0 else.
 */
int remove_next_special_character(char *str, char charac);

/*!
 * Remove all occurrences of charac in str.
 * 
 * \param str String, where charac should be deleted.
 * \param charac Character which should be deleted.
 */
void remove_character(char *str, char charac);

/*!
 * Remove the leading whitespaces of str.
 * 
 * \param str String, where whitespaces should get deleted
 */
char *remove_leading_whitespaces(char *str);
