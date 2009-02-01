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

task :default => :spec
