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

  std::vector<Click2TransSession*> sessions;
  Click2TransSession* trans;
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

  Click2TransSession* getOtherLeg(Click2TransSession* thisLeg);

  void connectSession(Click2TransSession* session);
  void disconnectSession(Click2TransSession* session);

  void terminate();
  void transfer();
  void setTransferSession(Click2TransSession* kicked); 
};

#endif //_CLICK2TRANSDIALOG_H_
