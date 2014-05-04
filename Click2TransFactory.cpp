#include "Click2TransFactory.h"
#include "log.h"

#include <sstream>
#include <string>
#include <memory>

#define MOD_NAME "click2trans"

EXPORT_SESSION_FACTORY(Click2TransFactory,MOD_NAME);

Click2TransFactory::Click2TransFactory(const string& _app_name)
  : AmSessionFactory(_app_name)
{
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
  
  DBG("dialog ID=%s created", dialogID.c_str());
  
  return session;
}

