#ifndef BRANCH_H
#define BRANCH_H

#include "reference.h"
#include "libgitpp_global.h"
#include <string>

namespace libgitpp {

class LIBGITPP_EXPORT Branch: public Reference
{
public:
  Branch(git_reference* ref, git_branch_t type);

  git_branch_t getType() const;

  std::string getName() const;

private:
  git_branch_t type;
};

} // namespace libgitpp

#endif // BRANCH_H
