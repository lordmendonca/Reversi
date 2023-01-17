/*
 * Standard (system) header files
 */
#include <iostream>
#include <stdlib.h>
/*
 * More standard header files as required
 */
#include <ctype.h>
/*
 * Project specific header files
 * */
#include "ReversiConsoleView.h"

typedef ReversiBoard ReversiBoard_t;
typedef ReversiConsoleView ReversiConsoleView_t;

/*
 * Main Program
 */
int main (void)
{
	/* Test for Reversi Board. */
	ReversiBoard_t RB;
	ReversiConsoleView_t RCV(&RB);
	unsigned int input_row{0}, input_column{0};
	while(1)
	{
		std::cout << "-----------------------------------------------------------------" << std::endl;
		std::cout << "Enter the ROW index on the Reversi Board	: ";
		std::cin >> input_row;
		std::cout << "Enter the COLUMN index on the Reversi Board	: ";
		std::cin >> input_column;
		std::cout << "-----------------------------------------------------------------" << std::endl;
		if((TERMINATEGAME == input_row) || (TERMINATEGAME == input_column))
		{
			std::cout << "Game terminated.";
			exit(EXIT_SUCCESS);
		}
		RB.queryBoard(input_row, input_column);
		RB.makeMove(input_row, input_column);
		RCV.printReversiConsole();
		std::cout << "If you wish to terminate the game, please enter ROW and/or COLUMN index as 9." << std::endl;
	}

	return 0;
}
