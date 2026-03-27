
add_library(gitpp SHARED
  branch.cpp
  commit.cpp
  diff.cpp
  gittime.cpp
  index.cpp
  indexentry.cpp
  oid.cpp
  print.cpp
  reference.cpp
  repository.cpp
  revwalk.cpp
  signature.cpp
)
add_library(gitpp::gitpp ALIAS gitpp)

target_sources(gitpp PUBLIC
  FILE_SET HEADERS TYPE HEADERS BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_BINARY_DIR}" FILES
  branch.h
  commit.h
  diff.h
  gittime.h
  index.h
  indexentry.h
  libgitpp_global.h
  oid.h
  print.h
  reference.h
  repository.h
  revwalk.h
  signature.h
)

  target_compile_definitions(gitpp PRIVATE LIBGITPP_LIBRARY)

target_link_libraries(gitpp
  PUBLIC PkgConfig::LIBGIT2
)

set_target_properties(gitpp
    PROPERTIES
      VERSION
        ${CMAKE_PROJECT_VERSION}
      SOVERSION
        ${CMAKE_PROJECT_VERSION_MAJOR} #.${CMAKE_PROJECT_VERSION_MINOR}
      DEFINE_SYMBOL
        LIBGITPP
)

install(TARGETS gitpp
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  FILE_SET HEADERS DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/gitpp
)

# pkg-config file
if (UNIX)
  configure_file(libgitpp.pc.in ${CMAKE_CURRENT_BINARY_DIR}/libgitpp.pc)
  install(
    FILES
      ${CMAKE_CURRENT_BINARY_DIR}/libgitpp.pc
    DESTINATION
      ${CMAKE_INSTALL_LIBDIR}/pkgconfig
    COMPONENT
      pkgconfig
  )
endif (UNIX)


