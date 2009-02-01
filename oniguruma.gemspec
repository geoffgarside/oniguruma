# -*- encoding: utf-8 -*-

Gem::Specification.new do |s|
  s.name = %q{oniguruma}
  s.version = "2.0.2"

  s.required_rubygems_version = Gem::Requirement.new(">= 0") if s.respond_to? :required_rubygems_version=
  s.authors = ["Geoff Garside"]
  s.date = %q{2009-02-01}
  s.description = %q{TODO}
  s.email = %q{geoff-rubygems@geoffgarside.co.uk}
  s.extensions = ["ext/extconf.rb"]
  s.files = ["History.txt", "License.txt", "README.txt", "VERSION.yml", "ext/depend", "ext/extconf.rb", "ext/rb_oniguruma.c", "ext/rb_oniguruma_ext_match.c", "ext/rb_oniguruma_ext_string.c", "ext/rb_oniguruma_match.c", "ext/rb_oniguruma_oregexp.c", "ext/rb_oniguruma.h", "ext/rb_oniguruma_ext.h", "ext/rb_oniguruma_match.h", "ext/rb_oniguruma_struct_args.h", "ext/rb_oniguruma_version.h", "spec/match_ext_spec.rb", "spec/oniguruma_spec.rb", "spec/oregexp_spec.rb", "spec/spec.opts", "spec/spec_helper.rb", "spec/string_ext_spec.rb"]
  s.has_rdoc = true
  s.homepage = %q{http://github.com/geoffgarside/ruby-oniguruma}
  s.rdoc_options = ["--inline-source", "--charset=UTF-8"]
  s.require_paths = ["ext"]
  s.rubygems_version = %q{1.3.1}
  s.summary = %q{Oniguruma Regular Expressions bindings}

  if s.respond_to? :specification_version then
    current_version = Gem::Specification::CURRENT_SPECIFICATION_VERSION
    s.specification_version = 2

    if Gem::Version.new(Gem::RubyGemsVersion) >= Gem::Version.new('1.2.0') then
    else
    end
  else
  end
end
