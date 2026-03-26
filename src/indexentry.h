#ifndef INDEXENTRY_H
#define INDEXENTRY_H

#include "libgitpp_global.h"
#include <git2/index.h>
#include <cstdint>
#include <string>

namespace libgitpp {

class LIBGITPP_EXPORT IndexEntry
{
public:
  IndexEntry(const git_index_entry* entry=nullptr);

  git_index_time getCtime() const;

  git_index_time getMtime() const;

  uint32_t getDev() const;

  uint32_t getIno() const;

  uint32_t getMode() const;

  uint32_t getUid() const;

  uint32_t getGid() const;

  uint32_t getFile_size() const;

  git_oid getId() const;

  uint16_t getFlags() const;

  uint16_t getFlags_extended() const;

  std::string getPath() const;

  int getStage() const;

private:
  git_index_time ctime;
  git_index_time mtime;

  uint32_t dev;
  uint32_t ino;
  uint32_t mode;
  uint32_t uid;
  uint32_t gid;
  uint32_t file_size;

  git_oid id;

  uint16_t flags;
  uint16_t flags_extended;

  std::string path;
};

} // namespace libgitpp

#endif // INDEXENTRY_H
