#ifndef _RB_ONIGURUMA_H_
#define _RB_ONIGURUMA_H_

#include <ruby.h>
#include <oniguruma.h>

/* Module and Class variables */
RUBY_EXTERN VALUE og_mOniguruma;
RUBY_EXTERN VALUE og_cOniguruma_ORegexp;

/* Init functions */
void Init_oniguruma();
void Init_oniguruma_oregexp(VALUE parent);
void Init_oniguruma_string_ext();
void Init_oniguruma_match_data_ext();

/* Ruby to C constant mapping functions */
OnigEncodingType* og_oniguruma_extract_encoding(VALUE encoding);
OnigSyntaxType* og_oniguruma_extract_syntax(VALUE syntax);

#define og_oniguruma_extract_option(opt) (OnigOptionType)NUM2INT(opt)

/* Oniguruma::ORegexp C class data structure */
typedef struct og_oregexp {
  regex_t *reg;
} og_ORegexp;

#endif /* _RB_ONIGURUMA_H_ */
