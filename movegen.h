#ifndef _MOVEGEN_H_
#define _MOVEGEN_H_

#include "reversi.h"

template <Color Us> ExtMove* generate(const Position& pos, ExtMove* moveList);

template <Color Us>
struct MoveList {

  explicit MoveList(const Position& pos) : last(generate<Us>(pos, moveList)) {}
  const ExtMove* begin() const { return moveList; }
  const ExtMove* end() const { return last; }
  size_t size() const { return last - moveList; }

private:
  ExtMove moveList[SQ_NB], *last;
};

#endif // _REVERSI_H_