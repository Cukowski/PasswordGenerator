# Simple C Password Generator

A lightweight command-line password generator written in C. You can specify which character sets to include (uppercase, lowercase, digits, special characters) and choose the length.

## Files

- `passgen.c` : The C source code.
- `Makefile`  : Build instructions.
- `README.md` : This file.

## Requirements

- A C compiler (e.g., `gcc`)
- Unix-like environment (Linux, macOS) or WSL on Windows.

## Build

```bash
make
````

This will compile `passgen.c` into an executable named `passgen`.

## Usage

```
./passgen [--length N] [--upper] [--lower] [--digits] [--special]
./passgen --help
```

* `--length N` : Set the desired password length (default: 12, maximum: 127).
* `--upper`    : Include uppercase letters (`A–Z`).
* `--lower`    : Include lowercase letters (`a–z`).
* `--digits`   : Include digits (`0–9`).
* `--special`  : Include special characters (e.g., `!@#$%^&*()...`).
* `--help`     : Show usage instructions.

### Default Behavior

If you do **not** specify any of `--upper`, `--lower`, `--digits`, or `--special`, the tool will default to using uppercase, lowercase, and digits (but *not* special characters).

### Examples

* Generate a 12-character password with uppercase, lowercase, and digits (default):

  ```bash
  ./passgen
  ```
* Generate a 16-character password including everything (upper, lower, digits, special):

  ```bash
  ./passgen --length 16 --upper --lower --digits --special
  ```
* Generate an 8-character password with only lowercase letters and digits:

  ```bash
  ./passgen --length 8 --lower --digits
  ```
* Generate a 10-character password with special characters only:

  ```bash
  ./passgen --length 10 --special
  ```

## Cleaning Up

To remove the compiled executable:

```bash
make clean
```

---

> **Note:** This generator uses the C standard library's `rand()` function seeded with `time(NULL)`. For cryptographic or production use, consider replacing `rand()` with a cryptographically secure random function (e.g., `getrandom()` on Linux, `SecRandomCopyBytes()` on macOS).

