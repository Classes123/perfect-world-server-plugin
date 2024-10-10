project('perfect-world-server-plugin', 'c', 'cpp',
  version : '1.0.0',
  meson_version : '>=1.5.0',
  license : 'GPL-3.0',
  license_files : 'LICENSE',
  default_options : {
    'cpp_std' : 'c++17'
  }
)

subdir('src')

add_project_arguments('-Wno-fortify-source',
  language : ['c', 'cpp']
)

add_project_link_arguments('-static-libstdc++',
  language : ['cpp']
)

shared_module('plugin', src,
  name_prefix : '',
  gnu_symbol_visibility : 'inlineshidden'
)