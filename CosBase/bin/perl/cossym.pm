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

# default settings
$progname=basename($0);
$nm="nm -P -g";
@infiles=();
$filelist='';
$out="_cossym.c";
$datestr=scalar localtime();

# default settings
$modlist='';
$modname='';
$prjname='';
$rmgen='';
$rmcls='';
$rmdoc='';
$rmtrc='';

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
    "in=s" =>    \@infiles,  # each file contains a list of filenames to process (TODO: fix in gen and prp!)
    "out=s" =>   \$out,
    "prj=s" =>   \$prjname,
    "mod=s" =>   \$modname, # need to handle prjname override
    "dep=s" =>   \@modlist,
    "rmgen=s" => \@rmgen,
    "rmcls=s" => \@rmcls,
    "rmdoc" =>   \$rmdoc,
    "rmtrc" =>   \$rmtrc,
    "nm=s" =>    \$nm,
) or usage();

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
    $sym=`$nm $filelist \
    | grep -E -e "^_?cos_($prefix)_($token) D " \
    | cut  -f 1 -d ' ' \
    | sed  -e 's/^_cos/cos/g' \
    | sort -u`
    if ( @rmcls ) {
        $lnk=`$nm $filelist \
        | grep -E -e "^_?cos_l_($token) B " \
        | cut  -f 1 -d ' ' \
        | sed  -e 's/^_cos/cos/g' \
        | sort -u`
    }
}

# remove generic patterns
if [ "$rmgen" != "" ] ; then
    for pat in $rmgen ; do
#       extract generics
        if [ "$rmtrc" = "Y" ] ; then
            gen=`echo $sym \
               | tr ' ' '\n' \
               | grep -E -e "^cos_g_($pat)$" \
               | sed  -e 's/^cos_g_//g'`
            rmlst="$rmlst $gen"
        fi
#       remove generic pattern
        sym=`echo $sym \
           | tr ' ' '\n' \
           | grep -E -v -e "^cos_g_($pat)$" \
           | grep -E -v -e "^cos_m_($pat)_"`
    done

#   display removed generics
    rmlst=`echo $rmlst`
    if [ "$rmlst" != "" ] ; then
        echo '** Removed generics:' >&2
        echo `echo $rmlst` >&2
        rmlst=
    fi
fi

# remove class patterns and subclasses
if [ "$rmcls" != "" ] ; then
    for pat in $rmcls ; do
#       extract classes
        if [ "$rmtrc" = "Y" ] ; then
            cls=`echo $sym \
               | tr ' ' '\n' \
               | grep -E -e "^cos_c_($pat)$" \
               | sed  -e 's/^cos_c_//g'`
            rmlst="$rmlst $cls"
        fi
#       extract subclasses
        sub=`echo $lnk \
           | tr ' ' '\n' \
           | grep -E -e "^cos_l_($pat)__isSuperOf__" \
           | sed  -e "s/^cos_l_${token}__isSuperOf__//g"`
        sublst="$sublst $sub"
# DEBUG echo "sublst:" `echo $sublst` >&2
#       remove link pattern
        lnk=`echo $lnk \
           | tr ' ' '\n' \
           | grep -E -v -e "^cos_l_($pat)__isSuperOf__"`
#       remove class pattern
        sym=`echo $sym \
           | tr ' ' '\n' \
           | grep -E -v -e "^cos_c_(|m|pm)($pat)$" \
           | grep -E -v -e "^cos_m_($token)_(|m|pm)($pat)(_|$)"`
    done

#   display removed classes
    rmlst=`echo $rmlst`
    if [ "$rmlst" != "" ] ; then
        echo '** Removed classes:' >&2
        echo `echo $rmlst` >&2
        rmlst=
    fi

#   remove subclasses
    sublst=`echo $sublst`
    while [ "$sublst" != "" ] ; do
#       add subclasses to removed classes
        if [ "$rmtrc" = "Y" ] ; then
            rmlst="$rmlst $sublst"
        fi
#       build subclass pattern
        pat=`echo $sublst \
           | sed -e 's/ /\|/g'`
# DEBUG echo "pat: $pat" >&2
#       extract subclasses
        sub=`echo $lnk \
           | tr ' ' '\n' \
           | grep -E -e "^cos_l_($pat)__isSuperOf__" \
           | sed  -e "s/^cos_l_${token}__isSuperOf__//g"`
        sublst="$sub"
# DEBUG echo "sublst:" `echo $sublst` >&2
#       remove link pattern
        lnk=`echo $lnk \
           | tr ' ' '\n' \
           | grep -E -v -e "^cos_l_($pat)__isSuperOf__"`
#       remove subclass pattern
        sym=`echo $sym \
           | tr ' ' '\n' \
           | grep -E -v -e "^cos_c_(|m|pm)($pat)$" \
           | grep -E -v -e "^cos_m_($token)_(|m|pm)($pat)(_|$)"`
    done

#   display removed subclasses
    rmlst=`echo $rmlst`
    if [ "$rmlst" != "" ] ; then
        echo '** Removed subclasses:' >&2
        echo `echo $rmlst` >&2
        rmlst=
    fi
fi

##### Start of _cossym.c #####

mkdir -p `dirname $out`

cat > $out <<"END_OF_TEXT" ;
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
for s in $sym ; do
    echo "extern struct Any $s;"       >> $out
done
echo                                   >> $out

# output table definition
echo 'static struct Any* symtbl[] = {' >> $out

for s in $sym ; do
    echo "  &$s,"                      >> $out
done

cat >> $out <<"END_OF_TEXT" ;
  0
};

void cos_symbol_register(struct Any**, const char*);

END_OF_TEXT

for m in $modlist ; do
  echo "void cos_symbol_init$m(void);"    >> $out
done

cat >> $out <<"END_OF_TEXT" ;

void cos_symbol_init$modname(void);
void cos_symbol_init$modname(void)
{
   static int done = 0;
   
   if (!done) {
     done = 1;
END_OF_TEXT

for m in $modlist ; do
  echo "     cos_symbol_init$m();"        >> $out
done

cat >> $out <<"END_OF_TEXT" ;
     cos_symbol_register(symtbl,"$prjname");
   }
}
END_OF_TEXT

##### Enf of _cossym.c #####

# end of script
