#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static char child_stack[1024 * 1024];

int child_main(void *arg) {
  printf("Hello from child! PID=%d\n", getpid());
  return 0;
}

int main(int argc, char *argv[]) {
  int flags = CLONE_NEWPID;
  pid_t pid = clone(child_main, child_stack + sizeof(child_stack), flags | SIGCHLD, argv + 1);
  if (pid < 0) {
    fprintf(stderr, "clone failed: %d\n", pid);
    return 1;
  }
  printf("clone() = %ld\n", (long)pid);
  waitpid(pid, NULL, 0);
  return 0;
}