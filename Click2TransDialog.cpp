#include "Click2TransDialog.h"
#include "AmMediaProcessor.h"
#include "AmB2ABSession.h"

#include <algorithm>

Click2TransDialog::Click2TransDialog(const std::string& uniq_id) : id(uniq_id),
  legA(NULL),legB(NULL),legC(NULL),state(TERMINATED)
{
  connector.reset(new AmSessionAudioConnector);
}

void Click2TransDialog::addSession(Click2TransSession* session)
{
  if(legA == NULL)
  {
    state = INCOMING;
    legA = session;
  }
  else if(legB == NULL)
  {
    if(state != TRANSFERRING)
      state = OUTGOING;
    legB = session;
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

bool Click2TransDialog::isTerminated() const
{
  return state == TERMINATED;
}

bool Click2TransDialog::isTransferring() const
{
  return state == TRANSFERRING;
}

Click2TransSession* Click2TransDialog::getOtherLeg(Click2TransSession* thisLeg)
{
  if(legA == thisLeg)
    return legB;
  if(legB == thisLeg)
    return legA;
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
  DBG("disconnecting session tag=%s",session->getLocalTag().c_str());

  connector->disconnectSession(session);
}

void Click2TransDialog::terminate()
{
  DBG("setting dialog to terminated");
  state = TERMINATED;
}

void Click2TransDialog::transfer()
{
  DBG("setting dialog to transferring");
  state = TRANSFERRING;
}

void Click2TransDialog::outgoing()
{
  DBG("setting dialog to outgoing");
  state = OUTGOING;
}

void Click2TransDialog::setTransferer(Click2TransSession* transferer)
{
  if(legA == transferer)
  {
    legA = legB;
    legB = NULL;
  }
  else if(legB == transferer)
  {
    legB = NULL;
  }
  legC = transferer;
}

Click2TransSession* Click2TransDialog::removeTransferer()
{
  Click2TransSession* tmp = legC;
  legC = NULL;
  return tmp;
}

void Click2TransDialog::doDiTransfer()
{
  //convenience: just defer to onDtmf() of first call leg, where transfer is prototyped
  legA->onDtmf(999,999);//bogus values
}
