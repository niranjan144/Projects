#include <iostream.h>
#include <conio.h>
#include <dos.h>  // For delay()
#include <stdlib.h> // For rand()
#include <iomanip.h>

const int width = 20;
const int height = 20;

int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
int gameOver;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void Setup() {
    gameOver = 0;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

void Draw() {
    clrscr(); // Clear the screen (specific to Turbo C++)
    // Top border
    for (int i = 0; i < width + 2; i++)
	cout << "#";
    cout << endl;

    // Game field
    for (i = 0; i < height; i++) {
	for (int j = 0; j < width; j++) {
	    if (j == 0)
		cout << "#"; // Left border
	    if (i == y && j == x)
		cout << "O"; // Snake head
	    else if (i == fruitY && j == fruitX)
		cout << "F"; // Fruit
	    else {
		int print = 0;
		for (int k = 0; k < nTail; k++) {
		    if (tailX[k] == j && tailY[k] == i) {
			cout << "o"; // Snake tail
			print = 1;
		    }
		}
		if (!print)
		    cout << " ";
	    }
	    if (j == width - 1)
		cout << "#"; // Right border
	}
	cout << endl;
    }

    // Bottom border
    for (i = 0; i < width + 2; i++)
	cout << "#";
    cout << endl;

    // Score
    cout << "Score: " << score << endl;
}

void Input() {
    if (kbhit()) {  // Check if a key is pressed
	char key = getch();  // Get the pressed key
	switch (key) {
	    case 'a':  // Move left
	    case 'A':
		if (dir != RIGHT) dir = LEFT;
		break;
	    case 'd':  // Move right
	    case 'D':
		if (dir != LEFT) dir = RIGHT;
		break;
	    case 'w':  // Move up
	    case 'W':
		if (dir != DOWN) dir = UP;
		break;
	    case 's':  // Move down
	    case 'S':
		if (dir != UP) dir = DOWN;
		break;
	    case 'x':  // Exit the game
	    case 'X':
		gameOver = 1;  // Set the game over flag
		break;
	}
    }
}

void Logic() {
    // Update the snake's tail
    int prevX = tailX[0], prevY = tailY[0];
    int prev2X, prev2Y;

    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++) {
	prev2X = tailX[i];
	prev2Y = tailY[i];
	tailX[i] = prevX;
	tailY[i] = prevY;
	prevX = prev2X;
	prevY = prev2Y;
    }

    // Movement logic
    switch (dir) {
	case LEFT:
	    x--;
	    break;
	case RIGHT:
	    x++;
	    break;
	case UP:
	    y--;
	    break;
	case DOWN:
	    y++;
	    break;
    }

    // Check for collision with walls
    if (x >= width || x < 0 || y >= height || y < 0) {
	gameOver = 1;
    }

    // Check for collision with self
    for (i = 0; i < nTail; i++) {
	if (tailX[i] == x && tailY[i] == y) {
	    gameOver = 1;
	}
    }

    // Check if the snake eats the fruit
    if (x == fruitX && y == fruitY) {
	score += 10;  // Increase score
	nTail++;      // Increase tail size

	// Generate new food position
	fruitX = rand() % width;
	fruitY = rand() % height;

	// Ensure food doesn't spawn on the snake
	for (int i = 0; i < nTail; i++) {
	    if (tailX[i] == fruitX && tailY[i] == fruitY) {
		fruitX = rand() % width;
		fruitY = rand() % height;
		i = -1;  // Restart the loop
	    }
	}
    }
}

void main() {
    clrscr();
    Setup();
    while (!gameOver) {  // Main game loop
    Input();         // Continuously check for user input
    Logic();         // Update game logic
    Draw();          // Draw the game board
    delay(100);      // Add delay for smooth gameplay
}
}