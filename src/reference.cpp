#include "reference.h"
#include "branch.h"

namespace libgitpp {

Reference::Reference(git_reference* ref):
  ref(ref)
{
}

Reference::~Reference()
{
  git_reference_free(ref);
}

std::string Reference::getName() const
{
  return git_reference_name(ref);
}

bool Reference::isBranch() const
{
  return git_reference_is_branch(ref) != 0;
}

bool Reference::isRemote() const
{
  return git_reference_is_remote(ref) != 0;
}

bool Reference::isTag() const
{
  return git_reference_is_tag(ref) != 0;
}

bool Reference::isNote() const
{
  return git_reference_is_note(ref) != 0;
}

std::unique_ptr<Branch> Reference::asBranch() const
{
  if (isBranch())
  {
    git_reference *r;
    git_reference_dup(&r,ref);
    return std::make_unique<Branch>(r,GIT_BRANCH_LOCAL);
  }
  else if (isBranch())
  {
    git_reference *r;
    git_reference_dup(&r,ref);
    return std::make_unique<Branch>(r,GIT_BRANCH_REMOTE);
  }
  return std::unique_ptr<Branch>();
}


git_reference* Reference::raw() const
{
  return ref;
}

} // namespace libgitpp
