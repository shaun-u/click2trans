#ifndef _CLICK2TRANSDIALOG_H_
#define _CLICK2TRANSDIALOG_H_

#include <vector>
#include <string>

#include "Click2TransSession.h"

class Click2TransDialog
{
  std::vector<const Click2TransSession*> sessions;
  const std::string id;

public:
  Click2TransDialog(const std::string& uniq_id);

  /**
   * @param session lifecycle managed by SEMS
   */
  void addSession(const Click2TransSession* session);

  /**
   * unique ID of this Click2TransDialog
   */
  const std::string& getID() const;
};

#endif //_CLICK2TRANSDIALOG_H_
