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

// Taken from examining some output from rb2cx
static VALUE
og_oniguruma_string_block_helper(VALUE bl_val, VALUE proc, VALUE self)
{
  int argc;
  VALUE *argv, tmp;
  
  if (ruby_current_node->nd_state != 1) {
    if (bl_val == Qundef)
      bl_val = rb_ary_new2(0);
    else {
      tmp = rb_check_array_type(bl_val);
      bl_val = (NIL_P(tmp) ? rb_ary_new3(1, bl_val) : tmp);
    }
  }
  if (RARRAY(bl_val)->len == 0)
    return rb_funcall3(proc, rb_intern("call"), 0, 0);
  else {
    argc = RARRAY(bl_val)->len;
    argv = ALLOCA_N(VALUE, argc);
    MEMCPY(argv, RARRAY(bl_val)->ptr, VALUE, argc);
    return rb_funcall3(proc, rb_intern("call"), argc, argv);
  }
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
