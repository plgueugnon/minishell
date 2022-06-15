# minishell : 42 Cursus project [![pgueugno's 42 minishell Score](https://badge42.vercel.app/api/v2/cl4cqx7ks006409jn1s8sg534/project/2138978)](https://github.com/JaeSeoKim/badge42)
<p align="left"> <a href="https://www.cprogramming.com/" target="_blank" rel="noreferrer"> <img src="https://raw.githubusercontent.com/devicons/devicon/master/icons/c/c-original.svg" alt="c" width="40" height="40"/> </a> <a href="https://www.gnu.org/software/bash/" target="_blank" rel="noreferrer"> <img src="https://www.vectorlogo.zone/logos/gnu_bash/gnu_bash-icon.svg" alt="bash" width="40" height="40"/> </a> </p>

### Overview
- Code our own mini bash following bash POSIX implementation as technical guideline
- Learn about contextual parsing and execution, advanced file descriptor use, pipes, signal processing, processes and parent / child
- As usual per 42 standard : no memory or fd leaks allowed, and project is up to 42's coding norm

### Specifications
- Display a prompt when waiting for a new command.
- Have a working history.
- Search and launch the right executable (based on the PATH variable or using a relative or an absolute path).
- Not interpret unclosed quotes or special characters which are not required by the subject such as \ (backslash) or ; (semicolon).
- Handle ’ (single quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence.
- Handle " (double quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence except for $ (dollar sign).
- Implement redirections:
  - < should redirect input.
  - \> should redirect output.
  - << should be given a delimiter, then read the input until a line containing the delimiter is seen. However, it doesn’t have to update the history!
- \>> should redirect output in append mode.
- Implement pipes (| character). The output of each command in the pipeline is connected to the input of the next command via a pipe.
- Handle environment variables ($ followed by a sequence of characters) which should expand to their values.
- Handle $? which should expand to the exit status of the most recently executed foreground pipeline.
- Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.
- In interactive mode:
  - ctrl-C displays a new prompt on a new line.
  - ctrl-D exits the shell.
  - ctrl-\ does nothing.
- Your shell must implement the following builtins:
  - echo with option -n
  - cd with only a relative or absolute path
  - pwd with no options
  - export with no options
  - unset with no options
  - env with no options or arguments
  - exit with no options

### Reference
[Bash reference manual](https://www.gnu.org/software/bash/manual/html_node/index.html#SEC_Contents)
[Basis of pipe communication](http://www.zeitoun.net/articles/communication-par-tuyau/start)

### Credit
@[pgueugno](pgueugno@student.42.fr) @[jdamoise](jdamoise@student.42.fr)
