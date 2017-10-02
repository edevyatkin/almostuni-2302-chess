/*
 * Volodya Mozhenkov (Almost University) 2017
 * Программа: 23 ФЕВРАЛЯ
 * http://www.almost-university.com/
 * GNU GPL v 3.0
 */

#include "ChessMove.hpp"

#include <cassert>
#include "Log.hpp"

ChessMove::ChessMove()
	: previous(false), to(nullptr), from(nullptr)
{}

bool ChessMove::isMovePossible() const
{
	return true;
/*	if(ChessBoard::ptr pTo = to.lock())
	{
		ChessPiece kingPiece;
		if(pTo->getTurn()==ChessPlayerColour::WHITE)
		{
			// if it's white to move, we are looking for a black king
			kingPiece = KING_BLACK;
		}
		else
		{
			kingPiece = KING_WHITE;
		}
		size_t king[2]={}; // TODO: change this monstrocity!!!!
		bool found=false;
		for(size_t rank=0; !found && rank<8; ++rank)
		{
			for(size_t file=0; file<8; ++file)
			{
				if(
					(pTo->getPiecePos(file, rank)==kingPiece)
				  )
				{
					found = true;
					king[0] = rank;
					king[1] = file;
					break;
				}
			}
		}
		auto possiblePieces = ChessBoard::possiblePieces;
		for(auto attackingPiece = possiblePieces->begin(); attackingPiece != possiblePieces->end(); ++attackingPiece)
		{
			if(*attackingPiece == EMPTY_CELL || getColour(*attackingPiece) == pTo->getTurn())
			{
				continue;
			}
			const MoveTemplate* takeMove = moveParameters.at(*attackingPiece)->takeMove;
			for(auto dir=takeMove->begin(); dir!=takeMove->end(); ++dir)
			{
				for(auto pos=dir->begin(); pos!=dir->end(); ++pos)
				{
					int rank = king[0] - pos->first;
					int file = king[1] - pos->second;
					if(rank < 0 || file < 0 || rank >= 8 || file >= 8 ) // TODO: change to board dimentions
					{
						break;
					}
					auto piece = pTo->getPiecePos(file, rank);
					
					if(piece==*attackingPiece)
					{
						return false;
					}

					if(piece!=EMPTY_CELL)
					{
						break;
					}
				}
			}
		}
		
		return true;
	}
	else
	{
		return false;
	}
	*/
}

bool ChessMove::hasPrevious() const
{
	return previous;
}

void ChessMove::setFrom(ChessBoard::ptr from_)
{
	from = from_;
}
void ChessMove::setTo(ChessBoard::ptr to_)
{
	to = to_;
	turn = !to_->getTurn();
}

ChessBoard::ptr ChessMove::getFrom() const
{
	return from;
}
ChessBoard::ptr ChessMove::getTo() const
{
	return to;
}
ChessPlayerColour ChessMove::getTurn() const
{
	return turn;
}
std::string ChessMove::getNotation() const
{
	std::string result ="";
	
	if(from)
	{
		ChessPiece piece;
		int rankFrom, rankTo;
		char fileFrom, fileTo;
		for(auto it=to->begin(), end=to->end(); it!=end; ++it)
		{
			auto pos = it.getPos();
			if(*it == from->getPiecePos(pos))
			{
				continue;
			}
			
			if(*it==EMPTY_CELL)
			{
				fileFrom = it.getFile();
				rankFrom = it.getRank();
				piece = from->getPiecePos(pos);
			}
			else
			{
				fileTo = it.getFile();
				rankTo = it.getRank();
			}
		}
		
		result = chessPieceStrings[piece] + " " +
			(char)fileFrom + std::to_string(rankFrom) + " " +
			(char)fileTo + std::to_string(rankTo);
	}
	return result;
}

void ChessMove::moveAttempts(
	const ChessMoveRecordingFunction &recFunTake,
	const ChessMoveRecordingFunction &recFunDefend,
	const ChessBoard &cb, const size_t pos,
	const MoveTemplate& mt,
	bool canTake, bool canMoveToEmpty)
{
	const size_t width = cb.getWidth();
	
	const size_t rank = pos / width;
	const size_t file = pos % width;
	
	size_t newPos;
	
	for(auto direction = mt.begin(), directionEnd=mt.end(); direction != directionEnd; ++direction)
	{
		for(auto attempt = direction->begin(), attemptEnd=direction->end(); attempt != attemptEnd; ++attempt)
		{
			const int& rankShift = attempt->second;
			const int& fileShift = attempt->first;
			
			size_t newFile = (int)file + fileShift;
			size_t newRank = (int)rank + rankShift;
			
			if( newFile >= width )
			{
				break;
			}
			
			newPos = cb.getPos(newFile, newRank);
			
			if( newPos >= cb.getCellCount() )
			{
				break;
			}
			
			if(!cb.isEmptyPos(newPos))
			{
				if(canTake)
				{
					
					if(getColour(cb.getPiecePos(newPos)) != cb.getTurn())
					{
						recFunTake(pos, newPos);
					}
					recFunDefend(pos, newPos);
				}
				break; // stop if a cell isn't empty
			}
			else // if empty
			{
				if(canMoveToEmpty)
				{
					recFunTake(pos, newPos);
				}
				recFunDefend(pos, newPos);
			}
		}
	}
}
