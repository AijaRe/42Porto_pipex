
# Pipex

Program execution: `./pipex infile cmd1 cmd2 outfile`

`Infile` and `outfile` - file names

`cmd1` and `cmd2` - shell commands with their parameters

The program should behave as the shell command `< infile cmd1 | cmd2 > outfile`

Example: `./pipex infile "grep a" "cat -e" outfile` should behave like `< infile grep a | cat -e > outfile`

### Materials:

[Playlist on Unix processes from Code Vault](https://www.youtube.com/watch?v=cex9XrZCU14&list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY)

[Write your own Shell playlist](https://www.youtube.com/watch?v=cIBmeEpsMj0&list=PLxIRFba3rzLzxxZMMbrm_-mkI7mV9G0pj)

[Pipex tutorial - Medium](https://csnotes.medium.com/pipex-tutorial-42-project-4469f5dd5901)

[Reactive guide with some edge cases](https://reactive.so/post/42-a-comprehensive-guide-to-pipex)

[Pipex explained (in Russian)](https://www.youtube.com/watch?v=7e_gExniT_Y)

[Error handling](https://www.youtube.com/watch?v=OOuZLI5ingc)

[Exit](https://www.youtube.com/watch?v=8RucxSeAemw)

[Wait, waitpid](https://www.tutorialspoint.com/unix_system_calls/waitpid.htm)

[Pipe explained](https://www.codequoi.com/en/pipe-an-inter-process-communication-method/)

[Execve explained](https://www.youtube.com/watch?v=Wtd-8OiZOjk&t=657s)

### Pipex Plan (mandatory):

Validate the input.

Open the infile. Check access rights. Redirect to standard input.

Create path array from env.

Create pipe.

Fork the process.

Child process deals with command 1.

 - Redirect the stdout to pipe.

 - Get path.

 - Check path access.

 - Split the command input.

 - Execve the path and command 1.

Parent process deals with command 2.

 - Redirect the stdin to pipe.

 - Open / create the outfile. Redirect to stdout.

 - Get path.

 - Check path access.

 - Split the command input.

 - Execve the path and command2.

### Misc comments

fork() returns PID of the child process to the parent.

Find command path with `whereis`.

Check your fds currently open with the command `ls -la /proc/$$/fd`

To see what is inside `envp`, type `env` in your terminal.

## Norminette
This project has to be written in accordance with the Norm, which is the coding standard of the school 42.

The Norm includes:
- Forbidden: for, do...while, switch, case, goto, ternary operators and variable-length arrays 
- Maximum of 25 lines per function
- Maximum line length: 80 columns
- Maximum 4 parameters per function 
- Variable assignments and declarations must be on separate lines
- etc...
  

Line `PATH` in `env` contains all possible paths to the command binaries. PATH=/nfs/homes/arepsa/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin

Split, using `:` as delimiter. Add a `/` at the end for the path to work correctly.

Valgrind check with `--trace-children=yes`.
