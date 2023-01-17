/*
 * ReversiBoard.cpp
 *
 *  Created on: 2 Nov 2021
 *      Author: JASON
 */

/* Standard (system) header files */
#include <iostream>
#include <stdlib.h>

/* Function specific header file as required */
#include "ReversiBoard.h"

ReversiBoard::ReversiBoard()
{
	/*
	 * Initialization of number of rows and columns to the standard size of 8 each.
	 */
	m_rows = REVERSI_ROWS;
	m_columns = REVERSI_COLUMNS;
	/*
	 * Initialization of array of Valid States to 0.
	 */
	setMoveValidSt(0);
	/*
	 * All the elements of the Reversi Board are initialized to an empty field, represented by the value 2.
	 */
	m_boardElement = new unsigned short [REVERSI_SIZE];
	for(unsigned short index = 0; index < REVERSI_SIZE; index++)
	{
		m_boardElement[index] = EMPTY_FIELD;
	}
	/*
	 * Start the game with the Player A owning coin 0.
	 */
	m_currPlayer = BLACK;
	/*
	 * Initialization of the center of the board with 2 of each coins.
	 */
	updateMove(3,3);
	m_currPlayer = WHITE;
	updateMove(3,4);
	m_currPlayer = BLACK;
	updateMove(4,4);
	m_currPlayer = WHITE;
	updateMove(4,3);
	/* Initialization for the next move to be made by Player A. */
	m_currPlayer = BLACK;

	/*
	 * Initialization of the Total Score of each of the players to 2 as two of their coins are
	 * initialized on the board.
	 */
	m_totalScore[0] = 2;
	m_totalScore[1] = 2;

	m_endGameSt = 0;
}

ReversiBoard::~ReversiBoard()
{
	delete [] m_boardElement;
}

void ReversiBoard::setMoveValidSt(unsigned int Value)
{
	for(unsigned short index = Value; index < REVERSI_ROWS; index++)
	{
		m_moveValidSt[index] = Value;
	}
}

unsigned short ReversiBoard::getRows() const
{
	return m_rows;
}

unsigned short ReversiBoard::getColumns() const
{
	return m_columns;
}

unsigned short ReversiBoard::getCurrPlayer() const
{
	return m_currPlayer;
}
unsigned short ReversiBoard::getBoardElement(unsigned short position) const
{
	return m_boardElement[position];
}
unsigned short ReversiBoard::getTotalScore(unsigned short PlayerIndex) const
{
	return m_totalScore[PlayerIndex];
}
unsigned short ReversiBoard::getEndGameSt() const
{
	return m_endGameSt;
}

int ReversiBoard::boardIndexCalc(unsigned short row, unsigned short column)
{
	/*	To check if player input parameters are outside board dimensions.	 */
	if (row >= getRows() || column >= getColumns())
	{
		return INVALID_INDEX;
	}
	/* To check if calculated coin position is outside the scope of the board dimensions. */
	else if(row < 0 || column < 0)
	{
		return INVALID_INDEX;
	}
	/* Calculation of coin position on the board. */
	else
	{
		unsigned short t_pos = (row * getColumns()) + column;
		return t_pos;
	}
}

int ReversiBoard::validMove(unsigned short row, unsigned short col)
{
	/* To check if player input is not in an already placed coin position. */
	if (EMPTY_FIELD != this->m_boardElement[boardIndexCalc(row,col)])
	{
		std::cout << "Invalid Move! Field is not empty." << std::endl;
		return 0;
	}
	/*
	 * t_oppPlayer : Identifies the opponent player at a particular move.
	 */
    int t_oppPlayer = (m_currPlayer + 1) % 2;
    /*
     * t_row : A temporary variable that holds the concurrent row value at a calculation.
     * t_col : A temporary variable that holds the concurrent column value at a calculation.
     * t_pos : A temporary variable that holds the concurrent position value at after the board index calculation.
     */
    int t_row{0}, t_col{0}, t_pos{0};
    /*
     * Reset of valid move state, represented by @attribute m_MoveValidSt, to zero before the
     * current calcultaion begins.
     */
    setMoveValidSt(0);

    /* Begin validation of the move */

    /*
     * Validating the move along LEFT direction.
     */
    t_row = row;
    t_col = col - 1;
    t_pos = boardIndexCalc(t_row, t_col);
    if(this->m_boardElement[t_pos] != m_currPlayer)
    {
    	while ((INVALID_INDEX != t_pos) && (t_oppPlayer == this->m_boardElement[t_pos]))
    	{
    		t_col--;
    		t_pos = boardIndexCalc(t_row, t_col);
    	}

    	if ((INVALID_INDEX != t_pos) && (m_currPlayer == this->m_boardElement[t_pos]))
    	{
    		m_moveValidSt[0] = 1;
    	}
    }
    /*
     * Validating the move along RIGHT direction.
     */
    t_row = row;
    t_col = col + 1;
    t_pos = boardIndexCalc(t_row, t_col);

    if(this->m_boardElement[t_pos] != m_currPlayer)
    {
    	while ((INVALID_INDEX != t_pos) && (t_oppPlayer == this->m_boardElement[t_pos]))
    	{
    		t_col++;
    		t_pos = boardIndexCalc(t_row, t_col);
    	}

    	if ((INVALID_INDEX != t_pos) && (m_currPlayer == this->m_boardElement[t_pos]))
    	{
    		m_moveValidSt[1] = 1;
    	}
    }
    /*
     * Validating the move along UPPER direction.
     */
    t_row = row - 1;
    t_col = col;
    t_pos = boardIndexCalc(t_row, t_col);
    if(this->m_boardElement[t_pos] != m_currPlayer)
    {
    	while ((INVALID_INDEX != t_pos) && (t_oppPlayer == this->m_boardElement[t_pos]))
    	{
    		t_row--;
    		t_pos = boardIndexCalc(t_row, t_col);
    	}

    	if ((INVALID_INDEX != t_pos) && (m_currPlayer == this->m_boardElement[t_pos]))
    	{
    		m_moveValidSt[2] = 1;
    	}
    }
    /*
     * Validating the move along DOWNWARDS direction.
     */
    t_row = row + 1;
    t_col = col;
    t_pos = boardIndexCalc(t_row, t_col);
    if(this->m_boardElement[t_pos] != m_currPlayer)
    {
    	while ((INVALID_INDEX != t_pos) && (t_oppPlayer == this->m_boardElement[t_pos]))
    	{
    		t_row++;
    		t_pos = boardIndexCalc(t_row, t_col);
    	}

    	if ((INVALID_INDEX != t_pos) && (m_currPlayer == this->m_boardElement[t_pos]))
    	{
    		m_moveValidSt[3] = 1;
    	}
    }
    /*
     * Validating the move along DIAGONAL UPPER-LEFT direction.
     */
    t_row = row - 1;
    t_col = col - 1;
    t_pos = boardIndexCalc(t_row, t_col);
    if(this->m_boardElement[t_pos] != m_currPlayer)
    {
    	while ((INVALID_INDEX != t_pos) && (t_oppPlayer == this->m_boardElement[t_pos]))
    	{
    		t_row--;
    		t_col--;
    		t_pos = boardIndexCalc(t_row, t_col);
    	}

    	if ((INVALID_INDEX != t_pos) && (m_currPlayer == this->m_boardElement[t_pos]))
    	{
    		m_moveValidSt[4] = 1;
    	}
    }
    /*
     * Validating the move along DIAGONAL UPPER-RIGHT direction.
     */
    t_row = row - 1;
    t_col = col + 1;
    t_pos = boardIndexCalc(t_row, t_col);
    if(this->m_boardElement[t_pos] != m_currPlayer)
    {
    	while ((INVALID_INDEX != t_pos) && (t_oppPlayer == this->m_boardElement[t_pos]))
    	{
    		t_row--;
    		t_col++;
    		t_pos = boardIndexCalc(t_row, t_col);
    	}

    	if ((INVALID_INDEX != t_pos) && (m_currPlayer == this->m_boardElement[t_pos]))
    	{
    		m_moveValidSt[5] = 1;
    	}
    }
    /*
     * Validating the move along DIAGONAL DOWNWARDS-LEFT direction.
     */
    t_row = row + 1;
    t_col = col - 1;
    t_pos = boardIndexCalc(t_row, t_col);
    if(this->m_boardElement[t_pos] != m_currPlayer)
    {
    	while ((INVALID_INDEX != t_pos) && (t_oppPlayer == this->m_boardElement[t_pos]))
    	{
    		t_row++;
    		t_col--;
    		t_pos = boardIndexCalc(t_row, t_col);
    	}

    	if ((INVALID_INDEX != t_pos) && (m_currPlayer == this->m_boardElement[t_pos]))
    	{
    		m_moveValidSt[6] = 1;
    	}
    }
    /*
     * Validating the move along DIAGONAL DOWNWARDS-RIGHT direction..
     */
    t_row = row + 1;
    t_col = col + 1;
    t_pos = boardIndexCalc(t_row, t_col);
    if(this->m_boardElement[t_pos] != m_currPlayer)
    {
    	while ((INVALID_INDEX != t_pos) && (t_oppPlayer == this->m_boardElement[t_pos]))
    	{
    		t_row++;
    		t_col++;
    		t_pos = boardIndexCalc(t_row, t_col);
    	}

    	if ((INVALID_INDEX != t_pos) && (m_currPlayer == this->m_boardElement[t_pos]))
    	{
    		m_moveValidSt[7] = 1;
    	}
    }

    /* End validation of the move */

    /*
     * t_movevalidst : Temporary variable  is calculated such that it evaluates a '1' if the move input by the player is valid along at least one direction.
	 * It therefore represents the valid move status and returns the same from the method.
     */

    unsigned short t_movevalidst = 0;
    for(unsigned short index = 0; index < 8; index++)
    {
    	t_movevalidst |= m_moveValidSt[index];
    }

    return t_movevalidst;
}

void ReversiBoard::updateMove(unsigned short row, unsigned short column)
{
	/*
	 * t_pos : A temporary variable that holds the concurrent position value at after the board index calculation.
	 */
	int t_pos = boardIndexCalc(row, column);
	/* Updates the valid user move with the user-specific element. */
	this->m_boardElement[t_pos] = m_currPlayer;
	m_totalScore[m_currPlayer]++;
	/*
	 * t_row : A temporary variable that holds the concurrent row value at a calculation.
	 * t_col : A temporary variable that holds the concurrent column value at a calculation.
	 */
	int t_row{0}, t_col{0};
	/*
	 * t_oppPlayer : Identifies the opponent player at a particular move.
	 */
	int t_oppPlayer = (m_currPlayer + 1) % 2;

	for(unsigned short index = 0; index < 8; index++)
	{
		if(1 == m_moveValidSt[index])
		{
			switch(index)
			{
			case 0 : /* Flip coins along LEFT direction. */
				t_row = row;
				t_col = column - 1;
				t_pos = boardIndexCalc(t_row, t_col);
				while (t_oppPlayer == this->m_boardElement[t_pos])
				{
					this->m_boardElement[t_pos] = m_currPlayer;
					/* Update the total score of both the players based on the flip. */
					m_totalScore[m_currPlayer]++;
					m_totalScore[t_oppPlayer]--;
					t_col--;
					t_pos = boardIndexCalc(t_row, t_col);
				}
				break;
			case 1 : /* Flip coins along RIGHT direction. */
				t_row = row;
				t_col = column + 1;
				t_pos = boardIndexCalc(t_row, t_col);
				while (t_oppPlayer == this->m_boardElement[t_pos])
				{
					this->m_boardElement[t_pos] = m_currPlayer;
					/* Update the total score of both the players based on the flip. */
					m_totalScore[m_currPlayer]++;
					m_totalScore[t_oppPlayer]--;
					t_col++;
					t_pos = boardIndexCalc(t_row, t_col);
				}
				break;
			case 2 :  /* Flip coins along UPPER direction. */
				t_row = row - 1;
				t_col = column;
				t_pos = boardIndexCalc(t_row, t_col);
				while (t_oppPlayer == this->m_boardElement[t_pos])
				{
					this->m_boardElement[t_pos] = m_currPlayer;
					/* Update the total score of both the players based on the flip. */
					m_totalScore[m_currPlayer]++;
					m_totalScore[t_oppPlayer]--;
					t_row--;
					t_pos = boardIndexCalc(t_row, t_col);
				}
				break;
			case 3 :  /* Flip coins along DOWNWARDS direction. */
				t_row = row + 1;
				t_col = column;
				t_pos = boardIndexCalc(t_row, t_col);
				while (t_oppPlayer == this->m_boardElement[t_pos])
				{
					this->m_boardElement[t_pos] = m_currPlayer;
					/* Update the total score of both the players based on the flip. */
					m_totalScore[m_currPlayer]++;
					m_totalScore[t_oppPlayer]--;
					t_row++;
					t_pos = boardIndexCalc(t_row, t_col);
				}
				break;
			case 4 :  /* Flip coins along DIAGONAL UPPER-LEFT direction. */
				t_row = row - 1;
				t_col = column - 1;
				t_pos = boardIndexCalc(t_row, t_col);
				while (t_oppPlayer == this->m_boardElement[t_pos])
				{
					this->m_boardElement[t_pos] = m_currPlayer;
					/* Update the total score of both the players based on the flip. */
					m_totalScore[m_currPlayer]++;
					m_totalScore[t_oppPlayer]--;
					t_row--;
					t_col--;
					t_pos = boardIndexCalc(t_row, t_col);
				}
				break;
			case 5 :  /* Flip coins along DIAGONAL UPPER-RIGHT direction. */
				t_row = row - 1;
				t_col = column + 1;
				t_pos = boardIndexCalc(t_row, t_col);
				while (t_oppPlayer == this->m_boardElement[t_pos])
				{
					this->m_boardElement[t_pos] = m_currPlayer;
					/* Update the total score of both the players based on the flip. */
					m_totalScore[m_currPlayer]++;
					m_totalScore[t_oppPlayer]--;
					t_row--;
					t_col++;
					t_pos = boardIndexCalc(t_row, t_col);
				}
				break;
			case 6 :  /* Flip coins along DIAGONAL DOWNWARDS-LEFT direction. */
				t_row = row + 1;
				t_col = column - 1;
				t_pos = boardIndexCalc(t_row, t_col);
				while (t_oppPlayer == this->m_boardElement[t_pos])
				{
					this->m_boardElement[t_pos] = m_currPlayer;
					/* Update the total score of both the players based on the flip. */
					m_totalScore[m_currPlayer]++;
					m_totalScore[t_oppPlayer]--;
					t_row++;
					t_col--;
					t_pos = boardIndexCalc(t_row, t_col);
				}
				break;
			case 7 :  /* Flip coins along DIAGONAL DOWNWARDS-RIGHT direction. */
				t_row = row + 1;
				t_col = column + 1;
				t_pos = boardIndexCalc(t_row, t_col);
				while (t_oppPlayer == this->m_boardElement[t_pos])
				{
					this->m_boardElement[t_pos] = m_currPlayer;
					/* Update the total score of both the players based on the flip. */
					m_totalScore[m_currPlayer]++;
					m_totalScore[t_oppPlayer]--;
					t_row++;
					t_col++;
					t_pos = boardIndexCalc(t_row, t_col);
				}
				break;
			default	: /* No default case applicable. */
				std::cout << "Unexpected Error! No default case applicable." << std::endl;
				break;
			}
		}
	}
}

unsigned short ReversiBoard::availableMoves()
{
	for(unsigned int i = 0; i < getRows(); i++)
	{
		for(unsigned int j = 0; j < getColumns(); j++)
		{
			unsigned int t_pos = boardIndexCalc(i, j);
			if(EMPTY_FIELD == m_boardElement[t_pos])
			{
				if(VALID_MOVE == validMove(i, j))
				{
					return	VALID_MOVE;
				}
			}
		}
	}
	return INVALID_MOVE;
}

void ReversiBoard::queryBoard(unsigned short row, unsigned short column)
{
	std::cout << "*****************************************************************" << std::endl;
	std::cout << "CURRENT MOVE QUERY" << std::endl;
	/*
	 * t_pos : A temporary variable that holds the concurrent position value at an after the board index calculation.
	 */
	int t_pos = boardIndexCalc(row, column);
	/*
	 * To check if user-requested index is valid and
	 */
	if(INVALID_INDEX != t_pos)
	{
		int t_pos = boardIndexCalc(row, column);
		if(INVALID_INDEX != t_pos)
		{
			unsigned int t_fieldElement = m_boardElement[t_pos];
			unsigned char t_fieldColor;
			switch(t_fieldElement)
			{
			case 0 :
					t_fieldColor = 'B';
					break;
			case 1 :
					t_fieldColor = 'W';
					break;
			case 2 :
					t_fieldColor =  '*';
					break;
			default:
					/*No default case exists. */
					std::cout << "Unexpected Error! No default case exists.";
					break;
			}
		std::cout << "Coin '" << t_fieldColor << "' was placed at position ("
				<< row << "," << column <<")." << std::endl;
		}
	}
	else
	{
		std::cout << "Incorrect position query! at ("<< row << "," << column <<")." << std::endl;
	}
}

void ReversiBoard::makeMove(unsigned short row, unsigned short column)
{
	/* To check if the position index based on user-input is within the board dimensions. */
	if(INVALID_INDEX != boardIndexCalc(row, column))
	{
		/* To check the validity of the move requested by the user. */
		if(1 ==  validMove(row, column))
		{
			/* Update the board with user-specific symbol if the move is valid. */
			updateMove(row, column);
			/* Update the Current Player for the next move. */
			m_currPlayer = (m_currPlayer + 1) % 2;
		}
		else
		{
			std::cout << "----------------------------------------------------------" << std::endl;
			std::cout << "Incorrect move!" << std::endl;
			std::cout << "Player	: " << m_currPlayer + 1 << " plays again." << std::endl;
			std::cout << "----------------------------------------------------------" << std::endl;
		}
	}
	else
	{
		std::cout << "Entered coin position is outside the scope of the board dimensions." << std::endl;
	}

	for(unsigned int t_playerindex = 0; t_playerindex < 2; t_playerindex++)
	{
		if(VALID_MOVE != availableMoves())
		{
			m_endGameSt++;
			m_currPlayer = (m_currPlayer + 1) % 2;
		}
	}

	/* Continue the game if only one of the two players has invalid moves. */
	if(GAMECONTINUE == m_endGameSt)
		m_endGameSt = 0;

}
