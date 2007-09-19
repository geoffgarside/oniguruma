#ifndef _RB_ONIGURUMA_H_
#define _RB_ONIGURUMA_H_

#include <ruby.h>
#include <oniguruma.h>

#ifndef OG_M_ONIGURUMA
#define OG_M_ONIGURUMA "Oniguruma"
#endif

#ifndef OG_M_EXTENSIONS
#define OG_M_EXTENSIONS "Extensions"
#endif

#ifndef OG_C_OREGEXP
#define OG_C_OREGEXP "ORegexp"
#endif

/* Init functions */
void og_oniguruma_oregexp(VALUE mod, const char* name);
void og_oniguruma_string_ext(VALUE mod);
void og_oniguruma_match_ext(VALUE mod);

/* Ruby to C constant mapping functions */
OnigEncodingType* og_oniguruma_extract_encoding(VALUE encoding);
OnigSyntaxType* og_oniguruma_extract_syntax(VALUE syntax);

#define og_oniguruma_extract_option(opt) (OnigOptionType)NUM2INT(opt)

/* Oniguruma::ORegexp C class data structure */
typedef struct og_oregexp {
  regex_t *reg;
} og_ORegexp;

#define DEBUG 1

#ifdef DEBUG
# define NOTE "**NOTE***:  "
# define note(str) printf(NOTE str "\n")
# define note1(str, arg) printf(NOTE str "\n", arg)
# define note2(str, a, b) printf(NOTE str "\n", a, b)
# define note3(str, a, b, c) printf(NOTE str "\n", a, b, c)
#else
# define note(str)
# define note1(str, arg)
# define note2(str, a, b)
# define note3(str, a, b, c)
#endif

#endif /* _RB_ONIGURUMA_H_ */
