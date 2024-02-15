/*
 * giac_history.c
 * Copyright (C) Harald Milz <hm@seneca.muc.de> 2024
 *
 * Command line history extension for giac, the XCAS cli
 *   
 * compile with 
 *   gcc -shared -fPIC -o giac_history.so giac_history.c
 * and use like
 *   LD_PRELOAD=/path/to/giac_history.so giac
 *     
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <dlfcn.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define MAXLEN 256
char histfile[MAXLEN]; 
int histfilesize; 

typedef void (*original_add_history_ptr)();
typedef void (*original_using_history_ptr)();

// void add_history (const char *string)
void add_history (const char *string) {

    // Get a pointer to the original function
    original_add_history_ptr original_add_history = (original_add_history_ptr)dlsym(RTLD_NEXT, "add_history");

    if (original_add_history) {
        // Call the original function
        original_add_history(string);
    } else {
        fprintf(stderr, "Failed to get pointer to original_add_history()\n");
    }
    
    append_history(1, histfile); 
    history_truncate_file (histfile, histfilesize); 
}


// void using_history (void)
void using_history (void) {

    char histfile[MAXLEN]; 
    int fd;
    
    // Get a pointer to the original function
    original_using_history_ptr original_using_history = (original_using_history_ptr)dlsym(RTLD_NEXT, "using_history");

    if (original_using_history) {
        // Call the original function
        original_using_history();
    } else {
        fprintf(stderr, "Failed to get pointer to original_using_history()\n");
    }

    if (getenv("GIAC_HISTFILE")) {    
        strncpy (histfile, getenv("GIAC_HISTFILE"), MAXLEN-1);
    } else {
        snprintf (histfile, MAXLEN-1, "%s/.giac_history", getenv("HOME"));  // default
    }
    
    if (getenv("GIAC_HISTFILESIZE")) {    
        histfilesize = atoi(getenv("GIAC_HISTFILESIZE"));
    } else {
        histfilesize = 100;                                                 // default
    }
    
    
    // create a histfile if none exists
    fd = open(histfile, O_CREAT | O_RDONLY, 0644);
    close (fd);

    read_history (histfile);
}




