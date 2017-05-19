#ifndef CHESSFUNCTIONS__
#define CHESSFUNCTIONS__

#include <vector>
#include <functional>
#include "ChessBoard.hpp"
#include "moveTemplate.hpp"

namespace ChessFunctions
{
	typedef std::function<void(char, int, char, int, bool)> MoveRecordingFunction;
	void move(MoveRecordingFunction resFunction,
		const ChessBoard &cb, char file, int rank,
		const MoveTemplate& mt, bool canTake=true, bool canNotTake=true);

	bool ownPiece(ChessPiece cp, PlayerColour turn);
	int countPieces(/*const*/ ChessBoard &cb, std::function<bool(ChessPiece)> test);
	int countPieces(/*const*/ ChessBoard &cb, ChessPiece cp);
};

#endif