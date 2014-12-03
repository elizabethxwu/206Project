#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 256

void unencode(char *src, char *last, char *dest);
void login(char *user);
void displayCatalogue();
void displayError();

int main(void) 
{    
    char *user_input;
    char *pass_input;
    char *username;
    char *password;
    char inputArray[MAXLEN];
    char outputArray[MAXLEN];
    char line[MAXLEN];

// Assuming CGI is envoked with Method POST, not GET
    int n = atoi(getenv("CONTENT_LENGTH"));             //Get length of input
    fgets(inputArray, n+1, stdin);                      //Form input is sent as stdin

/* Input is sent in with format:
   username="username'&password="password"   
   We need to parse this encoded URL      */

    unencode(inputArray, inputArray+n, outputArray);    //Unencode URL

    //Parse the unencoded output array
    //Create temp pointer to copy line
    char *tmp = malloc(sizeof(char)*1024);
    tmp = strdup(outputArray);                    //Copy unencoded output array
    char *tok = strtok(tmp, "=");                 //Split tmp string into first token
    user_input = strtok(NULL, "&");               //Set "user_input" to point to second token
    char *tok2 = strtok(NULL, "=");               
    pass_input = strtok(NULL, "\n");              //Set "pass_input" to point to third token

    FILE* members = fopen("Members.csv", "rt");    //Open Members.csv file

   while (fgets(line, MAXLEN, members))
    {
        //Create temp pointer to copy line
        char *temp = malloc(sizeof(char)*MAXLEN);
        temp = strdup(line);                        
        
        char *token = strtok(temp, ","); 
                   //split temp string into tokens
        username = strtok(NULL, ","); 
                                                      //Set "username" to point to second token
        password = strtok(NULL, "\n");              //Set "password" to point to third token

        //Username and password are valid
        if(strcmp(user_input, username)==0){
            if(strcmp(pass_input, password)==0) {
                login(username);                        
                displayCatalogue(username);                     
                break;        
            }
        }        
        free(temp);        
    }

    //EOF reached and Username & Password not found (i.e. not valid)
    if(feof(members)){                              
        displayError();                             
    }

    fclose(members);
    return 0;
}

//Decodes the Form Inputs from POST
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

//Append username to loggedin.csv
void login(char *user){
    FILE* ptr = fopen("loggedin.csv", "a+");        //a+ means stream is positioned at EOF for writing     
    fprintf(ptr, "%s\n", user);                     // append user name to loggedin.csv
    fclose(ptr);
}

void displayCatalogue(char *user){
    printf( "Content-type: text/html\n\n");
    puts("<head><meta name='description' content='Buy our stuff'><title>Catalogue</title></head>");
    puts("<body style='margin:10px 100px;padding:0;font-family:Arial'>");
    puts("<table style='width:30%%;height:50px;text-align:center;'' align='center'><tr><td><a href='index.html'>Home</a></td><td><a style='color:#FF0000' href='cat.html'>Catalogue</a></td><td><a href='login.html'>Login</a></td><td><a href='signup.html'>Register</a></td></tr></table>");
    puts("<center><table>")
    puts("<tr style='text-align:center'><td><h2>T-shirt</h2></td><td><h2>Sweater</h2></td><td><h2>Mittens</h2></td></tr>");
    puts("<tr style='text-align:center'><td><img src='t.jpg' width='200'></td><td><img src='sweat.jpg' width='200'></td><td><img src='mitten.jpg' width='200'></td></tr>");
    puts("<tr style='text-align: left'><td><p style='color:red; text-align: center'>$15</p><p>Its red, has cool slevees (1/4), says Mcgill on it.</p></td>");
    puts("<td><p style='color:red; text-align: center'>$65<p><p>Its red, has cool sleeves (4/4), says Mcgill on it, is warm.</p></td><td><p style='color:red; text-align: center'>$20<p><p>Look cool. Note: Must have thumbs. </p></td></tr>");
    puts("<tr style='text-align:center'><td><form action='cgi-bin/purchase.py' method='post'><input type='text' name='Qty' width='10px' placeholder='Qty' style='border:2px solid #ddd;border-radius:5px;font-size:100%%;width:20%%;height:30px;margin-bottom:10px'>");
    puts("<INPUT TYPE='hidden' NAME='username' VALUE='");
    puts(user);
    puts("'>");
    puts("Confirm: <input id='confirm' type='checkbox' value='1' name='confirm'><INPUT TYPE='hidden' NAME='product' VALUE='1'><INPUT TYPE='hidden' NAME='price' VALUE='15'><br><button type='submit' id='submit1' value='Sumbit'>Submit</button></form></td>");                
    puts("<td><p><form action='cgi-bin/purchase.py' method='post'><input type='text' name='Qty' width='10px' placeholder='Qty' style='border: 2px solid #ddd; border-radius: 5px; font-size: 100%%; width: 20%%; height: 30px; margin-bottom:10px'>Confirm: <input id='confirm' type='checkbox' value='1' name='confirm'>");    
    puts("<INPUT TYPE='hidden' NAME='username' VALUE='");
    puts(user);
    puts("'>");
    puts("<INPUT TYPE='hidden' NAME='product' VALUE='2'><INPUT TYPE='hidden' NAME='price' VALUE='65'><br><button type='submit' id='submit1' value='Sumbit'>Submit</button></form></p></td>");            
    puts("<td><p><form action='cgi-bin/purchase.py' method='post'><input type='text' name='Qty' width='10px' placeholder='Qty' style='border: 2px solid #ddd; border-radius: 5px; font-size: 100%%; width: 20%%; height: 30px; margin-bottom:10px'>Confirm: <input id='confirm' type='checkbox' value='1' name='confirm'>");  
    puts("<INPUT TYPE='hidden' NAME='username' VALUE='");
    puts(user);
    puts("'>");                    
    puts("<INPUT TYPE='hidden' NAME='product' VALUE='3'><INPUT TYPE='hidden' NAME='price' VALUE='20'><br><button type='submit' id='submit1' value='Sumbit'>Submit</button></form></p></td>");
    puts("</tr></table></center></body>");
}

//Display error HTML page
void displayError(){
    FILE* cat = fopen("error.html","r");
    int ch;
    printf("%s%c%c\n", "Content-Type:text/html;charset=iso-8859-1",13,10);
    while((ch=getc(f)) != EOF){
        putchar(ch);
    }
        
    fclose(f); 
}
