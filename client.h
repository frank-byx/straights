#ifndef CLIENT_H
#define CLIENT_H

#include "textdisplay.h"
#include "game.h"
#include "abstractcpu.h"
#include <vector>
#include <memory>

class Client {
  Game game;
  TextDisplay td;
  std::vector<std::unique_ptr<AbstractCPU>> cpus;
public:
  Client(unsigned seed);
  void run();
};

#endif
