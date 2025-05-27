# minishell

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

A lightweight, Norm-compliant Unix shell in C, supporting command execution, pipes, redirections, built-ins, and basic signal handling.

## Table of Contents

- [Contributors](#contributors)
- [About](#about)  
- [Features](#features)  
- [Installation](#installation)  
- [Usage](#usage)  

## Contributors

- Mert5558 ([@mert5558](https://github.com/Mert5558)) – parsing & tokenization 
- Matvej-g ([@matvej-g](https://github.com/matvej-g)) – execution & pipes  

## About

`minishell` parses and executes command lines much like Bash. It handles tokenization (words, quotes, expansions), launches external programs via `fork()`/`execve()`, chains commands with pipes, and redirects input/output.

## Features

- **Command parsing**  
  - Handles single/double quotes and environment variable expansion.  
  - Supports here-document (`<<`) for simple heredoc.  
- **Execution**  
  - Launches external binaries with arguments.  
  - Captures and propagates exit statuses.  
- **Pipes & Redirections**  
  - Unlimited `|` pipelines.  
  - Input `<`, output `>`, append `>>`.  
- **Built-in commands**  
  - `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`.  
- **Signal handling**  
  - Ignores Ctrl-\\ (`SIGQUIT`) and handles Ctrl-C (`SIGINT`) gracefully.  
- **Norm-compliant**  
  - Only permitted functions
  - 25 lines max per function.  
  - 80-column width limit.  
  - Max 4 functions per file.  
  - Max 4 parameters per function.  

## Installation

1. **Clone the repo**  
   ```bash
   git clone https://github.com/YourUsername/minishell.git
   cd minishell
   make
   ```

## Usage

Run the executable `minishell` and use it like the normal Shell UNIX environemnt.
  ```bash
  ./minishell
  ```
