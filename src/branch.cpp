#include "branch.h"
#include <git2/branch.h>
#include <git2/errors.h>
#include <stdexcept>

namespace libgitpp {

Branch::Branch(git_reference* ref, git_branch_t type):Reference(ref),
  type(type)
{
}

git_branch_t Branch::getType() const
{
  return type;
}

std::string Branch::getName() const
{
  const char* s;
  int err = git_branch_name(&s,raw());
  if (err != GIT_OK)
  {
    auto err = git_error_last();
    throw std::runtime_error(err->message);
  }
  return s;
}

} // namespace libgitpp
