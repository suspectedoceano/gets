#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stddef.h>  // For offsetof

#define RST     "\033[0m"
#define C       "\033[1;36m"
#define Y       "\033[1;33m"
#define p(...)      printf(__VA_ARGS__)
#define BUFFER_SIZE 5
#define PASSWORD    "1337"

struct s_login
{
    char    password[BUFFER_SIZE];
   	char	password_correct;
};
void	info_struct(struct s_login*);
void clean_buffer(char *str, int size);


void stack_view(struct s_login *login)
{

    p(C"\t STRUCT LAYOUT \n\n"RST);
    for (int i = 0; i < sizeof(*login); ++i) 
	{
        char *curr_ptr = (char*)login + i;
        char c = *curr_ptr;


		if (isprint(c)) 
        	p("["Y"%c"RST"]<-%p", c, curr_ptr);
        else 
        	p("["Y"%#0x"RST"]<-%p", c, curr_ptr);
        

        if (curr_ptr == &login->password_correct) p(" 🔐\n");
        else if (curr_ptr == login->password) p(" 📦\n");
        else p("\n");
    }
    p("\n\n");
}

int main(void)
{
    struct s_login login = {.password_correct = 0, .password = {0}};

	info_struct(&login);
    do {
        stack_view(&login);

        p("Enter the password: ");

       	fgets(login.password, BUFFER_SIZE, stdin);
		fpurge(stdin); //implement a cleaning routine by urself

        if (!strcmp(login.password, PASSWORD)) login.password_correct = 1;

        login.password_correct ? p("✅ Access Granted ✅\n\n"
                                   C"\t 🤫 The secret is 42 🤫\n\n"RST),
                                 stack_view(&login)
                               : p("💥 Nope 💥\n\n");

    } while (!login.password_correct);

    return EXIT_SUCCESS;
}

void	info_struct(struct s_login *login)
{
    p("🔒password_correct🔒->%p\n"
	  "    📦password📦    ->%p\n"
	  "      Distance      ->%ld\n"
	  "    Size struct     ->%zu\n\n",
        &login->password_correct, login->password, 
		offsetof(struct s_login, password_correct) - 
		offsetof(struct s_login, password),
		sizeof(struct s_login));
}

       	//fgets(login.password, BUFFER_SIZE, stdin);
		//fpurge(stdin);
