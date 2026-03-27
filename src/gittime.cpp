#include "gittime.h"
#include <sstream>
#include <iomanip>

namespace libgitpp {

GitTime::GitTime(git_time t):
  time(t)
{
}

int64_t GitTime::getSecondsSinceEpoch()
{
  return time.time;
}

int GitTime::getTZOffset()
{
  return time.offset;
}

char GitTime::getSign()
{
  return time.sign;
}

std::string GitTime::toString()
{
  char sign = '+';
  int offset = time.offset;
  if (offset < 0)
  {
    sign = '-';
    offset = -offset;
  }
  int hours   = offset / 60;
  int minutes = offset % 60;
  time_t t = (time_t)time.time + (time.offset * 60);
  struct tm* intm = gmtime(&t);
  char out[32];
  strftime(out, sizeof(out), "%a %b %e %T %Y", intm);
  std::ostringstream s;
  s << out << " " << sign;
  s << std::setw(2) << std::setfill('0') << hours;
  s << std::setw(2) << std::setfill('0') << minutes;
  return s.str();
}

} // namespace libgitpp
