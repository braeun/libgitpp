#ifndef LIBGIT_TIME_H
#define LIBGIT_TIME_H

#include <git2/types.h>
#include <string>

namespace libgitpp {

class GitTime
{
public:
  GitTime(git_time t);

  int64_t getSecondsSinceEpoch();

  int getTZOffset();

  char getSign();

  std::string toString();

private:
  git_time time;
};

} // namespace libgitpp

#endif // TIME_H
