#include <ruby.h>
#include "rb_oniguruma_ext.h"

static VALUE
og_oniguruma_string_do_substitution(VALUE self, char *method, int argc, VALUE *argv)
{
  og_DefineConstantNames;
  VALUE oregexp, re, arg, oargv[2], nargv[3];
  
  og_ObtainConstants;
  if (rb_block_given_p()) {
    note("Block was given to the string sub func");
    rb_scan_args(argc, argv, "1&", &re, &arg);
  } else {
    note("No block given to string sub func");
    rb_scan_args(argc, argv, "2", &re, &arg);
  }
  
  /* Get the regular expression and make our initialization argv */
  oargv[0] = re;
  oargv[1] = (VALUE)NULL;
  
  nargv[0] = self;
  nargv[1] = arg;
  nargv[2] = (VALUE)NULL;
  
  // TODO: Find how to pass a block back to ruby
  oregexp = rb_class_new_instance(1, oargv, og_cOniguruma_ORegexp);
  return rb_funcall3(oregexp, rb_intern(method), 2, nargv);
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
