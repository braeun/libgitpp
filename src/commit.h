#ifndef COMMIT_H
#define COMMIT_H

#include "gittime.h"
#include "libgitpp_global.h"
#include "oid.h"
#include <git2/commit.h>
#include <memory>
#include <string>

namespace libgitpp {

class Signature;

class LIBGITPP_EXPORT Commit
{
public:
  Commit(git_commit *commit);
  ~Commit();

  OID getId();

  std::string getMessage() const;

  std::unique_ptr<Signature> getAuthor() const;

  std::unique_ptr<Signature> getCommitter() const;

  GitTime getCommitTime() const;

  int getParentCount() const;

  OID getParentId(unsigned int index);

  std::string toString() const;

  git_commit* raw();

private:
  git_commit *commit;
};

} // namespace libgitpp

#endif // COMMIT_H
