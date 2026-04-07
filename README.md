# detach

This is innocent program to detach command from terminal without `nohup`, `jobs`,
or `disown`. No error handling, no help, no messages. You know exactly what you
do, right? Pretty straightforward:

```shell
detach <command>
```

`command` will release terminal and become a child of `PID` 1 with `stdout` and
`stderr` set to `/dev/null`.

It can be used with args:

```shell
detach <command> <args>
```

or with redirection:
```shell
detach <command> <args> >file.out
detach <command> <args> 2>&1 >file.out
```

working exactly as expected.

# Build

```shell
make
sudo make install # to copy executable to /usr/local/bin
```

# Rationale

I got tired of doing

```shell
nohup <command> >/dev/null &
```

It says strange things in terminal when everything is OK, and you still spot
`nohup.out` here and there sometimes.

The original idea of `nohup` is to prevent exit on `SIGHUP` in case of terminal
hangup. Detaching from tty with `nohup` is kinda party trick, based on
POSIX convetion to send `SIGCONT` aftern `SIGHUP` to suspended processes in
orphaned group to allow them process hangup. `nohup` makes suspended process to
ignore hangup and continue. Same with `disown`. Why thinking about detach in
terms of background shell job? `detach` is more straightforward. Just `fork`,
`exit` from parent to release terminal, set `stdout` and `stderr` to
`/dev/null` if they are `tty`s and `execv` with arguments.

# Zsh completion
```shell
compdef _precommand detach
```

# Bugs

A musthave section in 13 LOC long software.
