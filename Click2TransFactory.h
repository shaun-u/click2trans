#ifndef _CLICK2TRANSFACTORY_H_
#define _CLICK2TRANSFACTORY_H_

#include <map>

#include "AmApi.h"
#include "Click2TransDialog.h"

class Click2TransFactory: public AmSessionFactory
{
  std::map<std::string, Click2TransDialog> dialogs;

public:
  Click2TransFactory(const string& _app_name);

  int onLoad();
  AmSession* onInvite(const AmSipRequest& req);
};

#endif //_CLICK2TRANSFACTORY_H_

