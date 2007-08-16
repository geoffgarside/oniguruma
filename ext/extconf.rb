require 'mkmf'
$CFLAGS='-I/usr/local/include -Wall'
$LDFLAGS='-L/usr/local/lib'

have_library('onig')
create_makefile('oniguruma')
