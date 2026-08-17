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