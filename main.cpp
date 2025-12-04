#include "FEHLCD.h"
#include "FEHUtility.h"
#include "FEHImages.h"
#include "FEHRandom.h"
#include "FEHKeyboard.h"

int i = 1;  //Index variable
int xInput, yInput;  //x and y coordinates of the user's input
int type, randomCoordinate;  //type of object and starting x-coordinate
int xpos, ypos;  //Position of the falling object
int score, incorrect;  //Keeps track of the player's score and number of incorrectly sorted items
int o = 0;  //Index to determine whether the game is over or not

char first, last;  //First and last initial

FEHImage Start_Screen, Background, Bins, GameOver;  //Background images
FEHImage bottle, trash, banana;  //Icon images

void Create();
void Start();
void Credits();
void Stats();
void Instructions();
void User_Info();
void Generate();
void Fall();
void Drag();
void Score();
void Check_End();
void Results();

//The Create() function is void ad creates the start screen background
void Create(){
    Start_Screen.Open("Create.png"); //Opens the Start Screen file
    Start_Screen.Draw(0,0);  //Draws the Start Screen
    return; //Returns to the main function
}

//The Start() Function creates the gameplay background and begins the game
void Start(){
    LCD.Clear();  //Clearing the screen
    Background.Open("Background.png");  //Opening background file
    Bins.Open("Bins.png"); //Opening bins file
    Background.Draw(0,0); //Drawing background to screen
    Bins.Draw(0,213); //Drawing bins to screen
    GameOver.Open("GameOver.png");  //Opening GameOver file
    bottle.Open("bottle.png");  //Opening bottle icon
    trash.Open("trash.png");  //Opening trash icon
    banana.Open("banana.png");  // Opening banana icon
    return;  //Return to int main()
}

//The Credits() Function displays the credits screen to the player
void Credits(){
    LCD.SetBackgroundColor(BLACK);
    LCD.Clear();

    LCD.SetFontColor(GREENYELLOW);
 
    LCD.SetFontScale(2);
    LCD.WriteAt("Credits", 110,20);
    
    LCD.SetFontScale(1);
    LCD.WriteAt("Coding", 10,35);
    LCD.SetFontScale(0.5);
    LCD.WriteAt("Adam Wiest &", 10,50);
    LCD.WriteAt("David Fagbolagun", 10,60);
 
    LCD.SetFontScale(1);
    LCD.WriteAt("References", 10,80);
    LCD.SetFontScale(0.5);
    LCD.WriteAt("Fruit Ninja", 10,95);

    LCD.SetFontColor(RED);
    LCD.DrawRectangle(0, 0, 50, 25);
    LCD.FillRectangle(0, 0, 50, 25);

    Sleep(1.0);

        while (!LCD.Touch(&xInput, &yInput)) {
		// Screen not being touched
	    }

        //Detects for input on the exit button
        while(LCD.Touch(&xInput, &yInput)){
            if (xInput >= 0 && xInput <= 50 && yInput >= 0 && yInput <= 25){
                return;
            }
        }
}

void Stats(){}
void Instructions(){}

//The User_Info() Function displays the gameplay background and prompts the player to enter their name
void User_Info(){
    //Draws the gameplay background
    Background.Open("Background.png");
    Background.Draw(0,0);

    return;
}

//The Generate() Function generates a random x-coordinate and type of item
void Generate(){
    //Randomixing type of object and x-coordinate of object
    type = Random.RandInt();
    randomCoordinate = Random.RandInt();
    xpos = randomCoordinate / 97;
    ypos = 0;

    if (type % 3 == 0){
        //Generate recycling
        type = 1;  //Type will be used in the Fall() Function
                    //Type 1 = recycling
    }
    else if (type % 3 == 1){
        //Generate trash
        type = 2;  //Type 2 = trash
    }
    else if (type % 3 == 2){
        //Generate compost
        type = 3;  //type 3 = compost
    }
    return;
}

//The Fall() Function Creates an animation of the object falling
void Fall(){
    Sleep(0.1);  //The function sleeps for one second to ensure there is no input form the player
    while(ypos <= 213){  //The object will only fall until it reaches y = 213
        while(!LCD.Touch(&xInput, &yInput)){  //If the screen is being touched, then the object will stop falling
            Background.Draw(0, 0);  //Redrawing background
            if(type == 1){  //Draws for recycle
                bottle.Draw(xpos, ypos);
            }
            else if(type == 2){  //Draws for trash
                trash.Draw(xpos, ypos);
            }
            else if(type == 3){  //Draws for compost
                banana.Draw(xpos, ypos);
            }
            Bins.Draw(0, 213);  //Redraws bins
            ypos += 1;  //Increasing y position by 1 for next loop
            Sleep(0.01);  //Sleeps for 0.01 seconds between frames
            if(ypos > 213){  //If the object goes below y = 213, it will return to main
                return;
            }
        }
        while(LCD.Touch(&xInput, &yInput)){
            return;
        }
    }
}

//The Drag() Function allows the object to be dragged by the user and updates it's position globally
void Drag(){
    while(ypos <= 213){
        while(LCD.Touch(&xpos, &ypos)){
            Background.Draw(0, 0);  //Redrawing background
            if(type == 1){  //Draws for recycle
                bottle.Draw(xpos, ypos);
            }
            else if(type == 2){  //Draws for trash
                trash.Draw(xpos, ypos);
            }
            else if(type == 3){  //Draws for compost
                banana.Draw(xpos, ypos);
            }
            Bins.Draw(0, 213);  //Redraws Bins
        }

        if(ypos <= 213){  //If the player lets go, the object will start to fall again
            Fall();
        }

        else if(ypos > 213){  //If the object is in the bin it returns to main
            return;
        }
    }
}

//The Score() Function keeps track of the player's score
void Score(){
    if(xpos >= 0 && xpos <= 100 && ypos >= 213){
        if(type == 1){  //Adds one for correctly sorting recycling
            score += 1;
        }
        else{  //Adds one to the incorrect counter for incorrectly sorting into recycling
            incorrect +=1;
        }
    }

    else if(xpos >= 106 && xpos <= 212 && ypos >= 213){  //Adds one for correctly sorting compost
        if(type == 3){
            score += 1;
        }
        else{  //Adds one to incorrect counter for incorrectly sorting into compost
            incorrect +=1;
        }
    }

    else if(xpos >= 219 && xpos <= 340 && ypos >= 213){
        if(type == 2){  //Adds one for correctly sorting trash
            score += 1;
        }
        else{  //Adds one to incorrect counter for incorrectly sorting into trash
            incorrect +=1;
        }
    }
    else{  //Adds one to incorrect counter for not making it into any bin
        incorrect += 1;
    }

    return;
}

//The Check_End() Function checks whether the game is over or not
void Check_End(){
    if(incorrect == 5){ //If the player has sorted 5 items incorrectly, o = 1 and the while loop in int main() will end
        o = 1;
        return;
    }
    else if(incorrect < 5){  //If the player has sorted less than 5 items incorrectly, the game will continue
        o = 0;
        return;
    }
}

//The Results() Function draws a game over screen and displays the player's final score
void Results(){
    GameOver.Draw(0,0);  //Draws game over screen
    LCD.WriteAt("Your Score:", 90, 70);  //Displays the text for "Your Score"
    LCD.WriteAt(score, 130, 100);  //Displays the player's score
    LCD.SetFontScale(0.5);  //Shrinks Font Size
    LCD.Update();
    Sleep(10);
    return;
}

int main(){
    //Detects where user input it, and which button it is
    while(1){
        while (i == 1){
            
            Create();  //Creates the start page
            while(!LCD.Touch(&xInput, &yInput)){
                //No touch detected
            }
            while(LCD.Touch(&xInput,&yInput)){
                    // TODO: Screen is not being touched
                    
                    //Play Now:        TL: (112,187)      BR: (200,204)
                    //Credits:         TL: (59,214)       BR: (102,227)
                    //Stats:           TL: (110,214)      BR: (151, 227)
                    //Instructions:    TL: (159,214)      BR: (202,227)
                    //Exit:            TL: (209,214)      BR: (252,227)
                    if (xInput <= 102 && xInput >= 59 && yInput <= 227 && yInput >=214){
                        Credits();  //Takes player to credits page
                    }
                    else if (xInput <= 151 && xInput >= 110 && yInput <= 227 && yInput >=214){
                        Stats();  //Takes player to stats page
                    }
                    else if (xInput <= 202 && xInput >= 159 && yInput <= 227 && yInput >=214){
                        Instructions();  //Takes player to instructions page
                    }
                    else if (xInput <= 252 && xInput >= 209 && yInput <= 227 && yInput >=214){
                        abort(); //Exits the program
                    }
                    else if(xInput <= 200 && xInput >= 112 && yInput <= 204 && yInput >=187){
                        i = 0; //Breaks out of the menu loop and ensures that it will not repeat
                        break;
                    }
            }
        }

        User_Info();
        Start();

        while(o == 0){
            Generate();
            Fall();

            i = 1;

            while(i == 1){
                if(ypos >= 213){
                    Score();
                    i = 0;
                }
                else if(ypos < 213){
                    Drag();
                }
            }

            Check_End();
        }

        Results();
        i = 0;
    }
}
