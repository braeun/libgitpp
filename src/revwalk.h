#ifndef REVWALK_H
#define REVWALK_H

#include "libgitpp_global.h"
#include "oid.h"
#include <git2/revwalk.h>
#include <string>

namespace libgitpp {

class LIBGITPP_EXPORT RevWalk
{
public:
  RevWalk(git_revwalk* walker);
  ~RevWalk();

  void setSorting(int flags);

  void addRevision(const std::string& rev, bool mergeBase=false);

  void reset();

  OID getNext();

  // void push(git_object* obj);

  // void hide(git_object* obj);

  git_revwalk* raw();

private:
  void push(git_object* obj, bool hide);

  git_revwalk* walker;
};

} // namespace libgitpp

#endif // REVWALK_H
