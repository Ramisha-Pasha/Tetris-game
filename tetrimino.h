
#include <SFML/Graphics.hpp>
#include<iostream>
#include <cstdlib> // for rand and srand
#include <ctime> // for time


using namespace sf;
using namespace std;


//returns color of the tetrimino.
Color getColor(int id) {
	if (id == 1)
		return Color::Blue;
	else if (id == 2)
		return Color::Green;
	else if (id == 3)
		return Color::Magenta;
	else if (id == 4)
		return Color::Yellow;
	else if (id == 5)
		return Color::Red;
	else if (id == 6)
		return Color::Cyan;
	else if (id == 7)
		return Color::Color(255, 165, 0);
	else
		return Color::Red;
}

class Gameboard {
public:
	int r = 20;
	int c = 10;
	int board[20][10];
	void drawBoard(RenderWindow& window) {
		RectangleShape well;
		well.setFillColor(Color::Black);
		well.setOutlineColor(Color::White);
		well.setSize(Vector2f(30.0f, 30.0f));
		well.setOutlineThickness(1);
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 10; j++) {
				well.setPosition(Vector2f(j * 30.0f, i * 30.0f));
				window.draw(well);
			}
		}

		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 10; j++) {
				int tetriminoId = board[i][j];
				if (tetriminoId != 0) {
					sf::Color tetriminoColor = getColor(tetriminoId); // Get the color based on the tetrimino id
					well.setFillColor(tetriminoColor);
					well.setPosition(sf::Vector2f(j * 30.0f, i * 30.0f));
					window.draw(well);
				}
			}
		}
		
	}
	Gameboard() {
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 10; j++) {
				board[i][j] = 0;
			}
		}
		

	}
	void setId(int x, int y, int blockId) {
		board[y][x] = blockId;
	}
	int getBId(int x, int y) const {
		return board[y][x];
	}

	int clearRows() {
		bool flag;
		int clear = 0;
		for (int y = 20 - 1; y >= 0; y--) {
			bool filled = true;
			flag = filled;
			for (int x = 0; x < 10; x++) {
				if (board[y][x] == 0) {
					flag = false;
					filled = false;
					break;
				}
			}
			if (filled) {
				// Clear the row
				for (int x = 0; x < 10; x++) {
					board[y][x] = 0;
				}
				// Shift the rows above it down
				for (int i = y - 1; i >= 0; i--) {
					for (int x = 0; x < 10; x++) {
						setId(x, i + 1, getBId(x, i));
						setId(x, i, 0);
					}
				}
				clear++;
			}
		}
		return clear;
	}

	bool isEmpty( int x, int y) {
		int X = 0;
		int  Y = 0;
		for (int i = 0;i < 20;i++) {
			for (int j = 0;j < 10;j++) {
				X = x + j;
				Y = y + i;
				if (board[Y][X] != 0)
					return false;
			}
		}
		return true;

	}
	
	


};
//base class tetrimino.
class tetrimino {
public:
	Color color;
	int shape[4][4];
	int x, y;
	int rotation = 0;
public:
	tetrimino(sf::Color color, int x, int y, int sha[4][4]) {
		// Set the color of the Tetrimino
		this->color = color;

		

		// Set the position of the Tetrimino
		this->x = x;
		this->y = y;

	}
	tetrimino operator=(const tetrimino& lhs) {
		if (this != &lhs) {
			color = lhs.color;
			x = lhs.x;
			y = lhs.y;
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					this->shape[i][j] = lhs.shape[i][j];
				}
			}
			rotation = lhs.rotation;

		}

	}
	virtual void draw(sf::RenderWindow& window) {
		cout << "hehe";
	};
	virtual bool moveRight(int board[][10]) {
		return false;
	}
	virtual bool moveLeft(int board[][10]) {
		return false;
	}
	virtual bool moveDown(int board[][10]) {
		return false;
	}
	virtual void moveRight() {}
	virtual void moveLeft() {}
	virtual void moveDown() {}
	
	virtual void rotate(int board[][10]) {
		cout << "rotate function";
	}
	virtual bool IsColliding(int x, int y, int rotation, int board[][10]) {
		return false;
	}
	/*int getX(int i) const {
		return x + shape[i][0];
	}

	int getY(int i) const {
		return y + shape[i][1];
	}*/
	virtual int getId() {
		return 0;
	};
	int getRotation() {
		return this->rotation;
	}
	

};


//Lshape inherited.
class LShape :public tetrimino {
public:
	int block[4][4];


	//CONSTRUCTOR FOR L SHAPE.
	LShape(int x, int y) : tetrimino(Color::Blue ,x, y,block) {
		// Set the shape of the L Tetrimino
		for (int i = 0;i < 4;i++) {
			for (int j = 0;j < 4;j++) {
				block[i][j] = 0;
			}
		}
		block[0][1] = 1;
		block[1][1] = 1;
		block[2][1] = 1;
		block[2][2] = 1;

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				shape[i][j] = 0;
				
			}

		}
		shape[0][1] = 1;
		shape[1][1] = 1;
		shape[2][1] = 1;
		shape[2][2] = 1;

	}
	//DRAW FUNCTION OVERRIDED.
	void draw(RenderWindow& window) {
		// Set the color of the L Tetrimino
		sf::RectangleShape shape(sf::Vector2f(30.0f, 30.0f));
		shape.setFillColor(Color::Blue);

		// Draw the blocks for the L Tetrimino
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (block[i][j] == 1) {
					shape.setPosition((x + j) * 30.0f, (y + i) * 30.0f);
					shape.setOutlineColor(Color::White);
					shape.setOutlineThickness(1.0f);
					window.draw(shape);
				}
			}
		}

	}
	//COLLISION DETECTION FUNCTION OVERRIDED.
	bool IsColliding(int x, int y, int rotation, int board[][10]) {
		// check if any cell of the grid of the shape is outside the game grid boundary.
		int X = 0;
		int  Y = 0;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (this->block[i][j] == 1) {
					X = x + j;
					Y = y + i;
					if (X < 0 || X >= 10 || Y >= 20) {
						return true;
					}
				}
			}
		}
		X = 0;
		Y = 0;
		// Check if any cells of the shape are colliding with another cell of another shape on the game board.
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (this->block[i][j] == 1) {
					X = x + j;
					Y = y + i;
					if (Y >= 0 && board[Y][X] != 0) {
						return true;
					}
				}
			}
		}

		// No collision detected
		return false;

	}

	//ROTATION FUNCTION OVERRIDED.
	void rotate(int board[][10]) {
		// Save current rotation state
		int Crotation = rotation;
		int oldx = x;
		int oldy = y;

		// Rotate the tetrimino shape by 90 degrees
		int hehe[4][4];
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				hehe[i][j] = this->block[i][j];
			}
		}
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				this->block[i][j] = hehe[3 - j][i];
			}
		}
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				shape[i][j] = hehe[3 - j][i];
			}
		}

		
		// Check if the new position of the tetrimino collides with any occupied cells on the game board
		if (IsColliding(x, y, rotation, board)) {
			// If the new position collides, restore the previous rotation state.
			rotation = Crotation;
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					this->block[i][j] = hehe[i][j];
				}
			}
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					shape[i][j] = hehe[i][j];
				}
			}
			x = oldx;
			y = oldy;
			
		}
		

		else {
			// If the new rotation does not collide, update the rotation state
			rotation = (rotation + 1) % 4;
		}
		
	}
	//MOVE RIGHT.
	bool moveRight(int board[][10])  {
		// Save the current position
		int oldX = x;

		// Move one unit to the right
		x++;

		// Check for collision
		if (this->IsColliding(x, y, 0, board)) {
			// Collision detected, revert to old position
			x = oldX;
			return true;
		}

		return false;
	}
	//MOVE LEFT.
	bool moveLeft(int board[][10])  {
		// Save the current position
		int oldX = x;

		// Move one unit to the left
		x--;

		// Check for collision
		if (this->IsColliding(x, y, 0, board)) {
			// Collision detected, revert to old position
			x = oldX;
			return true;
		}

		return false;
	}
	//MOVE DOWN.
	bool moveDown(int board[][10])  {
		// Save the current position
		int oldY = y;

		// Move one unit down
		y++;

		// Check for collision
		if (this->IsColliding(x, y, 0, board)) {
			// Collision detected, revert to old position
			y = oldY;
			return true;
		}

		return false;
	}
	//RETURN ID OF THE TETRIMINO(LSHAPE=1)
	int getId() {
		return 1;
	}
	//MOVE FUNCTIONS.
	void moveRight() {
		x++;
	}
	void moveLeft() {
		x--;
	}
	void moveDown()  {
		y++;
	}
	
};

//Sshape inherited.
class sShape :public tetrimino {
public:
	int block[4][4];
	//CONSTRUCTOR FOR L SHAPE.
	sShape(int x, int y) : tetrimino(Color::Green, x, y,block) {
		for (int i = 0;i < 4;i++) {
			for (int j = 0;j < 4;j++) {
				block[i][j] = 0;
			}
		}
		// Set the shape of the L Tetrimino
		block[1][1] = 2;
		block[1][2] = 2;
		block[2][0] = 2;
		block[2][1] = 2;


		for (int i = 0;i < 4;i++) {
			for (int j = 0;j < 4;j++) {
				shape[i][j] = 0;
			}
		}

		shape[1][1] = 2;
		shape[1][2] = 2;
		shape[2][0] = 2;
		shape[2][1] = 2;


	}
	//DRAW FUNCTION OVERRIDED.
	void draw(RenderWindow& window) {
		// Set the color of the L Tetrimino
		sf::RectangleShape shape(sf::Vector2f(30.0f, 30.0f));
		shape.setFillColor(Color::Green);

		// Draw the blocks for the L Tetrimino
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (block[i][j] == 2) {
					shape.setPosition((x + j) * 30.0f, (y + i) * 30.0f);
					shape.setOutlineColor(Color::White);
					shape.setOutlineThickness(1.0f);
					window.draw(shape);
				}
			}
		}

	}
	//COLLISION DETECTION FUNCTION OVERRIDED.
	bool IsColliding(int x, int y, int rotation, int board[][10]) {
		// check if any cell of the grid of the shape is outside the game grid boundary.
		int X = 0;
		int  Y = 0;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (this->block[i][j] == 2) {
					X = x + j;
					Y = y + i;
					if (X < 0 || X >= 10 || Y >= 20) {
						return true;
					}
				}
			}
		}
		X = 0;
		Y = 0;
		// Check if any cells of the shape are colliding with another cell of another shape on the game board.
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (this->block[i][j] == 2) {
					X = x + j;
					Y = y + i;
					if (Y >= 0 && board[Y][X] != 0) {
						return true;
					}
				}
			}
		}

		// No collision detected
		return false;

	}

	//ROTATION FUNCTION OVERRIDED.
	void rotate(int board[][10]) {
		// Save current rotation state
		int Crotation = rotation;

		// Rotate the tetrimino shape by 90 degrees
		int hehe[4][4];
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				hehe[i][j] = this->block[i][j];
			}
		}
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				this->block[i][j] = hehe[3 - j][i];
			}
		}
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				shape[i][j] = hehe[3 - j][i];
			}
		}


		// Check if the new position of the tetrimino collides with any occupied cells on the game board
		if (IsColliding(x, y, rotation, board)) {
			// If the new position collides, restore the previous rotation state.
			rotation = Crotation;
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					this->block[i][j] = hehe[i][j];
				}
			}
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					shape[i][j] = hehe[i][j];
				}
			}
		}
		else {
			// If the new rotation does not collide, update the rotation state
			rotation = (rotation + 1) % 4;
		}
		cout << "rotate called";
	}
	//MOVE RIGHT.
	bool moveRight(int board[][10]) {
		// Save the current position
		int oldX = x;

		// Move one unit to the right
		x++;

		// Check for collision
		if (this->IsColliding(x, y, 0, board)) {
			// Collision detected, revert to old position
			x = oldX;
			return true;
		}

		return false;
	}
	//MOVE LEFT.
	bool moveLeft(int board[][10]) {
		// Save the current position
		int oldX = x;

		// Move one unit to the left
		x--;

		// Check for collision
		if (this->IsColliding(x, y, 0, board)) {
			// Collision detected, revert to old position
			x = oldX;
			return true;
		}

		return false;
	}
	//MOVE DOWN.
	bool moveDown(int board[][10]) {
		// Save the current position
		int oldY = y;

		// Move one unit down
		y++;

		// Check for collision
		if (this->IsColliding(x, y, 0, board)) {
			// Collision detected, revert to old position
			y = oldY;
			return true;
		}

		return false;
	}
	//RETURN ID OF THE TETRIMINO(LSHAPE=1)
	int getId() {
		return 2;
	}
	//MOVE FUNCTIONS.
	void moveRight() {
		x++;
	}
	void moveLeft() {
		x--;
	}
	void moveDown() {
		y++;
	}
};

//Tshape inherited.
class TShape :public tetrimino {
public:
	int block[4][4];
	//CONSTRUCTOR FOR L SHAPE.
	TShape(int x, int y) : tetrimino(Color::Magenta, x, y,block) {
		for (int i = 0;i < 4;i++) {
			for (int j = 0;j < 4;j++) {
				block[i][j] = 0;
			}
		}
		// Set the shape of the L Tetrimino
		block[1][1] = 3;
		block[2][0] = 3;
		block[2][1] = 3;
		block[2][2] = 3;

		for (int i = 0;i < 4;i++) {
			for (int j = 0;j < 4;j++) {
				shape[i][j] = 0;
			}
		}

		shape[1][1] = 3;
		shape[2][0] = 3;
		shape[2][1] = 3;
		shape[2][2] = 3;


	}
	//DRAW FUNCTION OVERRIDED.
	void draw(RenderWindow& window) {
		// Set the color of the L Tetrimino
		sf::RectangleShape shape(sf::Vector2f(30.0f, 30.0f));
		shape.setFillColor(Color::Magenta);

		// Draw the blocks for the L Tetrimino
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (block[i][j] == 3) {
					shape.setPosition((x + j) * 30.0f, (y + i) * 30.0f);
					shape.setOutlineColor(Color::White);
					shape.setOutlineThickness(1.0f);
					window.draw(shape);
				}
			}
		}

	}
	//COLLISION DETECTION FUNCTION OVERRIDED.
	bool IsColliding(int x, int y, int rotation, int board[][10]) {
		// check if any cell of the grid of the shape is outside the game grid boundary.
		int X = 0;
		int  Y = 0;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (this->block[i][j] == 3) {
					X = x + j;
					Y = y + i;
					if (X < 0 || X >= 10 || Y >= 20) {
						return true;
					}
				}
			}
		}
		X = 0;
		Y = 0;
		// Check if any cells of the shape are colliding with another cell of another shape on the game board.
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (this->block[i][j] == 3) {
					X = x + j;
					Y = y + i;
					if (Y >= 0 && board[Y][X] != 0) {
						return true;
					}
				}
			}
		}

		// No collision detected
		return false;

	}

	//ROTATION FUNCTION OVERRIDED.
	void rotate(int board[][10]) {
		// Save current rotation state
		int Crotation = rotation;

		// Rotate the tetrimino shape by 90 degrees
		int hehe[4][4];
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				hehe[i][j] = this->block[i][j];
			}
		}
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				this->block[i][j] = hehe[3 - j][i];
			}
		}
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				shape[i][j] = hehe[3 - j][i];
			}
		}


		// Check if the new position of the tetrimino collides with any occupied cells on the game board
		if (IsColliding(x, y, rotation, board)) {
			// If the new position collides, restore the previous rotation state.
			rotation = Crotation;
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					this->block[i][j] = hehe[i][j];
				}
			}
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					shape[i][j] = hehe[i][j];
				}
			}
		}
		else {
			// If the new rotation does not collide, update the rotation state
			rotation = (rotation + 1) % 4;
		}
		cout << "rotate called";
	}
	//MOVE RIGHT.
	bool moveRight(int board[][10]) {
		// Save the current position
		int oldX = x;

		// Move one unit to the right
		x++;

		// Check for collision
		if (this->IsColliding(x, y, 0, board)) {
			// Collision detected, revert to old position
			x = oldX;
			return true;
		}

		return false;
	}
	//MOVE LEFT.
	bool moveLeft(int board[][10]) {
		// Save the current position
		int oldX = x;

		// Move one unit to the left
		x--;

		// Check for collision
		if (this->IsColliding(x, y, 0, board)) {
			// Collision detected, revert to old position
			x = oldX;
			return true;
		}

		return false;
	}
	//MOVE DOWN.
	bool moveDown(int board[][10]) {
		// Save the current position
		int oldY = y;

		// Move one unit down
		y++;

		// Check for collision
		if (this->IsColliding(x, y, 0, board)) {
			// Collision detected, revert to old position
			y = oldY;
			return true;
		}

		return false;
	}
	//RETURN ID OF THE TETRIMINO(LSHAPE=1)
	int getId() {
		return 3;
	}
	//MOVE FUNCTIONS.
	void moveRight() {
		x++;
	}
	void moveLeft() {
		x--;
	}
	void moveDown() {
		y++;
	}
};

//Oshape inherited.
class OShape :public tetrimino {
public:
	int block[4][4];
	//CONSTRUCTOR FOR L SHAPE.
	OShape(int x, int y) : tetrimino(Color::Yellow, x, y,block) {
		for (int i = 0;i < 4;i++) {
			for (int j = 0;j < 4;j++) {
				block[i][j] = 0;
			}
		}
		// Set the shape of the L Tetrimino
		block[1][1] = 4;
		block[1][2] = 4;
		block[2][1] = 4;
		block[2][2] = 4;
		for (int i = 0;i < 4;i++) {
			for (int j = 0;j < 4;j++) {
				shape[i][j] = 0;
			}
		}
	shape[1][1] = 4;
		shape[1][2] = 4;
		shape[2][1] = 4;
		shape[2][2] = 4;


	}
	//DRAW FUNCTION OVERRIDED.
	void draw(RenderWindow& window) {
		// Set the color of the L Tetrimino
		sf::RectangleShape shape(sf::Vector2f(30.0f, 30.0f));
		shape.setFillColor(Color::Yellow);

		// Draw the blocks for the L Tetrimino
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (block[i][j] == 4) {
					shape.setPosition((x + j) * 30.0f, (y + i) * 30.0f);
					shape.setOutlineColor(Color::White);
					shape.setOutlineThickness(1.0f);
					window.draw(shape);
				}
			}
		}

	}
	//COLLISION DETECTION FUNCTION OVERRIDED.
	bool IsColliding(int x, int y, int rotation, int board[][10]) {
		// check if any cell of the grid of the shape is outside the game grid boundary.
		int X = 0;
		int  Y = 0;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (this->block[i][j] == 4) {
					X = x + j;
					Y = y + i;
					if (X < 0 || X >= 10 || Y >= 20) {
						return true;
					}
				}
			}
		}
		X = 0;
		Y = 0;
		// Check if any cells of the shape are colliding with another cell of another shape on the game board.
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (this->block[i][j] == 4) {
					X = x + j;
					Y = y + i;
					if (Y >= 0 && board[Y][X] != 0) {
						return true;
					}
				}
			}
		}

		// No collision detected
		return false;

	}

	//ROTATION FUNCTION OVERRIDED.
	void rotate(int board[][10]) {
		// Save current rotation state
		int Crotation = rotation;

		// Rotate the tetrimino shape by 90 degrees
		int hehe[4][4];
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				hehe[i][j] = this->block[i][j];
			}
		}
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				this->block[i][j] = hehe[3 - j][i];
			}
		}
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				shape[i][j] = hehe[3 - j][i];
			}
		}


		// Check if the new position of the tetrimino collides with any occupied cells on the game board
		if (IsColliding(x, y, rotation, board)) {
			// If the new position collides, restore the previous rotation state.
			rotation = Crotation;
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					this->block[i][j] = hehe[i][j];
				}
			}
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					shape[i][j] = hehe[i][j];
				}
			}
		}
		else {
			// If the new rotation does not collide, update the rotation state
			rotation = (rotation + 1) % 4;
		}
		cout << "rotate called";
	}
	//MOVE RIGHT.
	bool moveRight(int board[][10]) {
		// Save the current position
		int oldX = x;

		// Move one unit to the right
		x++;

		// Check for collision
		if (this->IsColliding(x, y, 0, board)) {
			// Collision detected, revert to old position
			x = oldX;
			return true;
		}

		return false;
	}
	//MOVE LEFT.
	bool moveLeft(int board[][10]) {
		// Save the current position
		int oldX = x;

		// Move one unit to the left
		x--;

		// Check for collision
		if (this->IsColliding(x, y, 0, board)) {
			// Collision detected, revert to old position
			x = oldX;
			return true;
		}

		return false;
	}
	//MOVE DOWN.
	bool moveDown(int board[][10]) {
		// Save the current position
		int oldY = y;

		// Move one unit down
		y++;

		// Check for collision
		if (this->IsColliding(x, y, 0, board)) {
			// Collision detected, revert to old position
			y = oldY;
			return true;
		}

		return false;
	}
	//RETURN ID OF THE TETRIMINO(LSHAPE=1)
	int getId() {
		return 4;
	}
	//MOVE FUNCTIONS.
	void moveRight() {
		x++;
	}
	void moveLeft() {
		x--;
	}
	void moveDown() {
		y++;
	}
};

//Zshape inherited.
class ZShape :public tetrimino {
public:
	int block[4][4];
	//CONSTRUCTOR FOR L SHAPE.
	ZShape(int x, int y) : tetrimino(Color::Red, x, y,block) {
		for (int i = 0;i < 4;i++) {
			for (int j = 0;j < 4;j++) {
				block[i][j] = 0;
			}
		}
		// Set the shape of the L Tetrimino
		block[1][1] = 5;
		block[1][2] = 5;
		block[2][2] = 5;
		block[2][3] = 5;
		for (int i = 0;i < 4;i++) {
			for (int j = 0;j < 4;j++) {
				shape[i][j] = 0;
			}
		}
		shape[1][1] = 5;
		shape[1][2] = 5;
		shape[2][2] = 5;
		shape[2][3] = 5;


	}
	//DRAW FUNCTION OVERRIDED.
	void draw(RenderWindow& window) {
		// Set the color of the L Tetrimino
		sf::RectangleShape shape(sf::Vector2f(30.0f, 30.0f));
		shape.setFillColor(Color::Red);

		// Draw the blocks for the L Tetrimino
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (block[i][j] == 5) {
					shape.setPosition((x + j) * 30.0f, (y + i) * 30.0f);
					shape.setOutlineColor(Color::White);
					shape.setOutlineThickness(1.0f);
					window.draw(shape);
				}
			}
		}

	}
	//COLLISION DETECTION FUNCTION OVERRIDED.
	bool IsColliding(int x, int y, int rotation, int board[][10]) {
		// check if any cell of the grid of the shape is outside the game grid boundary.
		int X = 0;
		int  Y = 0;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (this->block[i][j] == 5) {
					X = x + j;
					Y = y + i;
					if (X < 0 || X >= 10 || Y >= 20) {
						return true;
					}
				}
			}
		}
		X = 0;
		Y = 0;
		// Check if any cells of the shape are colliding with another cell of another shape on the game board.
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (this->block[i][j] == 5) {
					X = x + j;
					Y = y + i;
					if (Y >= 0 && board[Y][X] != 0) {
						return true;
					}
				}
			}
		}

		// No collision detected
		return false;

	}

	//ROTATION FUNCTION OVERRIDED.
	void rotate(int board[][10]) {
		// Save current rotation state
		int Crotation = rotation;

		// Rotate the tetrimino shape by 90 degrees
		int hehe[4][4];
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				hehe[i][j] = this->block[i][j];
			}
		}
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				this->block[i][j] = hehe[3 - j][i];
			}
		}
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				shape[i][j] = hehe[3 - j][i];
			}
		}


		// Check if the new position of the tetrimino collides with any occupied cells on the game board
		if (IsColliding(x, y, rotation, board)) {
			// If the new position collides, restore the previous rotation state.
			rotation = Crotation;
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					this->block[i][j] = hehe[i][j];
				}
			}
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					shape[i][j] = hehe[i][j];
				}
			}
		}
		else {
			// If the new rotation does not collide, update the rotation state
			rotation = (rotation + 1) % 4;
		}
		cout << "rotate called";
	}
	//MOVE RIGHT.
	bool moveRight(int board[][10]) {
		// Save the current position
		int oldX = x;

		// Move one unit to the right
		x++;

		// Check for collision
		if (this->IsColliding(x, y, 0, board)) {
			// Collision detected, revert to old position
			x = oldX;
			return true;
		}

		return false;
	}
	//MOVE LEFT.
	bool moveLeft(int board[][10]) {
		// Save the current position
		int oldX = x;

		// Move one unit to the left
		x--;

		// Check for collision
		if (this->IsColliding(x, y, 0, board)) {
			// Collision detected, revert to old position
			x = oldX;
			return true;
		}

		return false;
	}
	//MOVE DOWN.
	bool moveDown(int board[][10]) {
		// Save the current position
		int oldY = y;

		// Move one unit down
		y++;

		// Check for collision
		if (this->IsColliding(x, y, 0, board)) {
			// Collision detected, revert to old position
			y = oldY;
			return true;
		}

		return false;
	}
	//RETURN ID OF THE TETRIMINO(LSHAPE=1)
	int getId() {
		return 5;
	}
	//MOVE FUNCTIONS.
	void moveRight() {
		x++;
	}
	void moveLeft() {
		x--;
	}
	void moveDown() {
		y++;
	}
};

//Ishape inherited.
class IShape :public tetrimino {
public:
	int block[4][4];
	//CONSTRUCTOR FOR L SHAPE.
	IShape(int x, int y) : tetrimino(Color::Cyan, x, y,block) {
		for (int i = 0;i < 4;i++) {
			for (int j = 0;j < 4;j++) {
				block[i][j] = 0;
			}
		}
		// Set the shape of the L Tetrimino
		block[0][2] = 6;
		block[1][2] = 6;
		block[2][2] = 6;
		block[3][2] = 6;
		for (int i = 0;i < 4;i++) {
			for (int j = 0;j < 4;j++) {
				shape[i][j] = 0;
			}
		}
		shape[0][2] = 6;
		shape[1][2] = 6;
		shape[2][2] = 6;
		shape[3][2] = 6;


	}
	//DRAW FUNCTION OVERRIDED.
	void draw(RenderWindow& window) {
		// Set the color of the L Tetrimino
		sf::RectangleShape shape(sf::Vector2f(30.0f, 30.0f));
		shape.setFillColor(Color::Cyan);

		// Draw the blocks for the L Tetrimino
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (block[i][j] == 6) {
					shape.setPosition((x + j) * 30.0f, (y + i) * 30.0f);
					shape.setOutlineColor(Color::White);
					shape.setOutlineThickness(1.0f);
					window.draw(shape);
				}
			}
		}

	}
	//COLLISION DETECTION FUNCTION OVERRIDED.
	bool IsColliding(int x, int y, int rotation, int board[][10]) {
		// check if any cell of the grid of the shape is outside the game grid boundary.
		int X = 0;
		int  Y = 0;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (this->block[i][j] == 6) {
					X = x + j;
					Y = y + i;
					if (X < 0 || X >= 10 || Y >= 20) {
						return true;
					}
				}
			}
		}
		X = 0;
		Y = 0;
		// Check if any cells of the shape are colliding with another cell of another shape on the game board.
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (this->block[i][j] == 6) {
					X = x + j;
					Y = y + i;
					if (Y >= 0 && board[Y][X] != 0) {
						return true;
					}
				}
			}
		}

		// No collision detected
		return false;

	}

	//ROTATION FUNCTION OVERRIDED.
	void rotate(int board[][10]) {
		// Save current rotation state
		int Crotation = rotation;

		// Rotate the tetrimino shape by 90 degrees
		int hehe[4][4];
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				hehe[i][j] = this->block[i][j];
			}
		}
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				this->block[i][j] = hehe[3 - j][i];
			}
		}
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				shape[i][j] = hehe[3 - j][i];
			}
		}


		// Check if the new position of the tetrimino collides with any occupied cells on the game board
		if (IsColliding(x, y, rotation, board)) {
			// If the new position collides, restore the previous rotation state.
			rotation = Crotation;
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					this->block[i][j] = hehe[i][j];
				}
			}
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					shape[i][j] = hehe[i][j];
				}
			}
		}
		else {
			// If the new rotation does not collide, update the rotation state
			rotation = (rotation + 1) % 4;
		}
		cout << "rotate called";
	}
	//MOVE RIGHT.
	bool moveRight(int board[][10]) {
		// Save the current position
		int oldX = x;

		// Move one unit to the right
		x++;

		// Check for collision
		if (this->IsColliding(x, y, 0, board)) {
			// Collision detected, revert to old position
			x = oldX;
			return true;
		}

		return false;
	}
	//MOVE LEFT.
	bool moveLeft(int board[][10]) {
		// Save the current position
		int oldX = x;

		// Move one unit to the left
		x--;

		// Check for collision
		if (this->IsColliding(x, y, 0, board)) {
			// Collision detected, revert to old position
			x = oldX;
			return true;
		}

		return false;
	}
	//MOVE DOWN.
	bool moveDown(int board[][10]) {
		// Save the current position
		int oldY = y;

		// Move one unit down
		y++;

		// Check for collision
		if (this->IsColliding(x, y, 0, board)) {
			// Collision detected, revert to old position
			y = oldY;
			return true;
		}

		return false;
	}
	//RETURN ID OF THE TETRIMINO(LSHAPE=1)
	int getId() {
		return 6;
	}
	//MOVE FUNCTIONS.
	void moveRight() {
		x++;
	}
	void moveLeft() {
		x--;
	}
	void moveDown() {
		y++;
	}
};

//L2shape inherited.
class L2Shape :public tetrimino {
public:
	int block[4][4];
	//CONSTRUCTOR FOR L SHAPE.
	L2Shape(int x, int y) : tetrimino(Color(255,265,0), x, y,block) {
		for (int i = 0;i < 4;i++) {
			for (int j = 0;j < 4;j++) {
				block[i][j] = 0;
			}
		}
		// Set the shape of the L Tetrimino
		block[0][1] = 7;
		block[1][1] = 7;
		block[2][1] = 7;
		block[2][0] = 7;
		for (int i = 0;i < 4;i++) {
			for (int j = 0;j < 4;j++) {
				shape[i][j] = 0;
			}
		}
		shape[0][1] = 7;
		shape[1][1] = 7;
		shape[2][1] = 7;
		shape[2][0] = 7;


	}
	//DRAW FUNCTION OVERRIDED.
	void draw(RenderWindow& window) {
		// Set the color of the L Tetrimino
		sf::RectangleShape shape(sf::Vector2f(30.0f, 30.0f));
		shape.setFillColor(Color(255,165,0));

		// Draw the blocks for the L Tetrimino
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (block[i][j] == 7) {
					shape.setPosition((x + j) * 30.0f, (y + i) * 30.0f);
					shape.setOutlineColor(Color::White);
					shape.setOutlineThickness(1.0f);
					window.draw(shape);
				}
			}
		}

	}
	//COLLISION DETECTION FUNCTION OVERRIDED.
	bool IsColliding(int x, int y, int rotation, int board[][10]) {
		// check if any cell of the grid of the shape is outside the game grid boundary.
		int X = 0;
		int  Y = 0;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (this->block[i][j] == 7) {
					X = x + j;
					Y = y + i;
					if (X < 0 || X >= 10 || Y >= 20) {
						return true;
					}
				}
			}
		}
		X = 0;
		Y = 0;
		// Check if any cells of the shape are colliding with another cell of another shape on the game board.
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (this->block[i][j] == 7) {
					X = x + j;
					Y = y + i;
					if (Y >= 0 && board[Y][X] != 0) {
						return true;
					}
				}
			}
		}

		// No collision detected
		return false;

	}

	//ROTATION FUNCTION OVERRIDED.
	void rotate(int board[][10]) {
		// Save current rotation state
		int Crotation = rotation;

		// Rotate the tetrimino shape by 90 degrees
		int hehe[4][4];
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				hehe[i][j] = this->block[i][j];
			}
		}
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				this->block[i][j] = hehe[3 - j][i];
			}
		}
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				shape[i][j] = hehe[3 - j][i];
			}
		}


		// Check if the new position of the tetrimino collides with any occupied cells on the game board
		if (IsColliding(x, y, rotation, board)) {
			// If the new position collides, restore the previous rotation state.
			rotation = Crotation;
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					this->block[i][j] = hehe[i][j];
				}
			}
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					shape[i][j] = hehe[i][j];
				}
			}
		}
		else {
			// If the new rotation does not collide, update the rotation state
			rotation = (rotation + 1) % 4;
		}
		cout << "rotate called";
	}
	//MOVE RIGHT.
	bool moveRight(int board[][10]) {
		// Save the current position
		int oldX = x;

		// Move one unit to the right
		x++;

		// Check for collision
		if (this->IsColliding(x, y, 0, board)) {
			// Collision detected, revert to old position
			x = oldX;
			return true;
		}

		return false;
	}
	//MOVE LEFT.
	bool moveLeft(int board[][10]) {
		// Save the current position
		int oldX = x;

		// Move one unit to the left
		x--;

		// Check for collision
		if (this->IsColliding(x, y, 0, board)) {
			// Collision detected, revert to old position
			x = oldX;
			return true;
		}

		return false;
	}
	//MOVE DOWN.
	bool moveDown(int board[][10]) {
		// Save the current position
		int oldY = y;

		// Move one unit down
		y++;

		// Check for collision
		if (this->IsColliding(x, y, 0, board)) {
			// Collision detected, revert to old position
			y = oldY;
			return true;
		}

		return false;
	}
	//RETURN ID OF THE TETRIMINO(LSHAPE=1)
	int getId() {
		return 7;
	}
	//MOVE FUNCTIONS.
	void moveRight() {
		x++;
	}
	void moveLeft() {
		x--;
	}
	void moveDown() {
		y++;
	}
};
//Random tetrimino generator.
tetrimino* getNew(RenderWindow& window) {
	tetrimino* newTetrimino;
	srand(time(nullptr));

	// generate a random number between 0 and 99
	int n = rand() % 7 + 1;
	switch (n) {
	case 1:
			newTetrimino = new  LShape(4, 0);
			break;
	case 2:
			newTetrimino = new  sShape(4, 0);
			break;
	case 3:
			newTetrimino = new  OShape(4, 0);
			break;
	case 4:
			newTetrimino = new  L2Shape(4, 0);
			break;
	case 5:
			newTetrimino = new  ZShape(4, 0);
			break;
	case 6:
			newTetrimino = new  IShape(4, 0);
			break;
	case 7:
			newTetrimino = new  TShape(4, 0);
			break;
	default:
		newTetrimino = new LShape(4, 0);
	}
	


	return newTetrimino;


}
//placing tetrimino on gameBoard once rested.
int placeTetrimino(tetrimino* tetrimino, RenderWindow& window, Gameboard& boards, int& score, int& l) {
	//sf::RectangleShape shape(sf::Vector2f(30.0f, 30.0f));
	//shape.setFillColor(Color::Blue);
	//shape.setPosition(Vector2f(0.0f, 0.0f));
	//window.draw(shape);

	int X = 0;
	int Y = 0;
	int c = 0;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (tetrimino->shape[i][j] == 1 || tetrimino->shape[i][j] == 2 || tetrimino->shape[i][j] == 3 || tetrimino->shape[i][j] == 4 || tetrimino->shape[i][j] == 5 || tetrimino->shape[i][j] == 6 || tetrimino->shape[i][j] == 7) {

				X = tetrimino->x + j;
				Y = tetrimino->y + i;

				boards.board[Y][X] = tetrimino->getId();


			}



		}
	}
	      c = boards.clearRows();
		
			if (c > 0) {
				score += 100;
				l++;
				
			}
	
	return score;
}
	












