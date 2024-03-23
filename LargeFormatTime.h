#include "ModeHandlers.h"
#include "Modes.h"

class LargeFormatTime : public ModeHandler {
  public:
    void handleEvent(EVENTS event);
};
