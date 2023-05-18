# shellby - Simple Shell

A simple UNIX command interpreter written as part of the low-level programming 
and algorithm sprint at ALX SE School.

## Description

**Shellby** : This is a simple UNIX command language interpreter. It was 
written to executes c commands read from standard input.

### Invocation
If **shellby** is invoked with arguments, the first argument is assumed to be a
string containing shell commands. **Shellby** reads and executes commands from
this string, then exits with the status of the last command executed.

If **shellby** is invoked without arguments, an *interactive* shell is opened.
When executing interactively, **shellby** displays the prompt `$ ` when
it is ready to read a command.

### Command Execution
After receiving a command, **shellby** tokenizes it into words and takes
the following actions:
* If the command name contains no slashes, the shell searches for it in the
list of shell builtins. If there exists a builtin by that name, the builtin
is invoked.
* If the commmand name is not a builtin, **shellby** searches each element of
the **PATH** environmental variable for a directory containing an executable
file by that name.
* If either of the above searches is successful, the shell executes the named
program with any remaining given arguments in a separate execution environment.

### Exit Status
**Shellby** returns the exit status of the last command executed, unless a
syntax error occurs, in which case it exits with a non-zero value.

### Shellby Builtin Commands

## Authors
* Kingsley Akpan <[khingz](https://github.com/khingz)> - ALX School student
* Amadi Glory <[ama-dii](https://github.com/ama-dii)> - ALX School student

## Acknowledgements
**Shellby** emulates basic functionality of the **sh** shell. This README
borrows form the Linux man page [sh(1)](https://linux.die.net/man/1/sh).

This project was written as part of the curriculum for ALX School. ALX School
is a online-based full-stack software engineering program that prepares
students for careers in the tech industry using project-based peer learning.
For more information, visit [this link](https://www.alxse.com/).

<p align="center">
  <img src="http://www.holbertonschool.com/holberton-logo.png">
</p>
