#ifndef SIGNATURE_H
#define SIGNATURE_H

#include "gittime.h"
#include <git2/signature.h>
#include <string>

namespace libgitpp {

class Signature
{
public:
  Signature(git_signature* sig);
  Signature(const std::string& name, const std::string& email);
  Signature(const Signature& s);
  ~Signature();

  std::string getName() const;

  std::string getEmail() const;

  GitTime getTime() const;

  const git_signature* raw() const;

  Signature& operator=(const Signature& s);

private:
  git_signature* sig;
};

} // namespace libgitpp

#endif // SIGNATURE_H
