#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

extern size_t ft_strlen(const char *s);
extern int ft_strcmp(const char *s1, const char *s2);
extern char *ft_strcpy(char *dest, const char *src);
extern char *ft_strdup(const char *s);
extern ssize_t ft_read(int fd, void *buf, size_t count);
extern ssize_t ft_write(int fd, const void *buf, size_t count);

void test_strlen() {
    printf("\n--- STRLEN ---\n");
    
    const char *tests[] = {"Hello", "", "longer string"};
    int num_tests = sizeof(tests) / sizeof(tests[0]);
    
    for (int i = 0; i < num_tests; i++) {
        size_t std_result = strlen(tests[i]);
        size_t ft_result = ft_strlen(tests[i]);
        printf("String: \"%s\"\n", tests[i]);
        printf("  strlen:    %zu\n", std_result);
        printf("  ft_strlen: %zu\n", ft_result);
    }
}

void test_strcmp() {
    printf("\n--- STRCMP ---\n");
    
    const char *tests[][2] = {
        {"abc", "abc"},
        {"abc", "abd"}, 
        {"", ""},
        {"hello", "world"},
    };
    int num_tests = sizeof(tests) / sizeof(tests[0]);
    
    for (int i = 0; i < num_tests; i++) {
        int std_result = strcmp(tests[i][0], tests[i][1]);
        int ft_result = ft_strcmp(tests[i][0], tests[i][1]);
        printf("Strings: \"%s\" vs \"%s\"\n", tests[i][0], tests[i][1]);
        printf("  strcmp:    %d\n", std_result);
        printf("  ft_strcmp: %d\n", ft_result);
    }
}

void test_strcpy() {
    printf("\n--- STRCPY ---\n");
    
    const char *tests[] = {"Hello", "", "Test string"};
    int num_tests = sizeof(tests) / sizeof(tests[0]);
    
    for (int i = 0; i < num_tests; i++) {
        char std_dest[100] = {0};
        char ft_dest[100] = {0};
        
        char *std_result = strcpy(std_dest, tests[i]);
        char *ft_result = ft_strcpy(ft_dest, tests[i]);
        
        printf("Source: \"%s\"\n", tests[i]);
        printf("  strcpy:    \"%s\" (returns: %p)\n", std_dest, (void*)std_result);
        printf("  ft_strcpy: \"%s\" (returns: %p)\n", ft_dest, (void*)ft_result);
    }
}

void test_strdup() {
    printf("\n--- STRDUP ---\n");
    
    const char *tests[] = {"Hello", "", "Test string"};
    int num_tests = sizeof(tests) / sizeof(tests[0]);
    
    for (int i = 0; i < num_tests; i++) {
        char *std_result = strdup(tests[i]);
        char *ft_result = ft_strdup(tests[i]);
        
        printf("Source: \"%s\"\n", tests[i]);
        printf("  strdup:    %s (ptr: %p)\n", std_result ? std_result : "NULL", (void*)std_result);
        printf("  ft_strdup: %s (ptr: %p)\n", ft_result ? ft_result : "NULL", (void*)ft_result);
    }
}

void test_write() {
    printf("\n--- WRITE ---\n");
    
    const char *tests[] = {"Hello", "Test message", ""};
    int num_tests = sizeof(tests) / sizeof(tests[0]);
    
    for (int i = 0; i < num_tests; i++) {
        printf("Testing: \"%s\"\n", tests[i]);
        
        write(1, "  write:    ", 12);
        write(1, tests[i], strlen(tests[i]));
        write(1, "\n", 1);
        
        write(1, "  ft_write: ", 12);
        ft_write(1, tests[i], strlen(tests[i]));
        write(1, "\n", 1);
    }
}

void test_read() {
    printf("\n--- READ ---\n");
    
    const char *test_content = "Hello World Test";
    
    int fd = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    write(fd, test_content, strlen(test_content));
    close(fd);
    
    fd = open("test.txt", O_RDONLY);
    char std_buffer[50] = {0};
    char ft_buffer[50] = {0};
    
    ssize_t std_result = read(fd, std_buffer, 10);
    lseek(fd, 0, SEEK_SET); // Reset file position
    ssize_t ft_result = ft_read(fd, ft_buffer, 10);
    
    printf("File content: \"%s\"\n", test_content);
    printf("Reading 10 bytes:\n");
    printf("  read:    \"%s\" (returned: %zd)\n", std_buffer, std_result);
    printf("  ft_read: \"%s\" (returned: %zd)\n", ft_buffer, ft_result);
    
    close(fd);
    unlink("test.txt");
}

int main() {
    printf("=== LIBASM vs STANDARD LIBRARY COMPARISON ===\n");
    
    test_strlen();
    test_strcmp();
    test_strcpy();
    test_strdup();
    test_write();
    test_read();
    
    printf("\n=== COMPARISON COMPLETED ===\n");
    return 0;
}