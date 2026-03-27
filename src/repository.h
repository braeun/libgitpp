#ifndef LIBGITPP_REPOSITORY_H
#define LIBGITPP_REPOSITORY_H

#include "oid.h"
#include "libgitpp_global.h"
#include <git2/repository.h>
#include <string>
#include <memory>
#include <vector>

namespace libgitpp
{

class Branch;
class Commit;
class Diff;
class Index;
class RevWalk;
class Signature;

class LIBGITPP_EXPORT Repository
{
public:
  ~Repository();

  static std::unique_ptr<Repository> init(const std::string& path=".");

  static std::unique_ptr<Repository> open(const std::string& path=".");

  const std::string& getPath();

  std::unique_ptr<Signature> getDefaultSignature();

  std::unique_ptr<RevWalk> getRevWalker();

  std::unique_ptr<Commit> getCommit(const OID& oid);

  std::unique_ptr<Index> getIndex();

  std::unique_ptr<Diff> diffIndex(Index* index);

  std::vector<std::string> add(const std::vector<std::string>& list);

  bool commit(const std::string& comment, const Signature* sig=nullptr);

  std::vector<std::unique_ptr<Branch>> getBranches(git_branch_t type=GIT_BRANCH_ALL);

  bool checkout(const std::string& branch, bool force=false);

  git_repository* raw() const;

private:
  Repository(std::string path);
  Repository(git_repository* repo);
  int resolve_refish(git_annotated_commit **commit, const std::string& refish);

  std::string path;
  git_repository* repo;
};

} // namespace

#endif // REPOSITORY_H
