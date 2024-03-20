#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <errno.h>
#include <ctype.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGS 10

// Function to display the shell prompt
void display_prompt() {
    printf("\033[1;36mArnela's and Dema's Shell\033[0m$ "); // Cyan color for the shell prompt
}

// Function to parse user input into command arguments
int parse_input(char *input, char **args) {
    int argc = 0;
    char *token = strtok(input, " \n");

    // Loop through each token in the input string
    while (token != NULL && argc < MAX_ARGS - 1) {
        args[argc++] = token; // Add token to arguments array
        token = strtok(NULL, " \n"); // Move to next token
    }
    args[argc] = NULL; // Set the last argument to NULL to mark the end of arguments

    return argc; // Return the number of arguments
}

// Function to execute the command
void execute_command(char **args) {
    pid_t pid = fork(); // Fork a new process

    if (pid == -1) {
        perror("fork"); // Print error if forking fails
    } else if (pid == 0) {
        // Child process
        if (execvp(args[0], args) == -1) { // Execute the command
            perror("exec"); // Print error if execution fails
            exit(EXIT_FAILURE); // Exit child process with failure status
        }
    } else {
        // Parent process
        wait(NULL); // Wait for the child process to finish
    }
}

// Function to display total uptime duration in human-readable format
void display_uptime() {
    struct timespec ts;
    if (clock_gettime(CLOCK_BOOTTIME, &ts) != 0) { // Get system uptime
        perror("clock_gettime"); // Print error if getting system uptime fails
        return;
    }

    // We converted uptime to days, hours, minutes, and seconds
    long uptime_seconds = ts.tv_sec;
    int days = uptime_seconds / (60 * 60 * 24);
    int hours = (uptime_seconds / (60 * 60)) % 24;
    int minutes = (uptime_seconds / 60) % 60;
    int seconds = uptime_seconds % 60;

    // Printing system uptime
    printf("\033[1;32mSystem uptime: %d days, %d hours, %d minutes, %d seconds\033[0m\n", days, hours, minutes, seconds);
}

// Function to create a directory
void create_directory(int argc, char **args) {
    if (argc < 2) {
        printf("\033[1;93mUsage: mkdir <directory_name>\033[0m\n"); // Yellow color for warning message
        return;
    }

    // Loop through each directory name provided as argument
    for (int i = 1; i < argc; i++) {
        // Attempt to create the directory
        if (mkdir(args[i], 0777) == -1) {
            // Print error if directory creation fails
            if (errno == EEXIST) {
                printf("\033[1;93mDIRECTORY '%s' ALREADY EXISTS.\033[0m\n", args[i]); // Yellow color for warning message
            } else {
                printf("\033[1;31mFAILED TO CREATE DIRECTORY '%s': %s\033[0m\n", args[i], strerror(errno)); // Red color for error message
            }
        } else {
            printf("\033[1;32mSUCCESFULLY CREATED NEW DIRECTORY '%s'.\033[0m\n", args[i]); // Green color for success message
        }
    }
}


// Function to display a random fact with white text and cool background colors
void display_random_fact() {
    char *facts[] = {
        "The first computer virus was created in 1983 and was called the Elk Cloner.",
        "The first version of Windows, Windows 1.0, was released on November 20, 1985.",
        "The most popular Linux distribution, Ubuntu, was first released on October 20, 2004.",
        "The original name of macOS was Mac OS X. It was later renamed to OS X and then macOS.",
        "The first computer mouse was invented by Douglas Engelbart in 1964. It was made of wood.",
        "Linus Torvalds created Linux as a hobby project while he was a student at the University of Helsinki.",
        "The first graphical web browser, called WorldWideWeb, was developed by Tim Berners-Lee in 1990.",
        "The concept of virtual memory, allowing programs to address more memory than is physically available, was introduced in the 1950s.",
        "The first IBM personal computer, the IBM 5150, was released in 1981. It ran on the Intel 8088 processor and had 16KB of RAM.",
        "The operating system Unix was developed in the late 1960s and early 1970s at AT&T Bell Labs."
    };


char *colors[] = {
    "41;37", // Red background with white text
    "44;37", // Blue background with white text
    "45;37", // Magenta background with white text
    "46;37", // Cyan background with white text
    "47;30", // White background with black text
    "105;37", // Pink background with white text
};

    int num_facts = sizeof(facts) / sizeof(facts[0]);
    int num_colors = sizeof(colors) / sizeof(colors[0]);
    srand(time(NULL));
    int random_index = rand() % num_facts;
    int color_index = rand() % num_colors;
    printf("\033[%smRandom Fact: %s\033[0m\n", colors[color_index], facts[random_index]);
}




// Function to list contents of a directory
void list_directory_contents() {
    struct dirent *entry;
    DIR *dp;

    dp = opendir(".");
    if (dp == NULL) {
        perror("opendir"); // Print error if opening directory fails
        return;
    }

    // Loop through each entry in the directory and print its name
    while ((entry = readdir(dp)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    closedir(dp); // Close the directory
}

// Main function
int main() {
    char input[MAX_COMMAND_LENGTH];
    char *args[MAX_ARGS];

    // We displayed the welcome message for our Shell :)
    printf("========================================\n");
    printf("WELCOME TO THE ARNELA'S AND DEMA'S SHELL\n");
    printf("========================================\n");

    // Main loop for shell operations
    while (1) {
        display_prompt(); // Display shell prompt
        fgets(input, MAX_COMMAND_LENGTH, stdin); // Read user input

        // Check if input command is in uppercase
        int uppercase = 1;
        for (int i = 0; input[i] != '\0'; i++) {
            if (islower(input[i])) {
                uppercase = 0;
                break;
            }
        }

        int argc;
        if (uppercase) {
            printf("\033[1;93mWARNING: CAPS LOCK MAY BE ON! DON'T SHOUT AT ME :( \033[0m\n"); // Yellow color for warning message

            argc = 0; // Set argc to 0 to prevent further processing
        } else {
            argc = parse_input(input, args); // Parse input into arguments
        }

        if (argc > 0) {
            if (strcmp(args[0], "exit") == 0) {
                break; // Exit the shell
            } else if (strcmp(args[0], "mkdir") == 0) {
                create_directory(argc, args); // Create directory command
            } else if (strcmp(args[0], "uptime") == 0) {
                display_uptime(); // Display system uptime command
            } else if (strcmp(args[0], "fact") == 0) {
                display_random_fact(); // Display random fact command
            } else if (strcmp(args[0], "ls") == 0) {
                list_directory_contents(); // List directory contents command
            } else if (strcmp(args[0], "sl") == 0) {
           printf("\033[1;93mYou seem to be half asleep. You need some coffee!\033[0m\n"); // Bright yellow color for warning message


            } else {
                execute_command(args); // Execute external command
            }
        }
    }

    return 0;
}
