/*
 * Volodya Mozhenkov (Almost University) 2017
 * Программа: 23 ФЕВРАЛЯ
 * http://www.almost-university.com/
 * GNU GPL v 3.0
 */

#ifndef CHESSMOVE__
#define CHESSMOVE__

#include "config.hpp"

#include "ChessBoard.hpp"
#include "ChessPlayerColour.hpp"
#include "moveTemplate.hpp"
#include <string>
#include <functional>


class ChessMove;

class ChessMove
{
public:
	typedef std::shared_ptr<ChessMove> ptr;

private:
	bool previous;
	ChessBoard::ptr from;
	ChessBoard::wptr to;
	
	//std::string notation;
	int moveNum;
	ChessMove(); // for initialisation in the factory

public:
	bool isMovePossible() const;
	bool hasPrevious() const;
	
	ChessBoard::ptr getFrom() const;
	ChessBoard::ptr getTo() const;
	ChessPlayerColour getTurn() const;
	std::string getNotation() const;
	
	friend class ChessBoardFactory;

	typedef std::function<void(size_t, size_t)> ChessMoveRecordingFunction;
	static void moveAttempts(
		const ChessMoveRecordingFunction &recFunTake,
		const ChessMoveRecordingFunction &recFunDefend,
		const ChessBoard &cb, size_t pos,
		const MoveTemplate& mt,
		bool canTake=true, bool canMoveToEmpty=true);

};



#endif