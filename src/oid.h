#ifndef OID_H
#define OID_H

#include "libgitpp_global.h"
#include <git2/oid.h>
#include <string>

namespace libgitpp {

class LIBGITPP_EXPORT OID
{
public:
  OID();
  OID(const git_oid& oid);
  OID(const git_oid* oid);

  std::string toString();

  std::string toString(size_t n);

  const git_oid* raw() const;

  operator bool() const;

private:
  git_oid oid;
};

} // namespace libgitpp

#endif // OID_H
