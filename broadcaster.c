#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    int fd;
    // The path to our named pipe (rendezvous point)
    char *myfifo = "/tmp/my_radio_channel";
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