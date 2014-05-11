#include "Click2TransDialog.h"
#include "AmMediaProcessor.h"
#include "AmB2ABSession.h"

Click2TransDialog::Click2TransDialog(const std::string& uniq_id) : id(uniq_id)
{
  connector.reset(new AmSessionAudioConnector);
}

void Click2TransDialog::addSession(Click2TransSession* session)
{
  //TODO ensure unique in container and throw exception if not
  sessions.push_back(session);
  
  switch(sessions.size())
  {
  case 1:
    {
      state = INCOMING;
      break;
    }
  case 2:
    {
      state = OUTGOING;
      break;
    }
  default:
    {

    }
  }
}

const std::string& Click2TransDialog::getID() const
{
  return id; 
}

bool Click2TransDialog::isIncoming() const
{
  return state == INCOMING;
}

bool Click2TransDialog::isOutgoing() const
{
  return state == OUTGOING;
}

Click2TransSession* Click2TransDialog::getOtherLeg(Click2TransSession* thisLeg)
{
  //TODO re-write properly!
  for(unsigned int i = 0; i < sessions.size(); ++i)
  {
    if(sessions[i] != thisLeg)
    {
      DBG("found other leg");
      return sessions[i];
    }
  }

  DBG("did not find other leg");

  return NULL;
}


void Click2TransDialog::connectSession(Click2TransSession* session)
{
  DBG("connecting session tag=%s",session->getLocalTag().c_str());

  connector->connectSession(session);
}

void Click2TransDialog::disconnectSession(Click2TransSession* session)
{

}
