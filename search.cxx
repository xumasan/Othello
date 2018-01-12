#include <iostream>
#include "reversi.h"
#include "movegen.h"

namespace {
  template<Color Us> Value eval(Position& pos) {

    int bCount = 0, wCount = 0;
    Color pc;
    for (Rank r = RANK_1; r < RANK_NB; ++r)
      for (File f = FILE_A; f < FILE_NB; ++f) {
        pc = pos.piece_on(make_square(f, r));
        if (pc == BLACK)
          bCount++;
        else if (pc == WHITE)
          wCount++;
      }

    return Us == BLACK ? Value(bCount - wCount)
                       : Value(wCount - bCount);
  }

  inline bool is_end(Position& pos) {

    auto moveList1 = MoveList<BLACK>(pos);
    auto moveList2 = MoveList<WHITE>(pos);
    
    return moveList1.size() == 0 && moveList2.size() == 0;
  }

  Depth new_depth(Depth d) {
      return Depth(d - 1); 
  }
}

template <Color Us>
Value search(Position& pos, Depth depth) {

  if (/*depth == DEPTH_ZERO ||*/ is_end(pos)) 
    return eval<Us>(pos);

  Value val;
  Value best = -VALUE_INFINITE;

  auto moveList = MoveList<Us>(pos);

  if (moveList.size() == 0) {

    return Us == BLACK ? -search<WHITE>(pos, new_depth(depth))
                       : -search<BLACK>(pos, new_depth(depth));
  }

  for (ExtMove move : moveList) {

    pos.move<Us, true>(move);
    
    val = Us == BLACK ? -search<WHITE>(pos, new_depth(depth))
                      : -search<BLACK>(pos, new_depth(depth));

    pos.move<Us, false>(move);

    if (best < val) 
      best = val;
  }

  return best;
}

void id_loop(Position& pos) {
  
  for (Depth d = ONE_PLY; ; ++d) {
    Value val = pos.side_to_move() == BLACK ? search<BLACK>(pos, d)
                                            : search<WHITE>(pos, d);

    std::cout << "Depth : " << (int)d << " Value : " << val << std::endl;
  }
}

void perfect_search(Position& pos) {

  std::cout << "Turn : ";
  pos.side_to_move() ? std::cout << "BLACK" 
                     : std::cout << "WHITE";
  std::cout << std::endl;
  Value val = pos.side_to_move() == BLACK ? search<BLACK>(pos, Depth(SQ_NB))
                                          : search<WHITE>(pos, Depth(SQ_NB));
  
  std::cout << "Value : " << val << std::endl;
}