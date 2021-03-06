/*
 * Volodya Mozhenkov (Almost University) 2017
 * Программа: 23 ФЕВРАЛЯ
 * http://www.almost-university.com/
 * GNU GPL v 3.0
 */

#ifndef CHESSENGINE__
#define CHESSENGINE__

#include "config.hpp"

#include "ChessBoard.hpp"
#include "ChessBoardAnalysis.hpp"
#include <list>
#include <functional>
#include <thread>

class ChessEngine;

class ChessEngineWorker
{
	friend class ChessEngine;
	
	typedef std::pair<double, ChessBoard::ptr> WeightBoardPair;
	
	bool pleaseStop; // request to stop received
	ChessBoard::ptr original;
	
	std::thread thread; // the thread that we run this worker in
	
	std::list<WeightBoardPair> positionPreferences;
	
	ChessEngineWorker();

	void stop();
	void startNextMoveCalculation(ChessBoard::ptr original, int startDepth); // this is what starts the thread
	void startNextMoveCalculationInternal(ChessBoard::ptr original, int startDepth); // this is what performs execution
	
	ChessBoardAnalysis::ptr calculation(ChessBoardAnalysis::ptr analysis, int depth,
		double alpha, double beta, ChessPlayerColour maximizingPlayer);
};
class ChessEngineWorkerInterruptedException
{};

class ChessEngine
{
	ChessBoard::ptr curPos;
	ChessEngineWorker worker;
	
	int START_DEPTH = 2;
public:
	void setCurPos(ChessBoard::ptr newPos);
	void makeMove(ChessBoard::ptr move);
	ChessBoard::ptr getCurPos() const;
	
	// TODO: implement calculation of the next move
	void startNextMoveCalculation();
	ChessBoard::ptr getNextBestMove();
	
	friend ChessEngineWorker;
};

#endif