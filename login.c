#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 1024

void unencode(char *src, char *last, char *dest);
void login(char *user);
void display();

int main(void) 
{
//    setenv("QUERY_STRING", "username=eliwu18&password=password", 100);
    
    char *user_input;
    char *pass_input;
    char *username;
    char *password;
    char inputArray[MAXLEN];
    char outputArray[MAXLEN];
    char line[MAXLEN];

    int n = atoi(getenv("CONTENT_LENGTH"));             //Get length of form input
//    int n = 34; for testing
    fgets(inputArray, n+1, stdin);                      //Form input is sent as stdin
    unencode(inputArray, inputArray+n, outputArray);    //Unencode URL

    char *tmp = malloc(sizeof(char)*1024);
    tmp = strdup(outputArray);                        //copy unencoded output array

    char *tok = strtok(tmp, "=");                 //split tmp string into first token
    user_input = strtok(NULL, "&");               //Set "user_input" to point to second token
    char *tok2 = strtok(NULL, "=");   
    pass_input = strtok(NULL, "\n");              //Set "pass_input" to point to third token

    free(tmp);

    FILE* members = fopen("Members.csv", "r");    //make sure first arg is Members.csv

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
        printf("<P>ERROR</P>\n"); 
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

void login(char *user){
    FILE* ptr = fopen("loggedin.csv", "a+");        //a+ means stream is positioned at EOF for writing     
    fprintf(ptr, "%s\n", user);                     // append user name to loggedin.csv
    fclose(ptr);
}

void display(){
    printf( "Content-type: text/html\n\n");        //Display catalogue page, insert hidden field
    printf("<HTML><BODY>\n");
    printf("<P>Hey! This is my first CGI response!</P>\n"); 
    printf( "</BODY></HTML>\n");
}
