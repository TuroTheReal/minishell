# MINISHELL
## Table of Contents
- [About](#about)
- [Usage](#usage)
- [Compilation](#compilation)
- [Key Concepts Learned](#key-concepts-learned)
- [Skills Developed](#skills-developed)
- [Features Implementation](#features-implementation)
- [Built-in Commands](#built-in-commands)
- [42 School Standards](#42-school-standards)

## About
This repository contains my implementation of the **minishell** project at 42 School.  
Minishell is a collaborative project that involves creating a simplified version of bash shell in C programming.  
The project focuses on understanding Unix processes, command parsing, execution, and implementing core shell functionalities including pipes, redirections, and built-in commands.

**Project Goal:**
Create a functional shell that can parse user input, execute commands, handle environment variables,
and manage processes just like bash, while following strict coding standards and memory management practices.


## Usage
The program creates an interactive shell environment with bash-like behavior:

```bash
# Compile and run
make
./minishell

# Shell prompt appears
minishell$ 
```

**Supported Shell Operations:**
```bash
# Basic command execution
minishell$ ls -la
minishell$ echo "Hello World"
minishell$ pwd

# Pipes
minishell$ ls | grep minishell
minishell$ cat file.txt | grep "search" | wc -l

# Redirections
minishell$ echo "content" > output.txt
minishell$ cat < input.txt
minishell$ ls >> logfile.txt

# Environment variables
minishell$ echo $USER
minishell$ export MY_VAR="value"
minishell$ echo $MY_VAR

# Built-in commands
minishell$ cd /home/user
minishell$ pwd
minishell$ env
minishell$ exit
```

**Command Line Features:**
- Interactive prompt display
- Command history (using readline)
- Signal handling (Ctrl+C, Ctrl+D, Ctrl+\)
- Environment variable expansion
- Quotes handling (single and double quotes)


## Compilation
The project follows standard makefile compilation practices:

```bash
# Compile with Makefile
make

# Clean object files
make clean

# Clean everything
make fclean

# Recompile
make re
```

**Compilation flags:** `-Wall -Wextra -Werror`  
**External library:** `-lreadline` (for command line editing)


## Key Concepts Learned

### Shell Architecture & Design
- **Command Line Interface**: Building interactive user interfaces with prompt display
- **Input Parsing**: Tokenizing and interpreting complex command structures
- **Lexical Analysis**: Breaking down input into meaningful tokens and operators
- **Syntax Analysis**: Validating command syntax and structure

### Unix System Programming
- **Process Management**: Creating child processes with `fork()` and `execve()`
- **Inter-Process Communication**: Implementing pipes for data flow between commands
- **File Descriptor Management**: Handling stdin, stdout, stderr redirections
- **Signal Handling**: Managing interrupt signals and process termination

### Advanced String Processing
- **Quote Processing**: Handling single quotes, double quotes, and escape sequences
- **Variable Expansion**: Implementing environment variable substitution (`$VAR`)
- **Word Splitting**: Parsing complex command lines with multiple arguments
- **Path Resolution**: Finding executables in system PATH directories

### Memory Management & Error Handling
- **Dynamic Memory Allocation**: Managing complex data structures for parsing
- **Resource Cleanup**: Preventing memory leaks in long-running shell sessions
- **Error Propagation**: Handling and reporting various error conditions
- **Exit Status Management**: Tracking and returning appropriate exit codes


## Skills Developed

- **System-Level Programming**: Deep understanding of Unix process and I/O model
- **Parser Development**: Building robust command line parsers and interpreters
- **Collaborative Programming**: Working in teams on large, complex projects
- **Debugging Complex Systems**: Troubleshooting multi-process, multi-threaded issues
- **Performance Optimization**: Efficient parsing and execution algorithms
- **Cross-Platform Compatibility**: Writing portable Unix system code


## Features Implementation

### Core Shell Functionality

**Command Execution Flow:**
1. **Input Reading**: Display prompt and read user input with readline
2. **Lexical Analysis**: Tokenize input into commands, arguments, and operators
3. **Parsing**: Build command structure and validate syntax
4. **Expansion**: Handle variable substitution and quote removal
5. **Execution**: Fork processes and execute commands with proper I/O setup
6. **Cleanup**: Wait for processes and clean up resources

**Key Components:**
```c
typedef struct s_token
{
	t_token_type	type;
	int				index;
	char			*token;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct s_gdata
{
	unsigned int	nb_command;
	char			*input;
	int				exit_code;
	int				heredoc;
	t_token			*s_tok;
	t_cmds			*s_cmds;
	t_env			s_env;
}					t_gdata;

typedef struct s_cmds
{
	unsigned int	index;
	unsigned int	nb_redir;
	char			**cmd;
	int				flag_error;
	const char		*hdoc;
	struct s_token	*redir;
	struct s_gdata	*g_data;
	struct s_cmds	*next;
	struct s_cmds	*prev;
	int				saved_stdout;
	int				saved_stdin;
}					t_cmds;
```

### Parsing Engine
- **Tokenization**: Split input into meaningful tokens
- **Quote Handling**: Process single quotes (literal) and double quotes (expandable)
- **Variable Expansion**: Replace `$VAR` with environment variable values
- **Special Variables**: Handle `$?` (exit status)
- **Operator Recognition**: Identify pipes (`|`), redirections (`<`, `>`, `>>`, `<<`), etc.

### Execution Engine
- **Pipeline Execution**: Chain multiple commands with pipes
- **Redirection Handling**: Manage input/output file redirections
- **Built-in Detection**: Execute built-in commands in shell process
- **External Commands**: Fork and exec external programs
- **Process Synchronization**: Wait for command completion and collect exit status


## Built-in Commands

The shell implements essential built-in commands that are executed directly without forking:

### `echo`
```bash
minishell$ echo Hello World
Hello World
minishell$ echo -n "No newline"
No newline
```
- Prints arguments to stdout
- Supports `-n` option to omit trailing newline
- Handles variable expansion and quote processing

### `cd`
```bash
minishell$ cd /home/user
minishell$ cd ..
minishell$ cd
minishell$ cd -
```
- Changes current working directory
- Supports relative and absolute paths
- `cd` without arguments goes to HOME directory
- `cd -` returns to previous directory

### `pwd`
```bash
minishell$ pwd
/current/working/directory
```
- Prints current working directory path
- Uses `getcwd()` system call for accurate path

### `export`
```bash
minishell$ export VAR=value
minishell$ export VAR="value with spaces"
minishell$ export
```
- Sets environment variables
- Without arguments, displays all exported variables
- Handles variable assignment with proper validation

### `unset`
```bash
minishell$ unset VAR
minishell$ unset VAR1 VAR2 VAR3
```
- Removes environment variables
- Accepts multiple variable names as arguments
- Validates variable names before removal

### `env`
```bash
minishell$ env
PATH=/usr/bin:/bin
HOME=/home/user
USER=username
...
```
- Displays all environment variables
- Shows current shell environment state

### `exit`
```bash
minishell$ exit
minishell$ exit 42
minishell$ exit "invalid"
```
- Terminates the shell with optional exit code
- Validates exit code arguments (must be numeric)
- Handles edge cases and error conditions


## 42 School Standards

### Norm Requirements
- ✅ Maximum 25 lines per function
- ✅ Maximum 5 functions per file
- ✅ Proper indentation and formatting
- ✅ No forbidden functions usage
- ✅ Compilation without warnings

### Coding Standards
- ✅ No memory leaks (checked with valgrind)
- ✅ Proper error handling for all system calls
- ✅ Signal handling implementation (SIGINT, SIGQUIT)
- ✅ Comprehensive input validation and sanitization
- ✅ Resource cleanup on exit and error conditions

### Authorized Functions
**Standard Library:**
- `malloc`, `free`, `write`, `read`, `open`, `close`
- `fork`, `wait`, `waitpid`, `wait3`, `wait4`
- `signal`, `sigaction`, `sigemptyset`, `sigaddset`
- `kill`, `exit`, `getcwd`, `chdir`, `stat`, `lstat`, `fstat`
- `execve`, `dup`, `dup2`, `pipe`, `opendir`, `readdir`, `closedir`

**External Libraries:**
- `readline`, `rl_clear_history`, `rl_on_new_line`
- `rl_replace_line`, `rl_redisplay`, `add_history`

### Behavioral Requirements
- ✅ Display prompt and wait for user input
- ✅ Parse and execute commands like bash
- ✅ Handle quotes and environment variables correctly
- ✅ Implement working pipes and redirections
- ✅ Provide accurate error messages matching bash behavior
- ✅ Handle edge cases and malformed input gracefully

### Team Collaboration
- **Pair Programming**: Developed as a team project with clear task division
- **Code Integration**: Merging parsing and execution components seamlessly
- **Shared Architecture**: Consistent data structures and interfaces
- **Cross-Testing**: Comprehensive testing of integrated functionality


## Contact
- **GitHub**: [@TuroTheReal](https://github.com/TuroTheReal)
- **Email**: arthurbernard.dev@gmail.com
- **LinkedIn**: [Arthur Bernard](https://www.linkedin.com/in/arthurbernard92/)

---
<p align="center">
  <img src="https://img.shields.io/badge/Made%20with-C-blue.svg"/>
  <img src="https://img.shields.io/badge/Shell-Programming-green.svg"/>
</p>
