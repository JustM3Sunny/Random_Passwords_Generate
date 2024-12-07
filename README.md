Description
This C program generates random passwords based on user input. The user specifies:

The number of passwords to generate.
The length of each password.
The generated passwords are saved in a file named passwords.txt, ensuring secure storage for later use.
Features
Dynamic Password Generation:

Create as many passwords as you need.
Set a custom length for each password.
Randomized Characters:

Passwords include uppercase, lowercase, digits, and special characters for better security.
File Storage:

All passwords are saved in a file (passwords.txt), making it easy to retrieve them.
How to Use
Compile the Program: Use GCC to compile the program:

bash
Copy code
gcc password_generator.c -o password_generator
Run the Program: Execute the compiled program:

bash
Copy code
./password_generator
Input Details:

Enter the number of passwords you want.
Enter the length of each password.
View Generated Passwords:

Passwords will be displayed on the terminal.
All passwords are saved to a file named passwords.txt in the same directory.
Sample Output
bash
Copy code
Enter the number of passwords to generate: 3
Enter the length of each password: 12

Generated Passwords:
1: $aB3#xY7g!H9
2: KqT8!f@4rP2z
3: W@hG2v&L7*Y9

All passwords saved to 'passwords.txt'.
File (passwords.txt) Content:

perl
Copy code
$aB3#xY7g!H9
KqT8!f@4rP2z
W@hG2v&L7*Y9
Customization
Change Characters: Modify the charset in the program to add/remove specific characters.

c
Copy code
const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()_+[]{}|;:,.<>?";
Change File Name: Update the file name in the code:

c
Copy code
FILE *file = fopen("custom_passwords.txt", "w");
Limitations
The maximum password length depends on your system's memory.
Ensure proper file permissions to write the passwords.txt file.
License
This project is open-source and free to use. Contributions and suggestions are welcome!
