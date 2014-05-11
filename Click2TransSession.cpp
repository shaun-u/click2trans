#include "Click2TransSession.h"
#include "Click2TransDialog.h"
#include "AmRingTone.h"
#include "AmMediaProcessor.h"
#include "AmUAC.h"
#include "AmSessionContainer.h"

enum { 
  DoConnect = 100,
};

struct DialoutEvent : public AmEvent {

  DialoutEvent(int event_id) : AmEvent(event_id){}
};

Click2TransSession::Click2TransSession(Click2TransDialog* parentDialog) : 
  dialog(parentDialog),ringTone(new AmRingTone(0,2000,4000,440,480))
{
  RTPStream()->setPlayoutType(ADAPTIVE_PLAYOUT);
  setCallgroup(dialog->getID());
}

Click2TransSession::~Click2TransSession()
{

}

void Click2TransSession::onInvite(const AmSipRequest& req)
{
  //do nothing
}

void Click2TransSession::onSessionStart(const AmSipRequest& req)
{
  if(dialog->isIncoming())
  {
    DBG("incoming session");

    try
    {
      std::string sdp_reply;
      acceptAudio(req.body,req.hdrs,&sdp_reply);
      if(dlg.reply(req,
	200,"OK INVITER IS CONNECTED", "application/sdp",
	  sdp_reply) != 0)
      {
	throw AmSession::Exception(500,"could not send response");
      }
    }
    catch(const AmSession::Exception& e)
    {
      ERROR("%i %s\n",e.code,e.reason.c_str());
      setStopped();
      dlg.reply(req,e.code,e.reason);
      return;
    }

    DBG("playing ringtone to inviter");

    setInOut(NULL,ringTone.get());
    AmSession::onSessionStart(req);
    AmMediaProcessor::instance()->addSession(this, callgroup);

    postEvent(new DialoutEvent(DoConnect));//TODO cleanup this allocation?
  }
  else if(dialog->isOutgoing())
  {
    DBG("outgoing session");  
  }
}

void Click2TransSession::process(AmEvent* ev)
{
  DialoutEvent* devt = dynamic_cast<DialoutEvent*>(ev);

  if(devt && devt->event_id == DoConnect)
  {
    DBG("Inviting invitee");

    Click2TransSession* s = new Click2TransSession(dialog);
    s->dlg.local_tag = AmSession::getNewId();
    s->dlg.callid = AmSession::getNewId();
    s->dlg.local_party = dlg.remote_party;
    s->dlg.remote_party = "sip:123@192.168.1.111";
    s->dlg.remote_uri = "sip:123@192.168.1.111";
    
    std::string body;
    s->sdp.genRequest(s->advertisedIP(),s->RTPStream()->getLocalPort(),body);
    
    dialog->addSession(s);

    s->dlg.sendRequest("INVITE","application/sdp",body,"");
    s->start();
    
    //AmSessionContainer::instance()->addSession(dialog->getID(),s);
    //I think to receive sip responses, this must be stored under local tag
    AmSessionContainer::instance()->addSession(s->dlg.local_tag,s);
    
    return;
  }

  AmSession::process(ev);
}

void Click2TransSession::onSipReply(const AmSipReply& reply, int old_dlg_status, const string& trans_method)
{

  DBG("sip reply: code=%i; reason=%s; status=%i", reply.code, reply.reason.c_str(), dlg.getStatus());

  if(dialog->isOutgoing())
  {
    DBG("sip reply for outgoing invite");

    switch(dlg.getStatus())
    {
      case AmSipDialog::Connected:
      {
	DBG("connected: connecting audio");
	acceptAudio(reply.body, reply.hdrs);

	Click2TransSession* otherLeg = dialog->getOtherLeg(this);
	AmMediaProcessor::instance()->removeSession(otherLeg);
	//setInOut(NULL, ringTone.get());
	//otherLeg->clearAudio();
	//setInOut(otherLeg->getOutput(),otherLeg->getInput());
	//-otherLeg->setInOut(getOutput(),getInput());
	//otherLeg->setInOut(getInput(),getOutput());
	//setInOut(otherLeg->getInput(),otherLeg->getOutput());
	//AmMediaProcessor::instance()->addSession(otherLeg, callgroup);
	dialog->connectSession(this);
	dialog->connectSession(otherLeg);
	AmMediaProcessor::instance()->addSession(this, callgroup);
	AmMediaProcessor::instance()->addSession(otherLeg, callgroup);
	break;
      }
      default:
      {
	DBG("TODO not implemented");
      }
    }

  }
  else if(dialog->isTerminated())
  {
    DBG("setting session to stopped");
    setStopped();
  }
  else
  {
    DBG("TODO expected isOutgoing() to be true");
  }
  
  AmSession::onSipReply(reply, old_dlg_status, trans_method);
}

void Click2TransSession::onBye(const AmSipRequest& req)
{
  DBG("bye received");
  if(!dialog->isTerminated())
  {
    DBG("terminating media");
    dialog->terminate();
    Click2TransSession* otherLeg = dialog->getOtherLeg(this);
    AmMediaProcessor::instance()->removeSession(this);
    AmMediaProcessor::instance()->removeSession(otherLeg);
    dialog->disconnectSession(this);
    dialog->disconnectSession(otherLeg);

    DBG("sending bye to other leg");
    otherLeg->dlg.bye();
    DBG("setting session to stopped");
    setStopped();
  }
  
  AmSession::onBye(req);
}

const std::string Click2TransSession::getDialogID() const
{
  return dialog->getID();
}

