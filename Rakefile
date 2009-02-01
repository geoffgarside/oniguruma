require 'rake'
require 'rake/testtask'

begin
  require 'hanna/rdoctask'
rescue LoadError
  require 'rake/rdoctask'
end

begin
  require 'spec/rake/spectask'
rescue LoadError
  puts 'To use rspec for testing you must install rspec gem:'
  puts '$ sudo gem install rspec'
  exit
end

begin
  require 'jeweler'
  Jeweler::Tasks.new do |s|
    s.name        = 'oniguruma'
    s.summary     = 'Oniguruma Regular Expressions bindings'
    s.email       = 'geoff-rubygems@geoffgarside.co.uk'
    s.homepage    = 'http://github.com/geoffgarside/ruby-oniguruma'
    s.description = "TODO"
    s.authors     = ['Geoff Garside']
    s.files       = FileList["[A-Z]*.*", "ext/depend", "ext/*.{rb,c,h}",
                      'ext/rb_oniguruma_version.h', "spec/*"]
    s.extensions << 'ext/extconf.rb'
    s.require_paths = ['ext']
  end
rescue LoadError
  puts "Jeweler not available. Install it with: sudo gem install technicalpickles-jeweler -s http://gems.github.com"
end

desc "Runs the specs in spec/"
Spec::Rake::SpecTask.new do |t|
  t.spec_opts  = ['--options', "spec/spec.opts"]
  t.spec_files = FileList['spec/*_spec.rb']
end

Rake::RDocTask.new do |rdoc|
  rdoc.rdoc_dir = 'rdoc'
  rdoc.title    = 'Ruby Oniguruma Bindings'
  rdoc.options << '--line-numbers' << '--inline-source'
  rdoc.rdoc_files.include('README*')
  rdoc.rdoc_files.include('ext/*.c')
end

## File build rules
GENERATED_FILES = ['ext/rb_oniguruma_version.h', 'ext/Makefile']
desc "Builds the Makefile for compiling the extension"
file 'ext/Makefile' => 'ext/extconf.rb' do
  Dir.chdir('ext') do
    sh 'ruby extconf.rb'
  end
end

desc "Generates the rb_oniguruma_version.h from VERSION.yml file"
file 'ext/rb_oniguruma_version.h' => 'VERSION.yml' do
  version_info = YAML.load_file('VERSION.yml')
  File.open('ext/rb_oniguruma_version.h', 'w') do |f|
    f.write <<-EOF
#ifndef _RB_ONIGURUMA_VERSION_H_
#define _RB_ONIGURUMA_VERSION_H_

#define OG_VERSION_MAJOR  #{version_info[:major]}
#define OG_VERSION_MINOR  #{version_info[:minor]}
#define OG_VERSION_TEENY  #{version_info[:patch]}

#endif /* _RB_ONIGURUMA_VERSION_H_ */
EOF
  end
end

desc "Builds the extension shared library file"
file 'ext/oniguruma.so' => FileList['ext/*.[ch]'].include(GENERATED_FILES) do
  Dir.chdir('ext') do
    sh 'make'
  end
end

desc "Rebuilds the extension"
task :recompile => [:clean, :compile]

desc "Builds the extension"
task :compile => 'ext/oniguruma.so'

desc "Cleans the extension"
task :clean do
  Dir.chdir('ext') do
    sh 'make clean'
    sh 'rm mkmf.log Makefile rb_oniguruma_version.h'
  end
end

task :spec => :compile
task :default => :spec

## Jeweler Overrides
task 'gem:build' => 'ext/rb_oniguruma_version.h'
