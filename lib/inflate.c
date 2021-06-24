<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा DEBG(x)
#घोषणा DEBG1(x)
/* inflate.c -- Not copyrighted 1992 by Mark Adler
   version c10p1, 10 January 1993 */

/* 
 * Adapted क्रम booting Linux by Hannu Savolainen 1993
 * based on gzip-1.0.3 
 *
 * Nicolas Pitre <nico@fluxnic.net>, 1999/04/14 :
 *   Little mods क्रम all variable to reside either पूर्णांकo rodata or bss segments
 *   by marking स्थिरant variables with 'const' and initializing all the others
 *   at run-समय only.  This allows क्रम the kernel uncompressor to run
 *   directly from Flash or ROM memory on embedded प्रणालीs.
 */

/*
   Inflate deflated (PKZIP's method 8 compressed) data.  The compression
   method searches क्रम as much of the current string of bytes (up to a
   length of 258) in the previous 32 K bytes.  If it करोesn't find any
   matches (of at least length 3), it codes the next byte.  Otherwise, it
   codes the length of the matched string and its distance backwards from
   the current position.  There is a single Huffman code that codes both
   single bytes (called "literals") and match lengths.  A second Huffman
   code codes the distance inक्रमmation, which follows a length code.  Each
   length or distance code actually represents a base value and a number
   of "extra" (someबार zero) bits to get to add to the base value.  At
   the end of each deflated block is a special end-of-block (EOB) literal/
   length code.  The decoding process is basically: get a literal/length
   code; अगर EOB then करोne; अगर a literal, emit the decoded byte; अगर a
   length then get the distance and emit the referred-to bytes from the
   sliding winकरोw of previously emitted data.

   There are (currently) three kinds of inflate blocks: stored, fixed, and
   dynamic.  The compressor deals with some chunk of data at a समय, and
   decides which method to use on a chunk-by-chunk basis.  A chunk might
   typically be 32 K or 64 K.  If the chunk is incompressible, then the
   "stored" method is used.  In this हाल, the bytes are simply stored as
   is, eight bits per byte, with none of the above coding.  The bytes are
   preceded by a count, since there is no दीर्घer an EOB code.

   If the data is compressible, then either the fixed or dynamic methods
   are used.  In the dynamic method, the compressed data is preceded by
   an encoding of the literal/length and distance Huffman codes that are
   to be used to decode this block.  The representation is itself Huffman
   coded, and so is preceded by a description of that code.  These code
   descriptions take up a little space, and so क्रम small blocks, there is
   a predefined set of codes, called the fixed codes.  The fixed method is
   used अगर the block codes up smaller that way (usually क्रम quite small
   chunks), otherwise the dynamic method is used.  In the latter हाल, the
   codes are customized to the probabilities in the current block, and so
   can code it much better than the pre-determined fixed codes.
 
   The Huffman codes themselves are decoded using a multi-level table
   lookup, in order to maximize the speed of decoding plus the speed of
   building the decoding tables.  See the comments below that precede the
   lbits and dbits tuning parameters.
 */


/*
   Notes beyond the 1.93a appnote.txt:

   1. Distance poपूर्णांकers never poपूर्णांक beक्रमe the beginning of the output
      stream.
   2. Distance poपूर्णांकers can poपूर्णांक back across blocks, up to 32k away.
   3. There is an implied maximum of 7 bits क्रम the bit length table and
      15 bits क्रम the actual data.
   4. If only one code exists, then it is encoded using one bit.  (Zero
      would be more efficient, but perhaps a little confusing.)  If two
      codes exist, they are coded using one bit each (0 and 1).
   5. There is no way of sending zero distance codes--a dummy must be
      sent अगर there are none.  (History: a pre 2.0 version of PKZIP would
      store blocks with no distance codes, but this was discovered to be
      too harsh a criterion.)  Valid only क्रम 1.93a.  2.04c करोes allow
      zero distance codes, which is sent as one code of zero bits in
      length.
   6. There are up to 286 literal/length codes.  Code 256 represents the
      end-of-block.  Note however that the अटल length tree defines
      288 codes just to fill out the Huffman codes.  Codes 286 and 287
      cannot be used though, since there is no length base or extra bits
      defined क्रम them.  Similarly, there are up to 30 distance codes.
      However, अटल trees define 32 codes (all 5 bits) to fill out the
      Huffman codes, but the last two had better not show up in the data.
   7. Unzip can check dynamic Huffman blocks क्रम complete code sets.
      The exception is that a single code would not be complete (see #4).
   8. The five bits following the block type is really the number of
      literal codes sent minus 257.
   9. Length codes 8,16,16 are पूर्णांकerpreted as 13 length codes of 8 bits
      (1+6+6).  Thereक्रमe, to output three बार the length, you output
      three codes (1+1+1), whereas to output four बार the same length,
      you only need two codes (1+3).  Hmm.
  10. In the tree reस्थिरruction algorithm, Code = Code + Increment
      only अगर BitLength(i) is not zero.  (Pretty obvious.)
  11. Correction: 4 Bits: # of Bit Length codes - 4     (4 - 19)
  12. Note: length code 284 can represent 227-258, but length code 285
      really is 258.  The last length deserves its own, लघु code
      since it माला_लो used a lot in very redundant files.  The length
      258 is special since 258 - 3 (the min match length) is 255.
  13. The literal/length and distance code bit lengths are पढ़ो as a
      single stream of lengths.  It is possible (and advantageous) क्रम
      a repeat code (16, 17, or 18) to go across the boundary between
      the two sets of lengths.
 */
#समावेश <linux/compiler.h>
#अगर_घोषित NO_INFLATE_MALLOC
#समावेश <linux/slab.h>
#पूर्ण_अगर

#अगर_घोषित RCSID
अटल अक्षर rcsid[] = "#Id: inflate.c,v 0.14 1993/06/10 13:27:04 jloup Exp #";
#पूर्ण_अगर

#अगर_अघोषित STATIC

#अगर defined(STDC_HEADERS) || defined(HAVE_STDLIB_H)
#  include <sys/types.h>
#  include <मानककोष.स>
#पूर्ण_अगर

#समावेश "gzip.h"
#घोषणा STATIC
#पूर्ण_अगर /* !STATIC */

#अगर_अघोषित INIT
#घोषणा INIT
#पूर्ण_अगर
	
#घोषणा slide winकरोw

/* Huffman code lookup table entry--this entry is four bytes क्रम machines
   that have 16-bit poपूर्णांकers (e.g. PC's in the small or medium model).
   Valid extra bits are 0..13.  e == 15 is EOB (end of block), e == 16
   means that v is a literal, 16 < e < 32 means that v is a poपूर्णांकer to
   the next table, which codes e - 16 bits, and lastly e == 99 indicates
   an unused code.  If a code with e == 99 is looked up, this implies an
   error in the data. */
काष्ठा huft अणु
  uch e;                /* number of extra bits or operation */
  uch b;                /* number of bits in this code or subcode */
  जोड़ अणु
    ush n;              /* literal, length base, or distance base */
    काष्ठा huft *t;     /* poपूर्णांकer to next level of table */
  पूर्ण v;
पूर्ण;


/* Function prototypes */
STATIC पूर्णांक INIT huft_build OF((अचिन्हित *, अचिन्हित, अचिन्हित, 
		स्थिर ush *, स्थिर ush *, काष्ठा huft **, पूर्णांक *));
STATIC पूर्णांक INIT huft_मुक्त OF((काष्ठा huft *));
STATIC पूर्णांक INIT inflate_codes OF((काष्ठा huft *, काष्ठा huft *, पूर्णांक, पूर्णांक));
STATIC पूर्णांक INIT inflate_stored OF((व्योम));
STATIC पूर्णांक INIT inflate_fixed OF((व्योम));
STATIC पूर्णांक INIT inflate_dynamic OF((व्योम));
STATIC पूर्णांक INIT inflate_block OF((पूर्णांक *));
STATIC पूर्णांक INIT inflate OF((व्योम));


/* The inflate algorithm uses a sliding 32 K byte winकरोw on the uncompressed
   stream to find repeated byte strings.  This is implemented here as a
   circular buffer.  The index is updated simply by incrementing and then
   ANDing with 0x7fff (32K-1). */
/* It is left to other modules to supply the 32 K area.  It is assumed
   to be usable as अगर it were declared "uch slide[32768];" or as just
   "uch *slide;" and then दो_स्मृति'ed in the latter हाल.  The definition
   must be in unzip.h, included above. */
/* अचिन्हित wp;             current position in slide */
#घोषणा wp outcnt
#घोषणा flush_output(w) (wp=(w),flush_winकरोw())

/* Tables क्रम deflate from PKZIP's appnote.txt. */
अटल स्थिर अचिन्हित border[] = अणु    /* Order of the bit length code lengths */
        16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15पूर्ण;
अटल स्थिर ush cplens[] = अणु         /* Copy lengths क्रम literal codes 257..285 */
        3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 15, 17, 19, 23, 27, 31,
        35, 43, 51, 59, 67, 83, 99, 115, 131, 163, 195, 227, 258, 0, 0पूर्ण;
        /* note: see note #13 above about the 258 in this list. */
अटल स्थिर ush cplext[] = अणु         /* Extra bits क्रम literal codes 257..285 */
        0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2,
        3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 0, 99, 99पूर्ण; /* 99==invalid */
अटल स्थिर ush cpdist[] = अणु         /* Copy offsets क्रम distance codes 0..29 */
        1, 2, 3, 4, 5, 7, 9, 13, 17, 25, 33, 49, 65, 97, 129, 193,
        257, 385, 513, 769, 1025, 1537, 2049, 3073, 4097, 6145,
        8193, 12289, 16385, 24577पूर्ण;
अटल स्थिर ush cpdext[] = अणु         /* Extra bits क्रम distance codes */
        0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6,
        7, 7, 8, 8, 9, 9, 10, 10, 11, 11,
        12, 12, 13, 13पूर्ण;



/* Macros क्रम inflate() bit peeking and grabbing.
   The usage is:
   
        NEEDBITS(j)
        x = b & mask_bits[j];
        DUMPBITS(j)

   where NEEDBITS makes sure that b has at least j bits in it, and
   DUMPBITS हटाओs the bits from b.  The macros use the variable k
   क्रम the number of bits in b.  Normally, b and k are रेजिस्टर
   variables क्रम speed, and are initialized at the beginning of a
   routine that uses these macros from a global bit buffer and count.

   If we assume that EOB will be the दीर्घest code, then we will never
   ask क्रम bits with NEEDBITS that are beyond the end of the stream.
   So, NEEDBITS should not पढ़ो any more bytes than are needed to
   meet the request.  Then no bytes need to be "returned" to the buffer
   at the end of the last block.

   However, this assumption is not true क्रम fixed blocks--the EOB code
   is 7 bits, but the other literal/length codes can be 8 or 9 bits.
   (The EOB code is लघुer than other codes because fixed blocks are
   generally लघु.  So, जबतक a block always has an EOB, many other
   literal/length codes have a signअगरicantly lower probability of
   showing up at all.)  However, by making the first table have a
   lookup of seven bits, the EOB code will be found in that first
   lookup, and so will not require that too many bits be pulled from
   the stream.
 */

STATIC ulg bb;                         /* bit buffer */
STATIC अचिन्हित bk;                    /* bits in bit buffer */

STATIC स्थिर ush mask_bits[] = अणु
    0x0000,
    0x0001, 0x0003, 0x0007, 0x000f, 0x001f, 0x003f, 0x007f, 0x00ff,
    0x01ff, 0x03ff, 0x07ff, 0x0fff, 0x1fff, 0x3fff, 0x7fff, 0xffff
पूर्ण;

#घोषणा NEXTBYTE()  (अणु पूर्णांक v = get_byte(); अगर (v < 0) जाओ underrun; (uch)v; पूर्ण)
#घोषणा NEEDBITS(n) अणुजबतक(k<(n))अणुb|=((ulg)NEXTBYTE())<<k;k+=8;पूर्णपूर्ण
#घोषणा DUMPBITS(n) अणुb>>=(n);k-=(n);पूर्ण

#अगर_अघोषित NO_INFLATE_MALLOC
/* A trivial दो_स्मृति implementation, adapted from
 *  दो_स्मृति by Hannu Savolainen 1993 and Matthias Urlichs 1994
 */

अटल अचिन्हित दीर्घ दो_स्मृति_ptr;
अटल पूर्णांक दो_स्मृति_count;

अटल व्योम *दो_स्मृति(पूर्णांक size)
अणु
       व्योम *p;

       अगर (size < 0)
		error("Malloc error");
       अगर (!दो_स्मृति_ptr)
		दो_स्मृति_ptr = मुक्त_mem_ptr;

       दो_स्मृति_ptr = (दो_स्मृति_ptr + 3) & ~3;     /* Align */

       p = (व्योम *)दो_स्मृति_ptr;
       दो_स्मृति_ptr += size;

       अगर (मुक्त_mem_end_ptr && दो_स्मृति_ptr >= मुक्त_mem_end_ptr)
		error("Out of memory");

       दो_स्मृति_count++;
       वापस p;
पूर्ण

अटल व्योम मुक्त(व्योम *where)
अणु
       दो_स्मृति_count--;
       अगर (!दो_स्मृति_count)
		दो_स्मृति_ptr = मुक्त_mem_ptr;
पूर्ण
#अन्यथा
#घोषणा दो_स्मृति(a) kदो_स्मृति(a, GFP_KERNEL)
#घोषणा मुक्त(a) kमुक्त(a)
#पूर्ण_अगर

/*
   Huffman code decoding is perक्रमmed using a multi-level table lookup.
   The fastest way to decode is to simply build a lookup table whose
   size is determined by the दीर्घest code.  However, the समय it takes
   to build this table can also be a factor अगर the data being decoded
   is not very दीर्घ.  The most common codes are necessarily the
   लघुest codes, so those codes करोminate the decoding समय, and hence
   the speed.  The idea is you can have a लघुer table that decodes the
   लघुer, more probable codes, and then poपूर्णांक to subsidiary tables क्रम
   the दीर्घer codes.  The समय it costs to decode the दीर्घer codes is
   then traded against the समय it takes to make दीर्घer tables.

   This results of this trade are in the variables lbits and dbits
   below.  lbits is the number of bits the first level table क्रम literal/
   length codes can decode in one step, and dbits is the same thing क्रम
   the distance codes.  Subsequent tables are also less than or equal to
   those sizes.  These values may be adjusted either when all of the
   codes are लघुer than that, in which हाल the दीर्घest code length in
   bits is used, or when the लघुest code is *दीर्घer* than the requested
   table size, in which हाल the length of the लघुest code in bits is
   used.

   There are two dअगरferent values क्रम the two tables, since they code a
   dअगरferent number of possibilities each.  The literal/length table
   codes 286 possible values, or in a flat code, a little over eight
   bits.  The distance table codes 30 possible values, or a little less
   than five bits, flat.  The optimum values क्रम speed end up being
   about one bit more than those, so lbits is 8+1 and dbits is 5+1.
   The optimum values may dअगरfer though from machine to machine, and
   possibly even between compilers.  Your mileage may vary.
 */


STATIC स्थिर पूर्णांक lbits = 9;          /* bits in base literal/length lookup table */
STATIC स्थिर पूर्णांक dbits = 6;          /* bits in base distance lookup table */


/* If BMAX needs to be larger than 16, then h and x[] should be ulg. */
#घोषणा BMAX 16         /* maximum bit length of any code (16 क्रम explode) */
#घोषणा N_MAX 288       /* maximum number of codes in any set */


STATIC अचिन्हित hufts;         /* track memory usage */


STATIC पूर्णांक INIT huft_build(
	अचिन्हित *b,            /* code lengths in bits (all assumed <= BMAX) */
	अचिन्हित n,             /* number of codes (assumed <= N_MAX) */
	अचिन्हित s,             /* number of simple-valued codes (0..s-1) */
	स्थिर ush *d,           /* list of base values क्रम non-simple codes */
	स्थिर ush *e,           /* list of extra bits क्रम non-simple codes */
	काष्ठा huft **t,        /* result: starting table */
	पूर्णांक *m                  /* maximum lookup bits, वापसs actual */
	)
/* Given a list of code lengths and a maximum table size, make a set of
   tables to decode that set of codes.  Return zero on success, one अगर
   the given code set is incomplete (the tables are still built in this
   हाल), two अगर the input is invalid (all zero length codes or an
   oversubscribed set of lengths), and three अगर not enough memory. */
अणु
  अचिन्हित a;                   /* counter क्रम codes of length k */
  अचिन्हित f;                   /* i repeats in table every f entries */
  पूर्णांक g;                        /* maximum code length */
  पूर्णांक h;                        /* table level */
  रेजिस्टर अचिन्हित i;          /* counter, current code */
  रेजिस्टर अचिन्हित j;          /* counter */
  रेजिस्टर पूर्णांक k;               /* number of bits in current code */
  पूर्णांक l;                        /* bits per table (वापसed in m) */
  रेजिस्टर अचिन्हित *p;         /* poपूर्णांकer पूर्णांकo c[], b[], or v[] */
  रेजिस्टर काष्ठा huft *q;      /* poपूर्णांकs to current table */
  काष्ठा huft r;                /* table entry क्रम काष्ठाure assignment */
  रेजिस्टर पूर्णांक w;               /* bits beक्रमe this table == (l * h) */
  अचिन्हित *xp;                 /* poपूर्णांकer पूर्णांकo x */
  पूर्णांक y;                        /* number of dummy codes added */
  अचिन्हित z;                   /* number of entries in current table */
  काष्ठा अणु
    अचिन्हित c[BMAX+1];           /* bit length count table */
    काष्ठा huft *u[BMAX];         /* table stack */
    अचिन्हित v[N_MAX];            /* values in order of bit length */
    अचिन्हित x[BMAX+1];           /* bit offsets, then code stack */
  पूर्ण *stk;
  अचिन्हित *c, *v, *x;
  काष्ठा huft **u;
  पूर्णांक ret;

DEBG("huft1 ");

  stk = दो_स्मृति(माप(*stk));
  अगर (stk == शून्य)
    वापस 3;			/* out of memory */

  c = stk->c;
  v = stk->v;
  x = stk->x;
  u = stk->u;

  /* Generate counts क्रम each bit length */
  memzero(stk->c, माप(stk->c));
  p = b;  i = n;
  करो अणु
    Tracecv(*p, (मानक_त्रुटि, (n-i >= ' ' && n-i <= '~' ? "%c %d\n" : "0x%x %d\n"), 
	    n-i, *p));
    c[*p]++;                    /* assume all entries <= BMAX */
    p++;                      /* Can't combine with above line (Solaris bug) */
  पूर्ण जबतक (--i);
  अगर (c[0] == n)                /* null input--all zero length codes */
  अणु
    *t = (काष्ठा huft *)शून्य;
    *m = 0;
    ret = 2;
    जाओ out;
  पूर्ण

DEBG("huft2 ");

  /* Find minimum and maximum length, bound *m by those */
  l = *m;
  क्रम (j = 1; j <= BMAX; j++)
    अगर (c[j])
      अवरोध;
  k = j;                        /* minimum code length */
  अगर ((अचिन्हित)l < j)
    l = j;
  क्रम (i = BMAX; i; i--)
    अगर (c[i])
      अवरोध;
  g = i;                        /* maximum code length */
  अगर ((अचिन्हित)l > i)
    l = i;
  *m = l;

DEBG("huft3 ");

  /* Adjust last length count to fill out codes, अगर needed */
  क्रम (y = 1 << j; j < i; j++, y <<= 1)
    अगर ((y -= c[j]) < 0) अणु
      ret = 2;                 /* bad input: more codes than bits */
      जाओ out;
    पूर्ण
  अगर ((y -= c[i]) < 0) अणु
    ret = 2;
    जाओ out;
  पूर्ण
  c[i] += y;

DEBG("huft4 ");

  /* Generate starting offsets पूर्णांकo the value table क्रम each length */
  x[1] = j = 0;
  p = c + 1;  xp = x + 2;
  जबतक (--i) अणु                 /* note that i == g from above */
    *xp++ = (j += *p++);
  पूर्ण

DEBG("huft5 ");

  /* Make a table of values in order of bit lengths */
  p = b;  i = 0;
  करो अणु
    अगर ((j = *p++) != 0)
      v[x[j]++] = i;
  पूर्ण जबतक (++i < n);
  n = x[g];                   /* set n to length of v */

DEBG("h6 ");

  /* Generate the Huffman codes and क्रम each, make the table entries */
  x[0] = i = 0;                 /* first Huffman code is zero */
  p = v;                        /* grab values in bit order */
  h = -1;                       /* no tables yet--level -1 */
  w = -l;                       /* bits decoded == (l * h) */
  u[0] = (काष्ठा huft *)शून्य;   /* just to keep compilers happy */
  q = (काष्ठा huft *)शून्य;      /* ditto */
  z = 0;                        /* ditto */
DEBG("h6a ");

  /* go through the bit lengths (k alपढ़ोy is bits in लघुest code) */
  क्रम (; k <= g; k++)
  अणु
DEBG("h6b ");
    a = c[k];
    जबतक (a--)
    अणु
DEBG("h6b1 ");
      /* here i is the Huffman code of length k bits क्रम value *p */
      /* make tables up to required level */
      जबतक (k > w + l)
      अणु
DEBG1("1 ");
        h++;
        w += l;                 /* previous table always l bits */

        /* compute minimum size table less than or equal to l bits */
        z = (z = g - w) > (अचिन्हित)l ? l : z;  /* upper limit on table size */
        अगर ((f = 1 << (j = k - w)) > a + 1)     /* try a k-w bit table */
        अणु                       /* too few codes क्रम k-w bit table */
DEBG1("2 ");
          f -= a + 1;           /* deduct codes from patterns left */
          xp = c + k;
          अगर (j < z)
            जबतक (++j < z)       /* try smaller tables up to z bits */
            अणु
              अगर ((f <<= 1) <= *++xp)
                अवरोध;            /* enough codes to use up j bits */
              f -= *xp;           /* अन्यथा deduct codes from patterns */
            पूर्ण
        पूर्ण
DEBG1("3 ");
        z = 1 << j;             /* table entries क्रम j-bit table */

        /* allocate and link in new table */
        अगर ((q = (काष्ठा huft *)दो_स्मृति((z + 1)*माप(काष्ठा huft))) ==
            (काष्ठा huft *)शून्य)
        अणु
          अगर (h)
            huft_मुक्त(u[0]);
          ret = 3;             /* not enough memory */
	  जाओ out;
        पूर्ण
DEBG1("4 ");
        hufts += z + 1;         /* track memory usage */
        *t = q + 1;             /* link to list क्रम huft_मुक्त() */
        *(t = &(q->v.t)) = (काष्ठा huft *)शून्य;
        u[h] = ++q;             /* table starts after link */

DEBG1("5 ");
        /* connect to last table, अगर there is one */
        अगर (h)
        अणु
          x[h] = i;             /* save pattern क्रम backing up */
          r.b = (uch)l;         /* bits to dump beक्रमe this table */
          r.e = (uch)(16 + j);  /* bits in this table */
          r.v.t = q;            /* poपूर्णांकer to this table */
          j = i >> (w - l);     /* (get around Turbo C bug) */
          u[h-1][j] = r;        /* connect to last table */
        पूर्ण
DEBG1("6 ");
      पूर्ण
DEBG("h6c ");

      /* set up table entry in r */
      r.b = (uch)(k - w);
      अगर (p >= v + n)
        r.e = 99;               /* out of values--invalid code */
      अन्यथा अगर (*p < s)
      अणु
        r.e = (uch)(*p < 256 ? 16 : 15);    /* 256 is end-of-block code */
        r.v.n = (ush)(*p);             /* simple code is just the value */
	p++;                           /* one compiler करोes not like *p++ */
      पूर्ण
      अन्यथा
      अणु
        r.e = (uch)e[*p - s];   /* non-simple--look up in lists */
        r.v.n = d[*p++ - s];
      पूर्ण
DEBG("h6d ");

      /* fill code-like entries with r */
      f = 1 << (k - w);
      क्रम (j = i >> w; j < z; j += f)
        q[j] = r;

      /* backwards increment the k-bit code i */
      क्रम (j = 1 << (k - 1); i & j; j >>= 1)
        i ^= j;
      i ^= j;

      /* backup over finished tables */
      जबतक ((i & ((1 << w) - 1)) != x[h])
      अणु
        h--;                    /* करोn't need to update q */
        w -= l;
      पूर्ण
DEBG("h6e ");
    पूर्ण
DEBG("h6f ");
  पूर्ण

DEBG("huft7 ");

  /* Return true (1) अगर we were given an incomplete table */
  ret = y != 0 && g != 1;

  out:
  मुक्त(stk);
  वापस ret;
पूर्ण



STATIC पूर्णांक INIT huft_मुक्त(
	काष्ठा huft *t         /* table to मुक्त */
	)
/* Free the दो_स्मृति'ed tables built by huft_build(), which makes a linked
   list of the tables it made, with the links in a dummy first entry of
   each table. */
अणु
  रेजिस्टर काष्ठा huft *p, *q;


  /* Go through linked list, मुक्तing from the दो_स्मृतिed (t[-1]) address. */
  p = t;
  जबतक (p != (काष्ठा huft *)शून्य)
  अणु
    q = (--p)->v.t;
    मुक्त((अक्षर*)p);
    p = q;
  पूर्ण 
  वापस 0;
पूर्ण


STATIC पूर्णांक INIT inflate_codes(
	काष्ठा huft *tl,    /* literal/length decoder tables */
	काष्ठा huft *td,    /* distance decoder tables */
	पूर्णांक bl,             /* number of bits decoded by tl[] */
	पूर्णांक bd              /* number of bits decoded by td[] */
	)
/* inflate (decompress) the codes in a deflated (compressed) block.
   Return an error code or zero अगर it all goes ok. */
अणु
  रेजिस्टर अचिन्हित e;  /* table entry flag/number of extra bits */
  अचिन्हित n, d;        /* length and index क्रम copy */
  अचिन्हित w;           /* current winकरोw position */
  काष्ठा huft *t;       /* poपूर्णांकer to table entry */
  अचिन्हित ml, md;      /* masks क्रम bl and bd bits */
  रेजिस्टर ulg b;       /* bit buffer */
  रेजिस्टर अचिन्हित k;  /* number of bits in bit buffer */


  /* make local copies of globals */
  b = bb;                       /* initialize bit buffer */
  k = bk;
  w = wp;                       /* initialize winकरोw position */

  /* inflate the coded data */
  ml = mask_bits[bl];           /* precompute masks क्रम speed */
  md = mask_bits[bd];
  क्रम (;;)                      /* करो until end of block */
  अणु
    NEEDBITS((अचिन्हित)bl)
    अगर ((e = (t = tl + ((अचिन्हित)b & ml))->e) > 16)
      करो अणु
        अगर (e == 99)
          वापस 1;
        DUMPBITS(t->b)
        e -= 16;
        NEEDBITS(e)
      पूर्ण जबतक ((e = (t = t->v.t + ((अचिन्हित)b & mask_bits[e]))->e) > 16);
    DUMPBITS(t->b)
    अगर (e == 16)                /* then it's a literal */
    अणु
      slide[w++] = (uch)t->v.n;
      Tracevv((मानक_त्रुटि, "%c", slide[w-1]));
      अगर (w == WSIZE)
      अणु
        flush_output(w);
        w = 0;
      पूर्ण
    पूर्ण
    अन्यथा                        /* it's an EOB or a length */
    अणु
      /* निकास अगर end of block */
      अगर (e == 15)
        अवरोध;

      /* get length of block to copy */
      NEEDBITS(e)
      n = t->v.n + ((अचिन्हित)b & mask_bits[e]);
      DUMPBITS(e);

      /* decode distance of block to copy */
      NEEDBITS((अचिन्हित)bd)
      अगर ((e = (t = td + ((अचिन्हित)b & md))->e) > 16)
        करो अणु
          अगर (e == 99)
            वापस 1;
          DUMPBITS(t->b)
          e -= 16;
          NEEDBITS(e)
        पूर्ण जबतक ((e = (t = t->v.t + ((अचिन्हित)b & mask_bits[e]))->e) > 16);
      DUMPBITS(t->b)
      NEEDBITS(e)
      d = w - t->v.n - ((अचिन्हित)b & mask_bits[e]);
      DUMPBITS(e)
      Tracevv((मानक_त्रुटि,"\\[%d,%d]", w-d, n));

      /* करो the copy */
      करो अणु
        n -= (e = (e = WSIZE - ((d &= WSIZE-1) > w ? d : w)) > n ? n : e);
#अगर !defined(NOMEMCPY) && !defined(DEBUG)
        अगर (w - d >= e)         /* (this test assumes अचिन्हित comparison) */
        अणु
          स_नकल(slide + w, slide + d, e);
          w += e;
          d += e;
        पूर्ण
        अन्यथा                      /* करो it slow to aव्योम स_नकल() overlap */
#पूर्ण_अगर /* !NOMEMCPY */
          करो अणु
            slide[w++] = slide[d++];
	    Tracevv((मानक_त्रुटि, "%c", slide[w-1]));
          पूर्ण जबतक (--e);
        अगर (w == WSIZE)
        अणु
          flush_output(w);
          w = 0;
        पूर्ण
      पूर्ण जबतक (n);
    पूर्ण
  पूर्ण


  /* restore the globals from the locals */
  wp = w;                       /* restore global winकरोw poपूर्णांकer */
  bb = b;                       /* restore global bit buffer */
  bk = k;

  /* करोne */
  वापस 0;

 underrun:
  वापस 4;			/* Input underrun */
पूर्ण



STATIC पूर्णांक INIT inflate_stored(व्योम)
/* "decompress" an inflated type 0 (stored) block. */
अणु
  अचिन्हित n;           /* number of bytes in block */
  अचिन्हित w;           /* current winकरोw position */
  रेजिस्टर ulg b;       /* bit buffer */
  रेजिस्टर अचिन्हित k;  /* number of bits in bit buffer */

DEBG("<stor");

  /* make local copies of globals */
  b = bb;                       /* initialize bit buffer */
  k = bk;
  w = wp;                       /* initialize winकरोw position */


  /* go to byte boundary */
  n = k & 7;
  DUMPBITS(n);


  /* get the length and its complement */
  NEEDBITS(16)
  n = ((अचिन्हित)b & 0xffff);
  DUMPBITS(16)
  NEEDBITS(16)
  अगर (n != (अचिन्हित)((~b) & 0xffff))
    वापस 1;                   /* error in compressed data */
  DUMPBITS(16)


  /* पढ़ो and output the compressed data */
  जबतक (n--)
  अणु
    NEEDBITS(8)
    slide[w++] = (uch)b;
    अगर (w == WSIZE)
    अणु
      flush_output(w);
      w = 0;
    पूर्ण
    DUMPBITS(8)
  पूर्ण


  /* restore the globals from the locals */
  wp = w;                       /* restore global winकरोw poपूर्णांकer */
  bb = b;                       /* restore global bit buffer */
  bk = k;

  DEBG(">");
  वापस 0;

 underrun:
  वापस 4;			/* Input underrun */
पूर्ण


/*
 * We use `noअंतरभूत' here to prevent gcc-3.5 from using too much stack space
 */
STATIC पूर्णांक noअंतरभूत INIT inflate_fixed(व्योम)
/* decompress an inflated type 1 (fixed Huffman codes) block.  We should
   either replace this with a custom decoder, or at least precompute the
   Huffman tables. */
अणु
  पूर्णांक i;                /* temporary variable */
  काष्ठा huft *tl;      /* literal/length code table */
  काष्ठा huft *td;      /* distance code table */
  पूर्णांक bl;               /* lookup bits क्रम tl */
  पूर्णांक bd;               /* lookup bits क्रम td */
  अचिन्हित *l;          /* length list क्रम huft_build */

DEBG("<fix");

  l = दो_स्मृति(माप(*l) * 288);
  अगर (l == शून्य)
    वापस 3;			/* out of memory */

  /* set up literal table */
  क्रम (i = 0; i < 144; i++)
    l[i] = 8;
  क्रम (; i < 256; i++)
    l[i] = 9;
  क्रम (; i < 280; i++)
    l[i] = 7;
  क्रम (; i < 288; i++)          /* make a complete, but wrong code set */
    l[i] = 8;
  bl = 7;
  अगर ((i = huft_build(l, 288, 257, cplens, cplext, &tl, &bl)) != 0) अणु
    मुक्त(l);
    वापस i;
  पूर्ण

  /* set up distance table */
  क्रम (i = 0; i < 30; i++)      /* make an incomplete code set */
    l[i] = 5;
  bd = 5;
  अगर ((i = huft_build(l, 30, 0, cpdist, cpdext, &td, &bd)) > 1)
  अणु
    huft_मुक्त(tl);
    मुक्त(l);

    DEBG(">");
    वापस i;
  पूर्ण


  /* decompress until an end-of-block code */
  अगर (inflate_codes(tl, td, bl, bd)) अणु
    मुक्त(l);
    वापस 1;
  पूर्ण

  /* मुक्त the decoding tables, वापस */
  मुक्त(l);
  huft_मुक्त(tl);
  huft_मुक्त(td);
  वापस 0;
पूर्ण


/*
 * We use `noअंतरभूत' here to prevent gcc-3.5 from using too much stack space
 */
STATIC पूर्णांक noअंतरभूत INIT inflate_dynamic(व्योम)
/* decompress an inflated type 2 (dynamic Huffman codes) block. */
अणु
  पूर्णांक i;                /* temporary variables */
  अचिन्हित j;
  अचिन्हित l;           /* last length */
  अचिन्हित m;           /* mask क्रम bit lengths table */
  अचिन्हित n;           /* number of lengths to get */
  काष्ठा huft *tl;      /* literal/length code table */
  काष्ठा huft *td;      /* distance code table */
  पूर्णांक bl;               /* lookup bits क्रम tl */
  पूर्णांक bd;               /* lookup bits क्रम td */
  अचिन्हित nb;          /* number of bit length codes */
  अचिन्हित nl;          /* number of literal/length codes */
  अचिन्हित nd;          /* number of distance codes */
  अचिन्हित *ll;         /* literal/length and distance code lengths */
  रेजिस्टर ulg b;       /* bit buffer */
  रेजिस्टर अचिन्हित k;  /* number of bits in bit buffer */
  पूर्णांक ret;

DEBG("<dyn");

#अगर_घोषित PKZIP_BUG_WORKAROUND
  ll = दो_स्मृति(माप(*ll) * (288+32));  /* literal/length and distance code lengths */
#अन्यथा
  ll = दो_स्मृति(माप(*ll) * (286+30));  /* literal/length and distance code lengths */
#पूर्ण_अगर

  अगर (ll == शून्य)
    वापस 1;

  /* make local bit buffer */
  b = bb;
  k = bk;


  /* पढ़ो in table lengths */
  NEEDBITS(5)
  nl = 257 + ((अचिन्हित)b & 0x1f);      /* number of literal/length codes */
  DUMPBITS(5)
  NEEDBITS(5)
  nd = 1 + ((अचिन्हित)b & 0x1f);        /* number of distance codes */
  DUMPBITS(5)
  NEEDBITS(4)
  nb = 4 + ((अचिन्हित)b & 0xf);         /* number of bit length codes */
  DUMPBITS(4)
#अगर_घोषित PKZIP_BUG_WORKAROUND
  अगर (nl > 288 || nd > 32)
#अन्यथा
  अगर (nl > 286 || nd > 30)
#पूर्ण_अगर
  अणु
    ret = 1;             /* bad lengths */
    जाओ out;
  पूर्ण

DEBG("dyn1 ");

  /* पढ़ो in bit-length-code lengths */
  क्रम (j = 0; j < nb; j++)
  अणु
    NEEDBITS(3)
    ll[border[j]] = (अचिन्हित)b & 7;
    DUMPBITS(3)
  पूर्ण
  क्रम (; j < 19; j++)
    ll[border[j]] = 0;

DEBG("dyn2 ");

  /* build decoding table क्रम trees--single level, 7 bit lookup */
  bl = 7;
  अगर ((i = huft_build(ll, 19, 19, शून्य, शून्य, &tl, &bl)) != 0)
  अणु
    अगर (i == 1)
      huft_मुक्त(tl);
    ret = i;                   /* incomplete code set */
    जाओ out;
  पूर्ण

DEBG("dyn3 ");

  /* पढ़ो in literal and distance code lengths */
  n = nl + nd;
  m = mask_bits[bl];
  i = l = 0;
  जबतक ((अचिन्हित)i < n)
  अणु
    NEEDBITS((अचिन्हित)bl)
    j = (td = tl + ((अचिन्हित)b & m))->b;
    DUMPBITS(j)
    j = td->v.n;
    अगर (j < 16)                 /* length of code in bits (0..15) */
      ll[i++] = l = j;          /* save last length in l */
    अन्यथा अगर (j == 16)           /* repeat last length 3 to 6 बार */
    अणु
      NEEDBITS(2)
      j = 3 + ((अचिन्हित)b & 3);
      DUMPBITS(2)
      अगर ((अचिन्हित)i + j > n) अणु
        ret = 1;
	जाओ out;
      पूर्ण
      जबतक (j--)
        ll[i++] = l;
    पूर्ण
    अन्यथा अगर (j == 17)           /* 3 to 10 zero length codes */
    अणु
      NEEDBITS(3)
      j = 3 + ((अचिन्हित)b & 7);
      DUMPBITS(3)
      अगर ((अचिन्हित)i + j > n) अणु
        ret = 1;
	जाओ out;
      पूर्ण
      जबतक (j--)
        ll[i++] = 0;
      l = 0;
    पूर्ण
    अन्यथा                        /* j == 18: 11 to 138 zero length codes */
    अणु
      NEEDBITS(7)
      j = 11 + ((अचिन्हित)b & 0x7f);
      DUMPBITS(7)
      अगर ((अचिन्हित)i + j > n) अणु
        ret = 1;
	जाओ out;
      पूर्ण
      जबतक (j--)
        ll[i++] = 0;
      l = 0;
    पूर्ण
  पूर्ण

DEBG("dyn4 ");

  /* मुक्त decoding table क्रम trees */
  huft_मुक्त(tl);

DEBG("dyn5 ");

  /* restore the global bit buffer */
  bb = b;
  bk = k;

DEBG("dyn5a ");

  /* build the decoding tables क्रम literal/length and distance codes */
  bl = lbits;
  अगर ((i = huft_build(ll, nl, 257, cplens, cplext, &tl, &bl)) != 0)
  अणु
DEBG("dyn5b ");
    अगर (i == 1) अणु
      error("incomplete literal tree");
      huft_मुक्त(tl);
    पूर्ण
    ret = i;                   /* incomplete code set */
    जाओ out;
  पूर्ण
DEBG("dyn5c ");
  bd = dbits;
  अगर ((i = huft_build(ll + nl, nd, 0, cpdist, cpdext, &td, &bd)) != 0)
  अणु
DEBG("dyn5d ");
    अगर (i == 1) अणु
      error("incomplete distance tree");
#अगर_घोषित PKZIP_BUG_WORKAROUND
      i = 0;
    पूर्ण
#अन्यथा
      huft_मुक्त(td);
    पूर्ण
    huft_मुक्त(tl);
    ret = i;                   /* incomplete code set */
    जाओ out;
#पूर्ण_अगर
  पूर्ण

DEBG("dyn6 ");

  /* decompress until an end-of-block code */
  अगर (inflate_codes(tl, td, bl, bd)) अणु
    ret = 1;
    जाओ out;
  पूर्ण

DEBG("dyn7 ");

  /* मुक्त the decoding tables, वापस */
  huft_मुक्त(tl);
  huft_मुक्त(td);

  DEBG(">");
  ret = 0;
out:
  मुक्त(ll);
  वापस ret;

underrun:
  ret = 4;			/* Input underrun */
  जाओ out;
पूर्ण



STATIC पूर्णांक INIT inflate_block(
	पूर्णांक *e                  /* last block flag */
	)
/* decompress an inflated block */
अणु
  अचिन्हित t;           /* block type */
  रेजिस्टर ulg b;       /* bit buffer */
  रेजिस्टर अचिन्हित k;  /* number of bits in bit buffer */

  DEBG("<blk");

  /* make local bit buffer */
  b = bb;
  k = bk;


  /* पढ़ो in last block bit */
  NEEDBITS(1)
  *e = (पूर्णांक)b & 1;
  DUMPBITS(1)


  /* पढ़ो in block type */
  NEEDBITS(2)
  t = (अचिन्हित)b & 3;
  DUMPBITS(2)


  /* restore the global bit buffer */
  bb = b;
  bk = k;

  /* inflate that block type */
  अगर (t == 2)
    वापस inflate_dynamic();
  अगर (t == 0)
    वापस inflate_stored();
  अगर (t == 1)
    वापस inflate_fixed();

  DEBG(">");

  /* bad block type */
  वापस 2;

 underrun:
  वापस 4;			/* Input underrun */
पूर्ण



STATIC पूर्णांक INIT inflate(व्योम)
/* decompress an inflated entry */
अणु
  पूर्णांक e;                /* last block flag */
  पूर्णांक r;                /* result code */
  अचिन्हित h;           /* maximum काष्ठा huft's malloc'ed */

  /* initialize winकरोw, bit buffer */
  wp = 0;
  bk = 0;
  bb = 0;


  /* decompress until the last block */
  h = 0;
  करो अणु
    hufts = 0;
#अगर_घोषित ARCH_HAS_DECOMP_WDOG
    arch_decomp_wकरोg();
#पूर्ण_अगर
    r = inflate_block(&e);
    अगर (r)
	    वापस r;
    अगर (hufts > h)
      h = hufts;
  पूर्ण जबतक (!e);

  /* Unकरो too much lookahead. The next पढ़ो will be byte aligned so we
   * can discard unused bits in the last meaningful byte.
   */
  जबतक (bk >= 8) अणु
    bk -= 8;
    inptr--;
  पूर्ण

  /* flush out slide */
  flush_output(wp);


  /* वापस success */
#अगर_घोषित DEBUG
  ख_लिखो(मानक_त्रुटि, "<%u> ", h);
#पूर्ण_अगर /* DEBUG */
  वापस 0;
पूर्ण

/**********************************************************************
 *
 * The following are support routines क्रम inflate.c
 *
 **********************************************************************/

अटल ulg crc_32_tab[256];
अटल ulg crc;		/* initialized in makecrc() so it'll reside in bss */
#घोषणा CRC_VALUE (crc ^ 0xffffffffUL)

/*
 * Code to compute the CRC-32 table. Borrowed from 
 * gzip-1.0.3/makecrc.c.
 */

अटल व्योम INIT
makecrc(व्योम)
अणु
/* Not copyrighted 1990 Mark Adler	*/

  अचिन्हित दीर्घ c;      /* crc shअगरt रेजिस्टर */
  अचिन्हित दीर्घ e;      /* polynomial exclusive-or pattern */
  पूर्णांक i;                /* counter क्रम all possible eight bit values */
  पूर्णांक k;                /* byte being shअगरted पूर्णांकo crc apparatus */

  /* terms of polynomial defining this crc (except x^32): */
  अटल स्थिर पूर्णांक p[] = अणु0,1,2,4,5,7,8,10,11,12,16,22,23,26पूर्ण;

  /* Make exclusive-or pattern from polynomial */
  e = 0;
  क्रम (i = 0; i < माप(p)/माप(पूर्णांक); i++)
    e |= 1L << (31 - p[i]);

  crc_32_tab[0] = 0;

  क्रम (i = 1; i < 256; i++)
  अणु
    c = 0;
    क्रम (k = i | 256; k != 1; k >>= 1)
    अणु
      c = c & 1 ? (c >> 1) ^ e : c >> 1;
      अगर (k & 1)
        c ^= e;
    पूर्ण
    crc_32_tab[i] = c;
  पूर्ण

  /* this is initialized here so this code could reside in ROM */
  crc = (ulg)0xffffffffUL; /* shअगरt रेजिस्टर contents */
पूर्ण

/* gzip flag byte */
#घोषणा ASCII_FLAG   0x01 /* bit 0 set: file probably ASCII text */
#घोषणा CONTINUATION 0x02 /* bit 1 set: continuation of multi-part gzip file */
#घोषणा EXTRA_FIELD  0x04 /* bit 2 set: extra field present */
#घोषणा ORIG_NAME    0x08 /* bit 3 set: original file name present */
#घोषणा COMMENT      0x10 /* bit 4 set: file comment present */
#घोषणा ENCRYPTED    0x20 /* bit 5 set: file is encrypted */
#घोषणा RESERVED     0xC0 /* bit 6,7:   reserved */

/*
 * Do the uncompression!
 */
अटल पूर्णांक INIT gunzip(व्योम)
अणु
    uch flags;
    अचिन्हित अक्षर magic[2]; /* magic header */
    अक्षर method;
    ulg orig_crc = 0;       /* original crc */
    ulg orig_len = 0;       /* original uncompressed length */
    पूर्णांक res;

    magic[0] = NEXTBYTE();
    magic[1] = NEXTBYTE();
    method   = NEXTBYTE();

    अगर (magic[0] != 037 ||
	((magic[1] != 0213) && (magic[1] != 0236))) अणु
	    error("bad gzip magic numbers");
	    वापस -1;
    पूर्ण

    /* We only support method #8, DEFLATED */
    अगर (method != 8)  अणु
	    error("internal error, invalid method");
	    वापस -1;
    पूर्ण

    flags  = (uch)get_byte();
    अगर ((flags & ENCRYPTED) != 0) अणु
	    error("Input is encrypted");
	    वापस -1;
    पूर्ण
    अगर ((flags & CONTINUATION) != 0) अणु
	    error("Multi part input");
	    वापस -1;
    पूर्ण
    अगर ((flags & RESERVED) != 0) अणु
	    error("Input has invalid flags");
	    वापस -1;
    पूर्ण
    NEXTBYTE();	/* Get बारtamp */
    NEXTBYTE();
    NEXTBYTE();
    NEXTBYTE();

    (व्योम)NEXTBYTE();  /* Ignore extra flags क्रम the moment */
    (व्योम)NEXTBYTE();  /* Ignore OS type क्रम the moment */

    अगर ((flags & EXTRA_FIELD) != 0) अणु
	    अचिन्हित len = (अचिन्हित)NEXTBYTE();
	    len |= ((अचिन्हित)NEXTBYTE())<<8;
	    जबतक (len--) (व्योम)NEXTBYTE();
    पूर्ण

    /* Get original file name अगर it was truncated */
    अगर ((flags & ORIG_NAME) != 0) अणु
	    /* Discard the old name */
	    जबतक (NEXTBYTE() != 0) /* null */ ;
    पूर्ण 

    /* Discard file comment अगर any */
    अगर ((flags & COMMENT) != 0) अणु
	    जबतक (NEXTBYTE() != 0) /* null */ ;
    पूर्ण

    /* Decompress */
    अगर ((res = inflate())) अणु
	    चयन (res) अणु
	    हाल 0:
		    अवरोध;
	    हाल 1:
		    error("invalid compressed format (err=1)");
		    अवरोध;
	    हाल 2:
		    error("invalid compressed format (err=2)");
		    अवरोध;
	    हाल 3:
		    error("out of memory");
		    अवरोध;
	    हाल 4:
		    error("out of input data");
		    अवरोध;
	    शेष:
		    error("invalid compressed format (other)");
	    पूर्ण
	    वापस -1;
    पूर्ण
	    
    /* Get the crc and original length */
    /* crc32  (see algorithm.करोc)
     * uncompressed input size modulo 2^32
     */
    orig_crc = (ulg) NEXTBYTE();
    orig_crc |= (ulg) NEXTBYTE() << 8;
    orig_crc |= (ulg) NEXTBYTE() << 16;
    orig_crc |= (ulg) NEXTBYTE() << 24;
    
    orig_len = (ulg) NEXTBYTE();
    orig_len |= (ulg) NEXTBYTE() << 8;
    orig_len |= (ulg) NEXTBYTE() << 16;
    orig_len |= (ulg) NEXTBYTE() << 24;
    
    /* Validate decompression */
    अगर (orig_crc != CRC_VALUE) अणु
	    error("crc error");
	    वापस -1;
    पूर्ण
    अगर (orig_len != bytes_out) अणु
	    error("length error");
	    वापस -1;
    पूर्ण
    वापस 0;

 underrun:			/* NEXTBYTE() जाओ's here अगर needed */
    error("out of input data");
    वापस -1;
पूर्ण


