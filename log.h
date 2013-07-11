/*
 log.h 
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

#include <stdio.h>   // For IO Operations
#include <errno.h>   // For errno
#include <string.h>  // For strerror
#include <stdlib.h>

/*!
 * Helpermethods for Logging.
 *
 * \author Dirk '26thmeusoc' Braun
 * \version 1.0
 */

/*!
 * Print an Errormessage. Give further Informations by using errno and
 * strerror().
 * 
 * \param message Message, provided by developer
 * \param recoverable If FALSE, quit this application. Otherwise continue
 */
void errno_msg(char *message, int recoverable);

/*!
 * Print an Errormessage.
 * 
 * \param message Message, provided by developer
 * \param recoverable If 0, quit this application. Otherwise continue
 */
void error_msg(char *message, int recoverable);

/*!
 * Print an Debugmessage. Notice, this is only possible, if 
 * Preprocessormacro 'DEBUG' is set at compiletime.
 * 
 * \param message Message to be printed.
 */
void debug_msg(char *debugmsg);

/*!
 * Parses given commandline argument given by user.
 * 
 * \param cmd Commandlinetext given by user
 */
void parse_cmd(char *cmd);
