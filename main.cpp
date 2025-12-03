#include "FEHLCD.h"
#include "FEHUtility.h"
#include "FEHImages.h"
#include "FEHRandom.h"

void Create();
void Start(); //HHH
void Credits(); //HHH
void Stats(); //HHH
void Instructions(); //HHH
void Exit(); //HHH
void User_Info();
void Generate();
void Fall();
void Drag();
void Score();
void Check_End();
void Results();

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

void Start(){
    int x, y;

    LCD.SetBackgroundColor(BLACK);
    LCD.Clear();

    LCD.SetFontColor(RED);
    LCD.DrawRectangle(0, 0, 50, 25);
    LCD.FillRectangle(0, 0, 50, 25);
    while (1){
            while (!LCD.Touch(&x,&y)) {
		// Screen not being touched
	}

        Generate();
    }
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
            while (!LCD.Touch(&x,&y)) {
		// Screen not being touched
	}

        while(LCD.Touch(&x, &y)){
            if (x>=0 && x<=50 && y >=0 && y<=25){
                Create();
            }
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
                Create();
            }
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
                Create();
            }
        }
    }

}

void Exit(){
    abort();
}

void User_Info(){

}

void Generate(){
    int randomNumber = Random.RandInt();
    
    LCD.SetBackgroundColor(BLACK);
    LCD.Clear();

    if (randomNumber % 3 == 0){
        //Generate recycling
        LCD.SetFontColor(GREEN);
        LCD.DrawCircle(50,50,5);
        LCD.FillCircle(50,50,5);
    }
    else if (randomNumber % 3 == 1){
        //Generate trash
        LCD.SetFontColor(BLUE);
        LCD.DrawCircle(50,50,5);
        LCD.FillCircle(50,50,5);
    }
    else if (randomNumber % 3 == 2){
        //Generate Compost
        LCD.SetFontColor(RED);
        LCD.DrawCircle(50, 50, 5);
        LCD.FillCircle(50,50,5);
    }


}

void Fall(){

}

void Drag(){

}

void Score(){

}

void Check_End(){

}

void Results(){

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
