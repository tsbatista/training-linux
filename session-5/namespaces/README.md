# Session 5 - Linux namespaces

## Requirements
* gcc

## PID namespace
We want to control what a child process can see, so we will be using clone instead of fork. Clone is very similar to fork, but allows you to pass flags and which resources you would want to share. Flags were already shared on slide 26.

Compile the source code:
```bash
$ gcc -o nspid nspid.c
# Try to execute it as user
$ ./nspid
# Is the output expected? If yes, why?
# lets try it as root
$ sudo ./nspid
# Is the output the same? Why?
```

## UTS (Unix TimeShare)
UTS namespaces isolates 2 specific identifiers of the system: `domainname` and `nodename`. Lets try to have a better understanding to what it means:
```bash
$ gcc -o nsuts nsuts.c
# Try to execute it as user
$ ./nsuts
# Is the output expected? If yes, why?
# lets try it as root
$ sudo ./nsuts
# Is the output the same? Why?
```

## Executing commands
Lets run a shell in the child process, for fun. First, compile the source code:
```bash
$ gcc -o nsrun nsrun.c
# Lets try it with a shell
$ sudo ./nsrun /bin/sh
# On the new shell check the process number of the shell
$ echo $$
$ ps aux
```

Since we have added flags to the clone function play with different commands, by removing and adding different flags.

## A more secure environment
On the previous step, did you thought you were isolated? Although shell pid number is 1, you can see all other processes! This is because list of processes is read from `procfs`. Which is still inherited!

What to do then? Let’s unmount procfs!
```bash
$ gcc -o nsrun2 nsrun2.c
# Try it with a shell
$ sudo ./nsrun2 /bin/sh
# On the new shell check the process number of the shell
$ echo $$
# Still seeing pid 1, ok...
$ ps
# oh uh! what happened?
```

By unmounting the access to the list of processes, now `ps` is not able to view any. Better safe than sorry, right?

## Pivot root
A shell that does not allow to view a process list is a bit weird, right? So let's make it work on a isolated environment. As it should.

We are going to use `pivot_root`, which is a syscall, that moves an existing rootfs into some subdirectory, and make other directory a new root.

```bash
$ gcc -o nspivotroot nspivotroot.c
# Now lets try it with a shell
$ sudo ./nspivotroot /bin/sh
# On the new shell check the process number of the shell
$ echo $$
# Still seeing pid 1, ok...
$ ps
# Ah, it works!
```

So process isolation is done, but how about network?

```bash
$ sudo ./nspivotroot /bin/sh
# On the new shell check the process number of the shell
$ ping google.com
ping: google.com: Name or service not known
# It seems we are really really isolated!
```

## Network