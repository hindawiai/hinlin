<शैली गुरु>
/* zconf.h -- configuration of the zlib compression library
 * Copyright (C) 1995-1998 Jean-loup Gailly.
 * For conditions of distribution and use, see copyright notice in zlib.h 
 */

/* @(#) $Id$ */

#अगर_अघोषित _ZCONF_H
#घोषणा _ZCONF_H

/* The memory requirements क्रम deflate are (in bytes):
            (1 << (winकरोwBits+2)) +  (1 << (memLevel+9))
 that is: 128K क्रम winकरोwBits=15  +  128K क्रम memLevel = 8  (शेष values)
 plus a few kilobytes क्रम small objects. For example, अगर you want to reduce
 the शेष memory requirements from 256K to 128K, compile with
     make CFLAGS="-O -DMAX_WBITS=14 -DMAX_MEM_LEVEL=7"
 Of course this will generally degrade compression (there's no मुक्त lunch).

   The memory requirements क्रम inflate are (in bytes) 1 << winकरोwBits
 that is, 32K क्रम winकरोwBits=15 (शेष value) plus a few kilobytes
 क्रम small objects.
*/

/* Maximum value क्रम memLevel in deflateInit2 */
#अगर_अघोषित MAX_MEM_LEVEL
#  define MAX_MEM_LEVEL 8
#पूर्ण_अगर

/* Maximum value क्रम winकरोwBits in deflateInit2 and inflateInit2.
 * WARNING: reducing MAX_WBITS makes minigzip unable to extract .gz files
 * created by gzip. (Files created by minigzip can still be extracted by
 * gzip.)
 */
#अगर_अघोषित MAX_WBITS
#  define MAX_WBITS   15 /* 32K LZ77 winकरोw */
#पूर्ण_अगर

/* शेष winकरोwBits क्रम decompression. MAX_WBITS is क्रम compression only */
#अगर_अघोषित DEF_WBITS
#  define DEF_WBITS MAX_WBITS
#पूर्ण_अगर

/* शेष memLevel */
#अगर MAX_MEM_LEVEL >= 8
#  define DEF_MEM_LEVEL 8
#अन्यथा
#  define DEF_MEM_LEVEL  MAX_MEM_LEVEL
#पूर्ण_अगर

                        /* Type declarations */

प्रकार अचिन्हित अक्षर  Byte;  /* 8 bits */
प्रकार अचिन्हित पूर्णांक   uInt;  /* 16 bits or more */
प्रकार अचिन्हित दीर्घ  uLong; /* 32 bits or more */
प्रकार व्योम     *व्योमp;

#पूर्ण_अगर /* _ZCONF_H */
