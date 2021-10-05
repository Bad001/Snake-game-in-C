void snakeGame();

struct Coordinate {
  int x;
  int y;
};

struct Serpente {
  struct Serpente* coda;
  struct Coordinate coordinate;
};
