#ifndef LIBGITPP_INDEX_H
#define LIBGITPP_INDEX_H

#include "libgitpp_global.h"
#include "indexentry.h"
#include <git2/index.h>
#include <git2/oid.h>
#include <vector>

namespace libgitpp {

class LIBGITPP_EXPORT Index
{
public:
  Index(git_index *index);
  ~Index();

  size_t getCount() const;

  std::vector<IndexEntry> getEntries() const;

  void write() const;

  git_oid writeTree() const;

  git_index* raw();

private:
  git_index *index;
};

} // namespace libgitpp

#endif // INDEX_H
