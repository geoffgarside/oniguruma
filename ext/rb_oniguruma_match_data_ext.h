#ifndef _RB_ONIGURUMA_MATCH_DATA_EXT_H_
#define _RB_ONIGURUMA_MATCH_DATA_EXT_H_

#include "ruby.h"

void Init_oniguruma_match_data_ext();

static VALUE og_oniguruma_match_data_to_index(VALUE self, VALUE sym);
static VALUE og_oniguruma_match_data_aref(int argc, VALUE *argv, VALUE self);
static VALUE og_oniguruma_match_data_begin(int argc, VALUE *argv, VALUE self);
static VALUE og_oniguruma_match_data_end(int argc, VALUE *argv, VALUE self);
static VALUE og_oniguruma_match_data_offset(int argc, VALUE *argv, VALUE self);

#endif /* _RB_ONIGURUMA_MATCH_DATA_EXT_H_ */
