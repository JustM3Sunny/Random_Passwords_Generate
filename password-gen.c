#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to generate a random password of given length
void generatePassword(int length, char *password) {
    const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()_+[]{}|;:,.<>?";
    int charsetSize = sizeof(charset) - 1;

    for (int i = 0; i < length; i++) {
        password[i] = charset[rand() % charsetSize];
    }
    password[length] = '\0'; // Null-terminate the string
}

// Main function
int main() {
    srand(time(0)); // Initialize random seed

    int numPasswords, passLength;

    // Input number of passwords and their length
    printf("Enter the number of passwords to generate: ");
    scanf("%d", &numPasswords);

    if (numPasswords <= 0) {
        printf("Number of passwords must be greater than 0.\n");
        return 1;
    }

    printf("Enter the length of each password: ");
    scanf("%d", &passLength);

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
        char password[passLength + 1]; // Buffer for the password
        generatePassword(passLength, password); // Generate a password

        printf("%d: %s\n", i + 1, password); // Print the password
        fprintf(file, "%s\n", password);    // Save the password to the file
    }

    fclose(file); // Close the file
    printf("\nAll passwords saved to 'passwords.txt'.\n");

    return 0;
}
