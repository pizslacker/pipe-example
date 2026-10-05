/*
 * broadcaster.c
 * Copyright (C) k!M/pizslacker 2026
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    int fd;
    // The path to our named pipe (rendezvous point)
    char *myfifo = "/tmp/my_receiver_channel";
    char buffer[100];

    // Create the FIFO (named pipe) 
    // 0666 are the permissions (read/write for everyone)
    mkfifo(myfifo, 0666);

    printf("📻 Broadcaster: Waiting for a listener to tune in...\n");
    
    // open() will BLOCK (pause execution) until another program opens the FIFO for reading!
    fd = open(myfifo, O_WRONLY);
    
    printf("📻 Broadcaster: Listener connected! Start typing (type 'exit' to quit).\n");

    while (1) {
        printf("Broadcast > ");
        fgets(buffer, 100, stdin);

        // Send the input down the pipe
        write(fd, buffer, strlen(buffer) + 1);

        // If the user typed "exit", break the loop
        if (strncmp(buffer, "exit", 4) == 0) {
            break;
        }
    }

    // Clean up
    close(fd);
    printf("📻 Broadcaster: Shutting down.\n");
    return 0;
}
