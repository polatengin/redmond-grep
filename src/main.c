#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define VERSION "1.0.0"

int main(int argc, char *argv[]) {
    int flag_i = 0, flag_n = 0, flag_E = 0;
    int arg_idx = 1;

    // Handle --help and --version inline
    while (arg_idx < argc && argv[arg_idx][0] == '-') {
        if (strcmp(argv[arg_idx], "-i") == 0) flag_i = 1;
        else if (strcmp(argv[arg_idx], "-n") == 0) flag_n = 1;
        else if (strcmp(argv[arg_idx], "-E") == 0) flag_E = 1;
        else if (strcmp(argv[arg_idx], "--help") == 0) {
            printf("Usage: %s [OPTIONS] pattern [file...]\n", argv[0]);
            printf("Options:\n");
            printf("  -i        Ignore case\n");
            printf("  -n        Show line numbers\n");
            printf("  -E        Use extended regex\n");
            printf("  --help    Show this help\n");
            printf("  --version Show version\n");
            return 0;
        }
        else if (strcmp(argv[arg_idx], "--version") == 0) {
            printf("%s version %s\n", argv[0], VERSION);
            return 0;
        }
        else {
            fprintf(stderr, "Unknown flag: %s\n", argv[arg_idx]);
            return 1;
        }
        arg_idx++;
    }

    if (arg_idx >= argc) {
        fprintf(stderr, "Usage: %s [OPTIONS] pattern [file...]\n", argv[0]);
        return 1;
    }

    char *pattern = argv[arg_idx++];
    regex_t regex;
    int reg_flags = REG_NOSUB | REG_NEWLINE;
    if (flag_i) reg_flags |= REG_ICASE;

    if (regcomp(&regex, pattern, flag_E ? REG_EXTENDED | reg_flags : reg_flags)) {
        fprintf(stderr, "Invalid regex pattern\n");
        return 1;
    }

    if (arg_idx == argc) {
        char *line = NULL;
        size_t len = 0;
        int lineno = 0;
        while (getline(&line, &len, stdin) != -1) {
            lineno++;
            if (!regexec(&regex, line, 0, NULL, 0)) {
                if (flag_n) printf("%d:", lineno);
                printf("%s", line);
            }
        }
        free(line);
    } else {
        for (int f = arg_idx; f < argc; f++) {
            FILE *fp = fopen(argv[f], "r");
            if (!fp) { perror(argv[f]); continue; }

            char *line = NULL;
            size_t len = 0;
            int lineno = 0;
            while (getline(&line, &len, fp) != -1) {
                lineno++;
                if (!regexec(&regex, line, 0, NULL, 0)) {
                    if (flag_n) printf("%d:", lineno);
                    printf("%s", line);
                }
            }
            free(line);
            fclose(fp);
        }
    }

    regfree(&regex);
    return 0;
}
