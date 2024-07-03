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

if get_option('tests')
    subdir('tests')
endif
