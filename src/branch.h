#ifndef BRANCH_H
#define BRANCH_H

#include "reference.h"
#include "libgitpp_global.h"
#include <string>
#include <memory>

namespace libgitpp {

class LIBGITPP_EXPORT Branch: public Reference
{
public:
  Branch(git_reference* ref, git_branch_t type);

  virtual std::string getName() const;

  git_branch_t getType() const;

  std::unique_ptr<Branch> getUpstreamBranch() const;

  std::string getUpstreamBranchName() const;

  std::string getRemoteName() const;

  static bool isNameValid(const std::string& name);

private:
  git_branch_t type;
};

} // namespace libgitpp

#endif // BRANCH_H
