#ifndef LIBGITPP_REPOSITORY_H
#define LIBGITPP_REPOSITORY_H

#include "oid.h"
#include "libgitpp_global.h"
#include <git2/credential.h>
#include <git2/repository.h>
#include <functional>
#include <string>
#include <memory>
#include <vector>

namespace libgitpp
{

class Branch;
class Commit;
class Diff;
class Index;
class Reference;
class RevWalk;
class Signature;

/**
 * @brief Callback to query credentials from user.
 *
 * The function is passed a vector of strings indicating what information is
 * required and a vector of string with the default values. The function must
 * return the rquired data as a vector of strings in the same order the
 * vectors passed as arguments.
 */
typedef std::function<std::vector<std::string>(const std::vector<std::string>&, const std::vector<std::string>&)> CredentialsCallback;

class LIBGITPP_EXPORT Repository
{
public:
  ~Repository();

  static std::unique_ptr<Repository> init(const std::string& path=".");

  static std::unique_ptr<Repository> open(const std::string& path=".");

  const std::string& getPath();

  std::unique_ptr<Signature> getDefaultSignature();

  std::unique_ptr<RevWalk> getRevWalker();

  std::unique_ptr<Reference> getHead();

  std::unique_ptr<Commit> getCommit(const OID& oid);

  std::unique_ptr<Index> getIndex();

  std::unique_ptr<Diff> diffIndex(Index* index);

  std::vector<std::string> add(const std::vector<std::string>& list);

  bool commit(const std::string& comment, const Signature* sig=nullptr);

  std::vector<std::unique_ptr<Branch>> getBranches(git_branch_t type=GIT_BRANCH_ALL);

  bool checkout(const std::string& branch, bool force=false);

  std::unique_ptr<Branch> createBranch(const std::string& name, bool checkout=false);

  void push();

  git_repository* raw() const;

  static void setCredentialsCallback(const CredentialsCallback& cb);

private:
  Repository(std::string path);
  Repository(git_repository* repo);
  int resolve_refish(git_annotated_commit **commit, const std::string& refish);

  static int cred_acquire_cb(git_credential **out, const char *url, const char *username_from_url, unsigned int allowed_types, void *payload);

  std::string path;
  git_repository* repo;

  static CredentialsCallback credentialCallback;
};

} // namespace

#endif // REPOSITORY_H
