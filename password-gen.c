#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <errno.h>

// Function to generate a random password of given length
int generatePassword(int length, char *password) {
    const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()_+[]{}|;:,.<>?";
    int charsetSize = sizeof(charset) - 1;

    // Check if length is valid
    if (length <= 0) {
        fprintf(stderr, "Password length must be greater than 0.\n");
        return -1; // Indicate failure
    }

    // Use arc4random_buf for better randomness (if available)
    for (int i = 0; i < length; i++) {
#ifdef __APPLE__ // macOS and iOS
        unsigned int key;
        arc4random_buf(&key, sizeof(key));
        password[i] = charset[key % charsetSize];
#else
        password[i] = charset[rand() % charsetSize];
#endif
    }
    password[length] = '\0'; // Null-terminate the string
    return 0; // Indicate success
}

// Function to safely read an integer from stdin
int safe_scanf_int(const char *prompt, int *value) {
    char buffer[256]; // Use a buffer to prevent buffer overflows

    printf("%s", prompt);
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        perror("Error reading input");
        return -1; // Indicate failure
    }

    // Attempt to convert the input to an integer
    char *endptr;
    errno = 0; // Reset errno before the call
    long temp = strtol(buffer, &endptr, 10);

    // Check for errors during conversion
    if (errno != 0) {
        perror("Error converting input to integer");
        return -1;
    }

    // Check if any characters remain after the number
    if (endptr == buffer) {
        fprintf(stderr, "No digits were found\n");
        return -1;
    }

    if (*endptr != '\n' && *endptr != '\0') {
        fprintf(stderr, "Invalid input: Extra characters found\n");
        return -1;
    }

    // Check for integer overflow
    if (temp > (int)2147483647 || temp < (int)-2147483648) {
        fprintf(stderr, "Integer overflow detected\n");
        return -1;
    }

    *value = (int)temp;
    return 0; // Indicate success
}


// Main function
int main() {
    srand(time(0)); // Initialize random seed

    int numPasswords, passLength;

    // Input number of passwords and their length
    if (safe_scanf_int("Enter the number of passwords to generate: ", &numPasswords) != 0) {
        return 1;
    }

    if (numPasswords <= 0) {
        printf("Number of passwords must be greater than 0.\n");
        return 1;
    }

    if (safe_scanf_int("Enter the length of each password: ", &passLength) != 0) {
        return 1;
    }

    if (passLength <= 0) {
        printf("Password length must be greater than 0.\n");
        return 1;
    }

    FILE *file = fopen("passwords.txt", "w"); // Open file to save passwords
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    printf("\nGenerated Passwords:\n");
    for (int i = 0; i < numPasswords; i++) {
        char *password = malloc(passLength + 1); // Allocate memory dynamically
        if (password == NULL) {
            perror("Memory allocation error");
            fclose(file);
            return 1;
        }

        if (generatePassword(passLength, password) != 0) {
            free(password);
            fclose(file);
            return 1;
        }

        printf("%d: %s\n", i + 1, password); // Print the password
        fprintf(file, "%s\n", password);    // Save the password to the file
        free(password); // Free the allocated memory
    }

    fclose(file); // Close the file
    printf("\nAll passwords saved to 'passwords.txt'.\n");

    return 0;
}