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
int highScore = 0;  //Stores high score for session

char first, last;  //First and last initial

FEHImage Start_Screen, Background, Bins, GameOver;  //Background images
FEHImage Stat, Credit, Instruction;  //Other screen images
FEHImage bottle, trash, banana;  //Icon images

void Create();
void Start();
void Credits();
void Stats();
void Instructions();
void Generate();
void Fall();
void Touch();
void Score();
void Check_End();
void Results();

//The Create() function is void and creates the start screen background
void Create(){
    Start_Screen.Open("Create.png"); //Opens the Start Screen file
    Start_Screen.Draw(0,0);  //Draws the Start Screen
    Stat.Open("Stats.png");  //Opens the stats screen file
    Credit.Open("Credits.png");
    Instruction.Open("Instructions.png");

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

    o = 0;  //Resets o index, allowing the game to replay
    incorrect = 0;  //Resets number of incorrect
    score = 0;  //Resets score
    return;  //Return to int main()
}

//The Credits() Function displays the credits screen to the player
void Credits(){
    LCD.Clear();  //Clears the screen

    Credit.Draw(0, 0);  //Draws the credits screen

    Sleep(1.0);  //Sleeps before allowing any input

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

//The Stats() Function displays the stats screen to the player
void Stats(){
    LCD.Clear();  //Clears the screen
    Stat.Draw(0,0);  //Draws the stats background

    LCD.SetFontScale(1.0);  //Sets font size for high score
    LCD.WriteAt(highScore, 150, 150);  //Writes high score to screen

        Sleep(1.0);  //Sleeps before allowing any input

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

//The Instructions() Function displays the instructions screen to the player
void Instructions(){
      int x, y;

    LCD.Clear();
    Instruction.Open("Instructions.png");
    Instruction.Draw(0,0);

    //LCD.SetFontColor(WHITE);
    //LCD.DrawRectangle(0, 0, 50, 25);
    //LCD.FillRectangle(0, 0, 50, 25);

    //Info
    LCD.SetFontColor(GREEN);
    LCD.SetFontScale(2);
    LCD.WriteAt("Instructions",20,30);
    //As the materials falls from the shoot, sort them into trash, recycling, and compost
    LCD.SetFontColor(WHITE);
    LCD.SetFontScale(1);
    LCD.WriteAt("As the objects falls from", 5,80);
    LCD.WriteAt("the shoot, sort them into", 5,110);
    LCD.WriteAt("trash, recycling, and", 5,140);
    LCD.WriteAt("compost. After 5 incorrect", 5,170);
    LCD.WriteAt("sorts, you loose.", 5,200);


        Sleep(1.0);  //Sleeps before allowing any input

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

//The Generate() Function generates a random x-coordinate and type of item
void Generate(){
    //Randomixing type of object and x-coordinate of object
    type = Random.RandInt();
    randomCoordinate = Random.RandInt();
    xpos = randomCoordinate / 100;
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
    int i=(score/10)+1;
    Sleep(0.05);  //The function sleeps for one second to ensure there is no input form the player
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
            ypos += i;  //Increasing y position by 1 for next loop and will increase depending on the score
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

//The Touch() Function allows the object to be moved by the user and updates it's position globally
void Touch(){
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
    if(score > highScore){  //Determines whether the score is a high score
        highScore = score;  //Stores new high score
    }
    
    GameOver.Draw(0,0);  //Draws game over screen
    LCD.SetFontScale(1.0);  //Sets larger font fot "Your Score"
    LCD.SetFontColor(WHITE);  //Sets font color to white
    LCD.WriteAt("Your Score:", 90, 70);  //Displays the text for "Your Score"
    LCD.WriteAt(score, 130, 100);  //Displays the player's score
    LCD.SetFontScale(0.5);  //Shrinks Font Size
    LCD.Update();
    return;
}

//The main() Function is a structure for the gameplay
int main(){
    //Detects where user input it, and which button it is
    while(1){
        i = 1;  //Allowing the next loop too start every time

        while (i == 1){
            
            Create();  //Creates the start page
            while(!LCD.Touch(&xInput, &yInput)){
                //No touch detected
            }
            
            /*This loop handles all the menu navigation and is crutial in game navigation*/
            while(LCD.Touch(&xInput,&yInput)){
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
        
        Start();  //If the user starts the game, the Start() Function is called

        while(o == 0){  //If game is not over, it will continue to generate items
            Generate();  //Generates an item
            Fall();  //Makes item fall
        
            while(1){  //Determines whether item is in bin
                if(ypos >= 213){  //If item is in bin, the Score() Function is calles
                    Score();  //Adjusts score
                    break;  //Breaks out of while loop to call Check_End()
                }
                else if(ypos < 213){  //If item is not in bin, the item continues to fall or be moved
                    Touch();  //Allows player to manipulate item
                }
            }

            Check_End();  //Checks whether the game is over
        }
        
        Results();  //If game is over, Results() is called and the game ends
        Sleep(5.0);  //Displays the results screen for 5 seconds before going to the Create() Function to allow player to play again
    }
}
