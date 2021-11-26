# minishell
Group project: The objective of this project is for you to create a simple shell.  (usernames on 42 intra: lwray &amp; idonado)

# Allowed functions descriptions
### readline()
syntax: char *readline(const char *prompt)
This function takes the parameter prompt and places it as a prompt.
Return: Whatever is typed into the terminal is returned by this function, blank lines will be black strings. 
*must free() the returned string.*
​
### add_history()
syntax: void add_history(const char *string)
This function adds whatever is tossed in as a parameter to a history buffer that is automatically created with readline(), we can then scroll through the command prompt history using arrow keys.
​
### rl_clear_history()
syntax: void rl_clear_history(void)
This clear the history that has been stored using add_history.
Although when checking, nothing seems to leak when if it isn't used, it might be needed in the future. Perhaps these leaks aren't being detected.
​
### rl_on_new_line()
syntax: int on_new_line(void)
I'm still unsure if this is going to be useful it apparently just notifies the readline functions that we have moved to a newline. (?)
​
### rl_replace_line()
syntax: void rl_replace_line(const char *text, int clear_undo)
Replaces the content of rl_line_buffer .. which I suppose is whatever is being written or whatever is written onto the readline buffer. The undo options remain th	e same unless clear_undo is set to zero. I suppose 0 clears history (?)

### rl_redisplay()
syntax: void rl_redisplay(void)
changes whatever is written on the terminal to the contents of the rl_line_buffer .. (?)

### fork()
syntax: int fork(void);
This function creates a clone of the existing process, we then have to check the Process ID in order to define behaviour within the child process or parent process. Within the child process the PID will be 0, that's how we know where we are. Fork starts when fork is declared, if we need to communicate with the parent process within the child process, we know fork returns the Parent PID for the child, and 0 for the parent.
​
### wait()
syntax: int wait(void)
This function waits for the child process to finish to continue further in the program. Keep in mind child processes can wait for their child processes so you must check in which process you're in to use this funciton or else all processes will wait for their child and the program will get stuck when the youngest child doesn't have a child to wait for.
+ https://www.youtube.com/watch?v=tcYo6hipaSA
+ https://www.youtube.com/watch?v=DiNmwwQWl0g
​
### waitpid()
syntax: int waitpid(int pid, int *status, int options)
This function is the same as wait() except it can wait for any specific child process by passing it's PID, the second parameter can be set to null or look up into how you can use that to obtain status information, the third parameter is used for enabling options.
​
​
### wait3() and wait4()
wait4() and wait#() is almost identical to waitpid() With wait4 we get a summary of resources used by the child process, and wait3() is almost identical to wait4(); These will most likely not be used.

### getcwd();
syntax: char* getcwd(char *buffer, size_t size);
This function allows us to obtain a string with the current directory(doesn't necessarily mean where the program is saved, because we can change directories to manipulate files all accross the computer). It accepts buffer which can be malloc'ed or just on the stack, and we must specify the size of the buffer too, it returns a pointer to the very same pointer we passed for some reason.

### chdir(char *path)
sytntax: int	chdir(char *path)
While getcwd() only gives us a string with our current directory, chrdir() changes the directory the process is working in, so it can manipulate files anywhere on the system. Returns 0 is it was a success or -1 if it failed.

### stat() fstat() lstat()
syntax: int stat(char *path, struct stat *structname)
All three functions above retrieve status and data about a file specified in the parameter. Returns 0 if it was a success and -1 if there was an error, on success the struct passed as an argument is filled with all the data.
stat simply fills the struct with data, fstat does the same but works with File Descriptors instead of path, and lstat gives information about the link in case it's a symbolic link, and not the file itself.
https://www.youtube.com/watch?v=LERSkW_pLBs

### execve()
syntax: int execve(char *path, char *argv[], char *env[])
This function simply executes a program specified by the path, argv are whatever flags/arguements are passed and env are a set of values that are passed as a string array in the form of "key=value"(null terminated). These are then used by the process that will be executed. Returns 0 if successfully executed the program or -1 otherwise. This function becomes the program executed & takes over the existing process and will exit when finished. If you don't want the program to exit once this program has finished executing, then you must fork() the program and run execve() within the child process.
+ https://www.youtube.com/watch?v=yN2Upw4dXu0

### dup() and dup2()
syntax: int dup(int fd) & int dup2(int fd, int fd_overwrite)
Dup simply copies the link to the indicated file descriptor and returns a file descriptor that identifies the same stream.
Dup2 does the same, execpt with the second parameter we can choose to overwrite any existing file descriptor and link that with the file descriptor indicated in the first parameter. 
A good way of using this is within a child process whenever we for example want to grab whateve it outputted without it printing onto the screen, we want to do this only within a child process because we will lose access to stdout afterward. 
+ https://www.youtube.com/watch?v=5fnVr-zH-SE

### pipe()
syntax: int pipe(int fd[2])
Calling pipe() before a fork() allows you to communicate between parent and child process through file descriptors. Otherwise the file descriptors will be cloned but also destroyed once the child process ends. Returns 0 on success -1 on fail.
+ https://www.youtube.com/watch?v=Mqb2dVRe0uo

### opendir(), readdir(), closedir()
syntax: DIR *opendir(const char *filename/path)
This function accepts a path as a parameter and returns a type "DIR" (it's just a struct with a typedef) included in its respective header file and that type gives us access to a lot of information about the directory and the files in it. Returns a NULL pointer is it failed.

syntax: struct dirent *readdir(DIR *dirp)
This function accepts declared our DIR "type" as a parameter and returns a pointer to the first "entry" (file or folder in the directory) and all its specific info. Each time it's called it moves on to the next entry and returns NULL when the list is over or if it fails.

syntax: int closedir(DIR *dirp)
This function simply closes (frees whatever it needs to free) what you opened with opendir(). Returns 0 on success -1 on error.
+ https://www.youtube.com/watch?v=j9yL30R6npk

### strerror() & perror()
syntax: char *strerror(int errno)
This funtion accepts the global variable errno and returns a string pointer with the specification of the error. If the error number is not recognized it returns Unknown error string AKA EINVAL.

syntax: void perror(const char *str)
This function just prints out the error contained in errno to the standard output with a message attached to the begining, the message if specified by the user using the str parameter. Prints out unknown error if it's not recognized.
+ https://www.youtube.com/watch?v=IZiUT-ipnj0

### isatty() , ttyname() & ttyslot()
syntax: int isatty(int fd)
this function accepts an integer as a parameter and checks wheather it's a valid terminal "device".. It seems to check wheather it's stdin, out or error.
If it is, it returns 1, if not, it returns 0.

syntax: char *ttyname(int fd)
This one returns a string with the "name" of the terminal type device indicated, it seems to just send back the same location for 0, 1, 2 and (NUL)L for anything else.

syntax: int ttyslot(void)
This seems to just return the first terminal type device file descriptor it finds... (0, or STDIN).

### getenv()
syntax: char *getenv(const char *name)
This function accepts the name of an envioronment variable you want to search for, and returns the value if it exists, or NULL if it didn't find it. 
for example if we need the PATH variable we'd call it like so 
```c
  char *path = getenv("PATH");
```
and we'd get a string with all the executable paths like this; 
####  /usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki
