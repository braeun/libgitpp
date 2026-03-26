#ifndef PRINT_H
#define PRINT_H

#include <git2/types.h>
#include <string>

namespace libgitpp {

namespace print {

extern std::string toString(const git_time *intime);

extern std::string toString(git_commit *commit, bool showLogSize);

}

} // namespace libgitpp

#endif // PRINT_H
