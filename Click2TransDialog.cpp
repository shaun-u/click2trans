#include "Click2TransDialog.h"
#include "AmMediaProcessor.h"


Click2TransDialog::Click2TransDialog(const std::string& uniq_id) : id(uniq_id)
{

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

