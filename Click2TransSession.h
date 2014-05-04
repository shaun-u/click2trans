#ifndef _CLICK2TRANSSESSION_H_
#define _CLICK2TRANSSESSION_H_

#include <memory>

#include "AmSession.h"

class Click2TransDialog;
class AmRingTone;

class Click2TransSession : public AmSession
{
  const Click2TransDialog* dialog;
  std::auto_ptr<AmRingTone> ringTone;    
public:
  Click2TransSession(const Click2TransDialog* parentDialog);
  virtual ~Click2TransSession();

  void onInvite(const AmSipRequest& req);
  void onSessionStart(const AmSipRequest& req);
};


#endif //_CLICK2TRANSSESSION_H_
