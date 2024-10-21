project('countrybattle2sides', 'c', 'cpp',
    version: '1.0.0',
    meson_version: '>1.5.0',
    default_options: {
        'cpp_std': 'c++17'
    }
)

subdir('src')

add_project_arguments('-Wno-fortify-source',
  language : ['c', 'cpp']
)

add_project_link_arguments('-static-libstdc++',
  language : ['cpp']
)

shared_module('countrybattle2sides', src,
  name_prefix : '',
  include_directories : inc,
  gnu_symbol_visibility : 'inlineshidden'
)