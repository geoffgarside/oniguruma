#include <ruby.h>
#include <node.h>
#include "rb_oniguruma_ext.h"

typedef struct og_string_substitution_args {
  VALUE oregexp;
  VALUE method;
  VALUE string;
} og_StringSubstitutionArgs;

#define og_StringSubstitutionArgs_set(args_, a, b, c) do {  \
  og_StringSubstitutionArgs *ssap = (args_);                \
  (ssap)->oregexp = a;                                      \
  (ssap)->method = b;                                       \
  (ssap)->string = c;                                       \
} while(0)

static VALUE
og_oniguruma_string_do_substitution_block(VALUE val)
{
  VALUE argv[2];
  og_StringSubstitutionArgs *args = (og_StringSubstitutionArgs *)val;
  
  argv[0] = args->string;
  argv[1] = (VALUE)NULL;
  
  return rb_funcall3(args->oregexp, args->method, 1, argv);
}

// The block will be yielded a MatchData object or nil
// Always one object at a time
static VALUE
og_oniguruma_string_block_helper(VALUE match, VALUE proc, VALUE self)
{
  VALUE argv[2];
  
  argv[0] = match;
  argv[1] = (VALUE)NULL;
  
  return rb_funcall3(proc, rb_intern("call"), 1, argv);
}

static VALUE
og_oniguruma_string_do_substitution(VALUE self, char *method, int argc, VALUE *argv)
{
  og_DefineConstantNames;
  VALUE oregexp, re, arg, oargv[2], nargv[3];
  og_StringSubstitutionArgs fargs;
  
  og_ObtainConstants;
  if (rb_block_given_p()) {
    note("Block was given to the string sub func");
    rb_scan_args(argc, argv, "1&", &re, &arg);
  } else {
    note("No block given to string sub func");
    rb_scan_args(argc, argv, "2", &re, &arg);
  }
  
  oargv[0] = re;
  oargv[1] = (VALUE)NULL;
  oregexp = rb_class_new_instance(1, oargv, og_cOniguruma_ORegexp);
  
  if (rb_block_given_p()) {
    og_StringSubstitutionArgs_set(&fargs, oregexp, rb_intern(method), self);
    return rb_iterate(og_oniguruma_string_do_substitution_block, (VALUE)&fargs,
      og_oniguruma_string_block_helper, (VALUE)arg);
  } else {
    nargv[0] = self;
    nargv[1] = arg;
    nargv[2] = (VALUE)NULL;

    return rb_funcall3(oregexp, rb_intern(method), 2, nargv);
  }
}

static VALUE
og_oniguruma_string_ogsub(int argc, VALUE *argv, VALUE self)
{
  return og_oniguruma_string_do_substitution(self, "gsub", argc, argv);
}

static VALUE
og_oniguruma_string_ogsub_bang(int argc, VALUE *argv, VALUE self)
{
  return og_oniguruma_string_do_substitution(self, "gsub!", argc, argv);
}

static VALUE
og_oniguruma_string_osub(int argc, VALUE *argv, VALUE self)
{
  return og_oniguruma_string_do_substitution(self, "sub", argc, argv);
}

static VALUE
og_oniguruma_string_osub_bang(int argc, VALUE *argv, VALUE self)
{
  return og_oniguruma_string_do_substitution(self, "sub!", argc, argv);
}

void
og_oniguruma_string_ext(VALUE og_mOniguruma_Extensions)
{
  VALUE og_mString =
    rb_define_module_under(og_mOniguruma_Extensions, "String");
  
  /*               Module      Method     Handler Function              Args */
  rb_define_method(og_mString, "ogsub",   og_oniguruma_string_ogsub,      -1);
  rb_define_method(og_mString, "ogsub!",  og_oniguruma_string_ogsub_bang, -1);
  rb_define_method(og_mString, "osub",    og_oniguruma_string_osub,       -1);
  rb_define_method(og_mString, "osub!",   og_oniguruma_string_osub_bang,  -1);
  
  rb_include_module(rb_cString, og_mString);
}
