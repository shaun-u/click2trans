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

void Click2TransDialog::connect()
{
  DBG("connecting audio for sessions");

  if(sessions.size() == 2)
  {
    DBG("connecting input and output");
    //sessions[0]->setInOut(sessions[1]->getOutput(),sessions[1]->getInput());
    //sessions[1]->setInOut(sessions[0]->getOutput(),sessions[0]->getInput());
    sessions[0]->setInOut(sessions[1]->getInput(),sessions[1]->getOutput());
    sessions[1]->setInOut(sessions[0]->getInput(),sessions[0]->getOutput());
    sessions[0]->setCallgroup(getID());
    sessions[1]->setCallgroup(getID());
    AmMediaProcessor::instance()->addSession(sessions[0],getID());
    AmMediaProcessor::instance()->addSession(sessions[1],getID());
  }
  else
  {
    DBG("TODO there should be two sessions!");
  }
}
