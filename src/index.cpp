#include "index.h"
#include <git2/errors.h>
#include <git2/global.h>
#include <git2/status.h>
#include <stdexcept>

namespace libgitpp {

Index::Index(git_index *index):
  index(index)
{
  int err = git_index_read(index,0);
}

Index::~Index()
{
  git_index_free(index);
}

size_t Index::getCount() const
{
  return git_index_entrycount(index);
}

std::vector<IndexEntry> Index::getEntries() const
{
  std::vector<IndexEntry> entries;
  for (size_t i=0;i<getCount();++i)
  {
    auto e = git_index_get_byindex(index,i);
    entries.emplace_back(IndexEntry(e));
  }
  return entries;
}

void Index::write() const
{
  int err = git_index_write(index);
  if (err != GIT_OK)
  {
    auto err = git_error_last();
    throw std::runtime_error(err->message);
  }
}

git_oid Index::writeTree() const
{
  git_oid tree_oid;
  int err = git_index_write_tree(&tree_oid,index);
  if (err != GIT_OK)
  {
    auto err = git_error_last();
    throw std::runtime_error(err->message);
  }
  return tree_oid;
}

git_index* Index::raw()
{
  return index;
}

} // namespace libgitpp
