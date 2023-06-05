#include "include.h"
#include "er_proc.h"

int main() {
    int fd = Socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(7777);
    Inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);

    Connect(fd, (struct sockaddr *) &addr, sizeof addr);

    char buf[256];
    ssize_t nread;
    write(fd, "Hello\n", 6);
    nread = read(fd, buf, 256);
    if (nread == -1) {
        perror("read failed");
        exit(1);
    }
    else if (nread == 0) {
        printf("EOF occured\n");
    }
    write(1, buf, nread);

    close(fd);

    return 0;
}