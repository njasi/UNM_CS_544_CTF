#include <stdio.h>
#include <string.h>

int main() {
    char password[] = "jkl87da32vdsaklfda6";
    char input[30];

    printf("Please enter the password:\n");
    scanf("%s", input);

    if (strcmp(password, input) == 0) {
        printf("Login successful\n");
    } else {
        printf("Wrong password\n");
    }

    return 0;
}