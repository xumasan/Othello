#include <sstream>

#include "reversi.h"

const Direct DirectTable[8] = {
  UP, DN, RT, LT, UR, DR, UL, DL
};


namespace {

const std::string PieceToChar(" +-x");

}

std::ostream& operator<<(std::ostream& os, const Position& pos) {

#ifdef B44
  os << "\n +---+---+---+---+\n";
#else
  os << "\n +---+---+---+---+---+---+\n";
#endif

  for (Rank r = RANK_1; r < RANK_NB; ++r)
  {
    for (File f = FILE_A; f < FILE_NB; ++f)
      os << " | " << PieceToChar[pos.piece_on(make_square(f, r))];

    os << " | ";
#ifdef B44
      os << "\n +---+---+---+---+\n";
#else
      os << "\n +---+---+---+---+---+---+\n";
#endif
  }

  return os;
}

void Position::init() {
  gamePly = 0;
  sideToMove = BLACK;
  std::fill_n(board_, SQ_NB, WALL); 
  for (Rank r = RANK_1; r < RANK_NB; ++r)
   for (File f = FILE_A; f < FILE_NB; ++f)
     board_[make_square(f, r)] = NONE;

#ifdef B44
  board_[SQ_B2] = board_[SQ_C3] = WHITE;
  board_[SQ_B3] = board_[SQ_C2] = BLACK;
#else
  board_[SQ_C3] = board_[SQ_D4] = WHITE;
  board_[SQ_C4] = board_[SQ_D3] = BLACK;
#endif
}

