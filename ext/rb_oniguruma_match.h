#ifndef _RB_ONIGURUMA_MATCH_H_
#define _RB_ONIGURUMA_MATCH_H_

#include <ruby.h>
#include <oniguruma.h>  /* for struct re_registers and OnigRegion */

/* Cannot include re.h due to typedef conflicts */
struct RMatch {
    struct RBasic basic;
    VALUE str;
    struct re_registers *regs;
};

#define RMATCH(obj)  (R_CAST(RMatch)(obj))

void rb_match_busy _((VALUE));

typedef struct og_callback_packet {
    VALUE hash;
    OnigRegion * region;
} og_CallbackPacket;

/* Our Match methods */
VALUE og_oniguruma_match_initialize(OnigRegion *region, VALUE string);

/* v2 uses UChar, v4+ uses const UChar for the callback */
#if ONIGURUMA_VERSION_MAJOR < 4
# define OG_CALLBACK_UCHAR UChar
#else
# define OG_CALLBACK_UCHAR const UChar
#endif

/* Oniguruma foreach callback */
int og_oniguruma_name_callback(OG_CALLBACK_UCHAR *name, OG_CALLBACK_UCHAR *name_end,
  int ngroup_num, int *group_nums, regex_t *reg, void *magic);

#endif /* _RB_ONIGURUMA_MATCH_H_ */
