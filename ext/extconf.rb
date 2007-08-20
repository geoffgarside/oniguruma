require 'mkmf'
Config::MAKEFILE_CONFIG["CFLAGS"] << ' -I/usr/local/include -Wall'
Config::MAKEFILE_CONFIG["LDFLAGS"] <<' -L/usr/local/lib'

init_mkmf
have_library('onig')
create_makefile('oniguruma')
