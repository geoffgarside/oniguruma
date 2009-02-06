== Oniguruma bindings for Ruby:

Ruby bindings to the Oniguruma[http://www.geocities.jp/kosako3/oniguruma/] regular expression library.
This gem does not require the recompilation of Ruby to enable or disable Oniguruma[http://www.geocities.jp/kosako3/oniguruma/].

This project is a rewrite of the original gem[http://oniguruma.rubyforge.org/]
as a Ruby/C extension only in C.

Through the rewrite the project aims to be compatible with more versions of
Oniguruma[http://www.geocities.jp/kosako3/oniguruma/]. The project should be
able to build against and operate with Oniguruma[http://www.geocities.jp/kosako3/oniguruma/]
versions 2, 4 and 5. It has been tested against the following versions

* 2.5.8
* 4.7.1
* 5.9.1

The RSpec tests will document any features which are not supported by different
versions, though primarily it is only the 2.5.8 version which does not support
multibyte regular expressions. Additionally some constant names were added or
removed between Oniguruma[http://www.geocities.jp/kosako3/oniguruma/] versions.

You can safely use this gem as a replacement to work with 
Textpow[http://textpow.rubyforge.org] and 
UltraViolet[http://ultraviolet.rubyforge.org] to get nice syntax highlighting
in Warehouse[http://warehouseapp.com].

== Features of Oniguruma[http://www.geocities.jp/kosako3/oniguruma/]:

* Increased performance. 
* Same interface as standard Regexp class (easy transition!). 
* Support for named groups, look-ahead, look-behind, and other 
  cool features!
* Support for other regexp syntaxes (Perl, Python, Java, etc.)

== Synopsis:

 reg = Oniguruma::ORegexp.new( '(?<before>.*)(a)(?<after>.*)' )
 match = reg.match( 'terraforming' )
 puts match[0]         <= 'terraforming'
 puts match[:before]   <= 'terr'
 puts match[:after]    <= 'forming'
 
== Syntax

Consult the Syntax.txt[link:files/Syntax_txt.html] page.

== Requirements:

* Oniguruma[http://www.geocities.jp/kosako3/oniguruma/] library, versions
  2, 4 and 5 are supported. To find out which version of the library being
  used you can check <code>Oniguruma::VERSION::ENGINE</code>.

== Install:

  sudo gem install -r geoffgarside-oniguruma -s http://gems.github.com/

== Bugs/Problems/Incompatibilities:

* Documentation is incomplete due to issues with <code>RDoc::C_Parser</code>.
* <code>ORegexp#~</code> is not implemented.
* <code>ORegexp#kcode</code> results are not compatible with <code>Regexp</code>.
* <code>ORegexp</code> options set in the string are not visible, this affects
  <code>ORegexp#options</code>, <code>ORegexp#to_s</code>, <code>ORegexp#inspect</code>
  and <code>ORegexp#==</code>.

== Todo:

* Get documentation working in RDoc.

== Credits:

* N. Lugovoi. ORegexp.sub and ORegexp.gsub code and lots of other stuff.
* K. Kosako. For his great library.
* A lot of the documentation has been copied from the original Ruby Regex documentation.
* Dizan Vasquez for the original Oniguruma bindings gem

== Licence:

Some portions of code are Copyright (c) 2007, Dizan Vasquez though due to
heavy refactoring and integration of the original Ruby layer in C has made the
division blurred.

See the License.txt[link:files/License_txt.html] page for details.
