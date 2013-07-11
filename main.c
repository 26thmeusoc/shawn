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

#include "main.h" // Get Forward Definitions and Includes.

/*!
 * shawn - SHell of AWesomeNess
 *
 * \author Dirk '26thmeusoc' Braun
 * \version 1.1
 */

#define READBUFFERSIZE 255

int quit = 0;
int last_exit_code;

int count_paramters(char *cmd) {
	int i = 1; // Init counter
	int escaped = 0;
	for(;*cmd;cmd++) {
		if ((*cmd == ' ' && escaped==0) || *cmd=='\n') { // New parameter
			i++;
			escaped = 0;
		} else if (*cmd == '\\') { // Escaped next symbol
			escaped = 1;
		} else { // Nothing to see here! Just switch escaped back, in case it was set!
			escaped = 0;
		}
	}
	return i;
}

void parse_cmd(char *cmd) {
	cmd = remove_leading_whitespaces(cmd);
	char *tok = find_next_space(cmd); // Find Command
	int status;
	debug_msg(cmd);
	#if USEBUILTINCLEAR
	if (strcmp(cmd, "clear") == 0) {
			clear();
	} else
	#endif
	if (strcmp(cmd, "env") == 0) {
		env();
	} else if (strcmp(cmd, "quit") == 0) {
		exit(EXIT_SUCCESS);
	} else if (strcmp(cmd, "version") == 0) {
		version();
	} else if (strcmp(cmd, "pwd") == 0) {
		pwd();
	}
	#if USEBUILTINLS 
	else if (strcmp(cmd, "ls") == 0) {
		ls();
	} 
	#endif
	else if (strcmp(cmd, "echo") == 0) {
		find_next_space(tok);
		remove_character(tok,'\\');
		echo(tok);
	} else if (strcmp(cmd, "cd") == 0) {
		find_next_space(tok); // Get Path
		remove_character(tok,'\\'); // Remove all '\' in target Path.
		debug_msg(tok);
		cd(tok);
	} else if (strcmp(cmd, "set") == 0) {
		// Get Name of Variable
		char *buffer = strtok(tok,"=");
		// Get new Value of Variable and set.
		set(buffer, strtok(NULL,"="));
	} else if (strcmp(cmd, "\0") == 0) {
		// Do nothing.
	} else {
		// Fork application here
		pid_t pID = fork();
		
		if (pID < 0) {
			// pID == -1: There was an error! Quit shawn!!
			errno_msg("Could not fork.",0);
		} else if (pID > 0) {
			// Parent Process, pID is PID of child.
			
			pID = wait(&status); // Wait for childs completion.
			if (WIFEXITED(status)) { // Has Child ended?
				last_exit_code = WEXITSTATUS(status); // Set our internal $?
				#if DEBUG
					printf("[DEBUG] Child exited with %i\n",last_exit_code);
				#endif
			}
		} else { // PID == 0
			// Child Process.
			
			// We need to fork here.
			unsigned int i = 2; // Prepare a counter
			char *parameters[count_paramters(tok)]; // Create a list for parameters
			char *buffer = find_next_space(tok); // Select first parameter.
			remove_character(tok,'\\');
			parameters[0] = cmd; // Set name of call. See execvp() Documentation
			parameters[1] = tok; // Set first parameter.
		
			// Save every Parameter now for our Call
			while (buffer != NULL) {
				// We need a second pointer here.
				char *placeholder = find_next_space(buffer);
				// remove all \ characters
				while(remove_next_special_character(buffer,'\\') == 1); 
				// Set the Parameter to our newly delimited string
				parameters[i] = buffer;
				// Replace buffer with our placeholder
				buffer = placeholder;
				i++; // Increment i, so we set the next parameter
			}
			parameters[i-1] = NULL; // Remove an empty Parameter. Else This would be a whitespace
			
			// Run Application now.
			int result = execvp(cmd,parameters);
			if (result != 0) {
				errno_msg("Executing Application",1);
			}
			exit(result);
		} 
	} // End of fork() Stuff.
}

char *find_next_space(char *cmd) {
	int escaped = 0;
	char *buffer = cmd;
	if (*buffer == '#') { // This is a Comment! We are not interested in whats happening in here!
		return NULL;
	}
	for(; *buffer; buffer++) {
		if (*buffer=='\\') {
			escaped = 1;
		} else if ((*buffer == ' ' && escaped == 0) || *buffer == '\n') { // A real Parameter delimiter?
			// Whitespace found
			*buffer = '\0';
			buffer++;
			return buffer;
		} else {
			escaped = 0;
		}
	}
	// No whitespace found, but string has ended!
	return NULL;
}

int remove_next_special_character(char *str, char charac) {
	int deleted = 0;
	int i = 0;
	char *plchld = str+1;
	for(; *str; str++) { // Move through str
		i++; // Increment counter
		if (*str == charac && deleted == 0) { // Have we found our character?
			debug_msg("Found something");
			deleted = 1; // Set Informationvariable
			*str = *plchld; // Move next character one place back.
		} else if (deleted == 1) {
			*str = *plchld; // Move this character one space back.
		}
		plchld++; // Move next character one space forward.
	}
	debug_msg("Ending remove of character.");
	return deleted;
}

void remove_character(char *str, char charac) {
	// Remove next charac as long as charac was found last time.
	while(remove_next_special_character(str,charac) == 1);
}

char *remove_leading_whitespaces(char *str) {
	char *plchld = str;
	while(*plchld == ' ') {
		plchld++;
	}
	return plchld++;
}

int main (int argc, char *argv[]) {
	if (argc == 2) { // Might got called as Script Executioner
		//FILE *fp = fopen(argv[1],"r"); // Prepare a file Pointer
		char *readString; // Read lines here
		/*while (fgets(readString, READBUFFERSIZE, fp) != NULL) {*/
		while ((readString = readline("Test"))) {
			remove_leading_whitespaces(readString);
			if (*readString != '#') {
				parse_cmd(readString);
			}
		}
		return EXIT_SUCCESS; // Exit this instance of shawn.
	}
	last_exit_code = 0;
	char *shell = malloc(sizeof(char[80])); // Prepare variable for path
	if (*argv[0] == '.') { // Has shawn been called with a relative path?
		strcat(shell,getenv("PWD")); // Yes, prepare string
		strcat(shell,strchr(argv[0],'/')); // Concat Strings to an absolute path
	} else {
		shell = argv[0]; // No, just take call of shawn
	}
	
	char *hostname = malloc(sizeof(char[80])); // Whats the Name of this Host? 
	if (gethostname(hostname,80) != 0) { // Could we read it?
		errno_msg("Reading hostname",0); // No, give an error and quit
	}  
	
	set("SHELL",shell); // Set SHELL Env Variable.
	debug_msg("Debugmode enabled!"); // Inform user, he is running in DEBUG mode.
	printf("Welcome to shawn 1.1\n");
	char readString[READBUFFERSIZE];  // Prepare Buffer
	do { // Loop.
		printf("%s:(%s)%s$ ",hostname,getenv("USER"),getenv("PWD"));
		fgets(readString, READBUFFERSIZE, stdin); // Read user command.
		parse_cmd(readString);
	} while (quit==0); // Infinite loop, quit is now recognized and handled in parsecmd()
	return EXIT_SUCCESS; // We can quit now, but this will never get called.
}
