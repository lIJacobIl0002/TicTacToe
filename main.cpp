#include <iostream>
#include <bitset>

using std::bitset;

// check win
// 0 = draw
// 1 = X win
// -1 = O win
// -2 = Nothing
int logic(bitset<9> xBoard, bitset<9> oBoard, const bitset<9>* winBit) {

	for(int i = 0; i < 8; i++) {
		if((xBoard & winBit[i]) == winBit[i]) // X win
			return 1;
		
		if((oBoard & winBit[i]) == winBit[i]) // O win
			return -1;
	}

	if((oBoard | xBoard).count() == 9) // draw
		return 0;
	
	//continue game
	return -2;
}

bitset<9> createMask(int p1, int p2, int p3) {
	bitset<9> mask; // easier to create win masks
	
	mask.set(p1);
	mask.set(p2);
	mask.set(p3);

	return mask;
}

// draw board on to screen;
void draw(bitset<9> xBoard, bitset<9> oBoard) {
	for(int i = 0; i < 9; i++) {
		if(xBoard.test(i))
			std::cout << 'X';
		else if(oBoard.test(i))
			std::cout << 'O';
		else // Istg I just got sick and tired of ternary operators
			std::cout << i+1;

		std::cout << ((i % 3 == 2) ?  "\n" : " | ");
	}

};

// player mechanism
void player_turn(char* turn, bitset<9>* xBoard, bitset<9>* oBoard) {
	int loc;

	std::cout << "Where would you like to place "
		<< turn << ": ";
	std::cin >> loc;

	// check if its already occupied
	if(xBoard->test(loc-1) | oBoard->test(loc-1)) {
		return;
	}
	
	//switch turns
	if(*turn == 'X') {
		*turn = 'O';
		xBoard->set(loc-1); // set X's turn
	
	} else {
		*turn = 'X';
		oBoard->set(loc-1);
	}
};

int main() {
	bitset<9> xBoard; // x board representation
	bitset<9> oBoard; // o board representation

	bitset<9> winBitMask[] { // wins
		// rows
		createMask(0, 1, 2),
		createMask(3, 4, 5),
		createMask(6, 7, 8),
		
		//columns
		createMask(0, 3, 6),
		createMask(1, 4, 7),
		createMask(2, 5, 8),

		// diag
		createMask(0, 4, 8),
		createMask(6, 4, 2),
	};

	char player = 'X';
	bool running = true;

	while(running) {
		draw(xBoard, oBoard);
		player_turn(&player, &xBoard, &oBoard);
		switch(logic(xBoard, oBoard, winBitMask)) {
			case 1:
				std::cout << "X wins!\n"; running = false;
				break;
			case -1:
				std::cout << "O wins!\n"; running = false;
				break;
			case 0:
				std::cout << "Draw!\n"; running = false;
				break;
		}
	}	
}
