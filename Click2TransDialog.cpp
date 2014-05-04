#include "Click2TransDialog.h"



Click2TransDialog::Click2TransDialog(const std::string& uniq_id) : id(uniq_id)
{

}

void Click2TransDialog::addSession(const Click2TransSession* session)
{
  //TODO ensure unique in container and throw exception if not
  sessions.push_back(session);
}

const std::string& Click2TransDialog::getID() const
{
  return id; 
}
