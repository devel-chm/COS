#!/bin/perl
#
#  C Object System
#  COS symbols
# 
#  Copyright 2017+ Chris Marshall <chm@cpan.org>
#  Copyright 2007+ Laurent Deniau <laurent.deniau@gmail.com>
# 
#  Licensed under the Apache License, Version 2.0 (the "License");
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
# 
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.
#

use File::Basename;
use Getopt::Long;
use File::Path;
use List::Util qw(uniqstr);  # TODO: Implement myself for portability
                             #       That should make the perl versions of
                             #       these utilities run with any core
                             #       perl 5.8.x and above.  Maybe they
                             #       could be used to replace the existing
                             #       shell implementations

# default settings
$progname=basename($0);
$nm="nm -P -g";
@infiles=();
@filelist=();
$filelist='';

$prjname='';
$modname='';
@modlist=();
@rmgen=();
$rmgen='';
@rmcls=();
$rmcls='';
$rmdoc='';
$rmtrc='';
$rmlst='';  # used for --rmgen trace output if --rmtrc set

$out="_cossym.c";
$datestr=scalar localtime();

# helper
sub usage() {

    print <<"END_OF_TEXT" ;

  $progname extracts COS symbols from object files or libraries
  and outputs a C file which must be compiled/linked with your project.

  Usage:
    $progname <options> files

  Options:
    --help
      This help.

    --in=<file_name>
      Use the content of file_name to specify list of files
      Multiple files can be provided with multiple --in

    --out=<file_name>
      Put the result in file_name
      Default is: $out

    --prj=<project_name>
      Specify the name of this COS project (program)

    --mod=<module_name>
      Specify the name of this COS module (library) to be used for
      future symbols dependencies (--dep). Set the project name but it
      can be overridden with --prj.

    --dep=<module_name>
      The COS modules (library) on which your library or program
      depends on for registration of table of symbols.
      Multiple modules can be provided with multiple --dep

    --rmgen=<generic-list>
      Remove all generic in the list
      Remove all methods specializing these generics
      Multiple lists can be provided with multiple --rmgen

    --rmcls=<class-list>
      Remove all classes in the list and their subclasses
      Remove all methods specialized by these classes and subclasses
      Multiple lists can be provided with multiple --rmcls
      It is applied after the rmgen option

    --rmdoc
      Remove documentation (defdoc)

    --rmtrc
      Trace removed generics and classes on stderr

    --nm=<command>
      Specify the command for collecting symbols from object files
      The output must print global symbols in first column (Posix)
      Default is: $nm

    where lists are names separated by '|' (or egrep patterns)
      e.g. --rmcls='True|False|TrueFalse'

END_OF_TEXT

    exit 1;
}

# parse arguments
# --help
# --in=<file_name>
# --out=<file_name>
# --prj=<project_name>
# --mod=<module_name>
# --dep=<module_name>
# --rmgen=<generic-list>
# --rmcls=<class-list>
# --rmdoc
# --rmtrc
# --nm=<command>

GetOptions(
    "help" =>    \&usage,
    "in=s" =>    \@infiles,  # each file contains a list of filenames to process
    "out=s" =>   \$out,
    "prj=s" =>   \$prjname,
    "mod=s" =>   \$modname,
    "dep=s" =>   \@modlist,
    "rmgen=s" => \@rmgen,
    "rmcls=s" => \@rmcls,
    "rmdoc" =>   \$rmdoc,
    "rmtrc" =>   \$rmtrc,
    "nm=s" =>    \$nm,
) or usage();

$prjname = $modname ? $modname : $prjname;

# add @infiles to @filelist
foreach my $in ( @infiles ) {
    open IN, "<$in" or die "$progname: could not open '$in' for reading: $!";
    my (@inlist) = <IN>;
    close IN;
    @filelist = (@filelist, @inlist);
}

# add non-option files to @filelist
@filelist = (@filelist,@ARGV) if @ARGV;

$token = '[A-Za-z_][A-Za-z0-9_]*';
$prefix = '[cdgm]';

if ($rmdoc) {
    $prefix = '[cgm]';
}

# retrieve symbols
if ( @filelist ) {
    $sym=qx($nm @filelist);  # make sure no \n stuff in @filelist
    @sym = split /\s*\n/, $sym;  # make clean list of lines no trailing whitespace
    @sym = grep { m/^_?cos_($prefix)_($token) D / } @sym;
    @sym = map { m/^(\S+) D.*$/ } @sym;
    @sym = map { m/^_?(cos.*)$/ } @sym;
    @sym = uniqstr sort @sym;
    if ( @rmcls ) {
        $lnk=qx($nm @filelist);  # make sure no \n stuff
        @lnk = split /\s*\n/, $lnk;
        @lnk = grep { /^_?cos_l_($token) B / } @lnk;
        @lnk = map { m/^(\S+) B.*$/ } @lnk;
        @lnk = map { m/^_?(cos.*)$/ } @lnk;
        @lnk = uniqstr sort @lnk;
    }
}

# remove generic patterns
if ( @rmgen ) {
    foreach my $pat (@rmgen) {
#       extract generics
        if ( $rmtrc ) {
            @gen = grep { m/^cos_g_($pat)$/ } @sym;
            @gen = map { m/^cos_g_(.*)$/ } @gen;
            $rmlst="$rmlst @gen";
        }
#       remove generic pattern
        @sym = grep { ! m/^cos_g_($pat)$/ } @sym;
        @sym = grep { ! m/^cos_m_($pat)_/ } @sym;
    }

#   display removed generics
    if ( $rmlst ) {
        print STDERR "** Removed generics:\n";
        print STDERR "$rmlst\n";
        $rmlst = '';
    }
}

# remove class patterns and subclasses
if ( @rmcls ) {
    foreach my $pat (@rmcls) {
#       extract classes
        if ( $rmtrc ) {
            @cls = grep { m/^cos_c_($pat)$/ } @sym;
            @cls = map { m/^cos_g_(.*)$/ } @cls;
            $rmlst="$rmlst @cls";
        }
#       extract subclasses
        @subcls = grep { m/^cos_l_($pat)__isSuperOf__/ } @lnk;
        @subcls = map { m/^cos_l_${token}__isSuperOf__(.*)$/ } @subcls;
        $sublst = "$sublst @subcls";
# DEBUG print STDERR "sublst: @sublst\n";
#       remove link pattern
        @lnk = grep { ! m/^cos_l_($pat)__isSuperOf__/ } @lnk;
#       remove class pattern
        @sym = grep { ! m/^cos_c_(|m|pm)($pat)$/ } @sym;
        @sym = grep { ! m/^cos_m_($token)_(|m|pm)($pat)(_|$)/ } @sym;
    }

#   display removed classes
    if ( $rmlst ) {
        print STDERR "** Removed classes:\n";
        print STDERR "$rmlst\n";
        $rmlst = '';
    }

#   remove subclasses
    while ( $sublst ) {
#       add subclasses to removed classes
        if ( $rmtrc ) {
            $rmlst = "$rmlst $sublst";
        }
#       build subclass pattern
        (my $pat = $sublst) =~ s/\s+/\|/g;
# DEBUG print STDERR "pat: $pat\n";
#       extract subclasses
        @subcls = grep { m/^cos_l_($pat)__isSuperOf__/ } @lnk;
        @subcls = map { m/^cos_l_${token}__isSuperOf__(.*)$/ } @subcls;
        $sublst = "@subcls";
# DEBUG print STDERR "sublst:\n$sublst\n";
#       remove link pattern
        @lnk = grep { ! m/^cos_l_($pat)__isSuperOf__/ } @lnk;
#       remove subclass pattern
        @sym = grep { ! m/^cos_c_(|m|pm)($pat)$/ } @sym;
        @sym = grep { ! m/^cos_m_($token)_(|m|pm)($pat)(_|$)/ } @sym;
    }

#   display removed subclasses
    $rmlst = qx(echo $rmlst);
    if ( $rmlst ) {
        print STDERR "** Removed subclasses:\n";
        print STDERR "$rmlst\n";
        $rmlst = '';
    }
}

#----------------------------------------------------------------- up to here
##### Start of _cossym.c #####

mkpath( dirname($out) );

open(my $outfh, ">", "$out") or die "cannot open > '$out': $!";

print $outfh <<"END_OF_TEXT" ;
/*
 * -----------------------------
 * COS symbols
 *
 * DO NOT EDIT - DO NOT EDIT - DO NOT EDIT
 * This file was automatically generated by $progname
 * $datestr
 * -----------------------------
 */

END_OF_TEXT

# output extern declarations
foreach my $s (@sym) {
     print $outfh "extern struct Any $s;\n";
}
print $outfh "\n";

# output table definition
print $outfh 'static struct Any* symtbl[] = {'."\n";
foreach my $s (@sym) {
     print $outfh "  &$s,\n";
}

print $outfh <<"END_OF_TEXT" ;
  0
};

void cos_symbol_register(struct Any**, const char*);

END_OF_TEXT

foreach my $m (@modlist) {
    print $outfh "void cos_symbol_init$m(void);\n";
}

print $outfh <<"END_OF_TEXT" ;

void cos_symbol_init$modname(void);
void cos_symbol_init$modname(void)
{
   static int done = 0;

   if (!done) {
     done = 1;
END_OF_TEXT

foreach my $m (@modlist) {
    print $outfh "     cos_symbol_init$m();\n";
}

print $outfh <<"END_OF_TEXT" ;
     cos_symbol_register(symtbl,"$prjname");
   }
}
END_OF_TEXT

##### Enf of _cossym.c #####
close($outfh);

# end of script
