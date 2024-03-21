# <div align="center">_SHELL PROJECT_</div>


## GROUP MEMBERS
- *Arnela Sokolić*
- *Dema Shahbandar*

## SUBMISSION CONTENTS
- _**shell.c**_: The main source code file containing the implementation of the shell.
- _**README.md**_: File containing information about the project.

## OUTLINE
## _Task 1.1  Shell Interface_

* Designed and implemented a basic shell interface in C programming language.
* The shell continually asks the user for input, parses the input, and executes commands.
* The prompt displays a name for the shell (_*"Arnela's and Dema's Shell"*_) and waits for user input.


## _Task 1.2 Shell programs/commands_
We implemented the following commands
```c
ls

// Lists the contents of the current directory.
```

```c
mkdir

// Creates a directory with the specified name.

// If no directory name is provided, the shell will display a usage message in yellow color indicating warning and how to use the mkdir command:
- Usage: mkdir <directory_name>

// The user can create multiple directories by providing multiple directory names separated by spaces.

// If the directory is successfully created, the shell will display a success message in green color:
- SUCCESFULLY CREATED NEW DIRECTORY '<directory_name>'.

// If the directory already exists, the shell will display a warning message in yellow color:
-DIRECTORY '<directory_name>' ALREADY EXISTS.

```
```c
uptime

// Displays the system uptime in a human-readable format in green color.

```
```c
sl

// The sl command is accidentally written because its name is similar to the ls command.
//In our implementation, when the user enters the sl command in our shell, instead of displaying the traditional train animation, we output a message to humorously suggest that the user might be half asleep and needs some coffee.
```


We have added an extra command in our shell. Now, let us introduce the *__fact__* command to you.

```c
fact

// This command displays a random fact with a different background color each time, providing users with intriguing snippets of information.
// Facts cover a range of topics, including historical milestones, technological advancements, notable inventions, and interesting facts about computing and operating systems.
```
Additionally, if the user enters any of the commands in uppercase, the shell will issue the following warning message:

```c
//Example : LS MKDIR UPTIME SL

//WARNING: CAPS LOCK MAY BE ON! DON'T SHOUT AT ME :(

```
## _Task 1.3  Shell Interface_
* We used the *fork()* system call to create separate child processes for executing user commands.
* By using *wait()*, we ensured that the parent process waits for the child process to complete before proceeding.
* Also, we added *execvp()* to replace the current process image with the user-entered command, allowing us to execute various commands with different arguments.

## _Task 1.4 Added colors to our shell and named it_
* We enhanced our shell by adding colors to the command prompt and various messages displayed to the user.
* Additionally, we gave our shell a name, *"Arnela's and Dema's Shell"*, which is displayed in cyan color.

## _Task 1.5 Concise and descriptive answer to the following questions_

## Question 1.5.1: The following actions, do they require the OS to use kernel mode or user mode is sufficient? Explain.
- Starting a new process.
- Multiplying two floating numbers stored in an application’s memory.
- Writing the results of the multiplication to a temporary log file on disk.<br>

### __ANSWER__:
* *__STARTING A NEW PROCESS__* - Starting a new process in an operating system involves a variety of privileged operations that require access to system resources, memory management, security mechanisms, and hardware control, all of which are handled by the operating system in kernel mode. User mode does not provide the necessary privileges or access rights to perform these operations, which is why kernel mode is essential for creating and managing processes.

* *__MULTIPLYING TWO FLOATING POINT NUMBERS STORED IN APPLICATION'S MEMORY__* -This action does not necessarily require kernel mode. Multiplying two numbers is a basic arithmetic operation that can be performed by the CPU directly in user mode. As long as the application has the necessary permissions to access and manipulate the memory where the floating-point numbers are stored, it can perform the multiplication without involving the operating system or switching to kernel mode.

* *__WRITING THE RESULTS OF THE MULTIPLICATION TO A TEMPORARY LOG FILE ON DISK__*:  To write the results to a log file on disk, the operating system must switch to kernel mode. When writing data to a file on disk, the operating system needs to handle tasks like accessing the disk, organizing the file, and ensuring security. These tasks require special permissions that are only available in kernel mode.

## Question 1.5.2: Explain the purpose of a system call. Describe how control passes to the kernel when executing a system call.

### __ANSWER__:
System calls are like requests made by programs to the core of the operating system, known as the kernel, for assistance with tasks like reading files or accessing hardware. When a program needs to make a system call, it's like asking the operating system for help with something. Control passes to the kernel by temporarily switching from the program's usual mode to a kernel mode, which gives the program access to protected system resources. Once the kernel completes the requested task, control returns to the program, allowing it to continue its execution.

When a program needs help from the operating system, it uses a system call. This call is like ringing a bell to get the attention of the core of the operating system, called the kernel. The computer then switches into a kernel mode, giving the kernel access to all the computer's resources. Once the kernel finishes the task, the computer goes back to its regular mode, and the program can keep running. 

## Question 1.5.3: Consider a parent process P that has forked a child process C in this program.


#### After the new process is forked, suppose that the parent process is scheduled first, before the child process. Once the parent resumes after fork, it closes the file descriptor and changes the value of a variable as shown above. Assume that the child process is scheduled for the first time only after the parent completes these two changes.
- A. What is the value of the variable a as printed in the child process, when it is scheduled next? Explain.
- B. Will the attempt to read from the file descriptor succeed in the child? Explain

```c
int a = 5;
int fd = open (...) //opening a file
int ret = fork() ;
if (ret >0) {
close (fd);
а = 6;
...
}
else if (ret==0) {
printf ("a=%d\n", a);
read (fd, something) ;
}

```

### __ANSWER__:

- A) The value of variable 'a' as printed in the child process will be 5. After forking, the child process gets its own separate memory space, including its own copy of the variables. Any changes made to variables in the parent process after forking will not affect the child process. Therefore, the child process accesses its own copy of 'a', which retains the original value of 5.

- B) No, the attempt to read from the file descriptor will not succeed in the child process. The reason is that the child process is attempting to read from a file descriptor that was never opened in its own context. The child process only inherits file descriptors from the parent that were open at the time of forking. Since the read() operation comes after the close() operation in the parent process, the file descriptor is closed in the parent before the child gets a chance to read from it. The attempt to read from the closed file descriptor will fail in the child process.

## Instructions for compiling Shell

```c
gcc -o shell shell.c

//Compile the shell.c program using gcc to create an executable named shell.
```


```c
./shell

//Execute the compiled shell program in the terminal.
```

## Challanges
While developing our Shell, we faced challenges with parsing user input accurately, managing child processes and integrating color formatting seamlessly. We tested this a lot to make sure everything worked smoothly before finishing.

## Sources/tutorials used to complete the assignment
We relied on various resources, including online tutorials, documentation, and programming forums to complete the assignment. These resources helped us understand C programming basics and system calls.
