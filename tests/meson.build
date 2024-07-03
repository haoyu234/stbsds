test(
  'tsprintf',
  executable(
    'tsprintf',
    sources: 'tsprintf.cpp',
    override_options: '-cpp_std=c++11',
    dependencies: [
      stbsds_dep,
      dependency('gtest', main: true),
    ],
  ),
)