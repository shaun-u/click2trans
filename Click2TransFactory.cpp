#include "Click2TransFactory.h"
#include "log.h"

#include <sstream>
#include <string>

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
  return NULL;
}

