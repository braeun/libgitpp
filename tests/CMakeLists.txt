
add_executable(open_repo
  open_repo.cpp
)
target_link_libraries(open_repo
  PUBLIC gitpp::gitpp
)

