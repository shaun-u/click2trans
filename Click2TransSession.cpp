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

    /*sessionArg.reset(new AmArg(this));
    AmUAC::dialout(dlg.user,
      "click2trans",
      "sip:11@192.168.1.111",
      dlg.local_uri,
      dlg.local_uri,
      "sip:11@192.168.1.111",
      "",
      "",
      sessionArg.get());*/
    /*AmUAC::dialout(const string& user,
    const string& app_name,
    const string& r_uri, 
    const string& from,
    const string& from_uri,
    const string& to,
    const string& local_tag,
    const string& hdrs,
    AmArg*  session_params);*/
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
    s->dlg.local_party = dlg.local_party;
    s->dlg.remote_party = "sip:11@192.168.1.111";
    s->dlg.remote_uri = "sip:11@192.168.1.111";
    
    std::string body;
    s->sdp.genRequest(s->advertisedIP(),s->RTPStream()->getLocalPort(),body);
    
    dialog->addSession(s);

    s->dlg.sendRequest("INVITE","application/sdp",body,"");
    s->start();
    
    AmSessionContainer::instance()->addSession(dialog->getID(),s);
    
    return;
  }

  AmSession::process(ev);
}

const std::string Click2TransSession::getDialogID() const
{
  return dialog->getID();
}

