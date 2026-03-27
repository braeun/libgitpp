#ifndef REFERENCE_H
#define REFERENCE_H

#include "libgitpp_global.h"
#include <git2/refs.h>

namespace libgitpp {

class LIBGITPP_EXPORT Reference
{
public:
  Reference(git_reference* ref);
  virtual ~Reference();

  git_reference* raw() const;

private:
  git_reference* ref;
};

} // namespace libgitpp

#endif // REFERENCE_H
