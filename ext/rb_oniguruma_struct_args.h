#ifndef _RB_ONIGURUMA_STRUCT_ARGS_H_
#define _RB_ONIGURUMA_STRUCT_ARGS_H_

#include <ruby.h>       /* for VALUE type */
#include <oniguruma.h>  /* for OnigRegion */

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

#endif /* _RB_ONIGURUMA_STRUCT_ARGS_H_ */
