dnl $Id$
dnl config.m4 for extension uniqueid

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

PHP_ARG_WITH(uniqueid, for uniqueid support,
[  --with-uniqueid             Include uniqueid support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(uniqueid, whether to enable uniqueid support,
[  --enable-uniqueid           Enable uniqueid support])

if test "$PHP_UNIQUEID" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-uniqueid -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/uniqueid.h"  # you most likely want to change this
  dnl if test -r $PHP_UNIQUEID/$SEARCH_FOR; then # path given as parameter
  dnl   UNIQUEID_DIR=$PHP_UNIQUEID
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for uniqueid files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       UNIQUEID_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$UNIQUEID_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the uniqueid distribution])
  dnl fi

  dnl # --with-uniqueid -> add include path
  dnl PHP_ADD_INCLUDE($UNIQUEID_DIR/include)

  dnl # --with-uniqueid -> check for lib and symbol presence
  dnl LIBNAME=uniqueid # you may want to change this
  dnl LIBSYMBOL=uniqueid # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $UNIQUEID_DIR/$PHP_LIBDIR, UNIQUEID_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_UNIQUEIDLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong uniqueid lib version or lib not found])
  dnl ],[
  dnl   -L$UNIQUEID_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(UNIQUEID_SHARED_LIBADD)

  PHP_NEW_EXTENSION(uniqueid, uniqueid.c incr.c semop.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
