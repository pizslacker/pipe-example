/*
 * receiver.c
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
    char *myfifo = "/tmp/my_receiver_channel";
    char buffer[100];

    printf("🎧 Receiver: Tuning in... waiting for broadcaster.\n");
    
    // open() will BLOCK until the broadcaster opens the FIFO for writing!
    fd = open(myfifo, O_RDONLY);
    
    printf("🎧 Receiver: Tuned in! Listening...\n\n");

    while (1) {
        // Read data from the pipe into our buffer
        read(fd, buffer, sizeof(buffer));

        // Did the broadcaster say exit?
        if (strncmp(buffer, "exit", 4) == 0) {
            printf("\n🎧 Receiver: Broadcaster signed off. Static... \n");
            break;
        }

        printf("Received: %s", buffer);
    }

    // Clean up
    close(fd);
    return 0;
}
