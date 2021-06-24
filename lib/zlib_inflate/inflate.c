<शैली गुरु>
/* inflate.c -- zlib decompression
 * Copyright (C) 1995-2005 Mark Adler
 * For conditions of distribution and use, see copyright notice in zlib.h
 *
 * Based on zlib 1.2.3 but modअगरied क्रम the Linux Kernel by
 * Riअक्षरd Purdie <riअक्षरd@खोलोedhand.com>
 *
 * Changes मुख्यly क्रम अटल instead of dynamic memory allocation
 *
 */

#समावेश <linux/zutil.h>
#समावेश "inftrees.h"
#समावेश "inflate.h"
#समावेश "inffast.h"
#समावेश "infutil.h"

/* architecture-specअगरic bits */
#अगर_घोषित CONFIG_ZLIB_DFLTCC
#  include "../zlib_dfltcc/dfltcc.h"
#अन्यथा
#घोषणा INFLATE_RESET_HOOK(strm) करो अणुपूर्ण जबतक (0)
#घोषणा INFLATE_TYPEDO_HOOK(strm, flush) करो अणुपूर्ण जबतक (0)
#घोषणा INFLATE_NEED_UPDATEWINDOW(strm) 1
#घोषणा INFLATE_NEED_CHECKSUM(strm) 1
#पूर्ण_अगर

पूर्णांक zlib_inflate_workspacesize(व्योम)
अणु
    वापस माप(काष्ठा inflate_workspace);
पूर्ण

पूर्णांक zlib_inflateReset(z_streamp strm)
अणु
    काष्ठा inflate_state *state;

    अगर (strm == शून्य || strm->state == शून्य) वापस Z_STREAM_ERROR;
    state = (काष्ठा inflate_state *)strm->state;
    strm->total_in = strm->total_out = state->total = 0;
    strm->msg = शून्य;
    strm->adler = 1;        /* to support ill-conceived Java test suite */
    state->mode = HEAD;
    state->last = 0;
    state->havedict = 0;
    state->dmax = 32768U;
    state->hold = 0;
    state->bits = 0;
    state->lencode = state->distcode = state->next = state->codes;

    /* Initialise Winकरोw */
    state->wsize = 1U << state->wbits;
    state->ग_लिखो = 0;
    state->whave = 0;

    INFLATE_RESET_HOOK(strm);
    वापस Z_OK;
पूर्ण

पूर्णांक zlib_inflateInit2(z_streamp strm, पूर्णांक winकरोwBits)
अणु
    काष्ठा inflate_state *state;

    अगर (strm == शून्य) वापस Z_STREAM_ERROR;
    strm->msg = शून्य;                 /* in हाल we वापस an error */

    state = &WS(strm)->inflate_state;
    strm->state = (काष्ठा पूर्णांकernal_state *)state;

    अगर (winकरोwBits < 0) अणु
        state->wrap = 0;
        winकरोwBits = -winकरोwBits;
    पूर्ण
    अन्यथा अणु
        state->wrap = (winकरोwBits >> 4) + 1;
    पूर्ण
    अगर (winकरोwBits < 8 || winकरोwBits > 15) अणु
        वापस Z_STREAM_ERROR;
    पूर्ण
    state->wbits = (अचिन्हित)winकरोwBits;
#अगर_घोषित CONFIG_ZLIB_DFLTCC
    /*
     * DFLTCC requires the winकरोw to be page aligned.
     * Thus, we overallocate and take the aligned portion of the buffer.
     */
    state->winकरोw = PTR_ALIGN(&WS(strm)->working_winकरोw[0], PAGE_SIZE);
#अन्यथा
    state->winकरोw = &WS(strm)->working_winकरोw[0];
#पूर्ण_अगर

    वापस zlib_inflateReset(strm);
पूर्ण

/*
   Return state with length and distance decoding tables and index sizes set to
   fixed code decoding.  This वापसs fixed tables from inffixed.h.
 */
अटल व्योम zlib_fixedtables(काष्ठा inflate_state *state)
अणु
#   include "inffixed.h"
    state->lencode = lenfix;
    state->lenbits = 9;
    state->distcode = distfix;
    state->distbits = 5;
पूर्ण


/*
   Update the winकरोw with the last wsize (normally 32K) bytes written beक्रमe
   वापसing. This is only called when a winकरोw is alपढ़ोy in use, or when
   output has been written during this inflate call, but the end of the deflate
   stream has not been reached yet. It is also called to winकरोw dictionary data
   when a dictionary is loaded.

   Providing output buffers larger than 32K to inflate() should provide a speed
   advantage, since only the last 32K of output is copied to the sliding winकरोw
   upon वापस from inflate(), and since all distances after the first 32K of
   output will fall in the output data, making match copies simpler and faster.
   The advantage may be dependent on the size of the processor's data caches.
 */
अटल व्योम zlib_updatewinकरोw(z_streamp strm, अचिन्हित out)
अणु
    काष्ठा inflate_state *state;
    अचिन्हित copy, dist;

    state = (काष्ठा inflate_state *)strm->state;

    /* copy state->wsize or less output bytes पूर्णांकo the circular winकरोw */
    copy = out - strm->avail_out;
    अगर (copy >= state->wsize) अणु
        स_नकल(state->winकरोw, strm->next_out - state->wsize, state->wsize);
        state->ग_लिखो = 0;
        state->whave = state->wsize;
    पूर्ण
    अन्यथा अणु
        dist = state->wsize - state->ग_लिखो;
        अगर (dist > copy) dist = copy;
        स_नकल(state->winकरोw + state->ग_लिखो, strm->next_out - copy, dist);
        copy -= dist;
        अगर (copy) अणु
            स_नकल(state->winकरोw, strm->next_out - copy, copy);
            state->ग_लिखो = copy;
            state->whave = state->wsize;
        पूर्ण
        अन्यथा अणु
            state->ग_लिखो += dist;
            अगर (state->ग_लिखो == state->wsize) state->ग_लिखो = 0;
            अगर (state->whave < state->wsize) state->whave += dist;
        पूर्ण
    पूर्ण
पूर्ण


/*
 * At the end of a Deflate-compressed PPP packet, we expect to have seen
 * a `stored' block type value but not the (zero) length bytes.
 */
/*
   Returns true अगर inflate is currently at the end of a block generated by
   Z_SYNC_FLUSH or Z_FULL_FLUSH. This function is used by one PPP
   implementation to provide an additional safety check. PPP uses
   Z_SYNC_FLUSH but हटाओs the length bytes of the resulting empty stored
   block. When decompressing, PPP checks that at the end of input packet,
   inflate is रुकोing क्रम these length bytes.
 */
अटल पूर्णांक zlib_inflateSyncPacket(z_streamp strm)
अणु
    काष्ठा inflate_state *state;

    अगर (strm == शून्य || strm->state == शून्य) वापस Z_STREAM_ERROR;
    state = (काष्ठा inflate_state *)strm->state;

    अगर (state->mode == STORED && state->bits == 0) अणु
	state->mode = TYPE;
        वापस Z_OK;
    पूर्ण
    वापस Z_DATA_ERROR;
पूर्ण

/* Macros क्रम inflate(): */

/* check function to use adler32() क्रम zlib or crc32() क्रम gzip */
#घोषणा UPDATE(check, buf, len) zlib_adler32(check, buf, len)

/* Load रेजिस्टरs with state in inflate() क्रम speed */
#घोषणा LOAD() \
    करो अणु \
        put = strm->next_out; \
        left = strm->avail_out; \
        next = strm->next_in; \
        have = strm->avail_in; \
        hold = state->hold; \
        bits = state->bits; \
    पूर्ण जबतक (0)

/* Restore state from रेजिस्टरs in inflate() */
#घोषणा RESTORE() \
    करो अणु \
        strm->next_out = put; \
        strm->avail_out = left; \
        strm->next_in = next; \
        strm->avail_in = have; \
        state->hold = hold; \
        state->bits = bits; \
    पूर्ण जबतक (0)

/* Clear the input bit accumulator */
#घोषणा INITBITS() \
    करो अणु \
        hold = 0; \
        bits = 0; \
    पूर्ण जबतक (0)

/* Get a byte of input पूर्णांकo the bit accumulator, or वापस from inflate()
   अगर there is no input available. */
#घोषणा PULLBYTE() \
    करो अणु \
        अगर (have == 0) जाओ inf_leave; \
        have--; \
        hold += (अचिन्हित दीर्घ)(*next++) << bits; \
        bits += 8; \
    पूर्ण जबतक (0)

/* Assure that there are at least n bits in the bit accumulator.  If there is
   not enough available input to करो that, then वापस from inflate(). */
#घोषणा NEEDBITS(n) \
    करो अणु \
        जबतक (bits < (अचिन्हित)(n)) \
            PULLBYTE(); \
    पूर्ण जबतक (0)

/* Return the low n bits of the bit accumulator (n < 16) */
#घोषणा BITS(n) \
    ((अचिन्हित)hold & ((1U << (n)) - 1))

/* Remove n bits from the bit accumulator */
#घोषणा DROPBITS(n) \
    करो अणु \
        hold >>= (n); \
        bits -= (अचिन्हित)(n); \
    पूर्ण जबतक (0)

/* Remove zero to seven bits as needed to go to a byte boundary */
#घोषणा BYTEBITS() \
    करो अणु \
        hold >>= bits & 7; \
        bits -= bits & 7; \
    पूर्ण जबतक (0)

/*
   inflate() uses a state machine to process as much input data and generate as
   much output data as possible beक्रमe वापसing.  The state machine is
   काष्ठाured roughly as follows:

    क्रम (;;) चयन (state) अणु
    ...
    हाल STATEn:
        अगर (not enough input data or output space to make progress)
            वापस;
        ... make progress ...
        state = STATEm;
        अवरोध;
    ...
    पूर्ण

   so when inflate() is called again, the same हाल is attempted again, and
   अगर the appropriate resources are provided, the machine proceeds to the
   next state.  The NEEDBITS() macro is usually the way the state evaluates
   whether it can proceed or should वापस.  NEEDBITS() करोes the वापस अगर
   the requested bits are not available.  The typical use of the BITS macros
   is:

        NEEDBITS(n);
        ... करो something with BITS(n) ...
        DROPBITS(n);

   where NEEDBITS(n) either वापसs from inflate() अगर there isn't enough
   input left to load n bits पूर्णांकo the accumulator, or it जारीs.  BITS(n)
   gives the low n bits in the accumulator.  When करोne, DROPBITS(n) drops
   the low n bits off the accumulator.  INITBITS() clears the accumulator
   and sets the number of available bits to zero.  BYTEBITS() discards just
   enough bits to put the accumulator on a byte boundary.  After BYTEBITS()
   and a NEEDBITS(8), then BITS(8) would वापस the next byte in the stream.

   NEEDBITS(n) uses PULLBYTE() to get an available byte of input, or to वापस
   अगर there is no input available.  The decoding of variable length codes uses
   PULLBYTE() directly in order to pull just enough bytes to decode the next
   code, and no more.

   Some states loop until they get enough input, making sure that enough
   state inक्रमmation is मुख्यtained to जारी the loop where it left off
   अगर NEEDBITS() वापसs in the loop.  For example, want, need, and keep
   would all have to actually be part of the saved state in हाल NEEDBITS()
   वापसs:

    हाल STATEw:
        जबतक (want < need) अणु
            NEEDBITS(n);
            keep[want++] = BITS(n);
            DROPBITS(n);
        पूर्ण
        state = STATEx;
    हाल STATEx:

   As shown above, अगर the next state is also the next हाल, then the अवरोध
   is omitted.

   A state may also वापस अगर there is not enough output space available to
   complete that state.  Those states are copying stored data, writing a
   literal byte, and copying a matching string.

   When वापसing, a "goto inf_leave" is used to update the total counters,
   update the check value, and determine whether any progress has been made
   during that inflate() call in order to वापस the proper वापस code.
   Progress is defined as a change in either strm->avail_in or strm->avail_out.
   When there is a winकरोw, जाओ inf_leave will update the winकरोw with the last
   output written.  If a जाओ inf_leave occurs in the middle of decompression
   and there is no winकरोw currently, जाओ inf_leave will create one and copy
   output to the winकरोw क्रम the next call of inflate().

   In this implementation, the flush parameter of inflate() only affects the
   वापस code (per zlib.h).  inflate() always ग_लिखोs as much as possible to
   strm->next_out, given the space available and the provided input--the effect
   करोcumented in zlib.h of Z_SYNC_FLUSH.  Furthermore, inflate() always defers
   the allocation of and copying पूर्णांकo a sliding winकरोw until necessary, which
   provides the effect करोcumented in zlib.h क्रम Z_FINISH when the entire input
   stream available.  So the only thing the flush parameter actually करोes is:
   when flush is set to Z_FINISH, inflate() cannot वापस Z_OK.  Instead it
   will वापस Z_BUF_ERROR अगर it has not reached the end of the stream.
 */

पूर्णांक zlib_inflate(z_streamp strm, पूर्णांक flush)
अणु
    काष्ठा inflate_state *state;
    स्थिर अचिन्हित अक्षर *next;  /* next input */
    अचिन्हित अक्षर *put;         /* next output */
    अचिन्हित have, left;        /* available input and output */
    अचिन्हित दीर्घ hold;         /* bit buffer */
    अचिन्हित bits;              /* bits in bit buffer */
    अचिन्हित in, out;           /* save starting available input and output */
    अचिन्हित copy;              /* number of stored or match bytes to copy */
    अचिन्हित अक्षर *from;        /* where to copy match bytes from */
    code this;                  /* current decoding table entry */
    code last;                  /* parent table entry */
    अचिन्हित len;               /* length to copy क्रम repeats, bits to drop */
    पूर्णांक ret;                    /* वापस code */
    अटल स्थिर अचिन्हित लघु order[19] = /* permutation of code lengths */
        अणु16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15पूर्ण;

    /* Do not check क्रम strm->next_out == शून्य here as ppc zImage
       inflates to strm->next_out = 0 */

    अगर (strm == शून्य || strm->state == शून्य ||
        (strm->next_in == शून्य && strm->avail_in != 0))
        वापस Z_STREAM_ERROR;

    state = (काष्ठा inflate_state *)strm->state;

    अगर (state->mode == TYPE) state->mode = TYPEDO;      /* skip check */
    LOAD();
    in = have;
    out = left;
    ret = Z_OK;
    क्रम (;;)
        चयन (state->mode) अणु
        हाल HEAD:
            अगर (state->wrap == 0) अणु
                state->mode = TYPEDO;
                अवरोध;
            पूर्ण
            NEEDBITS(16);
            अगर (
                ((BITS(8) << 8) + (hold >> 8)) % 31) अणु
                strm->msg = (अक्षर *)"incorrect header check";
                state->mode = BAD;
                अवरोध;
            पूर्ण
            अगर (BITS(4) != Z_DEFLATED) अणु
                strm->msg = (अक्षर *)"unknown compression method";
                state->mode = BAD;
                अवरोध;
            पूर्ण
            DROPBITS(4);
            len = BITS(4) + 8;
            अगर (len > state->wbits) अणु
                strm->msg = (अक्षर *)"invalid window size";
                state->mode = BAD;
                अवरोध;
            पूर्ण
            state->dmax = 1U << len;
            strm->adler = state->check = zlib_adler32(0L, शून्य, 0);
            state->mode = hold & 0x200 ? DICTID : TYPE;
            INITBITS();
            अवरोध;
        हाल DICTID:
            NEEDBITS(32);
            strm->adler = state->check = REVERSE(hold);
            INITBITS();
            state->mode = DICT;
	    fallthrough;
        हाल DICT:
            अगर (state->havedict == 0) अणु
                RESTORE();
                वापस Z_NEED_DICT;
            पूर्ण
            strm->adler = state->check = zlib_adler32(0L, शून्य, 0);
            state->mode = TYPE;
	    fallthrough;
        हाल TYPE:
            अगर (flush == Z_BLOCK) जाओ inf_leave;
	    fallthrough;
        हाल TYPEDO:
            INFLATE_TYPEDO_HOOK(strm, flush);
            अगर (state->last) अणु
                BYTEBITS();
                state->mode = CHECK;
                अवरोध;
            पूर्ण
            NEEDBITS(3);
            state->last = BITS(1);
            DROPBITS(1);
            चयन (BITS(2)) अणु
            हाल 0:                             /* stored block */
                state->mode = STORED;
                अवरोध;
            हाल 1:                             /* fixed block */
                zlib_fixedtables(state);
                state->mode = LEN;              /* decode codes */
                अवरोध;
            हाल 2:                             /* dynamic block */
                state->mode = TABLE;
                अवरोध;
            हाल 3:
                strm->msg = (अक्षर *)"invalid block type";
                state->mode = BAD;
            पूर्ण
            DROPBITS(2);
            अवरोध;
        हाल STORED:
            BYTEBITS();                         /* go to byte boundary */
            NEEDBITS(32);
            अगर ((hold & 0xffff) != ((hold >> 16) ^ 0xffff)) अणु
                strm->msg = (अक्षर *)"invalid stored block lengths";
                state->mode = BAD;
                अवरोध;
            पूर्ण
            state->length = (अचिन्हित)hold & 0xffff;
            INITBITS();
            state->mode = COPY;
	    fallthrough;
        हाल COPY:
            copy = state->length;
            अगर (copy) अणु
                अगर (copy > have) copy = have;
                अगर (copy > left) copy = left;
                अगर (copy == 0) जाओ inf_leave;
                स_नकल(put, next, copy);
                have -= copy;
                next += copy;
                left -= copy;
                put += copy;
                state->length -= copy;
                अवरोध;
            पूर्ण
            state->mode = TYPE;
            अवरोध;
        हाल TABLE:
            NEEDBITS(14);
            state->nlen = BITS(5) + 257;
            DROPBITS(5);
            state->ndist = BITS(5) + 1;
            DROPBITS(5);
            state->ncode = BITS(4) + 4;
            DROPBITS(4);
#अगर_अघोषित PKZIP_BUG_WORKAROUND
            अगर (state->nlen > 286 || state->ndist > 30) अणु
                strm->msg = (अक्षर *)"too many length or distance symbols";
                state->mode = BAD;
                अवरोध;
            पूर्ण
#पूर्ण_अगर
            state->have = 0;
            state->mode = LENLENS;
	    fallthrough;
        हाल LENLENS:
            जबतक (state->have < state->ncode) अणु
                NEEDBITS(3);
                state->lens[order[state->have++]] = (अचिन्हित लघु)BITS(3);
                DROPBITS(3);
            पूर्ण
            जबतक (state->have < 19)
                state->lens[order[state->have++]] = 0;
            state->next = state->codes;
            state->lencode = (code स्थिर *)(state->next);
            state->lenbits = 7;
            ret = zlib_inflate_table(CODES, state->lens, 19, &(state->next),
                                &(state->lenbits), state->work);
            अगर (ret) अणु
                strm->msg = (अक्षर *)"invalid code lengths set";
                state->mode = BAD;
                अवरोध;
            पूर्ण
            state->have = 0;
            state->mode = CODELENS;
	    fallthrough;
        हाल CODELENS:
            जबतक (state->have < state->nlen + state->ndist) अणु
                क्रम (;;) अणु
                    this = state->lencode[BITS(state->lenbits)];
                    अगर ((अचिन्हित)(this.bits) <= bits) अवरोध;
                    PULLBYTE();
                पूर्ण
                अगर (this.val < 16) अणु
                    NEEDBITS(this.bits);
                    DROPBITS(this.bits);
                    state->lens[state->have++] = this.val;
                पूर्ण
                अन्यथा अणु
                    अगर (this.val == 16) अणु
                        NEEDBITS(this.bits + 2);
                        DROPBITS(this.bits);
                        अगर (state->have == 0) अणु
                            strm->msg = (अक्षर *)"invalid bit length repeat";
                            state->mode = BAD;
                            अवरोध;
                        पूर्ण
                        len = state->lens[state->have - 1];
                        copy = 3 + BITS(2);
                        DROPBITS(2);
                    पूर्ण
                    अन्यथा अगर (this.val == 17) अणु
                        NEEDBITS(this.bits + 3);
                        DROPBITS(this.bits);
                        len = 0;
                        copy = 3 + BITS(3);
                        DROPBITS(3);
                    पूर्ण
                    अन्यथा अणु
                        NEEDBITS(this.bits + 7);
                        DROPBITS(this.bits);
                        len = 0;
                        copy = 11 + BITS(7);
                        DROPBITS(7);
                    पूर्ण
                    अगर (state->have + copy > state->nlen + state->ndist) अणु
                        strm->msg = (अक्षर *)"invalid bit length repeat";
                        state->mode = BAD;
                        अवरोध;
                    पूर्ण
                    जबतक (copy--)
                        state->lens[state->have++] = (अचिन्हित लघु)len;
                पूर्ण
            पूर्ण

            /* handle error अवरोधs in जबतक */
            अगर (state->mode == BAD) अवरोध;

            /* build code tables */
            state->next = state->codes;
            state->lencode = (code स्थिर *)(state->next);
            state->lenbits = 9;
            ret = zlib_inflate_table(LENS, state->lens, state->nlen, &(state->next),
                                &(state->lenbits), state->work);
            अगर (ret) अणु
                strm->msg = (अक्षर *)"invalid literal/lengths set";
                state->mode = BAD;
                अवरोध;
            पूर्ण
            state->distcode = (code स्थिर *)(state->next);
            state->distbits = 6;
            ret = zlib_inflate_table(DISTS, state->lens + state->nlen, state->ndist,
                            &(state->next), &(state->distbits), state->work);
            अगर (ret) अणु
                strm->msg = (अक्षर *)"invalid distances set";
                state->mode = BAD;
                अवरोध;
            पूर्ण
            state->mode = LEN;
	    fallthrough;
        हाल LEN:
            अगर (have >= 6 && left >= 258) अणु
                RESTORE();
                inflate_fast(strm, out);
                LOAD();
                अवरोध;
            पूर्ण
            क्रम (;;) अणु
                this = state->lencode[BITS(state->lenbits)];
                अगर ((अचिन्हित)(this.bits) <= bits) अवरोध;
                PULLBYTE();
            पूर्ण
            अगर (this.op && (this.op & 0xf0) == 0) अणु
                last = this;
                क्रम (;;) अणु
                    this = state->lencode[last.val +
                            (BITS(last.bits + last.op) >> last.bits)];
                    अगर ((अचिन्हित)(last.bits + this.bits) <= bits) अवरोध;
                    PULLBYTE();
                पूर्ण
                DROPBITS(last.bits);
            पूर्ण
            DROPBITS(this.bits);
            state->length = (अचिन्हित)this.val;
            अगर ((पूर्णांक)(this.op) == 0) अणु
                state->mode = LIT;
                अवरोध;
            पूर्ण
            अगर (this.op & 32) अणु
                state->mode = TYPE;
                अवरोध;
            पूर्ण
            अगर (this.op & 64) अणु
                strm->msg = (अक्षर *)"invalid literal/length code";
                state->mode = BAD;
                अवरोध;
            पूर्ण
            state->extra = (अचिन्हित)(this.op) & 15;
            state->mode = LENEXT;
	    fallthrough;
        हाल LENEXT:
            अगर (state->extra) अणु
                NEEDBITS(state->extra);
                state->length += BITS(state->extra);
                DROPBITS(state->extra);
            पूर्ण
            state->mode = DIST;
	    fallthrough;
        हाल DIST:
            क्रम (;;) अणु
                this = state->distcode[BITS(state->distbits)];
                अगर ((अचिन्हित)(this.bits) <= bits) अवरोध;
                PULLBYTE();
            पूर्ण
            अगर ((this.op & 0xf0) == 0) अणु
                last = this;
                क्रम (;;) अणु
                    this = state->distcode[last.val +
                            (BITS(last.bits + last.op) >> last.bits)];
                    अगर ((अचिन्हित)(last.bits + this.bits) <= bits) अवरोध;
                    PULLBYTE();
                पूर्ण
                DROPBITS(last.bits);
            पूर्ण
            DROPBITS(this.bits);
            अगर (this.op & 64) अणु
                strm->msg = (अक्षर *)"invalid distance code";
                state->mode = BAD;
                अवरोध;
            पूर्ण
            state->offset = (अचिन्हित)this.val;
            state->extra = (अचिन्हित)(this.op) & 15;
            state->mode = DISTEXT;
	    fallthrough;
        हाल DISTEXT:
            अगर (state->extra) अणु
                NEEDBITS(state->extra);
                state->offset += BITS(state->extra);
                DROPBITS(state->extra);
            पूर्ण
#अगर_घोषित INFLATE_STRICT
            अगर (state->offset > state->dmax) अणु
                strm->msg = (अक्षर *)"invalid distance too far back";
                state->mode = BAD;
                अवरोध;
            पूर्ण
#पूर्ण_अगर
            अगर (state->offset > state->whave + out - left) अणु
                strm->msg = (अक्षर *)"invalid distance too far back";
                state->mode = BAD;
                अवरोध;
            पूर्ण
            state->mode = MATCH;
	    fallthrough;
        हाल MATCH:
            अगर (left == 0) जाओ inf_leave;
            copy = out - left;
            अगर (state->offset > copy) अणु         /* copy from winकरोw */
                copy = state->offset - copy;
                अगर (copy > state->ग_लिखो) अणु
                    copy -= state->ग_लिखो;
                    from = state->winकरोw + (state->wsize - copy);
                पूर्ण
                अन्यथा
                    from = state->winकरोw + (state->ग_लिखो - copy);
                अगर (copy > state->length) copy = state->length;
            पूर्ण
            अन्यथा अणु                              /* copy from output */
                from = put - state->offset;
                copy = state->length;
            पूर्ण
            अगर (copy > left) copy = left;
            left -= copy;
            state->length -= copy;
            करो अणु
                *put++ = *from++;
            पूर्ण जबतक (--copy);
            अगर (state->length == 0) state->mode = LEN;
            अवरोध;
        हाल LIT:
            अगर (left == 0) जाओ inf_leave;
            *put++ = (अचिन्हित अक्षर)(state->length);
            left--;
            state->mode = LEN;
            अवरोध;
        हाल CHECK:
            अगर (state->wrap) अणु
                NEEDBITS(32);
                out -= left;
                strm->total_out += out;
                state->total += out;
                अगर (INFLATE_NEED_CHECKSUM(strm) && out)
                    strm->adler = state->check =
                        UPDATE(state->check, put - out, out);
                out = left;
                अगर ((
                     REVERSE(hold)) != state->check) अणु
                    strm->msg = (अक्षर *)"incorrect data check";
                    state->mode = BAD;
                    अवरोध;
                पूर्ण
                INITBITS();
            पूर्ण
            state->mode = DONE;
	    fallthrough;
        हाल DONE:
            ret = Z_STREAM_END;
            जाओ inf_leave;
        हाल BAD:
            ret = Z_DATA_ERROR;
            जाओ inf_leave;
        हाल MEM:
            वापस Z_MEM_ERROR;
        हाल SYNC:
        शेष:
            वापस Z_STREAM_ERROR;
        पूर्ण

    /*
       Return from inflate(), updating the total counts and the check value.
       If there was no progress during the inflate() call, वापस a buffer
       error.  Call zlib_updatewinकरोw() to create and/or update the winकरोw state.
     */
  inf_leave:
    RESTORE();
    अगर (INFLATE_NEED_UPDATEWINDOW(strm) &&
            (state->wsize || (state->mode < CHECK && out != strm->avail_out)))
        zlib_updatewinकरोw(strm, out);

    in -= strm->avail_in;
    out -= strm->avail_out;
    strm->total_in += in;
    strm->total_out += out;
    state->total += out;
    अगर (INFLATE_NEED_CHECKSUM(strm) && state->wrap && out)
        strm->adler = state->check =
            UPDATE(state->check, strm->next_out - out, out);

    strm->data_type = state->bits + (state->last ? 64 : 0) +
                      (state->mode == TYPE ? 128 : 0);

    अगर (flush == Z_PACKET_FLUSH && ret == Z_OK &&
            strm->avail_out != 0 && strm->avail_in == 0)
		वापस zlib_inflateSyncPacket(strm);

    अगर (((in == 0 && out == 0) || flush == Z_FINISH) && ret == Z_OK)
        ret = Z_BUF_ERROR;

    वापस ret;
पूर्ण

पूर्णांक zlib_inflateEnd(z_streamp strm)
अणु
    अगर (strm == शून्य || strm->state == शून्य)
        वापस Z_STREAM_ERROR;
    वापस Z_OK;
पूर्ण

/*
 * This subroutine adds the data at next_in/avail_in to the output history
 * without perक्रमming any output.  The output buffer must be "caught up";
 * i.e. no pending output but this should always be the हाल. The state must
 * be रुकोing on the start of a block (i.e. mode == TYPE or HEAD).  On निकास,
 * the output will also be caught up, and the checksum will have been updated
 * अगर need be.
 */
पूर्णांक zlib_inflateIncomp(z_stream *z)
अणु
    काष्ठा inflate_state *state = (काष्ठा inflate_state *)z->state;
    Byte *saved_no = z->next_out;
    uInt saved_ao = z->avail_out;

    अगर (state->mode != TYPE && state->mode != HEAD)
	वापस Z_DATA_ERROR;

    /* Setup some variables to allow misuse of updateWinकरोw */
    z->avail_out = 0;
    z->next_out = (अचिन्हित अक्षर*)z->next_in + z->avail_in;

    zlib_updatewinकरोw(z, z->avail_in);

    /* Restore saved variables */
    z->avail_out = saved_ao;
    z->next_out = saved_no;

    z->adler = state->check =
        UPDATE(state->check, z->next_in, z->avail_in);

    z->total_out += z->avail_in;
    z->total_in += z->avail_in;
    z->next_in += z->avail_in;
    state->total += z->avail_in;
    z->avail_in = 0;

    वापस Z_OK;
पूर्ण
