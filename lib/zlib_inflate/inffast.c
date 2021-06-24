<शैली गुरु>
/* inffast.c -- fast decoding
 * Copyright (C) 1995-2004 Mark Adler
 * For conditions of distribution and use, see copyright notice in zlib.h
 */

#समावेश <linux/zutil.h>
#समावेश "inftrees.h"
#समावेश "inflate.h"
#समावेश "inffast.h"

#अगर_अघोषित ASMINF

जोड़ uu अणु
	अचिन्हित लघु us;
	अचिन्हित अक्षर b[2];
पूर्ण;

/* Endian independed version */
अटल अंतरभूत अचिन्हित लघु
get_unaligned16(स्थिर अचिन्हित लघु *p)
अणु
	जोड़ uu  mm;
	अचिन्हित अक्षर *b = (अचिन्हित अक्षर *)p;

	mm.b[0] = b[0];
	mm.b[1] = b[1];
	वापस mm.us;
पूर्ण

/*
   Decode literal, length, and distance codes and ग_लिखो out the resulting
   literal and match bytes until either not enough input or output is
   available, an end-of-block is encountered, or a data error is encountered.
   When large enough input and output buffers are supplied to inflate(), क्रम
   example, a 16K input buffer and a 64K output buffer, more than 95% of the
   inflate execution समय is spent in this routine.

   Entry assumptions:

        state->mode == LEN
        strm->avail_in >= 6
        strm->avail_out >= 258
        start >= strm->avail_out
        state->bits < 8

   On वापस, state->mode is one of:

        LEN -- ran out of enough output space or enough available input
        TYPE -- reached end of block code, inflate() to पूर्णांकerpret next block
        BAD -- error in block data

   Notes:

    - The maximum input bits used by a length/distance pair is 15 bits क्रम the
      length code, 5 bits क्रम the length extra, 15 bits क्रम the distance code,
      and 13 bits क्रम the distance extra.  This totals 48 bits, or six bytes.
      Thereक्रमe अगर strm->avail_in >= 6, then there is enough input to aव्योम
      checking क्रम available input जबतक decoding.

    - The maximum bytes that a single length/distance pair can output is 258
      bytes, which is the maximum length that can be coded.  inflate_fast()
      requires strm->avail_out >= 258 क्रम each loop to aव्योम checking क्रम
      output space.

    - @start:	inflate()'s starting value क्रम strm->avail_out
 */
व्योम inflate_fast(z_streamp strm, अचिन्हित start)
अणु
    काष्ठा inflate_state *state;
    स्थिर अचिन्हित अक्षर *in;    /* local strm->next_in */
    स्थिर अचिन्हित अक्षर *last;  /* जबतक in < last, enough input available */
    अचिन्हित अक्षर *out;         /* local strm->next_out */
    अचिन्हित अक्षर *beg;         /* inflate()'s initial strm->next_out */
    अचिन्हित अक्षर *end;         /* जबतक out < end, enough space available */
#अगर_घोषित INFLATE_STRICT
    अचिन्हित dmax;              /* maximum distance from zlib header */
#पूर्ण_अगर
    अचिन्हित wsize;             /* winकरोw size or zero अगर not using winकरोw */
    अचिन्हित whave;             /* valid bytes in the winकरोw */
    अचिन्हित ग_लिखो;             /* winकरोw ग_लिखो index */
    अचिन्हित अक्षर *winकरोw;      /* allocated sliding winकरोw, अगर wsize != 0 */
    अचिन्हित दीर्घ hold;         /* local strm->hold */
    अचिन्हित bits;              /* local strm->bits */
    code स्थिर *lcode;          /* local strm->lencode */
    code स्थिर *dcode;          /* local strm->distcode */
    अचिन्हित lmask;             /* mask क्रम first level of length codes */
    अचिन्हित dmask;             /* mask क्रम first level of distance codes */
    code this;                  /* retrieved table entry */
    अचिन्हित op;                /* code bits, operation, extra bits, or */
                                /*  winकरोw position, winकरोw bytes to copy */
    अचिन्हित len;               /* match length, unused bytes */
    अचिन्हित dist;              /* match distance */
    अचिन्हित अक्षर *from;        /* where to copy match from */

    /* copy state to local variables */
    state = (काष्ठा inflate_state *)strm->state;
    in = strm->next_in;
    last = in + (strm->avail_in - 5);
    out = strm->next_out;
    beg = out - (start - strm->avail_out);
    end = out + (strm->avail_out - 257);
#अगर_घोषित INFLATE_STRICT
    dmax = state->dmax;
#पूर्ण_अगर
    wsize = state->wsize;
    whave = state->whave;
    ग_लिखो = state->ग_लिखो;
    winकरोw = state->winकरोw;
    hold = state->hold;
    bits = state->bits;
    lcode = state->lencode;
    dcode = state->distcode;
    lmask = (1U << state->lenbits) - 1;
    dmask = (1U << state->distbits) - 1;

    /* decode literals and length/distances until end-of-block or not enough
       input data or output space */
    करो अणु
        अगर (bits < 15) अणु
            hold += (अचिन्हित दीर्घ)(*in++) << bits;
            bits += 8;
            hold += (अचिन्हित दीर्घ)(*in++) << bits;
            bits += 8;
        पूर्ण
        this = lcode[hold & lmask];
      करोlen:
        op = (अचिन्हित)(this.bits);
        hold >>= op;
        bits -= op;
        op = (अचिन्हित)(this.op);
        अगर (op == 0) अणु                          /* literal */
            *out++ = (अचिन्हित अक्षर)(this.val);
        पूर्ण
        अन्यथा अगर (op & 16) अणु                     /* length base */
            len = (अचिन्हित)(this.val);
            op &= 15;                           /* number of extra bits */
            अगर (op) अणु
                अगर (bits < op) अणु
                    hold += (अचिन्हित दीर्घ)(*in++) << bits;
                    bits += 8;
                पूर्ण
                len += (अचिन्हित)hold & ((1U << op) - 1);
                hold >>= op;
                bits -= op;
            पूर्ण
            अगर (bits < 15) अणु
                hold += (अचिन्हित दीर्घ)(*in++) << bits;
                bits += 8;
                hold += (अचिन्हित दीर्घ)(*in++) << bits;
                bits += 8;
            पूर्ण
            this = dcode[hold & dmask];
          करोdist:
            op = (अचिन्हित)(this.bits);
            hold >>= op;
            bits -= op;
            op = (अचिन्हित)(this.op);
            अगर (op & 16) अणु                      /* distance base */
                dist = (अचिन्हित)(this.val);
                op &= 15;                       /* number of extra bits */
                अगर (bits < op) अणु
                    hold += (अचिन्हित दीर्घ)(*in++) << bits;
                    bits += 8;
                    अगर (bits < op) अणु
                        hold += (अचिन्हित दीर्घ)(*in++) << bits;
                        bits += 8;
                    पूर्ण
                पूर्ण
                dist += (अचिन्हित)hold & ((1U << op) - 1);
#अगर_घोषित INFLATE_STRICT
                अगर (dist > dmax) अणु
                    strm->msg = (अक्षर *)"invalid distance too far back";
                    state->mode = BAD;
                    अवरोध;
                पूर्ण
#पूर्ण_अगर
                hold >>= op;
                bits -= op;
                op = (अचिन्हित)(out - beg);     /* max distance in output */
                अगर (dist > op) अणु                /* see अगर copy from winकरोw */
                    op = dist - op;             /* distance back in winकरोw */
                    अगर (op > whave) अणु
                        strm->msg = (अक्षर *)"invalid distance too far back";
                        state->mode = BAD;
                        अवरोध;
                    पूर्ण
                    from = winकरोw;
                    अगर (ग_लिखो == 0) अणु           /* very common हाल */
                        from += wsize - op;
                        अगर (op < len) अणु         /* some from winकरोw */
                            len -= op;
                            करो अणु
                                *out++ = *from++;
                            पूर्ण जबतक (--op);
                            from = out - dist;  /* rest from output */
                        पूर्ण
                    पूर्ण
                    अन्यथा अगर (ग_लिखो < op) अणु      /* wrap around winकरोw */
                        from += wsize + ग_लिखो - op;
                        op -= ग_लिखो;
                        अगर (op < len) अणु         /* some from end of winकरोw */
                            len -= op;
                            करो अणु
                                *out++ = *from++;
                            पूर्ण जबतक (--op);
                            from = winकरोw;
                            अगर (ग_लिखो < len) अणु  /* some from start of winकरोw */
                                op = ग_लिखो;
                                len -= op;
                                करो अणु
                                    *out++ = *from++;
                                पूर्ण जबतक (--op);
                                from = out - dist;      /* rest from output */
                            पूर्ण
                        पूर्ण
                    पूर्ण
                    अन्यथा अणु                      /* contiguous in winकरोw */
                        from += ग_लिखो - op;
                        अगर (op < len) अणु         /* some from winकरोw */
                            len -= op;
                            करो अणु
                                *out++ = *from++;
                            पूर्ण जबतक (--op);
                            from = out - dist;  /* rest from output */
                        पूर्ण
                    पूर्ण
                    जबतक (len > 2) अणु
                        *out++ = *from++;
                        *out++ = *from++;
                        *out++ = *from++;
                        len -= 3;
                    पूर्ण
                    अगर (len) अणु
                        *out++ = *from++;
                        अगर (len > 1)
                            *out++ = *from++;
                    पूर्ण
                पूर्ण
                अन्यथा अणु
		    अचिन्हित लघु *sout;
		    अचिन्हित दीर्घ loops;

                    from = out - dist;          /* copy direct from output */
		    /* minimum length is three */
		    /* Align out addr */
		    अगर (!((दीर्घ)(out - 1) & 1)) अणु
			*out++ = *from++;
			len--;
		    पूर्ण
		    sout = (अचिन्हित लघु *)(out);
		    अगर (dist > 2) अणु
			अचिन्हित लघु *sfrom;

			sfrom = (अचिन्हित लघु *)(from);
			loops = len >> 1;
			करो
#अगर_घोषित CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS
			    *sout++ = *sfrom++;
#अन्यथा
			    *sout++ = get_unaligned16(sfrom++);
#पूर्ण_अगर
			जबतक (--loops);
			out = (अचिन्हित अक्षर *)sout;
			from = (अचिन्हित अक्षर *)sfrom;
		    पूर्ण अन्यथा अणु /* dist == 1 or dist == 2 */
			अचिन्हित लघु pat16;

			pat16 = *(sout-1);
			अगर (dist == 1) अणु
				जोड़ uu mm;
				/* copy one अक्षर pattern to both bytes */
				mm.us = pat16;
				mm.b[0] = mm.b[1];
				pat16 = mm.us;
			पूर्ण
			loops = len >> 1;
			करो
			    *sout++ = pat16;
			जबतक (--loops);
			out = (अचिन्हित अक्षर *)sout;
		    पूर्ण
		    अगर (len & 1)
			*out++ = *from++;
                पूर्ण
            पूर्ण
            अन्यथा अगर ((op & 64) == 0) अणु          /* 2nd level distance code */
                this = dcode[this.val + (hold & ((1U << op) - 1))];
                जाओ करोdist;
            पूर्ण
            अन्यथा अणु
                strm->msg = (अक्षर *)"invalid distance code";
                state->mode = BAD;
                अवरोध;
            पूर्ण
        पूर्ण
        अन्यथा अगर ((op & 64) == 0) अणु              /* 2nd level length code */
            this = lcode[this.val + (hold & ((1U << op) - 1))];
            जाओ करोlen;
        पूर्ण
        अन्यथा अगर (op & 32) अणु                     /* end-of-block */
            state->mode = TYPE;
            अवरोध;
        पूर्ण
        अन्यथा अणु
            strm->msg = (अक्षर *)"invalid literal/length code";
            state->mode = BAD;
            अवरोध;
        पूर्ण
    पूर्ण जबतक (in < last && out < end);

    /* वापस unused bytes (on entry, bits < 8, so in won't go too far back) */
    len = bits >> 3;
    in -= len;
    bits -= len << 3;
    hold &= (1U << bits) - 1;

    /* update state and वापस */
    strm->next_in = in;
    strm->next_out = out;
    strm->avail_in = (अचिन्हित)(in < last ? 5 + (last - in) : 5 - (in - last));
    strm->avail_out = (अचिन्हित)(out < end ?
                                 257 + (end - out) : 257 - (out - end));
    state->hold = hold;
    state->bits = bits;
    वापस;
पूर्ण

/*
   inflate_fast() speedups that turned out slower (on a PowerPC G3 750CXe):
   - Using bit fields क्रम code काष्ठाure
   - Dअगरferent op definition to aव्योम & क्रम extra bits (करो & क्रम table bits)
   - Three separate decoding करो-loops क्रम direct, winकरोw, and ग_लिखो == 0
   - Special हाल क्रम distance > 1 copies to करो overlapped load and store copy
   - Explicit branch predictions (based on measured branch probabilities)
   - Deferring match copy and पूर्णांकerspersed it with decoding subsequent codes
   - Swapping literal/length अन्यथा
   - Swapping winकरोw/direct अन्यथा
   - Larger unrolled copy loops (three is about right)
   - Moving len -= 3 statement पूर्णांकo middle of loop
 */

#पूर्ण_अगर /* !ASMINF */
