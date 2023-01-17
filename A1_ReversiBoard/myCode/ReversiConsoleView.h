/*
 * ReversiConsoleView.h
 *
 *  Created on: 8 Nov 2021
 *      Author: JASON
 */

#ifndef REVERSICONSOLEVIEW_H_
#define REVERSICONSOLEVIEW_H_

/*
 * Standard (system) header files
 */
#include <iostream>
#include <stdlib.h>
/*
 * Function specific header file as required
 */
#include "ReversiBoard.h"

/**
 * \brief Class ReversiConsoleView
 */
class ReversiConsoleView
{
	/**
	 * \param m_ReversiBoardPtr	: A pointer to the class object of type 'ReversiBoard'.
	 */
	ReversiBoard* m_reversiBoardPtr;
public:
	/**
	 * \brief Parameterized Constructor
	 * \param reversiBoardPtr : A pointer argument type 'ReversiBoard'.
	 */
	ReversiConsoleView(ReversiBoard* reversiBoardPtr);
	/**
	 * \brief Destructor
	 */
	~ReversiConsoleView();
	/**
	 * \brief This method is used to display the Reversi Board with up-to-date player status and scores.
	 */
	void printReversiConsole();
};

#endif /* REVERSICONSOLEVIEW_H_ */
