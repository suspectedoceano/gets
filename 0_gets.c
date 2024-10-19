#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define p(...)      printf(__VA_ARGS__)
#define BUFFER_SIZE 5
#define PASSWORD    "1337"

struct s_login
{
    char    password[BUFFER_SIZE];
   	char    password_correct;
};


int	main(void)
{
    struct s_login login = {.password_correct = 0, .password = {0}};

    do {

        p("Enter the password: ");
        gets(login.password);  // Warning: gets() is unsafe and deprecated, used here for demonstration

        if (!strcmp(login.password, PASSWORD)) login.password_correct = 1;

		p("%d\n", login.password_correct);

        login.password_correct ? p("✅ Access Granted ✅\n\n"
                                   "\t 🤫 The secret is 42 🤫\n\n")
                               : p("💥 Password Incorrect 💥\n\n");

    } while (!login.password_correct);

    return EXIT_SUCCESS;
}
