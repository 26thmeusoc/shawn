/*
 checkline.c
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

#include <stdlib.h>  // For EXIT_FAILURE/SUCCES
#include <stdio.h>   // For IO Operations

/**
 * This Applications repeats all given Parameters (argv[0] - argv[argc-1]).
 * Checkline was developed, to check a call of other applications by shawn.
 * 
 * \author Dirk '26thmeusoc' Braun
 * \version 1.0
 */

int main (int argc, char *argv[]) {
	printf("I was called as %s\n",argv[0]);
	for (int i=1; i<argc; i++) {
		printf("Argument %i was: %s\n", i, argv[i]);
	}
	
	return EXIT_SUCCESS;
}
