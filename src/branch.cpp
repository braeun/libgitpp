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

std::unique_ptr<Branch> Branch::getUpstreamBranch() const
{
  if (type == GIT_BRANCH_LOCAL)
  {
    git_reference* r;
    int err = git_branch_upstream(&r,ref);
    if (err == GIT_OK)
      return std::make_unique<Branch>(r,GIT_BRANCH_REMOTE);
    else if (err != GIT_ENOTFOUND)
    {
      auto err = git_error_last();
      throw std::runtime_error(err->message);
    }
  }
  return std::unique_ptr<Branch>();
}

std::string Branch::getUpstreamBranchName() const
{
  if (type == GIT_BRANCH_LOCAL)
  {
    git_buf buf GIT_BUF_INIT;
    int err = git_branch_upstream_name(&buf,git_reference_owner(ref),getName().c_str());
    if (err == GIT_OK)
    {
      std::string s = buf.ptr;
      git_buf_dispose(&buf);
      return s;
    }
    git_buf_dispose(&buf);
    if (err != GIT_ENOTFOUND)
    {
      auto err = git_error_last();
      throw std::runtime_error(err->message);
    }
  }
  return "";
}

std::string Branch::getRemoteName() const
{
  if (type == GIT_BRANCH_REMOTE)
  {
    git_buf buf GIT_BUF_INIT;
    int err = git_branch_remote_name(&buf,git_reference_owner(ref),getName().c_str());
    if (err == GIT_OK)
    {
      std::string s = buf.ptr;
      git_buf_dispose(&buf);
      return s;
    }
    git_buf_dispose(&buf);
    if (err != GIT_ENOTFOUND && err != GIT_EAMBIGUOUS)
    {
      auto err = git_error_last();
      throw std::runtime_error(err->message);
    }
  }
  return "";
}

bool Branch::isNameValid(const std::string &name)
{
  int valid;
  int err = git_branch_name_is_valid(&valid,name.c_str());
  if (err != GIT_OK)
  {
    auto err = git_error_last();
    throw std::runtime_error(err->message);
  }
  return valid != 0;
}

} // namespace libgitpp
