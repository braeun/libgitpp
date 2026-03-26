#include "revwalk.h"
#include <git2/errors.h>
#include <git2/merge.h>
#include <git2/object.h>
#include <git2/revparse.h>
#include <stdexcept>

namespace libgitpp {

RevWalk::RevWalk(git_revwalk* walker):
  walker(walker)
{
}

RevWalk::~RevWalk()
{
  git_revwalk_free(walker);
}

void RevWalk::setSorting(int flags)
{
  git_revwalk_sorting(walker,flags);
}

void RevWalk::addRevision(const std::string& rev)
{
  git_revspec revs;
  bool hide = false;

  if (rev.empty())
  {
    push(nullptr,false);
    return;
  }

  if (rev[0] == '^')
  {
    revs.flags = GIT_REVSPEC_SINGLE;
    hide = !hide;
    if (git_revparse_single(&revs.from, git_revwalk_repository(walker), rev.c_str() + 1) < 0) return;
  }
  else if (git_revparse(&revs, git_revwalk_repository(walker), rev.c_str()) < 0)
    return;

  if ((revs.flags & GIT_REVSPEC_SINGLE) != 0)
    push(revs.from,hide);
  else {
    push(revs.to,hide);

    if ((revs.flags & GIT_REVSPEC_MERGE_BASE) != 0)
    {
      git_oid base;
      int err = git_merge_base(&base, git_revwalk_repository(walker),git_object_id(revs.from), git_object_id(revs.to));
      if (err != GIT_OK)
      {
        auto err = git_error_last();
        throw std::runtime_error(err->message);
      }
      err = git_object_lookup(&revs.to, git_revwalk_repository(walker), &base, GIT_OBJECT_COMMIT);
      if (err != GIT_OK)
      {
        auto err = git_error_last();
        throw std::runtime_error(err->message);
      }
      push(revs.to, hide);
    }
    push(revs.from, !hide);
  }
}

void RevWalk::reset()
{
  git_revwalk_reset(walker);
}

bool RevWalk::getNext(git_oid* oid)
{
  return git_revwalk_next(oid,walker) == 0;
}

// void RevWalk::push(git_object* obj)
// {
//   int err = GIT_OK;
//   if (!obj)
//     err = git_revwalk_push_head(walker);
//   else
//     err = git_revwalk_push(walker,git_object_id(obj));
//   if (err != GIT_OK)
//   {
//     auto err = git_error_last();
//     git_object_free(obj);
//     throw std::runtime_error(err->message);
//   }
//   git_object_free(obj);
// }

// void RevWalk::hide(git_object* obj)
// {
//   if (!obj) return;
//   int err = git_revwalk_hide(walker,git_object_id(obj));
//   if (err != GIT_OK)
//   {
//     auto err = git_error_last();
//     git_object_free(obj);
//     throw std::runtime_error(err->message);
//   }
//   git_object_free(obj);
// }

git_revwalk* RevWalk::raw()
{
  return walker;
}

void RevWalk::push(git_object* obj, bool hide)
{
  int err = GIT_OK;
  if (!obj)
    err = git_revwalk_push_head(walker);
  else if (hide)
    int err = git_revwalk_hide(walker,git_object_id(obj));
  else
    err = git_revwalk_push(walker,git_object_id(obj));
  if (err != GIT_OK)
  {
    auto err = git_error_last();
    git_object_free(obj);
    throw std::runtime_error(err->message);
  }
  git_object_free(obj);
}

} // namespace libgitpp
