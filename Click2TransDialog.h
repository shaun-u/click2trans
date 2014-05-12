#ifndef _CLICK2TRANSDIALOG_H_
#define _CLICK2TRANSDIALOG_H_

#include <vector>
#include <string>
#include <memory>

#include "Click2TransSession.h"

class AmSessionAudioConnector;

class Click2TransDialog
{
  enum DialogState
  {
    INCOMING,OUTGOING,TRANSFERRING,TERMINATED
  };

  Click2TransSession* legA, *legB, *legC;
  const std::string id;
  DialogState state;
  std::auto_ptr<AmSessionAudioConnector> connector;
public:

  Click2TransDialog(const std::string& uniq_id);

  /**
   * @param session lifecycle managed by SEMS
   */
  void addSession(Click2TransSession* session);

  /**
   * unique ID of this Click2TransDialog
   */
  const std::string& getID() const;

  bool isIncoming() const;
  bool isOutgoing() const;
  bool isTerminated() const;
  bool isTransferring() const;

  Click2TransSession* getOtherLeg(Click2TransSession* thisLeg);

  void connectSession(Click2TransSession* session);
  void disconnectSession(Click2TransSession* session);

  void terminate();
  void transfer();
  void outgoing();
  void setTransferer(Click2TransSession* tranferrer); 
  Click2TransSession* removeTransferer();
};

#endif //_CLICK2TRANSDIALOG_H_
