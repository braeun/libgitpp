#include "repository.h"
#include "commit.h"
#include "revwalk.h"
#include <string>
#include <sstream>

namespace libgitpp {

namespace print {

std::string log(Repository* repo, std::string rev)
{
  auto walker = repo->getRevWalker();
  walker->addRevision(rev);
  std::ostringstream s;
  OID oid;
  while ((oid = walker->getNext()))
  {
    auto commit = repo->getCommit(oid);
    s << commit->toString();
    s << std::endl;
  }
  return s.str();
}


}


} // namespace libgitpp
