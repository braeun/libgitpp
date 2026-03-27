#include "reference.h"

namespace libgitpp {

Reference::Reference(git_reference* ref):
  ref(ref)
{
}

Reference::~Reference()
{
  git_reference_free(ref);
}

git_reference* Reference::raw() const
{
  return ref;
}

} // namespace libgitpp
