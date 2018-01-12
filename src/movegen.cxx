
#include "movegen.h"
#include "reversi.h"

template <Color Us> 
inline ExtMove* generate(const Position& pos, ExtMove* moveList) {

  Color opp = Us == BLACK ? WHITE 
                          : BLACK; 
  
  ExtMove move;
  Direct dir;
  Square s1, s2;
  int count;

  for (s1 = SQ_BEGIN; s1 <= SQ_END; ++s1) 
  {
    if (pos.piece_on(s1) == NONE) {
      move.init();
      for (int i = 0; i < (int)DIR_NB; ++i) {
        count = 0;
        dir = DirectTable[i];
        for (s2 = s1 + dir; pos.piece_on(s2) == opp; s2 += dir)
          ++count;

        if (count && pos.piece_on(s2) == Us) {
          move.sq = s1;
          move.count[i] = count;
        }
      }
      if (!move.empty()) 
        *moveList++ = move;
    }
  }

  return moveList;
}

template ExtMove* generate<BLACK>(const Position&, ExtMove*);
template ExtMove* generate<WHITE>(const Position&, ExtMove*);