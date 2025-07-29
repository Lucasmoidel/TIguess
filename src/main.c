#include <tice.h>
#include <graphx.h>
#include <keypadc.h>
#include <debug.h>
#include <string.h>
#include <time.h>

void main(void) {


    // Seed the random number generator using the current time.
    // This ensures a different sequence of numbers each time the program runs.
    srand(time(NULL));

    int randomint = (rand() % (100 - 1 + 1)) + 1;
    char randomstr[4];

    sprintf(randomstr, "%d", randomint);
    char guess[4];

    os_ClrHome();
    //os_PutStrLine(randomstr);
    //os_NewLine();
    while (atoi(guess) != randomint){
        os_GetStringInput("guess a random number between 1 and 100: ", guess, 4);os_NewLine();
        if (atoi(guess) <= randomint){
            os_PutStrLine(guess);os_PutStrLine(" was too low ");os_NewLine();
        } else if (atoi(guess) >= randomint){
            os_PutStrLine(guess);os_PutStrLine(" was too high ");os_NewLine();
        }
        
        
    }
    os_ClrHome();
    os_PutStrLine("you did it");
    os_NewLine();
    os_PutStrLine(guess);os_PutStrLine(" was correct");
    while (!os_GetCSC());
}
