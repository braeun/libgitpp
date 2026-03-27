#include "commit.h"
#include "signature.h"
#include <sstream>

namespace libgitpp {

Commit::Commit(git_commit *commit):
  commit(commit)
{
}

Commit::~Commit()
{
  git_commit_free(commit);
}

OID Commit::getId()
{
  return git_commit_id(commit);
}

std::string Commit::getMessage() const
{
  return git_commit_message(commit);
}

std::unique_ptr<Signature> Commit::getAuthor() const
{
  const git_signature *sig= git_commit_author(commit);
  git_signature* dest;
  git_signature_dup(&dest,sig);
  return std::make_unique<Signature>(dest);
}

std::unique_ptr<Signature> Commit::getCommitter() const
{
  const git_signature *sig= git_commit_committer(commit);
  git_signature* dest;
  git_signature_dup(&dest,sig);
  return std::make_unique<Signature>(dest);
}

GitTime Commit::getCommitTime() const
{
  return GitTime({git_commit_time(commit),git_commit_time_offset(commit),'+'});
}

int Commit::getParentCount() const
{
  return git_commit_parentcount(commit);
}

OID Commit::getParentId(unsigned int index)
{
  return git_commit_parent_id(commit,index);
}

std::string Commit::toString() const
{
  char buf[GIT_OID_SHA1_HEXSIZE + 1];
  std::ostringstream s;
  git_oid_tostr(buf, sizeof(buf), git_commit_id(commit));
  s << "commit " << buf << std::endl;

  int count = (int)git_commit_parentcount(commit);
  if (count > 1)
  {
    s << "Merge:";
    for (int i=0;i<count;++i)
    {
      git_oid_tostr(buf,8,git_commit_parent_id(commit, i));
      s << " " << buf;
    }
    s << std::endl;
  }
  auto sig = getAuthor();
  if (sig)
  {
    s << "Author: " << sig->getName() << " <" << sig->getEmail() << ">" << std::endl;
    s << "Date: " << sig->getTime().toString() << std::endl;
  }
  s << std::endl;
  std::string msg = git_commit_message(commit);
  auto lf = msg.find('\n');
  while (lf != msg.npos)
  {
    s << "    " << msg.substr(0,lf) << std::endl;
    msg = msg.substr(lf+1);
    lf = msg.find('\n');
  }
  s << "    " << msg << std::endl;
  return s.str();

}

git_commit* Commit::raw()
{
  return commit;
}



} // namespace libgitpp
