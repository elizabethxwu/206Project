#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 1024
#define EXTRA 8
/* 8 for field name "username", 1 for "=" */
#define MAXINPUT MAXLEN+EXTRA+2
/* 1 for added line break, 1 for trailing NUL */

void unencode(char *src, char *last, char *dest);
void decode(char *input);
void login(char *user);
void display();

int main(void) 
{
//    setenv("QUERY_STRING", "username=eliwu18&password=pass", 100);
    
    char *user_input;
    char *pass_input;
    char *username;
    char *password;
    char inputArray[MAXLEN];
    char outputArray[MAXLEN];
    char line[MAXLEN];

    int n = atoi(getenv("CONTENT_LENGTH"));
    fgets(inputArray, n+1, stdin);
    unencode(inputArray, inputArray+n, outputArray);

    char *tmp = malloc(sizeof(char)*1024);
    tmp = strdup(outputArray);                        //copy fgets line

    char *tok = strtok(tmp, "=");              //split temp string into tokens
    user_input = strtok(NULL, "&");               //Set "username" to point to second token
    pass_input = strtok(NULL, "\n");              //Set "password" to point to third token

    free(tmp);

    printf("%s\n", user_input);
    printf("%s\n", pass_input);

    FILE* members = fopen("Members.csv", "r");   //make sure first arg is Members.csv

    while (fgets(line, MAXLEN, members))
    {
        char *temp = malloc(sizeof(char)*1024);
        temp = strdup(line);                        //copy fgets line

        char *token = strtok(temp, ",");              //split temp string into tokens
        username = strtok(NULL, ",");               //Set "username" to point to second token
        password = strtok(NULL, "\n");              //Set "password" to point to third token

        if(strcmp(user_input, username) != 0)
            continue;

        if(strcmp(pass_input, password) != 0)
            continue;

        else{                                       //Username and password are valid
            login(username);                        //Login the user
            display();
            break;                                  
        }
        
        free(temp);
    }

    if(feof(members)){                              //Username & Password not found (i.e. not valid)
        printf( "Content-type: text/html\n\n");     //Display error HTML page
        printf("<HTML><BODY>\n");
        printf("<P>Hey! This is my first CGI response!</P>\n"); 
        printf( "</BODY></HTML>\n");
    }

    fclose(members);
    return 0;
}

void unencode(char *src, char *last, char *dest){
    for(; src != last; src++, dest++)
        if(*src == '+')
            *dest = ' ';
        else if(*src == '%') {
            int code;
            if(sscanf(src+1, "%2x", &code) != 1) code = '?';
                *dest = code;
                src +=2; 
        }     
        else
            *dest = *src;
    *dest = '\n';
    *++dest = '\0';
}

void parse(char input[]){

}

void login(char *user){
    FILE* ptr = fopen("loggedin.csv", "r+");        
    fprintf(ptr, "%s\n", user);                     // append user name to loggedin.csv
    fclose(ptr);

    // Display catalogue page, insert hidden field
}

void display(){
    printf( "Content-type: text/html\n\n");     //Display error HTML page
    printf("<HTML><BODY>\n");
    printf("<P>Hey! This is my first CGI response!</P>\n"); 
    printf( "</BODY></HTML>\n");
}
