🛡️ Random Password Generator

⚡ Features

Customizable Passwords: Generate as many passwords as you need, with your chosen length.
Strong Security: Uses uppercase, lowercase, numbers, and special characters.
File Storage: Saves all passwords in passwords.txt for easy access.

🚀 How to Use

Compile:

Copy code
gcc password_generator.c -o password_generator
Run:

Copy code
./password_generator
Input:
Enter the number of passwords to generate.
Enter the length for each password.
View Output:
Passwords are displayed on the terminal.
Check passwords.txt for all saved passwords.
📂 Example

Copy code
Enter the number of passwords to generate: 2
Enter the length of each password: 8


Generated Passwords:
1: a3$XyT@q
2: P9!fKz7&
Saved to passwords.txt ✅
🛠️ Customization
Add/Remove characters in charset[]:
c
Copy code
const char charset[] = "ABC...@#$";
Change file name:
c
Copy code
FILE *file = fopen("my_passwords.txt", "w");
🎉 Enjoy Secure Passwords! 💻✨
