#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#define MAX_NAME_LEN 100

int calculate_love_percentage(const char *name1, const char *name2) {
    int sum = 0;
    
    // Convert to lowercase and sum ASCII values for name1
    for (int i = 0; name1[i] != '\0'; i++) {
        sum += tolower(name1[i]);
    }
    
    // Add ASCII values for name2
    for (int i = 0; name2[i] != '\0'; i++) {
        sum += tolower(name2[i]);
    }
    
    return sum % 101;
}

const char* get_love_message(int percentage) {
    if (percentage < 20)
        return "Let's just be friends!";
    else if (percentage < 40)
        return "Maybe in another universe...";
    else if (percentage < 60)
        return "There's a spark here!";
    else if (percentage < 80)
        return "Looking pretty good!";
    else
        return "TRUE LOVE! 🔥";
}

void print_progress(int percentage) {
    int bar_length = 30;
    int filled = (bar_length * percentage) / 100;
    
    printf("\n[");
    for (int i = 0; i < filled; i++)
        printf("%c", 219); // Block character
    
    for (int i = filled; i < bar_length; i++)
        printf("%c", 176); // Light block character
    
    printf("] %d%%\n\n", percentage);
}

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    char name1[MAX_NAME_LEN];
    char name2[MAX_NAME_LEN];
    char again[10];
    int percentage;
    
    printf("================================================== \n");
    printf("        LOVE PERCENTAGE CALCULATOR\n");
    printf("==================================================\n\n");
    
    while (1) {
        // Input first name
        printf("Enter first name: ");
        if (fgets(name1, sizeof(name1), stdin) == NULL) {
            printf("Error reading input!\n");
            continue;
        }
        
        // Remove newline from name1
        size_t len = strlen(name1);
        if (len > 0 && name1[len - 1] == '\n')
            name1[len - 1] = '\0';
        
        // Validate first name
        if (strlen(name1) == 0) {
            printf("Please enter a valid name!\n\n");
            continue;
        }
        
        // Input second name
        printf("Enter second name: ");
        if (fgets(name2, sizeof(name2), stdin) == NULL) {
            printf("Error reading input!\n");
            continue;
        }
        
        // Remove newline from name2
        len = strlen(name2);
        if (len > 0 && name2[len - 1] == '\n')
            name2[len - 1] = '\0';
        
        // Validate second name
        if (strlen(name2) == 0) {
            printf("Please enter a valid name!\n\n");
            continue;
        }
        
        printf("\nCalculating love percentage...\n");
        sleep(1);
        
        percentage = calculate_love_percentage(name1, name2);
        
        printf("\n%s + %s\n", name1, name2);
        print_progress(percentage);
        printf("%s\n\n", get_love_message(percentage));
        
        printf("Try again? (yes/no): ");
        if (fgets(again, sizeof(again), stdin) == NULL) {
            printf("Thanks for playing! Bye!\n\n");
            break;
        }
        
        // Convert to lowercase for comparison
        for (int i = 0; again[i]; i++)
            again[i] = tolower(again[i]);
        
        if (strncmp(again, "yes", 3) != 0 && strncmp(again, "y", 1) != 0) {
            printf("\nThanks for playing! Spread the love!\n\n");
            break;
        }
        
        printf("\n==================================================\n\n");
    }
    
    return 0;
}
