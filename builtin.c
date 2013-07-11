/*
 builtin.c
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

#include "builtin.h"

/*!
 * builtin Applications for shawn.
 *
 * \author Dirk '26thmeusoc' Braun
 * \version 1.1
 */

extern char **environ;

void echo(char *message) {
	debug_msg("Exexuting echo (builtin).");
	printf("%s\n",message); // Print Message
}

void env() {
	// Use this global Variable
	debug_msg("Executing env (builtin).");
	char **env; // Create a new Variable we can parse
	for (env = environ; *env; env++) { // Read all environment Variable
		printf("%s\n",*env);
	}
}

void clear() {
	debug_msg("Executing clear (builtin).");
	printf("\033[2J");
}

void cd(char *dir) {
	debug_msg("Executing cd (builtin)");
	// Check if 'dir' exists.
	struct stat st;
	// Is selected Item a Directory?
	if ((stat(dir,&st)==0) && (S_ISDIR(st.st_mode))) {
		// YES.
		set("PWD", dir); // This everything we need to set here.
	} else {
		// NO.
		error_msg("does not exist or is no directory.",1);
	}
}

void pwd() {
	debug_msg("Executing pwd (builtin)");
	char *path = getenv("PWD"); // Get Value of PWD
	printf("%s\n",path); // Print PWD Value
}

void ls() {
	debug_msg("Listing Contents of Directory");
	DIR *dirp; // Create a Dir Pointer
	struct dirent *direntry; // Save all entries here
	if ((dirp = opendir(getenv("PWD"))) == NULL) {
		errno_msg("Opening Directory",1); // Could not Open Directory.
	} else {
		while ((direntry = readdir(dirp)) != NULL) { // Go through every Item in selected Directory
			printf("%s\n",direntry->d_name); // Print name of directory
		}
	}
}

void set(char *name, char *val) {
	debug_msg("Setting Environment Variable");
	if (setenv(name,val,1) == -1) {
		errno_msg("Setting Environment Variable",1);
	}
}

void version() {
	printf("shawn 1.0\nhttp://dev.spline.de/shawn\n(c) 2011 Dirk Braun [http://www.26thmeussoc.com]\n");
}
