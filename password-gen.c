#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <stdint.h> // For uint32_t
#include <limits.h> // For INT_MAX, INT_MIN
#ifdef _WIN32
#include <windows.h>
#include <bcrypt.h>
#pragma comment(lib, "Bcrypt.lib") // Link with Bcrypt.lib
#else
#include <unistd.h>
#include <sys/random.h>
#endif

#define MAX_PASSWORD_LENGTH 1024
#define SAFE_INPUT_BUFFER_SIZE 256

// Function to generate a random password of given length
int generatePassword(int length, char *password) {
    const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()_+[]{}|;:,.<>?";
    size_t charsetSize = sizeof(charset) - 1;

    // Check if length is valid
    if (length <= 0 || length > MAX_PASSWORD_LENGTH) {
        fprintf(stderr, "Password length must be between 1 and %d.\n", MAX_PASSWORD_LENGTH);
        return -1; // Indicate failure
    }

    // Use a better random number generator
    for (int i = 0; i < length; i++) {
        uint32_t random_value; // Use uint32_t for consistency
#ifdef _WIN32
        if (BCryptGenRandom(NULL, (PUCHAR)&random_value, sizeof(random_value), BCRYPT_USE_SYSTEM_PREFERRED_RNG) != 0) {
            fprintf(stderr, "Error generating random number.\n");
            return -1;
        }
#elif defined(__APPLE__) // macOS and iOS
        arc4random_buf(&random_value, sizeof(random_value));
#else
        ssize_t bytes_read = getrandom(&random_value, sizeof(random_value), GRND_NONBLOCK);
        if (bytes_read != sizeof(random_value)) {
            fprintf(stderr, "Error generating random number: %s\n", strerror(errno));
            return -1;
        }
#endif
        password[i] = charset[random_value % charsetSize];
    }
    password[length] = '\0'; // Null-terminate the string
    return 0; // Indicate success
}

// Function to safely read an integer from stdin
int safe_scanf_int(const char *prompt, int *value) {
    char buffer[SAFE_INPUT_BUFFER_SIZE]; // Use a buffer to prevent buffer overflows
    char *endptr;
    long temp;

    printf("%s", prompt);
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        perror("Error reading input");
        return -1; // Indicate failure
    }

    // Remove trailing newline, if present
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    // Attempt to convert the input to an integer
    errno = 0; // Reset errno before the call
    temp = strtol(buffer, &endptr, 10);

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

    // Check if any characters remain after the number
    if (*endptr != '\0') {
        fprintf(stderr, "Invalid input: Extra characters found\n");
        return -1;
    }

    // Check for integer overflow
    if (temp > (long)INT_MAX || temp < (long)INT_MIN) {
        fprintf(stderr, "Integer overflow detected\n");
        return -1;
    }

    *value = (int)temp;
    return 0; // Indicate success
}


// Main function
int main() {
    int numPasswords, passLength;
    char *password = NULL; // Initialize password pointer
    FILE *file = NULL;     // Initialize file pointer

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

    // Validate password length to prevent excessive memory allocation
    if (passLength > MAX_PASSWORD_LENGTH) {
        printf("Password length is too large. Please enter a value less than or equal to %d.\n", MAX_PASSWORD_LENGTH);
        return 1;
    }

    file = fopen("passwords.txt", "w"); // Open file to save passwords
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    printf("\nGenerated Passwords:\n");
    for (int i = 0; i < numPasswords; i++) {
        password = (char *)malloc(passLength + 1); // Allocate memory dynamically
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