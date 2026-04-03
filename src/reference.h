#ifndef REFERENCE_H
#define REFERENCE_H

#include "libgitpp_global.h"
#include <git2/refs.h>
#include <memory>

namespace libgitpp {

class Branch;

class LIBGITPP_EXPORT Reference
{
public:
  Reference(git_reference* ref);
  virtual ~Reference();

  virtual std::string getName() const;

  bool isBranch() const;

  bool isRemote() const;

  bool isTag() const;

  bool isNote() const;

  std::unique_ptr<Branch> asBranch() const;

  git_reference* raw() const;

protected:
  git_reference* ref;
};

} // namespace libgitpp

#endif // REFERENCE_H
