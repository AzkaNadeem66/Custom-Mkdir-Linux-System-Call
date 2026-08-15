#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>

#define __NR_mymkdir 548

int main() {
    long result = syscall(__NR_mymkdir, "hello_folder");
    printf("Syscall returned: %ld\n", result);
    return 0;
}


