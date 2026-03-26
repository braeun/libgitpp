#include <git2/commit.h>
#include <git2/types.h>
#include <git2/oid.h>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>

namespace libgitpp {

namespace print {

std::string toString(const git_time *intime)
{

  char sign = '+';
  int offset = intime->offset;
  if (offset < 0)
  {
    sign = '-';
    offset = -offset;
  }
  int hours   = offset / 60;
  int minutes = offset % 60;
  time_t t = (time_t)intime->time + (intime->offset * 60);
  struct tm* intm = gmtime(&t);
  char out[32];
  strftime(out, sizeof(out), "%a %b %e %T %Y", intm);
  std::ostringstream s;
  s << out << sign;
  s << std::setw(2) << std::setfill('0');
  s << hours << minutes;
  return s.str();
}

std::string toString(git_commit *commit, bool showLogSize)
{
  char buf[GIT_OID_SHA1_HEXSIZE + 1];
  std::ostringstream s;
  git_oid_tostr(buf, sizeof(buf), git_commit_id(commit));
  s << "commit " << buf << std::endl;

  std::string msg = git_commit_message(commit);
  if (showLogSize)
  {
    s << "log size " << msg.size() << std::endl;
  }

  int count = (int)git_commit_parentcount(commit);
  if (count > 1)
  {
    s << "Merge:";
    for (int i=0;i<count;++i)
    {
      git_oid_tostr(buf, 8, git_commit_parent_id(commit, i));
      s << " " << buf;
    }
    s << std::endl;
  }
  const git_signature *sig= git_commit_author(commit);
  if (sig)
  {
    s << "Author: " << sig->name << " <" << sig->email << ">" << std::endl;
    s << "Date: " << toString(&sig->when);
  }
  s << std::endl;
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

}


} // namespace libgitpp
