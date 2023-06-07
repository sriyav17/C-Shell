># *2021101084*

>## Sriya Venepally 
<br>

* sirya is a user-defined interactive shell program that can create and manage new processes
<br>

## To run
* make
* ./a.out
* To exit, type exit

## Assumptions

* Maximum input length is 1000 characters.
* Maximum number of commands is 1000.

## Features
* Supports multiple commands separated with a semicolon
* Supports commands run with an &, i.e., background processes
* Supports input/output redirection and command pipelines
* ctrl+z pushes any currently running foreground process to the background
* ctrl+c interrupts any currently running foreground process
* ctrl+d logs out of the shell
* autocompletion is supported

## Commands
>### cd
* Switches between directories
* '.' , '..', '-', '~' flags are implemented
>### pwd
* Prints the absolute path of the current working directory
>### echo
* Displays the line of text following it
>### ls
* Lists all the files and directories in  the specified directory in alphabetical order
* '-l', '-a' flags are implemented
* Executables are listed in green, files in white and directories in blue
>### pinfo
* Prints the process related info of the shell
* pinfo \<pid> prints the process info of the given pid
>### discover
* finds the given file from the specified directory 
* if no file is given as input, lists all the files and directories in the specified directory
* does not search hidden folders
>### history
* prints the last 10 command line inputs
* stores only the last 20 commands
* creates a new file hist.txt for implementation
>### jobs
* prints list of all currently running background processes spawned by the shell, along with job number, process id, and state
>### sig
* sends a signal to the corresponding process
>### fg
* brings the running or stopped background job corresponding to job number to the foreground, and changes
its state to running.
>### bg
* changes the state of a stopped background job to running (in the background)