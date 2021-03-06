/* Functions that emulate UNIX catgets, some small DOS file functions */

/* Copyright (C) 1999,2000 Jim Hall <jhall@freedos.org> */
/* Kitten version by Tom Ehlert, heavily modified by Eric Auer 2003 */

/*
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110, USA
*/


#ifndef _CATGETS_H
#define _CATGETS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Used to determine the OS environment at compile time */
#define DOS_DEFINE (defined(MSDOS) || defined(__DOS__) || defined(__MSDOS__) || defined(_MSDOS))
#define W32_DEFINE (defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__))
#define UNIX_DEFINE (!DOS_DEFINE && !W32_DEFINE) /* If not Win32 or DOS, assume it's a POSIX-based environment */

#if UNIX_DEFINE
    #include <nl_types.h>
    #include <unistd.h>
#elif W32_DEFINE
    #include <io.h>
#endif

/* Data types */

typedef int nl_catd;

/* Functions */

char    *kittengets(int set_number, int message_number,char *message);
nl_catd kittenopen(char *name);
void    kittenclose (void);

#if !UNIX_DEFINE
    #define catgets(catalog, set,message_number,message) kittengets(set,message_number,message)
    #define catopen(name,flag) kittenopen(name)
    #define catclose(catalog)  kittenclose()
#endif

int get_line (int file, char *buffer, int size);

#if !UNIX_DEFINE
#if DOS_DEFINE
    int dos_open(char *filename, int mode);
    int dos_read(int file, void *ptr, unsigned count);
    int dos_write(int file, void *ptr, unsigned count);
    void dos_close(int file);

    #define open(filename,mode) dos_open(filename,mode)
    #define read(file, ptr, count) dos_read(file,ptr,count)
    #define write(file, ptr, count) dos_write(file,ptr,count)
    #define close(file) dos_close(file)
#elif W32_DEFINE /* Windows */
#if UNICODE
    #define open(filename,mode) _wopen(filename,mode)
#else /* ANSI */
    #define open(filename,mode) _open(filename,mode))
#endif /* UNICODE */
    #define read(file,ptr,count) _read(file,ptr,count)
    #define write(file,ptr,count) _write(file,ptr,count)
    #define close(file) _close(file)
#endif /* DOS_DEFINE */

#ifdef __cplusplus
}
#endif

#endif /* _CATGETS_H */
