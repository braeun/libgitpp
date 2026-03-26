#include "repository.h"
#include "commit.h"
#include "diff.h"
#include "index.h"
#include "revwalk.h"
#include "signature.h"
#include <git2/commit.h>
#include <git2/errors.h>
#include <git2/global.h>
#include <git2/revparse.h>
#include <git2/signature.h>
#include <git2/status.h>
#include <stdexcept>
#include <git2.h>

namespace libgitpp
{

Repository::Repository(std::string path):
  path(path),
  repo(nullptr)
{
  git_libgit2_init();
  int err = git_repository_open_ext(&repo,path.c_str(),0,nullptr);
  printf("git_repository_open_ext = %d\n",err);
  if (err != GIT_OK)
  {
    auto err = git_error_last();
    throw std::runtime_error(err->message);
  }
}

Repository::Repository(git_repository* repo):
  repo(repo)
{
}

Repository::~Repository()
{
  if (repo) git_repository_free(repo);
  git_libgit2_shutdown();
}

std::unique_ptr<Repository> Repository::init(const std::string &path)
{
  git_libgit2_init();
  git_repository* r;
  int err = git_repository_init_ext(&r,path.c_str(),nullptr);
  printf("git_repository_init_ext = %d\n",err);
  if (err != GIT_OK)
  {
    auto err = git_error_last();
    throw std::runtime_error(err->message);
  }
  std::unique_ptr<Repository> repo(new Repository(r));
  return repo;
}

std::unique_ptr<Repository> Repository::open(const std::string &path)
{
  std::unique_ptr<Repository> repo(new Repository(path));
  return repo;
}

const std::string& Repository::getPath()
{
  return path;
}

std::unique_ptr<Signature> Repository::getDefaultSignature()
{
  git_signature* author = nullptr;
  int err = git_signature_default(&author,repo);
  if (err != GIT_OK)
  {
    auto err = git_error_last();
    throw std::runtime_error(err->message);
  }
  return std::make_unique<Signature>(author);
}

std::unique_ptr<RevWalk> Repository::getRevWalker()
{
  git_revwalk* walker = nullptr;
  int err = git_revwalk_new(&walker,repo);
  if (err != GIT_OK)
  {
    auto err = git_error_last();
    throw std::runtime_error(err->message);
  }
  return std::make_unique<RevWalk>(walker);
}

std::unique_ptr<Commit> Repository::getCommit(git_oid oid)
{
  git_commit* commit;
  int err = git_commit_lookup(&commit,repo,&oid);
  if (err != GIT_OK)
  {
    auto err = git_error_last();
    throw std::runtime_error(err->message);
  }
  return std::make_unique<Commit>(commit);
}


std::unique_ptr<Index> Repository::getIndex()
{
  git_index *index;
  int err = git_repository_index(&index, repo);
  if (err != GIT_OK)
  {
    auto err = git_error_last();
    throw std::runtime_error(err->message);
  }
  return std::make_unique<Index>(index);
}

std::unique_ptr<Diff> Repository::diffIndex(Index* index)
{
  git_diff* d = nullptr;
  git_index* idx = nullptr;
  git_diff_options options GIT_DIFF_OPTIONS_INIT;
  options.flags = GIT_DIFF_INCLUDE_UNTRACKED | GIT_DIFF_RECURSE_UNTRACKED_DIRS;
  if (index) idx = index->raw();
  int err = git_diff_index_to_workdir(&d,repo,idx,&options);
  if (err != GIT_OK)
  {
    auto err = git_error_last();
    throw std::runtime_error(err->message);
  }
  return std::make_unique<Diff>(d);
}

struct callback_data {
  std::vector<std::string> messages;
  git_repository* repo;
};

int add_callback(const char *path, const char *matched_pathspec, void *payload)
{
  struct callback_data *data = (struct callback_data *)(payload);
  unsigned int status;
  (void)matched_pathspec;

  /* Get the file status */
  if (git_status_file(&status, data->repo, path) < 0)
  {
    return -1;
  }
  if ((status & GIT_STATUS_CURRENT))
  {
    return 1;
  }
  if ((status & GIT_STATUS_WT_NEW))
  {
    data->messages.push_back(std::string("add '")+path+"'");
  }
  else if ((status & GIT_STATUS_WT_MODIFIED))
  {
    data->messages.push_back(std::string("upd '")+path+"'");
  }
  else if ((status & GIT_STATUS_WT_DELETED))
  {
    data->messages.push_back(std::string("del '")+path+"'");
  }
  else if ((status & GIT_STATUS_WT_RENAMED))
  {
    data->messages.push_back(std::string("ren '")+path+"'");
  }
  return 0;
}

std::vector<std::string> Repository::add(const std::vector<std::string>& list)
{
  git_strarray a;
  a.count = list.size();
  a.strings = (char**)calloc(a.count, sizeof(char *));
  for (size_t i=0;i<a.count;++i)
  {
    a.strings[i] = (char*)list[i].c_str();
  }
  struct callback_data data;
  data.repo = repo;
  auto index = getIndex();
  int err = git_index_add_all(index->raw(),&a,0,add_callback, &data);
  free(a.strings);
  if (err != GIT_OK)
  {
    auto err = git_error_last();
    throw std::runtime_error(err->message);
  }
  return data.messages;
}

bool Repository::commit(const std::string& comment, const Signature* sig)
{
  git_object *parent = nullptr;
  git_reference *ref = nullptr;
  int err = git_revparse_ext(&parent, &ref, repo, "HEAD");
  if (err == GIT_ENOTFOUND)
  {
    printf("HEAD not found. Creating first commit\n");
    err = 0;
  }
  else if (err != 0)
  {
    auto err = git_error_last();
    throw std::runtime_error(err->message);
  }

  auto index = getIndex();
  git_oid tree_oid = index->writeTree();
  index->write();

  git_tree *tree;
  err = git_tree_lookup(&tree, repo, &tree_oid);
  if (err != GIT_OK)
  {
    auto err = git_error_last();
    git_object_free(parent);
    git_reference_free(ref);
    throw std::runtime_error(err->message);
  }

  auto signature = getDefaultSignature();

  git_oid commit_oid;
  err = git_commit_create_v(
                &commit_oid,
                repo,
                "HEAD",
                signature->raw(),
                sig?sig->raw():signature->raw(),
                nullptr,
                comment.c_str(),
                tree,
                parent ? 1 : 0, parent);

  git_tree_free(tree);
  git_object_free(parent);
  git_reference_free(ref);
  if (err != GIT_OK)
  {
    auto err = git_error_last();
    throw std::runtime_error(err->message);
  }
  return true;
}

git_repository* Repository::raw()
{
  return repo;
}


} // namespace

