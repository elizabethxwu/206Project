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
    puts("   <img src='../t.jpg'><h2>T-shirt</h2><p style='color:red; '>$15<p><p>its red, has cool slevees(1/4), says mcgill on it.</p><p><form action='purchase.py' method='post'><input type='text' name='Qty' width='40px' placeholder='Qty'><br>");
    puts("<INPUT TYPE='hidden' NAME='username' VALUE='");
    puts(user);
    puts("'>");
    puts("Confirm: <input id='confirm' type='checkbox' value='1' name='confirm'><br><INPUT TYPE='hidden' NAME='product' VALUE='1'><INPUT TYPE='hidden' NAME='price' VALUE='15'><input type='submit' id ='submit1' value='Submit' /></p></form></div>");
    


    puts("   <img src='../sweat.jpg'><h2>Sweater</h2><p style='color:red; '>$65<p><p>its red, has cool slevees(4/4), says mcgill on it, is warm. </p><p><form action='purchase.py' method='post'><input type='text' name='Qty' width='40px' placeholder='Qty'><br>");
    puts("<INPUT TYPE='hidden' NAME='username' VALUE='");
    puts(user);
    puts("'>");
    puts("Confirm: <input id='confirm' type='checkbox' value='1' name='confirm'><br><INPUT TYPE='hidden' NAME='product' VALUE='2'><INPUT TYPE='hidden' NAME='price' VALUE='65'><input type='submit' id ='submit1' value='Submit' /></p></form></div>");
    


    puts("   <img src='../mitten.jpg'><h2>T-shirt</h2><p style='color:red; '>$20<p><p>Look cool, finger # agnostic. Note: must have thumbs. </p><p><form action='purchase.py' method='post'><input type='text' name='Qty' width='40px' placeholder='Qty'><br>");
    puts("<INPUT TYPE='hidden' NAME='username' VALUE='");
    puts(user);
    puts("'>");
    puts("Confirm: <input id='confirm' type='checkbox' value='1' name='confirm'><br><INPUT TYPE='hidden' NAME='product' VALUE='3'><INPUT TYPE='hidden' NAME='price' VALUE='20'><input type='submit' id ='submit1' value='Submit' /></p></form></div>");

    puts(" <ul> <a href='../index.html'>Home </a> </ul>");
     
 //        <img src="sweat.jpg">

 //          <h2>Sweater</h2>
 //          <p style="color:red; ">$65<p>

 //          <p>its red, has cool slevees(4/4), says mcgill on it, is warm. </p>
 //          <p><form action="cgi-bin/purchase.py" method="post">
           
            
 //             <input type="text" name="Qty" width="40px" placeholder="Qty"><br>
 //             Confirm: <input id='confirm' type='checkbox' value='1' name='confirm'><br>
 //              <INPUT TYPE="hidden" NAME="username" VALUE="alec">
 //                <INPUT TYPE="hidden" NAME="product" VALUE="2">
 //             <INPUT TYPE="hidden" NAME="price" VALUE="65">
 //             <input type="submit" id ="submit1" value="Submit" />
 //             </form>
 //            </p>
          
 //       </div>
 //          <img src="mitten.jpg">
 //          <h2>Mittens</h2>
 //          <p style="color:red; ">$20<p>
 //          <p>Look cool, finger # agnostic. Note: must have thumbs. </p>
 //         <p><form action="cgi-bin/purchase.py" method="post">
           
            
 //             <input type="text" name="Qty" width="40px" placeholder="Qty"><br>
 //             Confirm: <input id='confirm' type='checkbox' value='1' name='confirm'><br>
 //              <INPUT TYPE="hidden" NAME="username" VALUE="alec">
 //                <INPUT TYPE="hidden" NAME="product" VALUE="3">
 //             <INPUT TYPE="hidden" NAME="price" VALUE="20">
 //             <input type="submit" id ="submit1" value="Submit" />
 //            </p>
 //          </form>
 //        </div>
 //      </div>

 // <h3>
 //    <ul> <a href="login.html">Login </a> </ul>
 //    <ul> <a href="signup.html">Signup </a> </ul>
 //    <ul> <a href="cat.html">Catalog </a> </ul>

 //  </h3>
   
 //  </body>",stdout);
 //    printf("Location: http://cs.mcgill.ca/~ewu5\n\n");      //Redirects to Catalogue page
// Need to find a way to insert hidden field
//<meta http-equiv="refresh" content="10; url=http://example.com/"> 
//<input type="hidden" name="redirect" value="http://www.example.com/form-submitted.html">    
}

//Display error HTML page
void displayError(){
    printf( "Content-type: text/html\n\n");     
    printf("<HTML><BODY>\n");
    printf("<P>ERROR</P>\n"); 
    printf("<P>Go back to <a href=\"../login.html\">Login</a></P>\n");
    printf("<P>Go back to <a href=\"../index.html\">Home</a></P>\n");
    printf( "</BODY></HTML>\n");
}
