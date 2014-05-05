#ifndef _CLICK2TRANSFACTORY_H_
#define _CLICK2TRANSFACTORY_H_

#include <map>

#include "AmApi.h"
#include "Click2TransDialog.h"

class Click2TransFactory: public AmSessionFactory
{
  /**
   * active Click2TransDialogs
   * i.e. active calls
   */
  std::map<const std::string, Click2TransDialog*> dialogs;

public:
  Click2TransFactory(const string& _app_name);

  int onLoad();

  /**
   * entry point for calls and hence new Click2TransDialogs
   */
  AmSession* onInvite(const AmSipRequest& req);

  /**
   * second call leg
   * @dialogId the dialog to which the second leg belongs
   */
  AmSession* onInvite(const AmSipRequest& req, AmArg& dialogId);
};

#endif //_CLICK2TRANSFACTORY_H_

