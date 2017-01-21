#include <graphics.h>
#include <dos.h>
#include<stdio.h>



void crossCircle(int x, int y, bool turn)
{
	//if torn is 0 draw cross
	if (turn == 0)
	{
		setcolor(LIGHTGREEN);
		setlinestyle(4, 0, 15);
		line(x - 120, y - 120, x - 30, y - 30);
		line(x - 120, y - 30, x - 30, y - 120);
		setlinestyle(0, 0, 0);
	}
	//if turn is 1 draw circle
	else
	{
		//for loop to draw series of to increase thickness 
		for (int i = 50; i>30; i--)
		{
			setlinestyle(0, 0, 3);
			setcolor(YELLOW);
			circle(x - 75, y - 75, i);

		}
	}
}

void line_points(int x, int y, bool turn, int temp[])
{
	//place is used to store 1 or 0 in array parrallal to our boxes every box is correspond to place e.g first box has place value 1 2nd has 2
	int place = 0;
	//these for loops are used to check where the mouse is clicked
	//our boxes have size of 150*150 so loop start with 150 and 150 added after every turn
	//first loop move in columns and second moves in rows
	for (int i = 150; i <= 450; i += 150)
	{
		for (int j = 150; j <= 450; j += 150)
		{
			//if clicked value is less than the right lower edge the the mouse is clicked in this box
			if (x <= j && y <= i)
			{
				//checking if there already some values
				if (temp[place] == 1 || temp[place] == 0)
				{
					//if value is aleady present in coresponding array it will again get the mouse click
					while (!ismouseclick(WM_LBUTTONDOWN))

					{
						delay(500);
					}
					getmouseclick(WM_LBUTTONDOWN, x, y);
					//resetting the the loop for new clicked positions
					place = 0;
					i = 150;
					j = 150;
				}
				else{
					//if no value is present in corresponding array then it call the cross circle to draw cross circles
					//and pass the value of turn to check whose playing now and clicked values
					crossCircle(j, i, turn);
					//storing the value of turn in corresponding array then breaking the loop
					temp[place] = turn;
					i = 460;
					break;
				}
			}
			//increment in place value after checking each box 
			place++;
		}
	}
}

int main()
{
	//calcultate player one and two winnings
	int player1wins = 0;
	int player2wins = 0;
	//record the string i.e. player one winning = ?. In graphics.h we should have to print the whole string
	char record1[30] = { '0' };
	char record2[30] = { '0' };
	//two variables in which we will store the value of clicked position of mouse
	int a, b;
	//boolian variable whose value changes after first turn so that next player can play
	bool turn = 0;
	//making game of best of three
	for (int best3 = 0; best3<3; best3++)
	{
		//parallal array to store 1 or 0 for first and second user so that winning and repition can be checked
		int temp[9] = { 2, 2, 2, 2, 2, 2, 2, 2, 2 };
		//initializing windows
		initwindow(800, 450);
		//filling the window with light blue
		setfillstyle(SOLID_FILL, LIGHTBLUE);
		floodfill(100, 100, WHITE);
		//making four lines for matrix
		setlinestyle(1, 1, 10);
		line(145, 20, 145, 444);
		line(295, 20, 295, 444);
		line(20, 145, 444, 145);
		line(20, 295, 444, 295);
		//setting text background color light blue
		setbkcolor(LIGHTBLUE);

		//storing the string in record 1 and 2 with player winning after that whole string will printed
		sprintf(record1, "player one winings = %d", player1wins);
		sprintf(record2, "player two winings = %d", player2wins);
		// changing text color to white
		setcolor(15);
		//setting text style
		settextstyle(8, HORIZ_DIR, 3);
		//printing the string stored in record 1 and 2
		outtextxy(460, 5, record1);
		outtextxy(460, 30, record2);
		//making a loop of 9 for a single game
		for (int n = 0; n<9; n++)
		{
			//making a loop to wait for mouse click
			while (!ismouseclick(WM_LBUTTONDOWN))

			{
				delay(10);
			}
			//getting mouse click
			getmouseclick(WM_LBUTTONDOWN, a, b);
			//calling line_point funtion
			line_points(a, b, turn, temp);
			setcolor(15);
			settextstyle(8, HORIZ_DIR, 3);
			setlinestyle(0,0,10);
			setcolor(LIGHTRED);
			//checking weather someone is winning or not
			if (temp[0] == 1 && temp[1] == 1 && temp[2] == 1){ outtextxy(460, 60, "player two wins"); player2wins++; line(0,75,450,75); break; }
			if (temp[3] == 1 && temp[4] == 1 && temp[5] == 1){ outtextxy(460, 60, "player two wins"); player2wins++; line(0,225,450,225); break; }
			if (temp[6] == 1 && temp[7] == 1 && temp[8] == 1){ outtextxy(460, 60, "player two wins"); player2wins++; line(0,375,450,375); break; }
			if (temp[0] == 1 && temp[3] == 1 && temp[6] == 1){ outtextxy(460, 60, "player two wins"); player2wins++; line(75,0,75,450); break; }
			if (temp[1] == 1 && temp[4] == 1 && temp[7] == 1){ outtextxy(460, 60, "player two wins"); player2wins++; line(225,0,225,450); break; }
			if (temp[2] == 1 && temp[5] == 1 && temp[8] == 1){ outtextxy(460, 60, "player two wins"); player2wins++; line(375,0,375,450); break; }
			if (temp[0] == 1 && temp[4] == 1 && temp[8] == 1){ outtextxy(460, 60, "player two wins"); player2wins++; line(0,0,450,450); break; }
			if (temp[2] == 1 && temp[4] == 1 && temp[6] == 1){ outtextxy(460, 60, "player two wins"); player2wins++; line(0,450,450,0); break; }

			if (temp[0] == 0 && temp[1] == 0 && temp[2] == 0){ outtextxy(460, 60, "player one wins"); player1wins++; line(0, 75, 450, 75); break; }
			if (temp[3] == 0 && temp[4] == 0 && temp[5] == 0){ outtextxy(460, 60, "player one wins"); player1wins++; line(0, 225, 450, 225); break; }
			if (temp[6] == 0 && temp[7] == 0 && temp[8] == 0){ outtextxy(460, 60, "player one wins"); player1wins++; line(0, 375, 450, 375); break; }
			if (temp[0] == 0 && temp[3] == 0 && temp[6] == 0){ outtextxy(460, 60, "player one wins"); player1wins++; line(75, 0, 75, 450); break; }
			if (temp[1] == 0 && temp[4] == 0 && temp[7] == 0){ outtextxy(460, 60, "player one wins"); player1wins++; line(225, 0, 225, 450); break; }
			if (temp[2] == 0 && temp[5] == 0 && temp[8] == 0){ outtextxy(460, 60, "player one wins"); player1wins++; line(375, 0, 375, 450); break; }
			if (temp[0] == 0 && temp[4] == 0 && temp[8] == 0){ outtextxy(460, 60, "player one wins"); player1wins++; line(0, 0, 450, 450); break; }
			if (temp[2] == 0 && temp[4] == 0 && temp[6] == 0){ outtextxy(460, 60, "player one wins"); player1wins++; line(0, 450, 450, 0); break; }
			//printing the string stored in record 1 and 2
			sprintf(record1, "player one winings = %d", player1wins);
			sprintf(record2, "player two winings = %d", player2wins);
			//changing turn of player
			if (turn == 0){ turn = 1; }
			else{ turn = 0; }
		}


		sprintf(record1, "player one winings = %d", player1wins);
		sprintf(record2, "player two winings = %d", player2wins);
		//checking if last game is playing then do not close the graph
		if (best3 != 2){
			getch();
			closegraph();
		}
	}
	//if last game have played then we should check wo wins or match draw
	if (player1wins>player2wins)
	{
		outtextxy(460, 80, "So player one wins overall game");
	}
	if (player2wins>player1wins)
	{
		outtextxy(460, 80, "So player two wins overall game");
	}
	if (player1wins == player2wins)
		outtextxy(460, 80, "Match Draw");
	getch();
	return 0;
}

