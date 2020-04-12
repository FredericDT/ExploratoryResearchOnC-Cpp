/*
 * MIT License
 *
 * Copyright (c) 2020 FredericDT <fredericdt@bupt.edu.cn>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#define _XOPEN_SOURCE 1
#define _XOPEN_SOURCE_EXTENDED 1
#define __USER_XOPEN_EXTENDED 1

#define __USE_GNU 1

#include <stdio.h>

#define N_OPEN_FD 10

/**
 * list all files in pwd
 *
 * -r recursively list all subdirs, which include relative paths
 * -a includes files whose name start with '.', which should be ignored in default mode
 * -l set minimium size of listed file
 * -h set maximium size of listed file
 * -m set maximium edit time gap in days
 * -- terminate arg parse
 *
 */ 

#include <time.h>
#include <sys/stat.h>
#include <ftw.h>
#include <stdint.h>

int config = 0;
const int RECURSIVE = 1;
const int INCLUDE_HIDDEN_FILE = 2;
const int MIN_SIZE_SET = 4;
const int MAX_SIZE_SET = 8;
const int EDIT_TIME_GAP_LIMIT = 16;
const int PRINT_HELP = 32;

int min_size = -1;
int max_size = -1;
int edit_time_gap = -1;

#include <inttypes.h>
#include <errno.h>
#include <stdlib.h>

#include <dirent.h>
#include <limits.h>
#include <string.h>
int edit_time_gap_in_seconds = -1;

FILE *OUTPUT;

void print_help(){
    fprintf(OUTPUT, 
        "FDTsList (c) 2020 by fdt <fredericdt@bupt.edu.cn>\n"
        "Usage: list [command] ... [--] [target_path] ...\n"
        "Supported commands are as below:\n"
        "   -? print this help\n"
        "   -r recursively list all subdirs, which include relative paths\n"
        "   -a includes files whose name start with '.', which should be ignored in default mode\n"
        "   -l set minimium size of listed file\n"
        "   -h set maximium size of listed file\n"
        "   -m set maximium edit time gap in days\n"
        "   -- terminate arg parse\n"
    );
}

/**
 * Argument parser
 * store parse result in config, min_size, max_size
 *
 * It's 2020... ┑(￣Д ￣)┍
 */
int parse_args(int argc, char **argv) {
    char *parse_end;
    char error_message[50];
    int i = 1;
    while (i < argc) {
        char is_command = argv[i][0] == '-';
        if (!is_command) {
            return i;
        }
        char command_type = argv[i][1];

        switch(command_type) {
            case '-':
                return i + 1;
            case 'r':
                config |= RECURSIVE;
                break;
            case 'a':
                config |= INCLUDE_HIDDEN_FILE;
                break;
            case 'l':
                config |= MIN_SIZE_SET;
                // Done: parse min size
                ++i;
                if (i >= argc) {
                    errno = EINVAL;
                    sprintf(error_message, "%s:%d: Parse min size reach end of argv", __FILE__, __LINE__);
                    perror(error_message);
                    exit(EXIT_FAILURE);
                }
                min_size = strtoimax(argv[i], &parse_end, 10);
                if (errno) {
                    perror("Min size parse error");
                    exit(EXIT_FAILURE);
                }
                break;
            case 'h':
                config |= MAX_SIZE_SET;
                // Done: parse max size
                ++i;
                if (i >= argc) {
                    errno = EINVAL;
                    sprintf(error_message, "%s:%d: Parse max size reach end of argv", __FILE__, __LINE__);
                    perror(error_message);
                    exit(EXIT_FAILURE);
                }
                max_size = strtoimax(argv[i], &parse_end, 10);
                if (errno) {
                    perror("Max size parse error");
                    exit(EXIT_FAILURE);
                }
                break;
            case 'm':
                config |= MAX_SIZE_SET;
                // Done: parse edit time gap
                ++i;
                if (i >= argc) {
                    errno = EINVAL;
                    sprintf(error_message, "%s:%d: Parse edit time gap reach end of argv", __FILE__, __LINE__);
                    perror(error_message);
                    exit(EXIT_FAILURE);
                }
                edit_time_gap = strtoimax(argv[i], &parse_end, 10);
                if (errno) {
                    perror("Edit time gap parse error");
                    exit(EXIT_FAILURE);
                }
                edit_time_gap_in_seconds = edit_time_gap * 86400;
                break;
            case '?':
                print_help();
                exit(EXIT_SUCCESS);
                break;
            default:
                errno = EINVAL;
                sprintf(error_message, "%s:%d", __FILE__, __LINE__);
                perror(error_message);

                print_help();
                exit(EXIT_FAILURE);
        }

        ++i;
    }
    return i;
}

// Output template for list_dir
const char *OUTPUT_TEMPLATE = "%d %s\n";

#define FTW_CONTINUE 0
#define FTW_ACTIONRETVAL 16
#define FTW_SKIP_SUBTREE 2

int ftw_first_dir = 1;

int file_triverse_parse(const char *fpath, const struct stat *stat_buf, int typeflag, struct FTW *ftwbuf) {
    if ((config & MIN_SIZE_SET) && stat_buf->st_size < min_size) {
        return FTW_CONTINUE;
    }

    if ((config & MAX_SIZE_SET) && stat_buf->st_size > max_size) {
        return FTW_CONTINUE;
    }
    
    if ((config & EDIT_TIME_GAP_LIMIT) && (time(NULL) - stat_buf->st_mtime > edit_time_gap_in_seconds)) {
        return FTW_CONTINUE;
    }

    if (typeflag & FTW_D && !(config & RECURSIVE)) {
        if (!ftw_first_dir) {
            return FTW_SKIP_SUBTREE;
        } else {
            ftw_first_dir = 0;
            return FTW_CONTINUE;
        }
    }

    //printf("%s:%d: ftwbuf->base: %d\n", __FILE__, __LINE__, ftwbuf->base);

    if (!(config & INCLUDE_HIDDEN_FILE) && fpath[ftwbuf->base > 0 ? ftwbuf->base : 0] == '.') {
        return FTW_SKIP_SUBTREE;
    }

    fprintf(OUTPUT, OUTPUT_TEMPLATE, stat_buf->st_size, fpath);
    return FTW_CONTINUE;
}

int list_dir(char *path) {
    errno = 0;
    nftw(path, file_triverse_parse, N_OPEN_FD, FTW_ACTIONRETVAL);
    return errno;
}


int main(int argc, char **argv) {
    OUTPUT = stdout;
    int path_start = parse_args(argc, argv);

    // if no path provided, use pwd instead
    if (path_start >= argc) {
        list_dir(".");
    }

    for (; path_start < argc; ++path_start) {
        list_dir(argv[path_start]);
    }

    return 0;
}
