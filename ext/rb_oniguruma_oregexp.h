#ifndef _RB_ONIGURUMA_OREGEXP_H_
#define _RB_ONIGURUMA_OREGEXP_H_

#include <ruby.h>
#include <oniguruma.h>

void Init_oniguruma_oregexp();
RUBY_EXTERN VALUE og_cOniguruma_ORegexp;

typedef struct og_oregexp {
  regex_t *reg;
} og_ORegexp;

typedef struct og_substitution_args {
  VALUE	self;
  int   argc;
  VALUE *argv;
  int	global;
  int update_self;
  OnigRegion *region;  
} og_SubstitutionArgs;

typedef struct og_scan_args {
  VALUE self;
  VALUE str;
  OnigRegion * region;
} og_ScanArgs;

#define og_SubstitutionArgs_set(args_, a, b, c, d, e, f) do { \
  og_SubstitutionArgs *sap = (args_);                         \
  (sap)->self         = (a);                                  \
  (sap)->argc         = (b);                                  \
  (sap)->argv         = (c);                                  \
  (sap)->global       = (d);                                  \
  (sap)->update_self  = (e);                                  \
  (sap)->region       = (f);                                  \
} while(0)

#define og_ScanArgs_set(args_, a, b, c) do {  \
  og_ScanArgs *sap = (args_);                 \
  (sap)->self      = (a);                     \
  (sap)->str       = (b);                     \
  (sap)->region    = (c);                     \
} while(0)

#define og_oniguruma_oregexp_get_code_point(cp, cpl, enc, rep, pos) do {  \
  cp = ONIGENC_MBC_TO_CODE(enc, RSTRING(rep)->ptr + pos,                  \
    RSTRING(rep)->ptr + RSTRING(rep)->len - 1);                           \
  cpl = enc_len(enc, RSTRING(rep)->ptr + pos);                \
} while(0)

/* Class Methods */
VALUE og_oniguruma_oregexp_escape(int argc, VALUE *argv, VALUE self);
VALUE og_oniguruma_oregexp_last_match(int argc, VALUE *argv, VALUE self);

/* Instance Methods */
VALUE og_oniguruma_oregexp_initialize(int argc, VALUE *argv, VALUE self);
VALUE og_oniguruma_oregexp_match(int argc, VALUE *argv, VALUE self);
VALUE og_oniguruma_oregexp_operator_match(VALUE self, VALUE str);
VALUE og_oniguruma_oregexp_operator_equality(VALUE self, VALUE str);
VALUE og_oniguruma_oregexp_operator_identical(VALUE self, VALUE str);
VALUE og_oniguruma_oregexp_sub(int argc, VALUE *argv, VALUE self);
VALUE og_oniguruma_oregexp_sub_bang(int argc, VALUE *argv, VALUE self);
VALUE og_oniguruma_oregexp_gsub(int argc, VALUE *argv, VALUE self);
VALUE og_oniguruma_oregexp_gsub_bang(int argc, VALUE *argv, VALUE self);
VALUE og_oniguruma_oregexp_scan(VALUE self, VALUE str);
VALUE og_oniguruma_oregexp_casefold(VALUE self);
VALUE og_oniguruma_oregexp_kcode(VALUE self);
VALUE og_oniguruma_oregexp_options(VALUE self);
VALUE og_oniguruma_oregexp_source(VALUE self);
VALUE og_oniguruma_oregexp_inspect(VALUE self);
VALUE og_oniguruma_oregexp_to_s(VALUE self);

#endif /* _RB_ONIGURUMA_OREGEXP_H_ */
