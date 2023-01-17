/*
 * ReversiConsoleView.cpp
 *
 *  Created on: 8 Nov 2021
 *      Author: JASON
 */

/* Standard (system) header files */
#include <iostream>
#include <stdlib.h>

/* Function specific header file as required */
#include "ReversiConsoleView.h"

ReversiConsoleView::ReversiConsoleView(ReversiBoard* reversiBoardPtr)
{
	m_reversiBoardPtr = reversiBoardPtr;

	/*
	 * Print the initialized Reversi Board.
	 */
	printReversiConsole();
}

ReversiConsoleView::~ReversiConsoleView()
{

}

void ReversiConsoleView::printReversiConsole()
{

	std::cout << "-----------------------------------------------------------------" << std::endl;

	unsigned t_row = m_reversiBoardPtr->getRows();
	unsigned t_column = m_reversiBoardPtr->getColumns();
	/* Display indentation along the column for user-friendly input. */
	std::cout << "#\t";
	for(unsigned short col = 0; col < t_column; col++)
	{
		std::cout << col << "|\t";
	}
	std::cout << std::endl;
	/* Printing the board elements. */
	for (unsigned short row = 0; row < t_row; row++)
	{
		/* Display indentation along the row for user-friendly input. */
		std::cout << row << "|\t";
		for (unsigned short column = 0; column < t_column; column++)
		{
			int t_pos = m_reversiBoardPtr->boardIndexCalc(row, column);
			if(INVALID_INDEX != t_pos)
			{
				unsigned int t_FieldColor = m_reversiBoardPtr->getBoardElement(t_pos);
				switch(t_FieldColor)
				{
				case 0 :
					std::cout << "B";
					break;
				case 1 :
					std::cout << "W";
					break;
				case 2 :
					std::cout << "*";
					break;
				default:
					/*No default case exists. */
					std::cout << "Unexpected Error! No default case exists.";
					break;
				}
			}
			std::cout << "\t";
		}
		std::cout << std::endl;
	}

	if(GAMEOVER != m_reversiBoardPtr->getEndGameSt())
	{
	/*
	 * Information for the next move.
	 */
	std::cout << "-----------------------------------------------------------------" << std::endl;
	std::cout << "NEXT MOVE DETAILS" << std::endl;
	std::cout << "Next Move by Player	: " << m_reversiBoardPtr->getCurrPlayer() + 1 << std::endl;
	std::cout << "[Player 1 has coin B] [Player 2 has coin W]" << std::endl;
	/*
	 * Displaying updated player scores.
	 */
	std::cout << "-----------------------------------------------------------------" << std::endl;
	std::cout << "Player 1 Score : " << m_reversiBoardPtr->getTotalScore(0) << std::endl;
	std::cout << "Player 2 Score : " << m_reversiBoardPtr->getTotalScore(1) << std::endl;
	}
	else
	{
		std::cout << "-----------------------------------------------------------------" << std::endl;
		std::cout << "GAME OVER!" << std::endl;
		std::cout << "No further moves are available for both the players." << std::endl;
		std::cout << "Player 1 Score : " << m_reversiBoardPtr->getTotalScore(0) << std::endl;
		std::cout << "Player 2 Score : " << m_reversiBoardPtr->getTotalScore(1) << std::endl;
		if(m_reversiBoardPtr->getTotalScore(0) > m_reversiBoardPtr->getTotalScore(1))
			std::cout << "PLAYER 1 WINS!" <<std::endl;
		else if(m_reversiBoardPtr->getTotalScore(0) < m_reversiBoardPtr->getTotalScore(1))
			std::cout << "PLAYER 2 WINS!" <<std::endl;
		else
			std::cout << "DRAW!" <<std::endl;
		std::cout << "*****************************************************************" << std::endl;
		exit(EXIT_SUCCESS);
	}
}
