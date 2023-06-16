Assignment #1, Chat Bots & Resource Synchronization

The first assignment will implement a program that can manage multiple chatbots that are running concurrently on their own thread but 
asynchronously. Each of these chatbots will write a specific text message to a singular, common shared resource, which is the file named 
QUOTE.txt. The program will utilize an approperiate IPC alglorithm to prevent data corruption.

Team Members:
1. Kobi Bell [cssc1432]
2. Mark Duraid [cssc1412]

Everything created for this project:

1. chatbots.c - Contains the implemntation of the program.
2. makefile - responsible for building and executing the program
3. README.md - This current file which has information about the program and group members. 

Compiling and Executing the program (follow in steps):

1. Head over to the project directory (~/a1).
2. Run the command: (make) in the terminal to compile the program.
3. Execute the program by running (./chatbots)

Conclusion:

This program creates the file QUOTE.txt in the directory and then writes its specific PID followed by (/r/n). Then it creates the semaphore
named FLAG to access the QUOTE.txt file. The threads are all created using the POSIX version of the threads (pthread_create()).
The thread aquires the FLAG semaphore and performs the following steps. First, it opens the QUOTE.txt file and writes the thread ID 
with the assigned quote. Then it prints "Thread <thread id> is running" to the console. Once all of the thread is printed, it will close the 
QUOTE.txt file and release the FLAG semaphore. Finally, it will repeat the steps listed 7 more times and once all the threads have completed their 
work, the semaphores will be destroyed and will exit and printing a message to the console. 




