#include "signature.h"
#include <git2/errors.h>
#include <stdexcept>

namespace libgitpp {

Signature::Signature(git_signature* sig):
  sig(sig)
{
}

Signature::Signature(const std::string& name, const std::string& email)
{
  int err = git_signature_now(&sig,name.c_str(),email.c_str());
  if (err != GIT_OK)
  {
    auto err = git_error_last();
    throw std::runtime_error(err->message);
  }
}

Signature::Signature(const Signature& s)
{
  int err = git_signature_dup(&sig,s.sig);
  if (err != GIT_OK)
  {
    auto err = git_error_last();
    throw std::runtime_error(err->message);
  }
}

Signature::~Signature()
{
  git_signature_free(sig);
}

std::string Signature::getName() const
{
  if (sig) return sig->name;
  return "unkown";
}

std::string Signature::getEmail() const
{
  if (sig) return sig->email;
  return "unknown";
}

GitTime Signature::getTime() const
{
  if (sig) return GitTime(sig->when);
  return GitTime({0,0,'+'});
}

const git_signature* Signature::raw() const
{
  return sig;
}

Signature& Signature::operator=(const Signature& s)
{
  if (sig)
  {
    git_signature_free(sig);
    sig = nullptr;
  }
  int err = git_signature_dup(&sig,s.sig);
  if (err != GIT_OK)
  {
    auto err = git_error_last();
    throw std::runtime_error(err->message);
  }
  return *this;
}

} // namespace libgitpp
