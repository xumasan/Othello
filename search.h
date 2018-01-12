#ifndef _SEARCH_H_
#define _SEARCH_H_

#include "reversi.h"

template <Color Us, bool Passed> Value search(Position& pos, Depth depth);
void id_loop(Position& pos);
void perfect_search(Position& pos);
#endif // _SEARCH_H_