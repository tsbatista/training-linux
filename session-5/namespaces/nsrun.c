#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static char child_stack[1024 * 1024];

int child_main(void *arg) {
  char **argv = (char **)arg;
  execvp(argv[0], argv);
  return 0;
}

int main(int argc, char *argv[]) {
  int flags = CLONE_NEWNS | CLONE_NEWUTS | CLONE_NEWPID | CLONE_NEWIPC | CLONE_NEWNET;
  pid_t pid = clone(child_main, child_stack + sizeof(child_stack), flags | SIGCHLD, argv + 1);
  if (pid < 0) {
    fprintf(stderr, "clone failed: %d\n", pid);
    return 1;
  }
  waitpid(pid, NULL, 0);
  return 0;
}