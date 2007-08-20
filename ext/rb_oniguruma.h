#ifndef _RB_ONIGURUMA_H_
#define _RB_ONIGURUMA_H_

#include <ruby.h>
#include <oniguruma.h>

#ifndef OG_M_ONIGURUMA
#define OG_M_ONIGURUMA "Oniguruma"
#endif

#ifndef OG_C_OREGEXP
#define OG_C_OREGEXP "ORegexp"
#endif

/* Init functions */
void og_oniguruma_oregexp(VALUE mod, const char* name);
void og_oniguruma_string_ext();
void og_oniguruma_match_data_ext();

/* Ruby to C constant mapping functions */
OnigEncodingType* og_oniguruma_extract_encoding(VALUE encoding);
OnigSyntaxType* og_oniguruma_extract_syntax(VALUE syntax);

#define og_oniguruma_extract_option(opt) (OnigOptionType)NUM2INT(opt)

/* Oniguruma::ORegexp C class data structure */
typedef struct og_oregexp {
  regex_t *reg;
} og_ORegexp;

#endif /* _RB_ONIGURUMA_H_ */
