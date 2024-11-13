
# pipex

### Language

- [Français](./readme_fr.md)
- [한국어](./readme_kr.md)

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Usage](#usage)
- [Important Functions](#important-functions)
- [Parent and Child Processes](#parent-and-child-processes)
- [Bonus Part](#bonus-part)

---

## Introduction

**pipex** is an Ecole 42 project designed to teach students how UNIX pipes and file descriptors work, specifically how to handle input/output redirection to simulate shell pipeline functionality. This project provides a simplified shell-like program to execute command pipelines with redirection.

---

## Features

- Emulates shell pipelines with two commands using file descriptors and `dup2`.
- Redirects standard input and output between files and commands.
- Includes robust error handling for file access and command execution.
- **Bonus**: Implements multiple command pipes and `here_doc` functionality for reading from standard input until a specific delimiter is reached.

---

## Usage

### Basic Usage

```bash
./pipex file1 cmd1 cmd2 file2
```

- `file1`: Input file.
- `cmd1`: First command.
- `cmd2`: Second command.
- `file2`: Output file.

Example:

```bash
./pipex infile "cat" "grep hello" outfile
```

This command will:
1. Read from `infile`.
2. Execute `cat` with `infile` content as input.
3. Pass the output of `cat` to `grep hello`.
4. Write the final output to `outfile`.

---

## Important Functions

### `open`

- **Usage**: `int fd = open("file.txt", O_RDONLY);`
- Opens a file for reading, writing, or appending and returns a file descriptor.
- Essential for opening `file1` and `file2` to set up the pipeline.

### `close`

- **Usage**: `close(fd);`
- Closes an open file descriptor, freeing resources associated with it.
- Important to close file descriptors to avoid memory leaks or resource exhaustion.

### `read`

- **Usage**: `int bytes_read = read(fd, buffer, sizeof(buffer));`
- Reads data from a file descriptor into a buffer, returning the number of bytes read.
- Useful for processing file data if needed.

### `write`

- **Usage**: `write(fd, buffer, bytes_to_write);`
- Writes data from a buffer to a file descriptor, such as a file or standard output.
- Used for writing final output to `file2`.

### `pipe`

- **Usage**: `pipe(pipefd);`
- Creates a pipe, setting up a unidirectional communication channel between processes.
- Returns two file descriptors: `pipefd[0]` for reading and `pipefd[1]` for writing.

### `dup2`

- **Usage**: `dup2(fd, STDOUT_FILENO);`
- Duplicates a file descriptor to another, allowing redirection of standard input/output.
- Essential for redirecting the input and output of each command in the pipeline.

### `fork`

- **Usage**: `pid_t pid = fork();`
- Creates a new process by duplicating the current process. The new process is known as the child.
- Allows running commands independently in separate processes.

### `execve`

- **Usage**: `execve(path, args, env);`
- Replaces the current process with a new program.
- Used for executing the shell commands within the pipeline.

### `waitpid`

- **Usage**: `waitpid(pid, &status, 0);`
- Waits for a specific child process to finish, allowing the parent process to manage child termination.
- Synchronizes the parent process with its children.

### `perror`

- **Usage**: `perror("Error message");`
- Prints an error message corresponding to the current `errno` value.
- Useful for debugging file or command execution errors.

---

## Parent and Child Processes

In **pipex**, processes are created using `fork()`, which enables command execution in the pipeline:

### Parent Process

The parent process is responsible for managing the overall flow of commands and file descriptors, as well as handling cleanup after the child processes complete.

1. **Setup**:
   - Opens `file1` as the input file and `file2` as the output file.
   - Creates a pipe to facilitate communication between the two commands.

2. **Forking**:
   - Forks two child processes (one for each command).
   - Waits for both child processes to complete using `waitpid`.

3. **Cleanup**:
   - Closes all file descriptors after the pipeline completes.
   - Handles any errors if a child process fails to execute a command.

### Child Processes

Each command in the pipeline runs in a separate child process created by `fork()`. The child processes handle input/output redirection to simulate piping.

#### First Child Process (cmd1)

1. **Redirects Input**:
   - Redirects standard input to `file1` by duplicating `file1`'s file descriptor to `STDIN_FILENO` using `dup2`.
   - Redirects the output to the pipe’s write end (`pipefd[1]`), enabling cmd1’s output to be used by cmd2.

2. **Execution**:
   - Executes `cmd1` using `execve` with its arguments and environment.
   - If `execve` fails, an error message is printed using `perror`.

#### Second Child Process (cmd2)

1. **Redirects Input**:
   - Redirects standard input to the read end of the pipe (`pipefd[0]`), using `dup2` so that it receives the output of `cmd1`.

2. **Redirects Output**:
   - Redirects output to `file2` by duplicating `file2`'s file descriptor to `STDOUT_FILENO` using `dup2`.

3. **Execution**:
   - Executes `cmd2` with `execve`.
   - If `execve` fails, prints an error message with `perror`.

### Error Handling

- Both child and parent processes use `perror` to print any errors encountered during file access or command execution.
- The parent process manages overall error handling, ensuring that resources are freed, and child processes are cleaned up correctly.

---

## Bonus Part

The bonus part of **pipex** extends the functionality to support:

1. **Multiple Commands**: Enables chaining more than two commands, simulating shell pipelines with multiple stages.

   - Usage:
     ```bash
     ./pipex_bonus infile "cmd1" "cmd2" "cmd3" ... "cmdN" outfile
     ```
   - Each intermediate command receives input from the previous command’s output and passes its output to the next command.

2. **Here Document**: Implements "here document" functionality, allowing input to be read from the standard input until a specified delimiter.

   - Usage:
     ```bash
     ./pipex_bonus here_doc LIMITER cmd1 cmd2 outfile
     ```
   - Reads from standard input until `LIMITER` is encountered, then processes the input through the commands and writes the output to `outfile`.
