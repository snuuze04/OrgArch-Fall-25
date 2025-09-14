#include <stdio.h>
#include <stdint.h>
#include <string.h>

void div_convert(uint32_t n, int base, char *out);
void sub_convert(uint32_t n, int base, char *out);
void print_tables(uint32_t n);

int main() {
    FILE *file = fopen("a1_test_file.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open a1_test_file.txt\n");
        return 1; // Exit with error
    }

    char line[256];
    int test_num = 1;
    int total = 0;
    int passed = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        line[strcspn(line, "\n")] = '\0';

        if (line[0] == '#' || line[0] == '\0') {
            continue;
        }

        char func[20], expected[65];
        uint32_t n;
        int base;
        char result[65];

        if (sscanf(line, "%s %u %d %s", func, &n, &base, expected) == 4) {
            total++;

            if (strcmp(func, "div_convert") == 0) {
                div_convert(n, base, result);
            } else if (strcmp(func, "sub_convert") == 0) {
                sub_convert(n, base, result);
            } else {
                continue;
            }

            if (strcmp(result, expected) == 0) {
                printf("Test %d: %s(%u, %d) -> Got: \"%s\" [PASS]\n",
                       test_num, func, n, base, result);
                passed++;
            } else {
                printf("Test %d: %s(%u, %d) -> Expected: \"%s\", Got: \"%s\" [FAIL]\n",
                       test_num, func, n, base, expected, result);
            }
            test_num++;

        } else {
            char extra[64];
            if (sscanf(line, "%s %u %s", func, &n, extra) == 3) {
                if (strcmp(func, "print_tables") == 0 &&
                    strcmp(extra, "FORMATTED_OUTPUT") == 0) {

                    printf("Test %d: print_tables(%u) -> [FORMATTED OUTPUT CHECK]\n",
                           test_num, n);

                    print_tables(n);

                    total++;
                    passed++;
                    test_num++;
                }
            }
        }
    }

    fclose(file);
    
    printf("Summary: %d/%d tests passed\n", passed, total);

    return 0;
}
