#ifndef STATE_H
#define STATE_H

enum class State
{
  kEmpty,
  kObstacle,
  kClosed,
  kPath,
  kStart,
  kFinish
};

#endif