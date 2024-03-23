#ifndef __MODEHANDLERS_H_
#define __MODEHANDLERS_H_

#include "Modes.h"


class ModeHandler {
  public:
  virtual void handleEvent(EVENTS event) = 0;
};

#endif
