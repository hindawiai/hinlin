<शैली गुरु>
/* zutil.h -- पूर्णांकernal पूर्णांकerface and configuration of the compression library
 * Copyright (C) 1995-1998 Jean-loup Gailly.
 * For conditions of distribution and use, see copyright notice in zlib.h
 */

/* WARNING: this file should *not* be used by applications. It is
   part of the implementation of the compression library and is
   subject to change. Applications should only use zlib.h.
 */

/* @(#) $Id: zutil.h,v 1.1 2000/01/01 03:32:23 davem Exp $ */

#अगर_अघोषित _Z_UTIL_H
#घोषणा _Z_UTIL_H

#समावेश <linux/zlib.h>
#समावेश <linux/माला.स>
#समावेश <linux/kernel.h>

प्रकार अचिन्हित अक्षर  uch;
प्रकार अचिन्हित लघु ush;
प्रकार अचिन्हित दीर्घ  ulg;

        /* common स्थिरants */

#घोषणा STORED_BLOCK 0
#घोषणा STATIC_TREES 1
#घोषणा DYN_TREES    2
/* The three kinds of block type */

#घोषणा MIN_MATCH  3
#घोषणा MAX_MATCH  258
/* The minimum and maximum match lengths */

#घोषणा PRESET_DICT 0x20 /* preset dictionary flag in zlib header */

        /* target dependencies */

        /* Common शेषs */

#अगर_अघोषित OS_CODE
#  define OS_CODE  0x03  /* assume Unix */
#पूर्ण_अगर

         /* functions */

प्रकार uLong (*check_func) (uLong check, स्थिर Byte *buf,
				       uInt len);


                        /* checksum functions */

#घोषणा BASE 65521L /* largest prime smaller than 65536 */
#घोषणा NMAX 5552
/* NMAX is the largest n such that 255n(n+1)/2 + (n+1)(BASE-1) <= 2^32-1 */

#घोषणा DO1(buf,i)  अणुs1 += buf[i]; s2 += s1;पूर्ण
#घोषणा DO2(buf,i)  DO1(buf,i); DO1(buf,i+1);
#घोषणा DO4(buf,i)  DO2(buf,i); DO2(buf,i+2);
#घोषणा DO8(buf,i)  DO4(buf,i); DO4(buf,i+4);
#घोषणा DO16(buf)   DO8(buf,0); DO8(buf,8);

/* ========================================================================= */
/*
     Update a running Adler-32 checksum with the bytes buf[0..len-1] and
   वापस the updated checksum. If buf is शून्य, this function वापसs
   the required initial value क्रम the checksum.
   An Adler-32 checksum is almost as reliable as a CRC32 but can be computed
   much faster. Usage example:

     uLong adler = zlib_adler32(0L, शून्य, 0);

     जबतक (पढ़ो_buffer(buffer, length) != खातापूर्ण) अणु
       adler = zlib_adler32(adler, buffer, length);
     पूर्ण
     अगर (adler != original_adler) error();
*/
अटल अंतरभूत uLong zlib_adler32(uLong adler,
				 स्थिर Byte *buf,
				 uInt len)
अणु
    अचिन्हित दीर्घ s1 = adler & 0xffff;
    अचिन्हित दीर्घ s2 = (adler >> 16) & 0xffff;
    पूर्णांक k;

    अगर (buf == शून्य) वापस 1L;

    जबतक (len > 0) अणु
        k = len < NMAX ? len : NMAX;
        len -= k;
        जबतक (k >= 16) अणु
            DO16(buf);
	    buf += 16;
            k -= 16;
        पूर्ण
        अगर (k != 0) करो अणु
            s1 += *buf++;
	    s2 += s1;
        पूर्ण जबतक (--k);
        s1 %= BASE;
        s2 %= BASE;
    पूर्ण
    वापस (s2 << 16) | s1;
पूर्ण

#पूर्ण_अगर /* _Z_UTIL_H */
