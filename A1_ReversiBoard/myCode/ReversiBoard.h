/*
 * ReversiBoard.h
 *
 *  Created on: 2 Nov 2021
 *      Author: JASON
 */

#ifndef REVERSIBOARD_H_
#define REVERSIBOARD_H_
/*
 * Standard (system) header files
 */
#include <iostream>
#include <stdlib.h>

/**
 * \brief Pre-processor value of the board.
 * \details EIGHT			: Eight directions of validity check exist for any coin on the board.
 */
#define EIGHT 8
/**
 * \brief Pre-processor value of the board.
 * \details REVERSI_ROWS	: Reversi Board has 8 rows..
 */
#define REVERSI_ROWS EIGHT
/**
 * \brief Pre-processor value of the board.
 * \details REVERSI_COLUMNS	: Reversi Board has 8 columns.
 */
#define REVERSI_COLUMNS REVERSI_ROWS
/**
 * \brief Pre-processor value of the board.
 * \details REVERSI_SIZE	: Size of the Reversi Board (Size : 64).
 */
#define REVERSI_SIZE REVERSI_ROWS*REVERSI_COLUMNS
/**
 * \brief Pre-processor value of the board.
 * \details NO_OF_PLAYERS	: Two players at a time.
 */
#define NO_OF_PLAYERS	2
/**
 * \brief Describes the field elements of the board.
 * \details BLACK			: Player 1 is given a coin of color 'BLACK' and value for display as '0'
 * \details WHITE			: Player 2 is given a coin of color 'WHITE' and value for display as '1'
 * \details EMPTY_FIELD		: An empty field is given a value of and displayed as '2'
 */
typedef enum {BLACK = 0 /**< 0 */, WHITE = 1 /**< 1 */, EMPTY_FIELD = 2 /**< 2 */} boardElement_t;
/**
 * \brief To calculate and indicate if the move made is within the board dimensions.
 * \details INVALID_INDEX	: To indicate that the move made is outside the board dimensions.
 * \details VALID_INDEX		: To indicate that the move made is within the board dimensions.
 */
typedef enum {INVALID_INDEX = -1 /**< -1 */, VALID_INDEX = 0 /**< 0 */} indexCalc_t;
/**
 * \brief To evaluate if the player has any valid moves remaining on the board.
 * \details INVALID_MOVE			: Valid moves do not exist for the player at current state of the board.
 * \details VALID_MOVE			: Valid moves do exist for the player at current state of the board.
 */
typedef enum {INVALID_MOVE = 0 /**< 0 */, VALID_MOVE = 1 /**< 1 */} validMove_t;
/**
 * \brief To represent the state of the GAME
 * \details GAMECONTINUE	: Used to continue the game if only one of the two players has no valid moves.
 * \details GAMEOVER		: Used to terminate the game when no further moves are possible.
 * \details TERMINATEGAME	: Used to end the game at any point of time.
 */
typedef enum {GAMECONTINUE = 1 /**< 1 */, GAMEOVER = 2 /**< 2 */, TERMINATEGAME = 9 /**< 9 */} gameSt_t;
/**
 * \brief Class ReversiBoard
 */
class ReversiBoard
{
	/**
	 * \param m_rows		: Number of rows in a board.
	 */
	unsigned short m_rows;
	/**
	 * \param m_columns		: Number of columns in a board.
	 */
	unsigned short m_columns;
	/**
	 * \param m_currPlayer	: The current player to make the move on the board. [0 = BLACK coin], [1 = WHITE coin].
	 */
	unsigned short m_currPlayer;
	/**
	 * \param m_totalScore	: Counts the total score of each of the two players in the game.
	 */
	unsigned short m_totalScore[NO_OF_PLAYERS];
	/**
	 * \param m_endGameSt	: Status variable used to represent end of the game when it reaches a value equal to @enumerator parameter ENDGAME (= 2).
	 */
	unsigned short m_endGameSt;
    /**
     * \param m_moveValidSt	: Holds the 8 validity status w.r.t. placement of a coin in directions indicated as below :
     * {LEFT, RIGHT, UPPPER, DOWNWARDS, DIAGONAL UPPER-LEFT, DIAGONAL UPPER-RIGHT, DIAGONAL DOWNWARDS-LEFT, DIAGONAL DOWNWARDS-RIGHT}
     */
	unsigned short m_moveValidSt[EIGHT];
	/**
	 * \param	m_boardElement	: An integer pointer that points to the individual position of the
	 * Reversi Board having 64 elements.
	 */
	unsigned short* m_boardElement;
	/**
	 * \brief Helper Function : This method validates the current move made by the player by considering
	 * the rules of the Reversi game. Its returns a 0 if move is invalid or 1 if valid.
	 * \return Return if the current player input on the board is valid [VALID_MOVE] or not [INVALID_MOVE].
	 */
	int validMove(unsigned short row, unsigned short col);
	/**
	 * \brief Helper Function : This method is used to update the Reversi Board if the move made is valid and bound within the board and the board rules.
	 * This function is also responsible for flipping of the coins when a move made is valid and successful.
	 */
	void updateMove(unsigned short row, unsigned short column);
	/**
	 * \brief Helper Function : Determines if the next player in turn has at least one valid move at his turn. 
	 * \return unsigned short : VALID_MOVE (= 1) if it has valid moves else INVALID_MOVE (= 0)
	 */
	unsigned short availableMoves();
public:
	/**
	 * \brief Constructor
	 */
	ReversiBoard();
	/**
	 * \brief Destructor
	 */
	~ReversiBoard();
	/**
	 * \brief Set Function : This method is used to initialize/set the class member 'm_MoveValidSt' of type integer array.
	 */
	void setMoveValidSt(unsigned int value);
	/**
	 * \brief Get Function : To get the number of rows on the board.
	 * \return unsigned int : Value of rows on the board.
	 */
	unsigned short getRows() const;
	/**
	 * \brief Get Function : To get the number of columns on the board.
	 * \return unsigned int : Value of columns on the board.
	 */
	unsigned short getColumns() const;
	/**
	 * \brief Get Function : To get the information on the current player.
	 * \return unsigned short : Current player on the board. [0 = BLACK coin = Player 1], [1 = WHITE coin = Player 2].
	 */
	unsigned short getCurrPlayer() const;
	/**
	 * \brief Get Function : To get the state of the board element at given position.
	 * \param [in] position : Calculated position on the board.
	 * \return unsigned short : Board element at the given position.
	 */
	unsigned short getBoardElement(unsigned short position) const;
	/**
	 * \brief Get Function : To get the score of any player indexed by 'playerIndex'.
	 * \param [in] playerIndex : Index to one of the two players.
	 * \return unsigned short : Score of the played indexed by 'playerIndex'.
	 */
	unsigned short getTotalScore(unsigned short playerIndex) const;
	/**
	 * \brief Get Function : To get the state of the game.
	 * \return unsigned short : Returns a value that represents the state of the game [GAMECONTINUE = 1, GAMEOVER = 2].
	 */
	unsigned short getEndGameSt() const;
	/**
	 * \brief It responds to the query of coin element placed at requested position of on the board and prints the same.
	 * \param [in] row : user row index.
	 * \param [in] column : user column index.
	 */
	void queryBoard(unsigned short row, unsigned short column);
	/**
	 * \brief Helper Function : This method takes user provided parameters for a co-ordinate in terms of a 'row' and a 'column' and calculates the position of the placement of coin at current move.
	 * \param [in] row : user row index.
	 * \param [in] column : user column index.
	 * \return int : It either returns 'INVALID_INDEX' or calculated coin position on the board.
	 */
	int boardIndexCalc(unsigned short row, unsigned short column);
	/**
	 * \brief This method performs placement of the coin by taking player request and updates the move only if the move is valid.
	 * \param [in] row : user row index.
	 * \param [in] column : user column index.
	 */
	void makeMove(unsigned short row, unsigned short column);
};

#endif /* REVERSIBOARD_H_ */
