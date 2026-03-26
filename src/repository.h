#ifndef LIBGITPP_REPOSITORY_H
#define LIBGITPP_REPOSITORY_H

#include <git2/repository.h>
#include "libgitpp_global.h"
#include <string>
#include <memory>
#include <vector>

namespace libgitpp
{

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

  std::unique_ptr<Commit> getCommit(git_oid oid);

  std::unique_ptr<Index> getIndex();

  std::unique_ptr<Diff> diffIndex(Index* index);

  std::vector<std::string> add(const std::vector<std::string>& list);

  bool commit(const std::string& comment, const Signature* sig=nullptr);

  git_repository* raw();

private:
  Repository(std::string path);
  Repository(git_repository* repo);

  std::string path;
  git_repository* repo;
};

} // namespace

#endif // REPOSITORY_H
