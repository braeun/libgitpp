#include <string>
#include <index.h>
#include <diff.h>
#include <repository.h>
#include <iostream>

int main(int argc, char* argv[])
{
  std::string path = ".";
  if (argc > 1)
  {
    path = argv[1];
  }
  try
  {
    auto repo = libgitpp::Repository::open(path);
    // auto index = repo->getIndex();
    // std::cout << "Index count: " << index->getCount() << std::endl;
    // for (const auto& entry : index->getEntries())
    // {
    //   std::cout << entry.getPath() << std::endl;
    // }
    std::cout << "--------------" << std::endl;
    auto diff = repo->diffIndex(nullptr);
    std::cout << diff->toString() << std::endl;
    std::cout << "--------------" << std::endl;
    auto deltas = diff->getDeltas();
    std::cout << "# deltas: " << deltas.size() << std::endl;
    for (const auto& d : deltas)
    {
      std::cout << d.getStatus() << " " << d.getOldFile().getPath() << std::endl;
    }
  }
  catch (std::exception& ex)
  {
    std::cout << ex.what() << std::endl;
  }

  return 0;
}
