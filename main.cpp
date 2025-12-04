#include "FEHLCD.h"
#include "FEHUtility.h"
#include "FEHImages.h"
#include "FEHRandom.h"
#include "FEHKeyboard.h"

void Create();
void Background();
void Start(); //HHH
void Credits(); //HHH
void Stats(); //HHH
void Instructions(); //HHH
void Exit(); //HHH
void User_Info();
void Generate();
void Fall(int x, int y, FEHImage icon, char* File, int xRange, int yRange);
void Drag(FEHImage Icon, char *File, int xRange, int yRange);
void Score(int x, int y);
void Check_End();
void Results();

int score = 0, type, incorrect;
int randomCoordinate;
int randomType;
/*
    SDP Training Minigame #2
  
    There is a circle that jumps but stays in the air.
    Make the circle fall back down.
*/

void Create (){
    LCD.SetBackgroundColor(BLACK);
    LCD.Clear();
    
    int x = 0, y = 0;

    //Create Start Page Art
    FEHImage Start_Screen;
    Start_Screen.Open("Create.png");
    Start_Screen.Draw(0, 0);
    
    //Scan for input
    while (1){
        while (!LCD.Touch(&x,&y)) {
            // Screen not being touched
        }

        while (LCD.Touch(&x,&y)) {
            // TODO: Screen is not being touched
            
            //Play Now:        TL: (112,187)      BR: (200,204)
            //Credits:         TL: (59,214)       BR: (102,227)
            //Stats:           TL: (110,214)      BR: (151, 227)
            //Instructions:    TL: (159,214)      BR: (202,227)
            //Exit:            TL: (209,214)      BR: (252,227)
            if (x <= 200 && x >= 112 && y <= 204 && y >=187){
                Start();
            }
            else if (x <= 102 && x >= 59 && y <= 227 && y >=214){
                Credits();
            }
            else if (x <= 151 && x >= 110 && y <= 227 && y >=214){
                Stats();
            }
            else if (x <= 202 && x >= 159 && y <= 227 && y >=214){
                Instructions();
            }
            else if (x <= 252 && x >= 209 && y <= 227 && y >=214){
                Exit();
            }
            else{
                //If there is an input, but it's not on an icon nothing will happen
            }
	    }
    }
}

void Background(){
    LCD.Clear();
    FEHImage Background, Bins;
    Background.Open("Background.png");
    Bins.Open("Bins.png");
    Background.Draw(0,0);
    Bins.Draw(0,213);
}

void Start(){
    //Needs updated with background
    Background();
    Generate();
}    

void Credits(){
      int x, y;

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
    while (1){
            while(!LCD.Touch(&x,&y)) {
		// Screen not being touched
	}

        while(LCD.Touch(&x, &y)){
            if (x>=0 && x<=50 && y >=0 && y<=25){
                break;
            }
        }
        if (x>=0 && x<=50 && y >=0 && y<=25){
                Create();
            }
    }

}

void Stats(){
      int x, y;

    LCD.SetBackgroundColor(BLACK);
    LCD.Clear();

    LCD.SetFontColor(RED);
    LCD.DrawRectangle(0, 0, 50, 25);
    LCD.FillRectangle(0, 0, 50, 25);

    //Stats
    LCD.WriteAt("High Scores:", 170, 10);

    while (1){
            while (!LCD.Touch(&x,&y)) {
		// Screen not being touched
	}

        while(LCD.Touch(&x, &y)){
            if (x>=0 && x<=50 && y >=0 && y<=25){
                break;
            }
        }
        if (x>=0 && x<=50 && y >=0 && y<=25){
                Create();
            }
    }
}

void Instructions(){
      int x, y;

    LCD.SetBackgroundColor(BLACK);
    LCD.Clear();

    LCD.SetFontColor(RED);
    LCD.DrawRectangle(0, 0, 50, 25);
    LCD.FillRectangle(0, 0, 50, 25);

    //Info
    LCD.SetFontColor(GREENYELLOW);
    LCD.SetFontScale(2);
    LCD.WriteAt("Instructions",20,20);
    //As the materials falls from the shoot, sort them into trash, recycling, and compost
    LCD.SetFontScale(1);
    LCD.WriteAt("As the objects falls from", 10,50);
    LCD.WriteAt("the shoot, sort them", 10,80);
    LCD.WriteAt("into trash, recycling,", 10,110);
    LCD.WriteAt("and compost.", 10,140);


    while (1){
            while (!LCD.Touch(&x,&y)) {
		// Screen not being touched
	}

        while(LCD.Touch(&x, &y)){
            if (x>=0 && x<=50 && y >=0 && y<=25){
                break;
            }
        }
        if (x>=0 && x<=50 && y >=0 && y<=25){
                Create();
            }
    }

}

void Exit(){
    abort();
}

void User_Info(){

}

void Generate(){
    Background();
    //Randomizing type of object and x-coordinate of object
    char File_name[20];
    randomCoordinate = Random.RandInt() / 97;
    randomType = Random.RandInt();

    FEHImage bottle, trash, banana;
    bottle.Open("Bottle.png");
    trash.Open("Trash.png");
    banana.Open("Banana.png");
    

    if (randomType % 3 == 0){
        //Generate recycling
        bottle.Draw(randomCoordinate, 0);
        strcpy(File_name, "Bottle.png");
        Fall(randomCoordinate, 0, bottle, File_name, 10, 30);
        type = 1;
    }
        else if (randomType % 3 == 2){
        //Generate Compost
        banana.Draw(randomCoordinate, 0);
        strcpy(File_name, "Banana.png");
        Fall(randomCoordinate, 0, banana, File_name, 16, 16);
        type = 2;
    }
    else if (randomType % 3 == 1){
        //Generate trash
        trash.Draw(randomCoordinate, 0);
        strcpy(File_name, "Trash.png");
        Fall(randomCoordinate, 0, trash, File_name, 19, 23);
        type = 3;
    }
}

void Fall(int x, int y, FEHImage Icon, char *File, int xRange, int yRange){
    int xInput, yInput;
    Icon.Open(File);

    FEHImage Bins;
    Bins.Open("Bins.png");

    float time;

    while(y < 213){
        time = TimeNow();

        while(TimeNow() - time < 0.1){
            if (LCD.Touch(&xInput, &yInput)){
                if ((xInput >= x && xInput <= x + xRange) && (yInput >= y && yInput <= y + yRange)){
                    break;
                }
            }
            else{}
        }
        if ((xInput >= x && xInput <= x + xRange) && (yInput >= y && yInput <= y + yRange)){
            Drag(Icon, File, xRange, yRange);
        }
        Background();
        y+=1;
        Icon.Draw(x, y);
        Bins.Draw(0,213);
    }
    if(y>213){
        Score(x,y);
    }

    
}

void Drag(FEHImage Icon, char *File, int xRange, int yRange){
    int x, y;
    FEHImage Bins;
    Bins.Open("Bins.png");
    Icon.Open(File);

    while(y < 213){
        while(LCD.Touch(&x, &y)){
            Background();
            Icon.Draw(x,y);
            Bins.Draw(0,213);
        }
        if(!LCD.Touch(&x, &y)){
            break;
        }
    }
    if(y>213){
        Score(x,y);
    }
    if(!LCD.Touch(&x, &y) && y > 213){
            Fall(x, y, Icon, File, xRange, yRange);
        }
}

void Score(int x, int y){
    if(x >= 0 && x <= 100 && y >= 213){
        if(type == 1){
            score += 1;
            Check_End();
        }
        else{
            incorrect +=1;
            Check_End();
        }
    }

    else if(x >= 106 && x <= 212 && y >= 213){
        if(type == 2){
            score += 1;
            Check_End();
        }
        else{
            incorrect +=1;
            Check_End();
        }
    }

    else if(x >= 219 && x <= 340 && y >= 213){
        if(type == 3){
            score += 1;
            Check_End();
        }
        else{
            incorrect +=1;
            Check_End();
        }
    }
    else{
        incorrect += 1;
        Check_End();
    }
}

void Check_End(){
    if(incorrect == 5){
        Results();
    }
    else if(incorrect <5){
        Generate();
    }
}

void Results(){
    Background();
    LCD.WriteAt(score, 50,50);
}

int main() {
    // Clear background
    LCD.SetBackgroundColor(BLACK);
    LCD.Clear();

    Create();

    while (1) {
        LCD.Update();
        // Never end
    }
    return 0;
}
