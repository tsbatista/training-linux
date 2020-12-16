#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mount.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static char child_stack[1024 * 1024];

int child_main(void *arg) {
  /* Unmount procfs */
  umount2("/proc", MNT_DETACH);
  /* Pivot root */
  mount("./rootfs", "./rootfs", "bind", MS_BIND | MS_REC, "");
  mkdir("./rootfs/oldrootfs", 0755);
  syscall(SYS_pivot_root, "./rootfs", "./rootfs/oldrootfs");
  chdir("/");
  umount2("/oldrootfs", MNT_DETACH);
  rmdir("/oldrootfs");

  /* Re-mount procfs */
  mount("proc", "/proc", "proc", 0, NULL);
  mount("sysfs", "/sys", "sysfs", 0, NULL);
  mount("none", "/tmp", "tmpfs", 0, NULL);
  mount("none", "/dev", "tmpfs", MS_NOSUID | MS_STRICTATIME, NULL);

  /* Run the process */
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