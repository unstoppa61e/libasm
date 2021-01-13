#include <stdio.h>
#include <unistd.h>

int main() {

    const int BUF_LEN = 255;
    char buf[BUF_LEN];

    int rc;
    rc = read(STDIN_FILENO, buf, BUF_LEN);
    if (rc == -1) {
        perror("read");
        return 1;
    }

    printf("test1: ");
    fwrite(buf, 1, rc, stdout);
    printf("\n");

    return 0;
}