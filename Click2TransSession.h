#ifndef _CLICK2TRANSSESSION_H_
#define _CLICK2TRANSSESSION_H_

#include "AmSession.h"

class Click2TransSession : public AmSession
{
    
public:
  Click2TransSession();
  virtual ~Click2TransSession();

  void onSessionStart(const AmSipRequest& req);
};

#endif //_CLICK2TRANSSESSION_H_
