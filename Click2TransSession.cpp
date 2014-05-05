#include "Click2TransSession.h"
#include "Click2TransDialog.h"
#include "AmRingTone.h"
#include "AmMediaProcessor.h"

Click2TransSession::Click2TransSession(const Click2TransDialog* parentDialog) : 
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
  }
  else if(dialog->isOutgoing())
  {
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
}

