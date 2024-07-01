project(
  'stbsds',
  ['c', 'cpp'],
  version: 'v0.1',
)

stbsds_lib = static_library(
  'stbsds',
  include_directories: 'include',
  sources: [
    'src/stbsds.c',
    'src/sds.c',
  ],
)

stbsds_dep = declare_dependency(
  link_whole: stbsds_lib,
  include_directories: 'include',
)

test(
  'tsprintf',
  executable(
    'tsprintf',
    sources: 'tests/tsprintf.cpp',
    override_options: '-cpp_std=c++11',
    dependencies: [
      stbsds_dep,
      dependency('gtest', main: true),
    ],
  ),
)