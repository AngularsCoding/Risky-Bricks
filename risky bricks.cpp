#include<iostream>
#include<graphics.h>
#include<conio.h>
#include<dos.h>
#include<time.h>
#include<stdio.h>
#include<math.h>

#define ScWidth 1400
#define ScHeight 700
#define OpWidth 400

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 77
#define KEY_RIGHT 75
#define SPACEBAR 32

using namespace std;

// Dispaly Gameover screen and reset score
void GameOver();

// Draw game board and score / control area
void DrawBoard();

// if enemy hit player this function returns 1 
int EnemyHitPlayer();

// if player hit fruit this function returns 1 
int PlayerHitFruit();
  
// Player Variables
int pSize = 40, step = 20;// player size, player speed
double px = ((ScWidth-OpWidth)/2), py = 350; // player X, player Y
 
// Enemy Variables
// Enemy X, Enemy Y, Enemy Speed
double enemy[3][3] = {0,200,10,0,320,10,0,440,10};
int ei = 1, ew=80, eh=40; // enemy index

// Fruit Variables
int fx = px, fy = ScHeight/2, fSize = 20;

// Other Variables
char option, txtScore[5];
int score = 0;

int main(){
	// to make sure generation of random numbers
	srand((unsigned) time(0));
	
	// Initialize Graphics
	int gd = DETECT, gm, err, tmp;
	initgraph( & gd, & gm, "C:\\tc\\bgi");
  	 
	while(1){ // for keeping game playing
		
		// Draws game board and score/controls area
		DrawBoard();
		
		// drawing player
		setcolor(WHITE);
		setfillstyle(1, WHITE);
		fillellipse(px, py, pSize, pSize);
		
		// drawing fruit
		setcolor(LIGHTBLUE);
		setfillstyle(1, LIGHTBLUE);
		fillellipse(fx, fy, fSize, fSize);
		
		// if any key is pressed
		if( kbhit()){
			option = getch(); // catch key in option variable 
			if(option == SPACEBAR){ // if spacebar is pressed toggle speed
	  		    
	  		    if(step <= 1 && step >= -1 ){ // if speed is slow
	  		    	step *= 20; // make it fast
	  		    }else{
	  		    	step /= 20; // make it slow
	  		    } 
			}
		}
		
 		// if player and fruit collide
 		if( PlayerHitFruit() == 1 ){
 			score++; // increase score
 			fy = 150 + rand()%400; // set fruit to a new random position
 		}
 		
		// If any of the enemies hit player
		if( EnemyHitPlayer() == 1 ){
			GameOver(); // display game over screen
			
			// Reset Enemy Positions
			enemy[0][0] = 0; 
			enemy[0][1] = 260;
			enemy[0][2] = 8+rand()%8;
			enemy[1][0] = 0; 
			enemy[1][1] = 320;
			enemy[1][2] = 8+rand()%8;
			enemy[2][0] = 0; 
			enemy[2][1] = 390;
			enemy[2][2] = 8+rand()%8;
		} 
		 
		
		for(int i=0; i<ei; i++){
			// Drawing enemey
			setcolor(YELLOW);
			setfillstyle(1,YELLOW);
			bar(enemy[i][0],enemy[i][1],enemy[i][0]+ew,enemy[i][1]+eh);
			
			// update enemy position
			enemy[i][0] += enemy[i][2];
			
			// if enemy goes beyond screen reset enemy position
			if( enemy[i][0] >= 1000 ){
				enemy[i][0] = 0; 
				enemy[i][2] = 8+rand()%8;
			}
			
			// if first enemy goes beyond 300px from left generate next enemy
			if( enemy[i][0] >= 300 && enemy[i][0] < 310 )
				if( ei < 3 )
					ei++;
		}

		// update player position
		py += step;
		// change direction if player goes outside bounds
		if( py > 600 || py < 100 ){
			step = -step;
		}
		
		delay(40);
		cleardevice();
	}
 
	
	getch();
	closegraph();
}


void GameOver(){
	cleardevice(); // clear screen
	
	setcolor(WHITE);
	// Print Game Over Text
	settextstyle(4,0,9);
	outtextxy(300,300,"Game Over");

	settextstyle(4,0,2);
	outtextxy(500,420,"Press any key to restart...");
	getch();
	score = 0; // reset score
} 

void DrawBoard(){	

	setcolor(WHITE);
	
	// draw board
	rectangle(0,0,ScWidth-OpWidth,ScHeight);
	rectangle(ScWidth-OpWidth,0,ScWidth,ScHeight);
	
	// draw title
	settextstyle(4,0,4);
	outtextxy(ScWidth-340, 50, "Risky Bricks");
	
	// print score
	// itoa function converts number to character array
	settextstyle(4,0,9);
	if( score<10 )
		outtextxy(ScWidth-270, 250, itoa(score,txtScore,10));
	else if( score>=10 )
		outtextxy(ScWidth-320, 250, itoa(score,txtScore,10));
	
	settextstyle(4,0,1);
	outtextxy(ScWidth-375, 500, "Controls: ");
	outtextxy(ScWidth-300, 550, "Use Spacebar to ");
	outtextxy(ScWidth-300, 580, "toggle speed");
}

// returns 1 if enemy hits player
int EnemyHitPlayer(){
	for(int i=0; i< ei; i++){
		// Check horizontal collision
		if( (px-pSize <= enemy[i][0]+ew && px-pSize >= enemy[i][0]) ||
		    (px+pSize >= enemy[i][0] && px+pSize <= enemy[i][0]+ew) ){
		    	
	    	// Check vertical collision
		    if( (py-pSize <= enemy[i][1]+eh && py-pSize >= enemy[i][1]) ||
				(py+pSize >= enemy[i][1] && py+pSize <= enemy[i][1]+eh)  ) 
			{
				return 1;
			}	
		}
	}
	return 0;
}

// return 1 if player collects fruit
int PlayerHitFruit(){
	// if collision occurs when ball is rising
	if( py-pSize <= fy+fSize && py-pSize >= fy-fSize ){
		return 1;
	}
	// if collision occurs when ball is falling
	if( py+pSize <= fy-fSize && py+pSize >= fy+fSize ){
		return 1;
	}
	return 0;
}
