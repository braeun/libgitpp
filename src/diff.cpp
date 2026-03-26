#include "diff.h"
#include <git2/buffer.h>
#include <git2/errors.h>

namespace libgitpp {

File::File():
  flags(0),
  mode(0),
  id_abbrev(0)
{
}

File::File(const git_diff_file& file)
{
  oid = file.id;
  path = file.path;
  flags = file.flags;
  mode = file.mode;
  id_abbrev = file.id_abbrev;
}

git_oid File::getOid() const
{
  return oid;
}

std::string File::getPath() const
{
  return path;
}

uint32_t File::getFlags() const
{
  return flags;
}

uint16_t File::getMode() const
{
  return mode;
}

uint16_t File::getIdAbbrev() const
{
  return id_abbrev;
}




Delta::Delta(const git_diff_delta *delta)
{
  if (delta)
  {
    status = delta->status;
    flags = delta->flags;
    similarity = delta->similarity;
    nfiles = delta->nfiles;
    oldFile = File(delta->old_file);
    newFile = File(delta->new_file);
  }
}

git_delta_t Delta::getStatus() const
{
  return status;
}

uint32_t Delta::getFlags() const
{
  return flags;
}

uint16_t Delta::getSimilarity() const
{
  return similarity;
}

uint16_t Delta::getNfiles() const
{
  return nfiles;
}

File Delta::getOldFile() const
{
  return oldFile;
}

File Delta::getNewFile() const
{
  return newFile;
}




Diff::Diff(git_diff* diff):
  diff(diff)
{
}

Diff::~Diff()
{
  if (diff) git_diff_free(diff);
}

std::string Diff::toString(git_diff_format_t fmt)
{
  git_buf buf GIT_BUF_INIT;
  int err = git_diff_to_buf(&buf,diff,fmt);
  if (err == GIT_OK)
  {
    return std::string(buf.ptr);
  }
  return "";
}

std::vector<Delta> Diff::getDeltas() const
{
  std::vector<Delta> list;
  for (size_t i=0;i<git_diff_num_deltas(diff);++i)
  {
    auto delta = git_diff_get_delta(diff,i);
    list.emplace_back(delta);
  }
  return list;
}

git_diff* Diff::raw()
{
  return diff;
}



} // namespace libgitpp
