/*
 * Volodya Mozhenkov (Almost University) 2017
 * Программа: 23 ФЕВРАЛЯ
 * http://www.almost-university.com/
 * GNU GPL v 3.0
 */

#include "ChessMove.hpp"

ChessMove::ChessMove()
{}

ChessMove::ChessMove(
	ChessBoard::ptr from_, char fileFrom, int rankFrom, char fileTo, int rankTo)
{
	to = ChessBoard::ptr(*from_);
	
	to->placePiece(fileTo, rankTo, from_->getPiece(fileFrom, rankFrom));
	to->placePiece(fileFrom, rankFrom, ' ');
	
	to->turn = (from->turn_==WHITE) ? BLACK : WHITE;
	to->from = *this;
}

bool ChessMove::isMovePossible() const
{
	int king[2]={};
	bool found=false;
	for(int rank=0; !found && rank<8; ++rank)
	{
		for(int file=0; file<8; ++file)
		{
			// if it's white to move, we are looking for a black king
			if(
				(to->getPiece(file+'A', rank+1)=='K' && to->getTurn()==BLACK) || 
				(to->getPiece(file+'A', rank+1)=='k' && to->getTurn()==WHITE)
			  )
			{
				found = true;
				king[0] = rank;
				king[1] = file;
				break;
			}
		}
	}

	if(to->getTurn()==BLACK)
	{
		// checking pawns
		for(auto dir=pawnBlackMoveTake.begin(); dir!=pawnBlackMoveTake.end(); ++dir)
		{
			for(auto pos=dir->begin(); pos!=dir->end(); ++pos)
			{
				auto piece = to->getPiece(king[1]-pos->second+'A', king[0]-pos->first+1);
				if(piece=='p')
				{
					return false;
				}
				else if(piece!=' ')
				{
					break;
				}
			}
		}
		// checking queen
		for(auto dir=queenMove.begin(); dir!=queenMove.end(); ++dir)
		{
			for(auto pos=dir->begin(); pos!=dir->end(); ++pos)
			{
				auto piece = to->getPiece(king[1]-pos->second+'A', king[0]-pos->first+1);
				if(piece=='q')
				{
					return false;
				}
				else if(piece!=' ')
				{
					break;
				}
			}
		}
	}
	
	return true;
}

bool ChessMove::hasPrevious() const
{
	return from;
}
ChessBoard::ptr ChessMove::getFrom() const
{
	return from;
}
ChessBoard::ptr ChessMove::getTo() const
{
	return to;
}
PlayerColour ChessMove::getTurn() const
{
	return !to->getTurn();
}