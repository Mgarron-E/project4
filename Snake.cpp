#include <NonBlockingGame.h>
#include <iostream>
#include <time.h>
#include <vector>
#include <Bridges.h>

//
//  The purpose of this assignment is to learn to 1. The classic game of Snake.
//  Move a "snake" (line of sprites) along a 2D grid attempting to run over a
//  randomly placed object to help it grow. 2. If it runs into itself the game is over
//  and the player has lost. 3. The object of the game is to make the snake as big as possible.
//
using namespace bridges::game;
using namespace std;

// this keeps a list of elements (squares) that represents the snake object
// linked list since it can grow as the game progresses
class Block {
  public:
    Block *next = nullptr;
    int x;
    int y;
    Block() {
      x = 0;
      y = 0;
    }
    Block(int x, int y) {
      this->x = x;
      this->y = y;
    }
};

struct my_game : public NonBlockingGame {
  long frameTime;
  long nextFrameTime;

    //TODO: create a variable to represent an apple, what type should it be?
	struct Apple {
		
		int x;
		int y;
		
	};
	Apple apple;	
    //TODO: create a variable to represent the head, what type should it be?
	 struct Head{
		
                int x;
                int y;
        	
        };
	Head head;

  enum Direction {East, West, South, North};
    
    //TODO: create a variable to store the last direction and initialize it to east
	Direction lastdirection =  East;
	Direction currentdirection = East;
    //TODO: create a variable to store the current direction and initialize it to east

  int frame = 0;

  my_game(int assID, std::string username, std::string apikey)
    : NonBlockingGame (0, "meg707", "91965385486",30,30) {
  }

  virtual void initialize() override {
    srand(time(NULL));
	my_game::Head head;
      //TODO: initialize the head to a new block starting at the point 15, 15
	head.x = 15;
	head.y = 15;
	
      //TODO: create a pointer to head
 	Block* current = new Block();
	current->x = head.x;
	current->y = head.y;
	current->next = nullptr;

	Block* next = new Block();
	next->x = head.x;
	next->y = head.y;
	
      //This code draws the rest of the snake
      //TODO: what color would you like your snake? The default is silver as you can see
    for (int i = 0; i < 3; i++) {
      setBGColor(15 - i, 15, NamedColor::green);

      if (i > 0) {
        current->next = new Block(15 - i, 15);
        current = current->next;
      }
    }

      //TODO: set the current direction to east
	currentdirection = Direction::East;
      //TODO: set the last direction equal to the current direction
	lastdirection = currentdirection;
      //TODO: initialize an apple to a block at 0,0
	apple.x = 0;
	apple.y = 0;
      //TODO: plant the apple
	plantApple();
      //TODO: paint the screen
	paint();
  }

  void handleInput() {
      //TODO: test which key was pressed (ex: keyLeftJustPressed())
      //if the user pressed left, change the current direction to west as long as the
      //the last direction does not equal east...the snake can't just flip
      //Do for up, down, left, right
	if (keyLeftJustPressed()){
		if (lastdirection != Direction::East){
			currentdirection = Direction::West;
		}
  	}
	else if (keyRightJustPressed()){
		if (lastdirection != Direction::West){
			currentdirection = Direction::East;
		}
	}
	else if (keyUpJustPressed()){
		if (lastdirection != Direction::South){
			currentdirection = Direction::North;
		}
	}
	else if (keyDownJustPressed()){
		if (lastdirection != Direction::North){
			currentdirection = Direction::South;
		}
	}
	lastdirection = currentdirection;
  }

  // update snake position
  void updatePosition() {
    Block * current = head.next;
    int nextX = head.x;
    int nextY = head.y;
    Block nextPos = head;

      //TODO: loop through the snake's body setting each node's (x,y) to the next node's (x,y)
	while (current != nullptr){
		switch (currentdirection){
			case Direction::East:
				nextPos.x = current ->x + 1;
				nextPos.y = current ->y;
				break;
			 case Direction::West:
                                nextPos.x = current ->x - 1;
                                nextPos.y = current ->y;
                                break;
			 case Direction::South:
                                nextPos.x = current ->x;
                                nextPos.y = current ->y + 1;
                                break;
			 case Direction::North:
                                nextPos.x = current ->x;
                                nextPos.y = current ->y -  1;
                                break;
			default:
				break;
		}
		*current = nextPos;
		current = current->next;
	}
}

      // TODO: handle edge cases
      //hint: a switch statement on the current direction would be really helpful
    


  // locate apple at new position
  void plantApple() {
    int x;
    int y;
	bool plantable = true;

      //TODO: get a new random x and a random y for the apple
      //loop through the snake to ensure that the apple's (x,y) does not
      //intersect with any part of the snake, if it does, get new random values to test
      //if it doesn't collide with the snake, set the apple's x and apple's y to the random
      //values that were identified
	while (plantable){
		x = rand()%30;
		y = rand()%30;
		plantable = false;
		Block* current = head;
		while(current != nullptr){
			if(current->x == x && current->y == y){
				plantable = true;
				break;
			}
		}
	}
	apple.x = x;
	apple.y = y;

}

  // check if snake has found the apple
  void detectApple() {
      //Tests to see if the snake has hit the apple
      //Erases the apple
    if (head.x == apple.x && head.y == apple.y) {
      drawSymbol(apple.x, apple.y, NamedSymbol::none, NamedColor::red);

        //TODO: Make the snake longer by adding a new block to the end of the snake
	Block* current = head;
	while(current->next != nullptr){
		current = curent->next;
	}
	Block* newBlock = new Block(apple.x, apple.y);
	current->next = newBlock;
        //Plant a new apple
      plantApple();
    }
  }

  // check if snake ate itself! Yuk!
  void detectDeath() {
    Block * current = head.next;
    while (current != nullptr) {
      if (head.x == current->x && Head.y == current->y) {
        // TODO: need to deallocate storage!
	Block* temp;
	while (Head != nullptr){
		temp = head;
		head = head->next;
		delete temp;
	}
        exit(0);
      }
      current = current->next;
    }
  }


  // redraw
  void paint() {
      //Paints the board by looping through the rows and columns
      //Optional TODO: change the color of the board
    for (int i = 0; i < 30; i++) {
      for (int j = 0; j < 30; j++) {
        if (i % 2 == j % 2) {
          setBGColor(i, j, NamedColor::green);
        }
        else {
          setBGColor(i, j, NamedColor::forestgreen);
        }
      }
    }

      //Optional TODO: change the color of the head of the snake
    setBGColor(head.x, head.y, NamedColor::white);

      //Optional TODO: use a different symbol or color
    drawSymbol(apple.x, apple.y, NamedSymbol::apple, NamedColor::red);

      //Paints the snake
      //Optional TODO: change the color of the snake
    Block * current = head.next;
    while (current != nullptr) {
      setBGColor(current->x, current->y, NamedColor::silver);
      current = current->next;
    }
  }

  // handle input, check if apple was detected, update position, redraw,
  // detect if snake ate itself
  virtual void gameLoop() override {
    frame += 1;
    handleInput();
    if (frame >= 5) {
      lastDir = dir;
      detectApple();
      updatePosition();
      paint();
      detectDeath();
      frame = 0;
    }
  }
};

// Initialize your game
// Call your game class with your assignment id, username, and api key
int main (int argc, char** argv) {
  my_game g(1, "meg707", "91965385486");

  g.start();
}

