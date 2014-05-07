#ifndef _CLICK2TRANSDIALOG_H_
#define _CLICK2TRANSDIALOG_H_

#include <vector>
#include <string>

#include "Click2TransSession.h"

class Click2TransDialog
{
  enum DialogState
  {
    INCOMING,OUTGOING,TRANSFERRING
  };

  std::vector<Click2TransSession*> sessions;
  const std::string id;
  DialogState state;

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

  /**
   * connect audio streams of active call legs
   */
  void connect();
};

#endif //_CLICK2TRANSDIALOG_H_
