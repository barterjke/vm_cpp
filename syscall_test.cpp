#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>

int main() {

    unsigned cpu, node;

    // Get current CPU core and NUMA node via system call
    // Note this has no glibc wrapper so we must call it directly
//    syscall(SYS_getcpu, &cpu, &node, NULL);
    const char * msg = "Hello World!\n";
    int a = (long long int) msg;
    printf("hello world %d\n", a);
    syscall(1, 0, (char *)a, 14);
    // Display information
//    printf("This program is running on CPU core %u and NUMA node %u.\n\n", cpu, node);

    return 0;

}