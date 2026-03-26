#ifndef DIFF_H
#define DIFF_H

#include "libgitpp_global.h"
#include <git2/diff.h>
#include <string>
#include <vector>

namespace libgitpp {

class LIBGITPP_EXPORT File
{
public:
  File();
  File(const git_diff_file& file);
  File(const File&) = default;
  File(File&&) = default;

  File& operator=(const File&) = default;

  git_oid getOid() const;

  std::string getPath() const;

  uint32_t getFlags() const;

  uint16_t getMode() const;

  uint16_t getIdAbbrev() const;

private:
  git_oid oid;
  std::string path;
  uint32_t flags;
  uint16_t mode;
  uint16_t id_abbrev;
};

class LIBGITPP_EXPORT Delta
{
public:
  Delta(const git_diff_delta* delta=nullptr);

  git_delta_t getStatus() const;

  uint32_t getFlags() const;

  uint16_t getSimilarity() const;

  uint16_t getNfiles() const;

  File getOldFile() const;

  File getNewFile() const;


private:
  git_delta_t status;
  uint32_t flags;
  uint16_t similarity;
  uint16_t nfiles;
  File oldFile;
  File newFile;
};

class LIBGITPP_EXPORT Diff
{
public:
  Diff(git_diff* diff);
  ~Diff();

  std::string toString(git_diff_format_t fmt=GIT_DIFF_FORMAT_PATCH);

  std::vector<Delta> getDeltas() const;

  git_diff* raw();

private:
  git_diff* diff;
};

} // namespace libgitpp

#endif // DIFF_H
