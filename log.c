/*
 log.c 
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

#include "log.h"

/*!
 * Helpermethods for Logging.
 *
 * \author Dirk '26thmeusoc' Braun
 * \version 1.0
 */

void errno_msg(char *message, int recoverable) {
	// Print error
	fprintf(stderr, "[ERROR] %s: %s (%d)\n", message, strerror(errno), errno);
	if (recoverable == 0) {
		exit(EXIT_FAILURE); // Can't continue! Quit now!
	}
} 
 
void error_msg(char *message, int recoverable) {
	fprintf(stderr, "[ERROR] %s\n", message); // Print Error
	if (recoverable == 0) {
		exit(EXIT_FAILURE); // Can't continue! Quit now!
	}
}

void debug_msg(char *message) {
	#if DEBUG // Was preprocessormacro set at compiletime?
	printf("[DEBUG] %s\n", message); //Print message
	#endif
}
