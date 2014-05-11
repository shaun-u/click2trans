#ifndef _CLICK2TRANSSESSION_H_
#define _CLICK2TRANSSESSION_H_

#include <memory>

#include "AmSession.h"

class Click2TransDialog;
class AmRingTone;

class Click2TransSession : public AmSession
{
  Click2TransDialog* dialog;
  std::auto_ptr<AmRingTone> ringTone;    
  std::auto_ptr<AmArg> sessionArg;
public:
  Click2TransSession(Click2TransDialog* parentDialog);
  virtual ~Click2TransSession();

  void onInvite(const AmSipRequest& req);
  void onSessionStart(const AmSipRequest& req);
  void onSipReply(const AmSipReply& reply, int old_dlg_status,const string& trans_method);
  void onBye(const AmSipRequest& req);

  void process(AmEvent* ev);
  
  const std::string getDialogID() const;
};


#endif //_CLICK2TRANSSESSION_H_
