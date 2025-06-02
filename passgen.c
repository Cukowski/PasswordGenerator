/*
A simple random password generator with optional flags
Usage:
  ./passgen [--length N] [--upper] [--lower] [--digits] [--special]
  ./passgen --help
By default (if no character-set flags are given), the generator includes
uppercase, lowercase, and digits. Special characters are only included if
--special is specified.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LEN 128

static void print_usage(const char *progname) {
    printf("Usage: %s [--length N] [--upper] [--lower] [--digits] [--special]\n", progname);
    printf("\n");
    printf("Options:\n");
    printf("  --length N   Specify password length (default: 12, max: %d)\n", MAX_LEN - 1);
    printf("  --upper      Include uppercase letters (A–Z)\n");
    printf("  --lower      Include lowercase letters (a–z)\n");
    printf("  --digits     Include digits (0–9)\n");
    printf("  --special    Include special characters (!@#$...)\n");
    printf("  --help       Show this help message and exit\n");
    printf("\n");
    printf("Examples:\n");
    printf("  %s --length 16 --upper --lower --digits --special\n", progname);
    printf("  %s --lower --digits          # generate a lowercase+digit password (length=12)\n", progname);
    printf("  %s --length 8 --special      # generate an 8-character password with special chars only\n", progname);
}

static char *generate_password(int length, int use_upper, int use_lower, int use_digits, int use_special)
{
    static char password[MAX_LEN];
    const char *upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char *lower = "abcdefghijklmnopqrstuvwxyz";
    const char *digits = "0123456789";
    const char *special = "!@#$%^&*()-_=+[]{};',.<>?/";
    
    char pool[MAX_LEN] = "";
    size_t pool_len = 0;

    if (use_upper) { 
        strcat(pool, upper); 
        pool_len += strlen(upper);
    }
    if (use_lower) { 
        strcat(pool, lower); 
        pool_len += strlen(lower);
    }
    if (use_digits) { 
        strcat(pool, digits); 
        pool_len += strlen(digits);
    }
    if (use_special) { 
        strcat(pool, special); 
        pool_len += strlen(special);
    }

    if (pool_len == 0) {
        fprintf(stderr, "Error: No characte sets selected.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < length; ++i) 
    {
        int index = rand() % pool_len;
        password[i] = pool[index];
    }
    password[length] = '\0';

    return password;
}

int main(int argc, char *argv[]) 
{
    int length = 12; // default
    int use_upper = 0, use_lower = 0, use_digits = 0, use_special = 0;
    int flag_count =0;

    for (int i = 1; i < argc; ++i)
    {
        if (strcmp(argv[i], "--help") == 0) {
            print_usage(argv[0]);
            return EXIT_SUCCESS;
        } else if (strcmp(argv[i], "--length") == 0) {
            if (i + 1 >= argc) {
                fprintf(stderr, "Error: --length requires a number\n");
                return EXIT_FAILURE;
            }
            length = atoi(argv[++i]);
            if (length <= 0 || length >= MAX_LEN) {
                fprintf(stderr, "Error: Length must be between 1 and %d.\n", MAX_LEN - 1); 
                return EXIT_FAILURE;
            }
        } else if (strcmp(argv[i], "--upper") == 0) {
            use_upper = 1;
            flag_count++;
        } else if (strcmp(argv[i], "--lower") == 0) {
            use_lower = 1;
            flag_count++;
        } else if (strcmp(argv[i], "--digits") == 0) {
            use_digits = 1;
            flag_count++;
        } else if (strcmp(argv[i], "--special") == 0) {
            use_special = 1;
            flag_count++;
        } else {
                fprintf(stderr, "Error: Unkown options '%s\n", argv[i]);
                print_usage(argv[0]);
                return EXIT_FAILURE;
        }
    }

    // If no character-set flag wer provided, enable upper, lower, digits by default
    if (flag_count == 0) {
        use_upper = use_lower = use_digits = 1;
    }

    srand((unsigned int)time(NULL));
    char *pwd = generate_password(length, use_upper, use_lower, use_digits, use_special);
    printf("Generated password: %s\n", pwd);

    return EXIT_SUCCESS;
}