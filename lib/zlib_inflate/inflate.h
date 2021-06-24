<शैली गुरु>
#अगर_अघोषित INFLATE_H
#घोषणा INFLATE_H

/* inflate.h -- पूर्णांकernal inflate state definition
 * Copyright (C) 1995-2004 Mark Adler
 * For conditions of distribution and use, see copyright notice in zlib.h
 */

/* WARNING: this file should *not* be used by applications. It is
   part of the implementation of the compression library and is
   subject to change. Applications should only use zlib.h.
 */

#समावेश "inftrees.h"

/* Possible inflate modes between inflate() calls */
प्रकार क्रमागत अणु
    HEAD,       /* i: रुकोing क्रम magic header */
    FLAGS,      /* i: रुकोing क्रम method and flags (gzip) */
    TIME,       /* i: रुकोing क्रम modअगरication समय (gzip) */
    OS,         /* i: रुकोing क्रम extra flags and operating प्रणाली (gzip) */
    EXLEN,      /* i: रुकोing क्रम extra length (gzip) */
    EXTRA,      /* i: रुकोing क्रम extra bytes (gzip) */
    NAME,       /* i: रुकोing क्रम end of file name (gzip) */
    COMMENT,    /* i: रुकोing क्रम end of comment (gzip) */
    HCRC,       /* i: रुकोing क्रम header crc (gzip) */
    DICTID,     /* i: रुकोing क्रम dictionary check value */
    DICT,       /* रुकोing क्रम inflateSetDictionary() call */
        TYPE,       /* i: रुकोing क्रम type bits, including last-flag bit */
        TYPEDO,     /* i: same, but skip check to निकास inflate on new block */
        STORED,     /* i: रुकोing क्रम stored size (length and complement) */
        COPY,       /* i/o: रुकोing क्रम input or output to copy stored block */
        TABLE,      /* i: रुकोing क्रम dynamic block table lengths */
        LENLENS,    /* i: रुकोing क्रम code length code lengths */
        CODELENS,   /* i: रुकोing क्रम length/lit and distance code lengths */
            LEN,        /* i: रुकोing क्रम length/lit code */
            LENEXT,     /* i: रुकोing क्रम length extra bits */
            DIST,       /* i: रुकोing क्रम distance code */
            DISTEXT,    /* i: रुकोing क्रम distance extra bits */
            MATCH,      /* o: रुकोing क्रम output space to copy string */
            LIT,        /* o: रुकोing क्रम output space to ग_लिखो literal */
    CHECK,      /* i: रुकोing क्रम 32-bit check value */
    LENGTH,     /* i: रुकोing क्रम 32-bit length (gzip) */
    DONE,       /* finished check, करोne -- reमुख्य here until reset */
    BAD,        /* got a data error -- reमुख्य here until reset */
    MEM,        /* got an inflate() memory error -- reमुख्य here until reset */
    SYNC        /* looking क्रम synchronization bytes to restart inflate() */
पूर्ण inflate_mode;

/*
    State transitions between above modes -

    (most modes can go to the BAD or MEM mode -- not shown क्रम clarity)

    Process header:
        HEAD -> (gzip) or (zlib)
        (gzip) -> FLAGS -> TIME -> OS -> EXLEN -> EXTRA -> NAME
        NAME -> COMMENT -> HCRC -> TYPE
        (zlib) -> DICTID or TYPE
        DICTID -> DICT -> TYPE
    Read deflate blocks:
            TYPE -> STORED or TABLE or LEN or CHECK
            STORED -> COPY -> TYPE
            TABLE -> LENLENS -> CODELENS -> LEN
    Read deflate codes:
                LEN -> LENEXT or LIT or TYPE
                LENEXT -> DIST -> DISTEXT -> MATCH -> LEN
                LIT -> LEN
    Process trailer:
        CHECK -> LENGTH -> DONE
 */

/* state मुख्यtained between inflate() calls.  Approximately 7K bytes. */
काष्ठा inflate_state अणु
    inflate_mode mode;          /* current inflate mode */
    पूर्णांक last;                   /* true अगर processing last block */
    पूर्णांक wrap;                   /* bit 0 true क्रम zlib, bit 1 true क्रम gzip */
    पूर्णांक havedict;               /* true अगर dictionary provided */
    पूर्णांक flags;                  /* gzip header method and flags (0 अगर zlib) */
    अचिन्हित dmax;              /* zlib header max distance (INFLATE_STRICT) */
    अचिन्हित दीर्घ check;        /* रक्षित copy of check value */
    अचिन्हित दीर्घ total;        /* रक्षित copy of output count */
 /*   gz_headerp head; */           /* where to save gzip header inक्रमmation */
        /* sliding winकरोw */
    अचिन्हित wbits;             /* log base 2 of requested winकरोw size */
    अचिन्हित wsize;             /* winकरोw size or zero अगर not using winकरोw */
    अचिन्हित whave;             /* valid bytes in the winकरोw */
    अचिन्हित ग_लिखो;             /* winकरोw ग_लिखो index */
    अचिन्हित अक्षर *winकरोw;  /* allocated sliding winकरोw, अगर needed */
        /* bit accumulator */
    अचिन्हित दीर्घ hold;         /* input bit accumulator */
    अचिन्हित bits;              /* number of bits in "in" */
        /* क्रम string and stored block copying */
    अचिन्हित length;            /* literal or length of data to copy */
    अचिन्हित offset;            /* distance back to copy string from */
        /* क्रम table and code decoding */
    अचिन्हित extra;             /* extra bits needed */
        /* fixed and dynamic code tables */
    code स्थिर *lencode;    /* starting table क्रम length/literal codes */
    code स्थिर *distcode;   /* starting table क्रम distance codes */
    अचिन्हित lenbits;           /* index bits क्रम lencode */
    अचिन्हित distbits;          /* index bits क्रम distcode */
        /* dynamic table building */
    अचिन्हित ncode;             /* number of code length code lengths */
    अचिन्हित nlen;              /* number of length code lengths */
    अचिन्हित ndist;             /* number of distance code lengths */
    अचिन्हित have;              /* number of code lengths in lens[] */
    code *next;             /* next available space in codes[] */
    अचिन्हित लघु lens[320];   /* temporary storage क्रम code lengths */
    अचिन्हित लघु work[288];   /* work area क्रम code table building */
    code codes[ENOUGH];         /* space क्रम code tables */
पूर्ण;

/* Reverse the bytes in a 32-bit value */
#घोषणा REVERSE(q) \
    ((((q) >> 24) & 0xff) + (((q) >> 8) & 0xff00) + \
     (((q) & 0xff00) << 8) + (((q) & 0xff) << 24))

#पूर्ण_अगर
