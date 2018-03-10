# ConnectFour
Connect four game written in C++ with Qt dependencies.

A player uses a mouse to control the game by selecting columns and plays against an AI.

The AI uses a recursive negamax algorithm (AI/AIController.cpp) to evaluate all possible subsequent moves after each move by the human player,
it will then choose the best next move based on a scoring criteria.

Efficiency improvements were made to the AI algorithm including a bitboard (AI/BitBoard.cpp) and caching (AI/TranspositionTable.cpp) so that 
the human player doesn't have to wait too long for the AI to take a turn.
