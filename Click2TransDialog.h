#ifndef _CLICK2TRANSDIALOG_H_
#define _CLICK2TRANSDIALOG_H_

#include <vector>
#include <string>
#include <memory>

#include "Click2TransSession.h"

class AmSessionAudioConnector;

/**
 * container for call legs in B2B bridged media connection
 */
class Click2TransDialog
{
  enum DialogState
  {
    INCOMING,OUTGOING,TRANSFERRING,TERMINATED
  };

  //TODO encapsulate properly
  Click2TransSession* legA, *legB, *legC;//legC is always used for transferrer
  const std::string id;//unique identifier for this dialog
  DialogState state;
  std::auto_ptr<AmSessionAudioConnector> connector;//audio bridge
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

  /**
   * quick convenience methods for accessing state of this dialog
   */
  bool isIncoming() const;
  bool isOutgoing() const;
  bool isTerminated() const;
  bool isTransferring() const;

  /**
   * quick convenience for getting the other party of the B2B bridged call
   */
  Click2TransSession* getOtherLeg(Click2TransSession* thisLeg);

  /**
   * bridge and unbridge the media between two call legs
   */
  void connectSession(Click2TransSession* session);
  void disconnectSession(Click2TransSession* session);

  void terminate();
  void transfer();
  void outgoing();

  /**
   * quick convenience for identifying the tranferring party
   */
  void setTransferer(Click2TransSession* tranferrer); 
  Click2TransSession* removeTransferer();

  /**
   * convenience for doing transfer invoked by xmlrpc (using DI interface)
   */
  void doDiTransfer();
};

#endif //_CLICK2TRANSDIALOG_H_
