#ifndef PRINT_H
#define PRINT_H

#include <git2/types.h>
#include <string>

namespace libgitpp {

class Repository;

namespace print {

extern std::string log(Repository* repo, std::string rev="");

}

} // namespace libgitpp

#endif // PRINT_H
