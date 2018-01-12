#ifndef _REVERSI_H_
#define _REVERSI_H_

#include <string>
#include <cassert>
#include <algorithm>

#define B44

enum Color {
  NONE, BLACK, WHITE, WALL, COLOR_NB
};

#ifdef B44
// todo : WALL など無駄が多いので要修正
enum Square {
  WALL01, WALL02, WALL03, WALL04, WALL05, WALL06,
  WALL07,  SQ_A1,  SQ_B1,  SQ_C1,  SQ_D1, WALL08,
  WALL09,  SQ_A2,  SQ_B2,  SQ_C2,  SQ_D2, WALL10,
  WALL11,  SQ_A3,  SQ_B3,  SQ_C3,  SQ_D3, WALL12,
  WALL13,  SQ_A4,  SQ_B4,  SQ_C4,  SQ_D4, WALL14,
  WALL15, WALL16, WALL17, WALL18, WALL19, WALL20,
  SQ_NB,
  SQ_BEGIN = SQ_A1,
  SQ_END   = SQ_D4,
};

enum File {
  FILE_NONE, FILE_A, FILE_B, FILE_C, FILE_D, FILE_NB,
};

enum Rank {
  RANK_NONE, RANK_1, RANK_2, RANK_3, RANK_4, RANK_NB,
};

enum Direct {
  UP  = -6, 
  DN  = -UP,
  RT  =  1,
  LT  = -RT,
  UR  = UP + RT,
  DR  = DN + RT,
  UL  = UP + LT,
  DL  = DN + LT,
  DIR_NB = 8,
};

#else

// todo : WALL など無駄が多いので要修正
enum Square {
  WALL01, WALL02, WALL03, WALL04, WALL05, WALL06, WALL07, WALL08,
  WALL11,  SQ_A1,  SQ_B1,  SQ_C1,  SQ_D1,  SQ_E1,  SQ_F1, WALL12,
  WALL13,  SQ_A2,  SQ_B2,  SQ_C2,  SQ_D2,  SQ_E2,  SQ_F2, WALL14,
  WALL15,  SQ_A3,  SQ_B3,  SQ_C3,  SQ_D3,  SQ_E3,  SQ_F3, WALL16,
  WALL17,  SQ_A4,  SQ_B4,  SQ_C4,  SQ_D4,  SQ_E4,  SQ_F4, WALL18,
  WALL19,  SQ_A5,  SQ_B5,  SQ_C5,  SQ_D5,  SQ_E5,  SQ_F5, WALL20,
  WALL21,  SQ_A6,  SQ_B6,  SQ_C6,  SQ_D6,  SQ_E6,  SQ_F6, WALL22,
  WALL23, WALL24, WALL25, WALL26, WALL27, WALL28, WALL29, WALL30,
  SQ_NB,
  SQ_BEGIN = SQ_A1,
  SQ_END   = SQ_F6,
};

enum File {
  FILE_NONE, FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_NB,
};

enum Rank {
  RANK_NONE, RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_NB,
};

enum Direct {
  UP  = -8, 
  DN  = -UP,
  RT  =  1,
  LT  = -RT,
  UR  = UP + RT,
  DR  = DN + RT,
  UL  = UP + LT,
  DL  = DN + LT,
  DIR_NB = 8,
};
#endif

enum Depth : int {

  ONE_PLY = 1,

  DEPTH_ZERO =  0 * ONE_PLY,
};

enum Value : int {
  VALUE_ZERO      = 0,
  VALUE_DRAW      = 0,
  VALUE_KNOWN_WIN = 10000,
  VALUE_MATE      = 32000,
  VALUE_INFINITE  = 32001,

  VALUE_MATE_IN_MAX_PLY  =  VALUE_MATE - SQ_NB,
  VALUE_MATED_IN_MAX_PLY = -VALUE_MATE + SQ_NB,
};

enum Score : int { SCORE_ZERO };

extern const Direct DirectTable[DIR_NB];

#define ENABLE_BASE_OPERATORS_ON(T)                                \
constexpr T operator+(T d1, T d2) { return T(int(d1) + int(d2)); } \
constexpr T operator-(T d1, T d2) { return T(int(d1) - int(d2)); } \
constexpr T operator-(T d) { return T(-int(d)); }                  \
inline T& operator+=(T& d1, T d2) { return d1 = d1 + d2; }         \
inline T& operator-=(T& d1, T d2) { return d1 = d1 - d2; }

#define ENABLE_INCR_OPERATORS_ON(T)                                \
inline T& operator++(T& d) { return d = T(int(d) + 1); }           \
inline T& operator--(T& d) { return d = T(int(d) - 1); }

#define ENABLE_FULL_OPERATORS_ON(T)                                \
ENABLE_BASE_OPERATORS_ON(T)                                        \
ENABLE_INCR_OPERATORS_ON(T)                                        \
constexpr T operator*(int i, T d) { return T(i * int(d)); }        \
constexpr T operator*(T d, int i) { return T(int(d) * i); }        \
constexpr T operator/(T d, int i) { return T(int(d) / i); }        \
constexpr int operator/(T d1, T d2) { return int(d1) / int(d2); }  \
inline T& operator*=(T& d, int i) { return d = T(int(d) * i); }    \
inline T& operator/=(T& d, int i) { return d = T(int(d) / i); }

ENABLE_FULL_OPERATORS_ON(Value)
ENABLE_FULL_OPERATORS_ON(Depth)

ENABLE_INCR_OPERATORS_ON(Color)
ENABLE_INCR_OPERATORS_ON(Square)
ENABLE_INCR_OPERATORS_ON(File)
ENABLE_INCR_OPERATORS_ON(Rank)

ENABLE_BASE_OPERATORS_ON(Score)

constexpr Square operator+(Square d1, Direct d2) { return Square(int(d1) + int(d2)); }
inline Square& operator+=(Square& d1, Direct d2) { return d1 = d1 + d2; } 

#undef ENABLE_FULL_OPERATORS_ON
#undef ENABLE_INCR_OPERATORS_ON
#undef ENABLE_BASE_OPERATORS_ON

inline Square make_square(File f, Rank r) {
    return Square((int)f + (int)r * (int)DN);
}

constexpr Value mate_in(int score) {
  return Value(VALUE_MATE - score);
}

constexpr Value mated_in(int score) {
  return Value(-VALUE_MATE + score);
}

struct ExtMove {
  Square sq;
  int count[(int)DIR_NB];
  void init() { 
    sq = WALL01;
    std::fill_n(count, (int)DIR_NB, 0); 
  }
  bool empty() { return sq == WALL01; }
};

class Position {
public:
  Position() { init(); };
  ~Position() {}
  void init();
  template <Color Us, bool Do> void move(ExtMove move);
  int game_ply() const;
  Color side_to_move() const;
  Color piece_on(Square s) const;
private:
  int gamePly;
  Color sideToMove; 
  Color board_[SQ_NB];
};

extern std::ostream& operator<<(std::ostream& os, const Position& pos);

inline Color Position::piece_on(Square s) const {
    return board_[s];
}

inline Color Position::side_to_move() const {
  return sideToMove;
}

inline int Position::game_ply() const {
  return gamePly;
}

// reversi.cxxに書きたいがリンカーエラーになるので
template <Color Us, bool Do> 
inline void Position::move(ExtMove move) {

  int sq  = (int)move.sq; 
  Color cl = Do ? Us
                : Us == BLACK ? WHITE
                              : BLACK;

  for (int i = 0; i < (int)DIR_NB; ++i) {
    for (int j = 0; j <= move.count[i]; ++j)
      board_[sq + (int)DirectTable[i] * j] = cl;
  }

  if (!Do) board_[sq] = NONE;

  sideToMove = Us == BLACK ? WHITE 
                           : BLACK; 
}

#endif // _REVERSI_H_