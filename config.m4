dnl $Id$
dnl config.m4 for extension kmf_helper

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(kmf_helper, for kmf_helper support,
dnl Make sure that the comment is aligned:
dnl [  --with-kmf_helper             Include kmf_helper support])

dnl Otherwise use enable:

dnl PHP_ARG_ENABLE(kmf_helper, whether to enable kmf_helper support,
dnl Make sure that the comment is aligned:
dnl [  --enable-kmf_helper           Enable kmf_helper support])

if test "$PHP_KMF_HELPER" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-kmf_helper -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/kmf_helper.h"  # you most likely want to change this
  dnl if test -r $PHP_KMF_HELPER/$SEARCH_FOR; then # path given as parameter
  dnl   KMF_HELPER_DIR=$PHP_KMF_HELPER
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for kmf_helper files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       KMF_HELPER_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$KMF_HELPER_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the kmf_helper distribution])
  dnl fi

  dnl # --with-kmf_helper -> add include path
  dnl PHP_ADD_INCLUDE($KMF_HELPER_DIR/include)

  dnl # --with-kmf_helper -> check for lib and symbol presence
  dnl LIBNAME=kmf_helper # you may want to change this
  dnl LIBSYMBOL=kmf_helper # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $KMF_HELPER_DIR/$PHP_LIBDIR, KMF_HELPER_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_KMF_HELPERLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong kmf_helper lib version or lib not found])
  dnl ],[
  dnl   -L$KMF_HELPER_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(KMF_HELPER_SHARED_LIBADD)

  PHP_NEW_EXTENSION(kmf_helper, kmf_helper.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
