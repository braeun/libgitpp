#ifndef COMMIT_H
#define COMMIT_H

#include "gittime.h"
#include <git2/commit.h>
#include <memory>
#include <string>

namespace libgitpp {

class Signature;

class Commit
{
public:
  Commit(git_commit *commit);
  ~Commit();

  const git_oid* getId();

  std::string getMessage() const;

  std::unique_ptr<Signature> getAuthor() const;

  std::unique_ptr<Signature> getCommitter() const;

  GitTime getCommitTime() const;

  int getParentCount() const;

  const git_oid* getParentId(unsigned int index);

  std::string toString() const;

  git_commit* raw();

private:
  git_commit *commit;
};

} // namespace libgitpp

#endif // COMMIT_H
