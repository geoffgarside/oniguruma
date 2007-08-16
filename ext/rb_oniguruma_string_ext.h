#ifndef _RB_ONIGURUMA_STRING_EXT_H_
#define _RB_ONIGURUMA_STRING_EXT_H_

#include "ruby.h"

void Init_oniguruma_string_ext();

static VALUE og_oniguruma_string_ogsub(int argc, VALUE *argv, VALUE self);
static VALUE og_oniguruma_string_ogsub_bang(int argc, VALUE *argv, VALUE self);

static VALUE og_oniguruma_string_osub(int argc, VALUE *argv, VALUE self);
static VALUE og_oniguruma_string_osub_bang(int argc, VALUE *argv, VALUE self);

#endif /* _RB_ONIGURUMA_STRING_EXT_H_ */
