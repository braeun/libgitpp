#include "indexentry.h"

namespace libgitpp {

IndexEntry::IndexEntry(const git_index_entry* entry):
  ctime{0,0},
  mtime{0,0},
  dev{0},
  ino{0},
  mode{0},
  uid{0},
  gid{0},
  file_size{0},
//  id{0},
  flags{0},
  flags_extended{0}
{
  if (entry)
  {
    ctime = entry->ctime;
    mtime = entry->mtime;
    dev = entry->dev;
    ino = entry->ino;
    mode = entry->mode;
    uid = entry->uid;
    gid = entry->gid;
    file_size = entry->file_size;
    id = entry->id;
    flags = entry->flags;
    flags_extended = entry->flags_extended;
    path = entry->path;
  }
}

git_index_time IndexEntry::getCtime() const
{
  return ctime;
}

git_index_time IndexEntry::getMtime() const
{
  return mtime;
}

uint32_t IndexEntry::getDev() const
{
  return dev;
}

uint32_t IndexEntry::getIno() const
{
  return ino;
}

uint32_t IndexEntry::getMode() const
{
  return mode;
}

uint32_t IndexEntry::getUid() const
{
  return uid;
}

uint32_t IndexEntry::getGid() const
{
  return gid;
}

uint32_t IndexEntry::getFile_size() const
{
  return file_size;
}

git_oid IndexEntry::getId() const
{
  return id;
}

uint16_t IndexEntry::getFlags() const
{
  return flags;
}

uint16_t IndexEntry::getFlags_extended() const
{
  return flags_extended;
}

std::string IndexEntry::getPath() const
{
  return path;
}

int IndexEntry::getStage() const
{
  return (flags & GIT_INDEX_ENTRY_STAGEMASK) >> GIT_INDEX_ENTRY_STAGESHIFT;
}

} // namespace libgitpp
