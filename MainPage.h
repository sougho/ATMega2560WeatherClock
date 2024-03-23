#include "ModeHandlers.h"
#include "Modes.h"

class MainPage : public ModeHandler {
  public:
    void handleEvent(EVENTS event);
};
