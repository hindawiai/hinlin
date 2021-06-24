<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/zlib.h>

/* bits taken from ppc */

बाह्य व्योम *avail_ram, *end_avail;

व्योम निकास (व्योम)
अणु
  क्रम (;;);
पूर्ण

व्योम *zalloc(अचिन्हित size)
अणु
        व्योम *p = avail_ram;

        size = (size + 7) & -8;
        avail_ram += size;
        अगर (avail_ram > end_avail) अणु
                //माला_दो("oops... out of memory\n");
                //छोड़ो();
                निकास ();
        पूर्ण
        वापस p;
पूर्ण

#घोषणा HEAD_CRC        2
#घोषणा EXTRA_FIELD     4
#घोषणा ORIG_NAME       8
#घोषणा COMMENT         0x10
#घोषणा RESERVED        0xe0

#घोषणा DEFLATED        8

व्योम gunzip (व्योम *dst, पूर्णांक dstlen, अचिन्हित अक्षर *src, पूर्णांक *lenp)
अणु
	z_stream s;
	पूर्णांक r, i, flags;

        /* skip header */
        i = 10;
        flags = src[3];
        अगर (src[2] != DEFLATED || (flags & RESERVED) != 0) अणु
                //माला_दो("bad gzipped data\n");
                निकास();
        पूर्ण
        अगर ((flags & EXTRA_FIELD) != 0)
                i = 12 + src[10] + (src[11] << 8);
        अगर ((flags & ORIG_NAME) != 0)
                जबतक (src[i++] != 0)
                        ;
        अगर ((flags & COMMENT) != 0)
                जबतक (src[i++] != 0)
                        ;
        अगर ((flags & HEAD_CRC) != 0)
                i += 2;
        अगर (i >= *lenp) अणु
                //माला_दो("gunzip: ran out of data in header\n");
                निकास();
        पूर्ण

	s.workspace = zalloc(zlib_inflate_workspacesize());
        r = zlib_inflateInit2(&s, -MAX_WBITS);
        अगर (r != Z_OK) अणु
                //माला_दो("inflateInit2 returned "); puthex(r); माला_दो("\n");
                निकास();
        पूर्ण
        s.next_in = src + i;
        s.avail_in = *lenp - i;
        s.next_out = dst;
        s.avail_out = dstlen;
        r = zlib_inflate(&s, Z_FINISH);
        अगर (r != Z_OK && r != Z_STREAM_END) अणु
                //माला_दो("inflate returned "); puthex(r); माला_दो("\n");
                निकास();
        पूर्ण
        *lenp = s.next_out - (अचिन्हित अक्षर *) dst;
        zlib_inflateEnd(&s);
पूर्ण

