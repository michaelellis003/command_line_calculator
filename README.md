# C++ Command-Line Calculator

This repository contains a simple command-line interface (CLI) calculator implemented in C++. It can parse and evaluate mathematical expressions involving basic arithmetic operations, parentheses, and exponentiation, respecting operator precedence and associativity.

## Features
- **Basic Arithmetic Operations:** Supports addition (+), subtraction (-), multiplication (*), division (/), and exponentiation (^).
- **Parentheses Support:** Correctly handles expressions with nested parentheses.
- **Operator Precedence:** Follows standard mathematical operator precedence (e.g., multiplication/division before addition/subtraction, exponentiation highest).
- **Operator Associativity:** Correctly applies left-associativity for +, -, *, / and right-associativity for ^.
- **Floating-Point Support:** Handles decimal numbers.
- **Error Handling:** Provides informative error messages for syntax errors (e.g., mismatched parentheses, unknown operators) and mathematical errors (e.g., division by zero).

## How It Works
The calculator processes mathematical expressions in two main stages:

1. Tokenization: The tokenizer.cpp component breaks down the input mathematical string into a sequence of meaningful units called "tokens" (e.g., numbers, operators, parentheses).
2. Expression Evaluation (Shunting-Yard Algorithm): The calculator.cpp component uses an implementation of the Shunting-yard algorithm to convert the tokenized infix expression into Reverse Polish Notation (RPN) implicitly and then evaluates it using a stack-based approach.

## Building the Project
This project uses CLI11 for command-line argument parsing. You will need a C++ compiler (like g++ or Clang) and the CLI11 header-only library.

1. **Download CLI11:**
    If you don't have it, you can download the CLI11.hpp header file from the latest release on the (CLI11 GitHub)[https://github.com/CLIUtils/CLI11] and place it in your project directory or a system include path.


2. **Compile:**
    Navigate to the project directory in your terminal and compile the source files.

    ```
    g++ -std=c++17 -o calculator main.cpp src/tokenizer.cpp src/calculator.cpp -Iinclude/
    ```

    - -std=c++17: Specifies the C++17 standard.

    - -o calculator: Names the output executable calculator.

    - main.cpp src/tokenizer.cpp src/calculator.cpp: The source files to compile.

    - -Iinclude/: Tells the compiler to look for include files (like CLI11.hpp and your project's headers) in the include/ directory.


## Usage
Run the compiled executable with the `-e` or `--expression` flag followed by the mathematical expression you want to evaluate. Remember to enclose expressions with spaces or special characters in quotes.

```
./calculator -e "2 + 3 * (4 - 1)"
```

### Examples:

- **Basic arithmetic:**
    ```
    ./calculator -e "10 / 2 + 5"
    ```
    Output: `10 / 2 + 5 = 10`

- **Parentheses:**
    ```
    ./calculator -e "(5 + 3) * 2"
    ```

    Output: `(5 + 3) * 2 = 16`

- **Exponentiation (Right-Associative):**
    ```
    ./calculator -e "2 ^ 3 ^ 2"
    ```

    Output: `2 ^ 3 ^ 2 = 512 (Evaluates as 2 ^ (3 ^ 2) = 2 ^ 9)`

- **Floating-point numbers:**
    ```
    ./calculator -e "1.5 * 4 - .5"
    ```

    Output: `1.5 * 4 - .5 = 5.5`

- **Division by zero (Error Handling):**
    ```
    ./calculator -e "10 / (5 - 5)"
    ```

    Output: `Math Error: Division by zero`

- Mismatched parentheses (Error Handling):
    ```
    ./calculator -e "(2 + 3"
    ```

    Output: `Syntax Error: Mismatched parentheses at end of expression.`

## Dependencies
- CLI11: A header-only C++11 library for parsing command line arguments.
    - GitHub: https://github.com/CLIUtils/CLI11