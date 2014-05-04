#ifndef _CLICK2TRANSSESSION_H_
#define _CLICK2TRANSSESSION_H_

#include "AmSession.h"

class Click2TransDialog;

class Click2TransSession : public AmSession
{
  const Click2TransDialog* dialog;
  
public:
  Click2TransSession(const Click2TransDialog* parentDialog);
  virtual ~Click2TransSession();

  void onSessionStart(const AmSipRequest& req);
};

#endif //_CLICK2TRANSSESSION_H_
