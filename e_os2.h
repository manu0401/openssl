/* e_os2.h */
/* ====================================================================
 * Copyright (c) 1998-2000 The OpenSSL Project.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer. 
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. All advertising materials mentioning features or use of this
 *    software must display the following acknowledgment:
 *    "This product includes software developed by the OpenSSL Project
 *    for use in the OpenSSL Toolkit. (http://www.openssl.org/)"
 *
 * 4. The names "OpenSSL Toolkit" and "OpenSSL Project" must not be used to
 *    endorse or promote products derived from this software without
 *    prior written permission. For written permission, please contact
 *    openssl-core@openssl.org.
 *
 * 5. Products derived from this software may not be called "OpenSSL"
 *    nor may "OpenSSL" appear in their names without prior written
 *    permission of the OpenSSL Project.
 *
 * 6. Redistributions of any form whatsoever must retain the following
 *    acknowledgment:
 *    "This product includes software developed by the OpenSSL Project
 *    for use in the OpenSSL Toolkit (http://www.openssl.org/)"
 *
 * THIS SOFTWARE IS PROVIDED BY THE OpenSSL PROJECT ``AS IS'' AND ANY
 * EXPRESSED OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE OpenSSL PROJECT OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 * ====================================================================
 *
 * This product includes cryptographic software written by Eric Young
 * (eay@cryptsoft.com).  This product includes software written by Tim
 * Hudson (tjh@cryptsoft.com).
 *
 */

#ifndef HEADER_E_OS2_H
#define HEADER_E_OS2_H

#include <openssl/opensslconf.h> /* OPENSSL_UNISTD */

#ifdef  __cplusplus
extern "C" {
#endif

/******************************************************************************
 * Detect operating systems.  This probably needs completing.
 * The result is that at least one OPENSSL_SYS_os macro should be defined.
 * However, if none is defined, Unix is assumed.
 **/

#define OPENSSL_SYS_UNIX

/* ----------------------- Macintosh, before MacOS X ----------------------- */
#if defined(__MWERKS__) && defined(macintosh) || defined(OPENSSL_SYSNAME_MAC)
# undef OPENSSL_SYS_UNIX
# define OPENSSL_SYS_MACINTOSH_CLASSIC
#endif

/* ---------------------- Microsoft operating systems ---------------------- */

/* The 16 bit environments are pretty straightforward */
#if defined(OPENSSL_SYSNAME_WIN16) || defined(OPENSSL_SYSNAME_MSDOS)
# undef OPENSSL_SYS_UNIX
# define OPENSSL_SYS_MSDOS
#endif
#if defined(OPENSSL_SYSNAME_WIN16)
# undef OPENSSL_SYS_UNIX
# define OPENSSL_SYS_WIN16
#endif

/* For 32 bit environment, there seems to be the CygWin environment and then
   all the others that try to do the same thing Microsoft does... */
#if defined(__CYGWIN32__) || defined(OPENSSL_SYSNAME_CYGWIN32)
# undef OPENSSL_SYS_UNIX
# define OPENSSL_SYS_WIN32_CYGWIN
#else
# if defined(_WIN32) || defined(OPENSSL_SYSNAME_WIN32)
#  undef OPENSSL_SYS_UNIX
#  define OPENSSL_SYS_WIN32
# endif
# if defined(OPENSSL_SYSNAME_WINNT)
#  undef OPENSSL_SYS_UNIX
#  define OPENSSL_SYS_WINNT
# endif
#endif

/* Anything that tries to look like Microsoft is "Windows" */
#if defined(OPENSSL_SYS_WIN16) || defined(OPENSSL_SYS_WIN32) || defined(OPENSSL_SYS_WINNT)
# undef OPENSSL_SYS_UNIX
# define OPENSSL_SYS_WINDOWS
#endif

/* -------------------------------- OpenVMS -------------------------------- */
#if defined(__VMS) || defined(VMS) || defined(OPENSSL_SYSNAME_VMS)
# undef OPENSSL_SYS_UNIX
# define OPENSSL_SYS_VMS
# if defined(__DECC)
#  define OPENSSL_SYS_VMS_DECC
# else
#  define OPENSSL_SYS_VMS_NODECC
# endif
#endif

/* --------------------------------- Unix ---------------------------------- */
#ifdef OPENSSL_SYS_UNIX
# if defined(linus) || defined(OPENSSL_SYSNAME_LINUX)
#  define OPENSSL_SYS_LINUX
# endif
# ifdef OPENSSL_SYSNAME_MPE
#  define OPENSSL_SYS_MPE
# endif
# ifdef OPENSSL_SYSNAME_SNI
#  define OPENSSL_SYS_SNI
# endif
# ifdef OPENSSL_SYSNAME_ULTRASPARC
#  define OPENSSL_SYS_ULTRASPARC
# endif
# ifdef OPENSSL_SYSNAME_NEWS4
#  define OPENSSL_SYS_NEWS4
# endif
# ifdef OPENSSL_SYSNAME_MACOSX
#  define OPENSSL_SYS_MACOSX
# endif
# if defined(_CRAY) || defined(OPENSSL_SYSNAME_CRAY)
#  define OPENSSL_SYS_CRAY
# endif
# if defined(_AIX) || defined(OPENSSL_SYSNAME_AIX)
#  define OPENSSL_SYS_AIX
# endif
#endif

/**
 * That's it for OS-specific stuff
 *****************************************************************************/


/* Specials for I/O an exit */
#ifdef OPENSSL_SYS_MSDOS
# define OPENSSL_UNISTD_IO <io.h>
# define OPENSSL_DECLARE_EXIT extern void exit(int);
#else
# define OPENSSL_UNISTD_IO OPENSSL_UNISTD
# define OPENSSL_DECLARE_EXIT /* declared in unistd.h */
#endif

/* Definitions of OPENSSL_GLOBAL and OPENSSL_EXTERN, to define and declare
   certain global symbols that, with some compilers under VMS, have to be
   defined and declared explicitely with globaldef and globalref.
   Definitions of OPENSSL_EXPORT and OPENSSL_IMPORT, to define and declare
   DLL exports and imports for compilers under Win32.  These are a little
   more complicated to use.  Basically, for any library that exports some
   global variables, the following code must be present in the header file
   that declares them, before OPENSSL_EXTERN is used:

   #ifdef SOME_BUILD_FLAG_MACRO
   # undef OPENSSL_EXTERN
   # define OPENSSL_EXTERN OPENSSL_EXPORT
   #endif

   The default is to have OPENSSL_EXPORT, OPENSSL_IMPORT and OPENSSL_GLOBAL
   have some generally sensible values, and for OPENSSL_EXTERN to have the
   value OPENSSL_IMPORT.
*/

#if defined(OPENSSL_SYS_VMS_NODECC)
# define OPENSSL_EXPORT globalref
# define OPENSSL_IMPORT globalref
# define OPENSSL_GLOBAL globaldef
#elif defined(OPENSSL_SYS_WINDOWS)
# define OPENSSL_EXPORT extern _declspec(dllexport)
# define OPENSSL_IMPORT extern _declspec(dllimport)
# define OPENSSL_GLOBAL
#else
# define OPENSSL_EXPORT extern
# define OPENSSL_IMPORT extern
# define OPENSSL_GLOBAL
#endif
#define OPENSSL_EXTERN OPENSSL_IMPORT

#ifdef  __cplusplus
}
#endif
#endif
