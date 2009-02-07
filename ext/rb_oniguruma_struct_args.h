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


void print_SubstitutionArgs(og_SubstitutionArgs *args)
{
    int i;
    
    printf("og_SubstitutionArgs { \n");
    printf("  [self] => %s,\n", RSTRING_PTR(rb_str_to_str(args->self)));
    printf("  [argc] => %d,\n", args->argc);
    printf("  [argv] => Array {\n");
    
    for (i = 0; i < args->argc; i++)
        printf("    [%d] => %s,\n", i, RSTRING_PTR(rb_str_to_str((args->argv[i]))));
    printf("  },\n");
    
    printf("  [global] => %d,\n  [update_self] => %d\n", args->global, args->update_self);
    printf("  [region] => OnigRegion {\n");
    
    printf("    [allocated] => %d,\n", args->region->allocated);
    printf("    [num_regs] => %d,\n", args->region->num_regs);
    
    if (args->region->beg == NULL)
      printf("    [beg] => %p (NULL),\n", args->region->beg);
    else
      printf("    [beg] => %p (%d),\n", args->region->beg, args->region->beg[0]);
    
    if (args->region->end == NULL)
      printf("    [end] => %p (NULL),\n", args->region->end);
    else
      printf("    [end] => %p (%d),\n", args->region->end, args->region->end[0]);
    
    printf("  }\n}\n");
}
#endif /* _RB_ONIGURUMA_STRUCT_ARGS_H_ */
