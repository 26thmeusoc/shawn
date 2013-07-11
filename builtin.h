/*
 builtin.h 
 Copyright (C) 2013  Dirk "26thmeusoc" Braun
 
 This file is part of shawn.
 
 shawn is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 shawn is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with shawn.  If not, see <http://www.gnu.org/licenses/>.
 */

#define _BSD_SOURCE // Required for Feature Test Macros

#include <stdlib.h>  // For EXIT_FAILURE/SUCCES
#include <stdio.h>   // For IO Operations
#include <sys/stat.h> // For stat
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include "log.h"

/*!
 * builtin Applications for shawn.
 *
 * \author Dirk '26thmeusoc' Braun
 * \version 1.1
 */

/*!
 * Print message
 * 
 * \param message Message to be printed
 */
void echo(char *message);

/*!
 * Print environment variables
 */
void env();

/*!
 * Clear screen
 */
void clear();

/*!
 * Change directory.
 * 
 * \param dir Target Directory.
 */
void cd(char *dir);

/*!
 * Print working directory
 */
void pwd();

/*!
 * List Contents of Directory saved in $PWD.
 */
void ls();

/*!
 * Set Environmentvariable.
 * 
 * \param name Name of Variable to be set
 * \param val New value of 'name'
 */
void set(char *name, char *val);

/*!
 * Print Informations about current Version
 */
void version();
