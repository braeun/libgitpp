#include "oid.h"
#include <cstring>

namespace libgitpp {

OID::OID()
{
  memset(&oid.id,0,sizeof(oid.id));
}

OID::OID(const git_oid& oid):
  oid(oid)
{
}

OID::OID(const git_oid* oid):
  oid(*oid)
{
}

std::string OID::toString()
{
  char buf[GIT_OID_SHA1_HEXSIZE + 1];
  git_oid_tostr(buf, sizeof(buf), &oid);
  return buf;
}

std::string OID::toString(size_t n)
{
  char buf[GIT_OID_SHA1_HEXSIZE + 1];
  n++; /* increment by one for '\0' termination */
  if (n > sizeof(buf)) n = sizeof(buf);
  git_oid_tostr(buf, n, &oid);
  return buf;
}

const git_oid* OID::raw() const
{
  return &oid;
}

OID::operator bool() const
{
  for (size_t i=0;i<sizeof(oid.id);++i)
  {
    if (oid.id[i] != 0) return true;
  }
  return false;
}


} // namespace libgitpp
