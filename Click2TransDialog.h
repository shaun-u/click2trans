#ifndef _CLICK2TRANSDIALOG_H_
#define _CLICK2TRANSDIALOG_H_

#include <vector>
#include <string>

#include "Click2TransSession.h"

class Click2TransDialog
{
public:
  std::vector<Click2TransSession> sessions;
  std::string id;
};

#endif //_CLICK2TRANSDIALOG_H_
