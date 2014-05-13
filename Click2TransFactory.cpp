#include "Click2TransFactory.h"
#include "log.h"

#include <sstream>
#include <string>
#include <memory>

#define MOD_NAME "click2trans"

EXPORT_SESSION_FACTORY(Click2TransFactory,MOD_NAME);
EXPORT_PLUGIN_CLASS_FACTORY(Click2TransFactory,MOD_NAME);

Click2TransFactory* Click2TransFactory::_instance=0;

Click2TransFactory::Click2TransFactory(const string& _app_name)
  : AmSessionFactory(_app_name), AmDynInvokeFactory(_app_name)
{
  _instance = this;
}

int Click2TransFactory::onLoad()
{
  DBG("Click2TransFactory loading");
  return 0;
}

AmSession* Click2TransFactory::onInvite(const AmSipRequest& req)
{
  const std::string dialogID = AmSession::getNewId();
  std::auto_ptr<Click2TransDialog> dialog(new Click2TransDialog(dialogID));
  Click2TransSession* session = new Click2TransSession(dialog.get());
  dialog->addSession(session);
  dialogs[dialogID] = dialog.release();
  
  DBG("dialog ID=%s created for incoming leg", dialogID.c_str());
  
  return session;
}

Click2TransFactory* Click2TransFactory::getInstance()
{
  DBG("di instance being returned");
  return _instance;
}
 
void Click2TransFactory::invoke(const string& method, const AmArg& args, AmArg& ret)
{
  DBG("di invoke method=%s",method.c_str());
  //TODO extract dialog id and destination for transfer sip uri from args and use for transfer
  
  //poc: simply invoke transfer on first and only dialog
  dialogs.begin()->second->doDiTransfer();
}

