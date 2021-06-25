<शैली गुरु>
/*
 * Update: The Berkeley copyright was changed, and the change
 * is retroactive to all "true" BSD software (ie everything
 * from UCB as opposed to other peoples code that just carried
 * the same license). The new copyright करोesn't clash with the
 * GPL, so the module-only restriction has been हटाओd..
 */

/* Because this code is derived from the 4.3BSD compress source:
 *
 * Copyright (c) 1985, 1986 The Regents of the University of Calअगरornia.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * James A. Woods, derived from original work by Spencer Thomas
 * and Joseph Orost.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	Calअगरornia, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to enकरोrse or promote products derived from this software
 *    without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/*
 * This version is क्रम use with contiguous buffers on Linux-derived प्रणालीs.
 *
 *  ==खाताVERSION 20000226==
 *
 *  NOTE TO MAINTAINERS:
 *     If you modअगरy this file at all, please set the number above to the
 *     date of the modअगरication as YYMMDD (year month day).
 *     bsd_comp.c is shipped with a PPP distribution as well as with
 *     the kernel; अगर everyone increases the खाताVERSION number above,
 *     then scripts can करो the right thing when deciding whether to
 *     install a new bsd_comp.c file. Don't change the क्रमmat of that
 *     line otherwise, so the installation script can recognize it.
 *
 * From: bsd_comp.c,v 1.3 1994/12/08 01:59:58 paulus Exp
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/माला.स>

#समावेश <linux/ppp_defs.h>

#अघोषित   PACKETPTR
#घोषणा  PACKETPTR 1
#समावेश <linux/ppp-comp.h>
#अघोषित   PACKETPTR

#समावेश <यंत्र/byteorder.h>

/*
 * PPP "BSD compress" compression
 *  The dअगरferences between this compression and the classic BSD LZW
 *  source are obvious from the requirement that the classic code worked
 *  with files जबतक this handles arbitrarily दीर्घ streams that
 *  are broken पूर्णांकo packets.  They are:
 *
 *	When the code size expands, a block of junk is not emitted by
 *	    the compressor and not expected by the decompressor.
 *
 *	New codes are not necessarily asचिन्हित every समय an old
 *	    code is output by the compressor.  This is because a packet
 *	    end क्रमces a code to be emitted, but करोes not imply that a
 *	    new sequence has been seen.
 *
 *	The compression ratio is checked at the first end of a packet
 *	    after the appropriate gap.	Besides simplअगरying and speeding
 *	    things up, this makes it more likely that the transmitter
 *	    and receiver will agree when the dictionary is cleared when
 *	    compression is not going well.
 */

/*
 * Macros to extract protocol version and number of bits
 * from the third byte of the BSD Compress CCP configuration option.
 */

#घोषणा BSD_VERSION(x)	((x) >> 5)
#घोषणा BSD_NBITS(x)	((x) & 0x1F)

#घोषणा BSD_CURRENT_VERSION	1

/*
 * A dictionary क्रम करोing BSD compress.
 */

काष्ठा bsd_dict अणु
    जोड़ अणु				/* hash value */
	अचिन्हित दीर्घ	fcode;
	काष्ठा अणु
#अगर defined(__LITTLE_ENDIAN)		/* Little endian order */
	    अचिन्हित लघु	prefix;	/* preceding code */
	    अचिन्हित अक्षर	suffix; /* last अक्षरacter of new code */
	    अचिन्हित अक्षर	pad;
#या_अगर defined(__BIG_ENDIAN)		/* Big endian order */
	    अचिन्हित अक्षर	pad;
	    अचिन्हित अक्षर	suffix; /* last अक्षरacter of new code */
	    अचिन्हित लघु	prefix; /* preceding code */
#अन्यथा
#त्रुटि Endianness not defined...
#पूर्ण_अगर
	पूर्ण hs;
    पूर्ण f;
    अचिन्हित लघु codem1;		/* output of hash table -1 */
    अचिन्हित लघु cptr;		/* map code to hash table entry */
पूर्ण;

काष्ठा bsd_db अणु
    पूर्णांक	    totlen;			/* length of this काष्ठाure */
    अचिन्हित पूर्णांक   hsize;		/* size of the hash table */
    अचिन्हित अक्षर  hshअगरt;		/* used in hash function */
    अचिन्हित अक्षर  n_bits;		/* current bits/code */
    अचिन्हित अक्षर  maxbits;		/* maximum bits/code */
    अचिन्हित अक्षर  debug;		/* non-zero अगर debug desired */
    अचिन्हित अक्षर  unit;		/* ppp unit number */
    अचिन्हित लघु seqno;		/* sequence # of next packet */
    अचिन्हित पूर्णांक   mru;			/* size of receive (decompress) bufr */
    अचिन्हित पूर्णांक   maxmaxcode;		/* largest valid code */
    अचिन्हित पूर्णांक   max_ent;		/* largest code in use */
    अचिन्हित पूर्णांक   in_count;		/* uncompressed bytes, aged */
    अचिन्हित पूर्णांक   bytes_out;		/* compressed bytes, aged */
    अचिन्हित पूर्णांक   ratio;		/* recent compression ratio */
    अचिन्हित पूर्णांक   checkpoपूर्णांक;		/* when to next check the ratio */
    अचिन्हित पूर्णांक   clear_count;		/* बार dictionary cleared */
    अचिन्हित पूर्णांक   incomp_count;	/* incompressible packets */
    अचिन्हित पूर्णांक   incomp_bytes;	/* incompressible bytes */
    अचिन्हित पूर्णांक   uncomp_count;	/* uncompressed packets */
    अचिन्हित पूर्णांक   uncomp_bytes;	/* uncompressed bytes */
    अचिन्हित पूर्णांक   comp_count;		/* compressed packets */
    अचिन्हित पूर्णांक   comp_bytes;		/* compressed bytes */
    अचिन्हित लघु  *lens;		/* array of lengths of codes */
    काष्ठा bsd_dict *dict;		/* dictionary */
पूर्ण;

#घोषणा BSD_OVHD	2		/* BSD compress overhead/packet */
#घोषणा MIN_BSD_BITS	9
#घोषणा BSD_INIT_BITS	MIN_BSD_BITS
#घोषणा MAX_BSD_BITS	15

अटल व्योम	bsd_मुक्त (व्योम *state);
अटल व्योम	*bsd_alloc(अचिन्हित अक्षर *options, पूर्णांक opt_len, पूर्णांक decomp);
अटल व्योम	*bsd_comp_alloc (अचिन्हित अक्षर *options, पूर्णांक opt_len);
अटल व्योम	*bsd_decomp_alloc (अचिन्हित अक्षर *options, पूर्णांक opt_len);

अटल पूर्णांक	bsd_init        (व्योम *db, अचिन्हित अक्षर *options,
			         पूर्णांक opt_len, पूर्णांक unit, पूर्णांक debug, पूर्णांक decomp);
अटल पूर्णांक	bsd_comp_init   (व्योम *state, अचिन्हित अक्षर *options,
			         पूर्णांक opt_len, पूर्णांक unit, पूर्णांक opthdr, पूर्णांक debug);
अटल पूर्णांक	bsd_decomp_init (व्योम *state, अचिन्हित अक्षर *options,
				 पूर्णांक opt_len, पूर्णांक unit, पूर्णांक opthdr, पूर्णांक mru,
				 पूर्णांक debug);

अटल व्योम	bsd_reset (व्योम *state);
अटल व्योम	bsd_comp_stats (व्योम *state, काष्ठा compstat *stats);

अटल पूर्णांक	bsd_compress (व्योम *state, अचिन्हित अक्षर *rptr,
			      अचिन्हित अक्षर *obuf, पूर्णांक isize, पूर्णांक osize);
अटल व्योम	bsd_incomp (व्योम *state, अचिन्हित अक्षर *ibuf, पूर्णांक icnt);

अटल पूर्णांक	bsd_decompress (व्योम *state, अचिन्हित अक्षर *ibuf, पूर्णांक isize,
				अचिन्हित अक्षर *obuf, पूर्णांक osize);

/* These are in ppp_generic.c */
बाह्य पूर्णांक  ppp_रेजिस्टर_compressor   (काष्ठा compressor *cp);
बाह्य व्योम ppp_unरेजिस्टर_compressor (काष्ठा compressor *cp);

/*
 * the next two codes should not be changed lightly, as they must not
 * lie within the contiguous general code space.
 */
#घोषणा CLEAR	256			/* table clear output code */
#घोषणा FIRST	257			/* first मुक्त entry */
#घोषणा LAST	255

#घोषणा MAXCODE(b)	((1 << (b)) - 1)
#घोषणा BADCODEM1	MAXCODE(MAX_BSD_BITS)

#घोषणा BSD_HASH(prefix,suffix,hshअगरt) ((((अचिन्हित दीर्घ)(suffix))<<(hshअगरt)) \
					 ^ (अचिन्हित दीर्घ)(prefix))
#घोषणा BSD_KEY(prefix,suffix)		((((अचिन्हित दीर्घ)(suffix)) << 16) \
					 + (अचिन्हित दीर्घ)(prefix))

#घोषणा CHECK_GAP	10000		/* Ratio check पूर्णांकerval */

#घोषणा RATIO_SCALE_LOG	8
#घोषणा RATIO_SCALE	(1<<RATIO_SCALE_LOG)
#घोषणा RATIO_MAX	(0x7fffffff>>RATIO_SCALE_LOG)

/*
 * clear the dictionary
 */

अटल व्योम
bsd_clear(काष्ठा bsd_db *db)
अणु
    db->clear_count++;
    db->max_ent      = FIRST-1;
    db->n_bits       = BSD_INIT_BITS;
    db->bytes_out    = 0;
    db->in_count     = 0;
    db->ratio	     = 0;
    db->checkpoपूर्णांक   = CHECK_GAP;
पूर्ण

/*
 * If the dictionary is full, then see अगर it is समय to reset it.
 *
 * Compute the compression ratio using fixed-poपूर्णांक arithmetic
 * with 8 fractional bits.
 *
 * Since we have an infinite stream instead of a single file,
 * watch only the local compression ratio.
 *
 * Since both peers must reset the dictionary at the same समय even in
 * the असलence of CLEAR codes (जबतक packets are incompressible), they
 * must compute the same ratio.
 */

अटल पूर्णांक bsd_check (काष्ठा bsd_db *db)	/* 1=output CLEAR */
  अणु
    अचिन्हित पूर्णांक new_ratio;

    अगर (db->in_count >= db->checkpoपूर्णांक)
      अणु
	/* age the ratio by limiting the size of the counts */
	अगर (db->in_count >= RATIO_MAX || db->bytes_out >= RATIO_MAX)
	  अणु
	    db->in_count  -= (db->in_count  >> 2);
	    db->bytes_out -= (db->bytes_out >> 2);
	  पूर्ण

	db->checkpoपूर्णांक = db->in_count + CHECK_GAP;

	अगर (db->max_ent >= db->maxmaxcode)
	  अणु
	    /* Reset the dictionary only अगर the ratio is worse,
	     * or अगर it looks as अगर it has been poisoned
	     * by incompressible data.
	     *
	     * This करोes not overflow, because
	     *	db->in_count <= RATIO_MAX.
	     */

	    new_ratio = db->in_count << RATIO_SCALE_LOG;
	    अगर (db->bytes_out != 0)
	      अणु
		new_ratio /= db->bytes_out;
	      पूर्ण

	    अगर (new_ratio < db->ratio || new_ratio < 1 * RATIO_SCALE)
	      अणु
		bsd_clear (db);
		वापस 1;
	      पूर्ण
	    db->ratio = new_ratio;
	  पूर्ण
      पूर्ण
    वापस 0;
  पूर्ण

/*
 * Return statistics.
 */

अटल व्योम bsd_comp_stats (व्योम *state, काष्ठा compstat *stats)
  अणु
    काष्ठा bsd_db *db = (काष्ठा bsd_db *) state;

    stats->unc_bytes    = db->uncomp_bytes;
    stats->unc_packets  = db->uncomp_count;
    stats->comp_bytes   = db->comp_bytes;
    stats->comp_packets = db->comp_count;
    stats->inc_bytes    = db->incomp_bytes;
    stats->inc_packets  = db->incomp_count;
    stats->in_count     = db->in_count;
    stats->bytes_out    = db->bytes_out;
  पूर्ण

/*
 * Reset state, as on a CCP ResetReq.
 */

अटल व्योम bsd_reset (व्योम *state)
  अणु
    काष्ठा bsd_db *db = (काष्ठा bsd_db *) state;

    bsd_clear(db);

    db->seqno       = 0;
    db->clear_count = 0;
  पूर्ण

/*
 * Release the compression काष्ठाure
 */

अटल व्योम bsd_मुक्त (व्योम *state)
अणु
	काष्ठा bsd_db *db = state;

	अगर (!db)
		वापस;

/*
 * Release the dictionary
 */
	vमुक्त(db->dict);
	db->dict = शून्य;
/*
 * Release the string buffer
 */
	vमुक्त(db->lens);
	db->lens = शून्य;
/*
 * Finally release the काष्ठाure itself.
 */
	kमुक्त(db);
पूर्ण

/*
 * Allocate space क्रम a (de) compressor.
 */

अटल व्योम *bsd_alloc (अचिन्हित अक्षर *options, पूर्णांक opt_len, पूर्णांक decomp)
  अणु
    पूर्णांक bits;
    अचिन्हित पूर्णांक hsize, hshअगरt, maxmaxcode;
    काष्ठा bsd_db *db;

    अगर (opt_len != 3 || options[0] != CI_BSD_COMPRESS || options[1] != 3
	|| BSD_VERSION(options[2]) != BSD_CURRENT_VERSION)
      अणु
	वापस शून्य;
      पूर्ण

    bits = BSD_NBITS(options[2]);

    चयन (bits)
      अणु
    हाल 9:			/* needs 82152 क्रम both directions */
    हाल 10:			/* needs 84144 */
    हाल 11:			/* needs 88240 */
    हाल 12:			/* needs 96432 */
	hsize = 5003;
	hshअगरt = 4;
	अवरोध;
    हाल 13:			/* needs 176784 */
	hsize = 9001;
	hshअगरt = 5;
	अवरोध;
    हाल 14:			/* needs 353744 */
	hsize = 18013;
	hshअगरt = 6;
	अवरोध;
    हाल 15:			/* needs 691440 */
	hsize = 35023;
	hshअगरt = 7;
	अवरोध;
    हाल 16:			/* needs 1366160--far too much, */
	/* hsize = 69001; */	/* and 69001 is too big क्रम cptr */
	/* hshअगरt = 8; */	/* in काष्ठा bsd_db */
	/* अवरोध; */
    शेष:
	वापस शून्य;
      पूर्ण
/*
 * Allocate the मुख्य control काष्ठाure क्रम this instance.
 */
    maxmaxcode = MAXCODE(bits);
    db         = kzalloc(माप (काष्ठा bsd_db),
					    GFP_KERNEL);
    अगर (!db)
      अणु
	वापस शून्य;
      पूर्ण

/*
 * Allocate space क्रम the dictionary. This may be more than one page in
 * length.
 */
    db->dict = vदो_स्मृति(array_size(hsize, माप(काष्ठा bsd_dict)));
    अगर (!db->dict)
      अणु
	bsd_मुक्त (db);
	वापस शून्य;
      पूर्ण

/*
 * If this is the compression buffer then there is no length data.
 */
    अगर (!decomp)
      अणु
	db->lens = शून्य;
      पूर्ण
/*
 * For decompression, the length inक्रमmation is needed as well.
 */
    अन्यथा
      अणु
        db->lens = vदो_स्मृति(array_size(माप(db->lens[0]), (maxmaxcode + 1)));
	अगर (!db->lens)
	  अणु
	    bsd_मुक्त (db);
	    वापस शून्य;
	  पूर्ण
      पूर्ण
/*
 * Initialize the data inक्रमmation क्रम the compression code
 */
    db->totlen     = माप (काष्ठा bsd_db)   +
      		    (माप (काष्ठा bsd_dict) * hsize);

    db->hsize      = hsize;
    db->hshअगरt     = hshअगरt;
    db->maxmaxcode = maxmaxcode;
    db->maxbits    = bits;

    वापस (व्योम *) db;
  पूर्ण

अटल व्योम *bsd_comp_alloc (अचिन्हित अक्षर *options, पूर्णांक opt_len)
  अणु
    वापस bsd_alloc (options, opt_len, 0);
  पूर्ण

अटल व्योम *bsd_decomp_alloc (अचिन्हित अक्षर *options, पूर्णांक opt_len)
  अणु
    वापस bsd_alloc (options, opt_len, 1);
  पूर्ण

/*
 * Initialize the database.
 */

अटल पूर्णांक bsd_init (व्योम *state, अचिन्हित अक्षर *options,
		     पूर्णांक opt_len, पूर्णांक unit, पूर्णांक debug, पूर्णांक decomp)
  अणु
    काष्ठा bsd_db *db = state;
    पूर्णांक indx;

    अगर ((opt_len != 3) || (options[0] != CI_BSD_COMPRESS) || (options[1] != 3)
	|| (BSD_VERSION(options[2]) != BSD_CURRENT_VERSION)
	|| (BSD_NBITS(options[2]) != db->maxbits)
	|| (decomp && db->lens == शून्य))
      अणु
	वापस 0;
      पूर्ण

    अगर (decomp)
      अणु
	indx = LAST;
	करो
	  अणु
	    db->lens[indx] = 1;
	  पूर्ण
	जबतक (indx-- > 0);
      पूर्ण

    indx = db->hsize;
    जबतक (indx-- != 0)
      अणु
	db->dict[indx].codem1 = BADCODEM1;
	db->dict[indx].cptr   = 0;
      पूर्ण

    db->unit = unit;
    db->mru  = 0;
#अगर_अघोषित DEBUG
    अगर (debug)
#पूर्ण_अगर
      db->debug = 1;

    bsd_reset(db);

    वापस 1;
  पूर्ण

अटल पूर्णांक bsd_comp_init (व्योम *state, अचिन्हित अक्षर *options,
			  पूर्णांक opt_len, पूर्णांक unit, पूर्णांक opthdr, पूर्णांक debug)
  अणु
    वापस bsd_init (state, options, opt_len, unit, debug, 0);
  पूर्ण

अटल पूर्णांक bsd_decomp_init (व्योम *state, अचिन्हित अक्षर *options,
			    पूर्णांक opt_len, पूर्णांक unit, पूर्णांक opthdr, पूर्णांक mru,
			    पूर्णांक debug)
  अणु
    वापस bsd_init (state, options, opt_len, unit, debug, 1);
  पूर्ण

/*
 * Obtain poपूर्णांकers to the various काष्ठाures in the compression tables
 */

#घोषणा dict_ptrx(p,idx) &(p->dict[idx])
#घोषणा lens_ptrx(p,idx) &(p->lens[idx])

#अगर_घोषित DEBUG
अटल अचिन्हित लघु *lens_ptr(काष्ठा bsd_db *db, पूर्णांक idx)
  अणु
    अगर ((अचिन्हित पूर्णांक) idx > (अचिन्हित पूर्णांक) db->maxmaxcode)
      अणु
	prपूर्णांकk ("<9>ppp: lens_ptr(%d) > max\n", idx);
	idx = 0;
      पूर्ण
    वापस lens_ptrx (db, idx);
  पूर्ण

अटल काष्ठा bsd_dict *dict_ptr(काष्ठा bsd_db *db, पूर्णांक idx)
  अणु
    अगर ((अचिन्हित पूर्णांक) idx >= (अचिन्हित पूर्णांक) db->hsize)
      अणु
	prपूर्णांकk ("<9>ppp: dict_ptr(%d) > max\n", idx);
	idx = 0;
      पूर्ण
    वापस dict_ptrx (db, idx);
  पूर्ण

#अन्यथा
#घोषणा lens_ptr(db,idx) lens_ptrx(db,idx)
#घोषणा dict_ptr(db,idx) dict_ptrx(db,idx)
#पूर्ण_अगर

/*
 * compress a packet
 *
 *	The result of this function is the size of the compressed
 *	packet. A zero is वापसed अगर the packet was not compressed
 *	क्रम some reason, such as the size being larger than uncompressed.
 *
 *	One change from the BSD compress command is that when the
 *	code size expands, we करो not output a bunch of padding.
 */

अटल पूर्णांक bsd_compress (व्योम *state, अचिन्हित अक्षर *rptr, अचिन्हित अक्षर *obuf,
			 पूर्णांक isize, पूर्णांक osize)
  अणु
    काष्ठा bsd_db *db;
    पूर्णांक hshअगरt;
    अचिन्हित पूर्णांक max_ent;
    अचिन्हित पूर्णांक n_bits;
    अचिन्हित पूर्णांक bitno;
    अचिन्हित दीर्घ accm;
    पूर्णांक ent;
    अचिन्हित दीर्घ fcode;
    काष्ठा bsd_dict *dictp;
    अचिन्हित अक्षर c;
    पूर्णांक hval;
    पूर्णांक disp;
    पूर्णांक ilen;
    पूर्णांक mxcode;
    अचिन्हित अक्षर *wptr;
    पूर्णांक olen;

#घोषणा PUTBYTE(v)			\
  अणु					\
    ++olen;				\
    अगर (wptr)				\
      अणु					\
	*wptr++ = (अचिन्हित अक्षर) (v);	\
	अगर (olen >= osize)		\
	  अणु				\
	    wptr = शून्य;		\
	  पूर्ण				\
      पूर्ण					\
  पूर्ण

#घोषणा OUTPUT(ent)			\
  अणु					\
    bitno -= n_bits;			\
    accm |= ((ent) << bitno);		\
    करो					\
      अणु					\
	PUTBYTE(accm >> 24);		\
	accm <<= 8;			\
	bitno += 8;			\
      पूर्ण					\
    जबतक (bitno <= 24);		\
  पूर्ण

  /*
   * If the protocol is not in the range we're पूर्णांकerested in,
   * just वापस without compressing the packet.  If it is,
   * the protocol becomes the first byte to compress.
   */

    ent = PPP_PROTOCOL(rptr);
    अगर (ent < 0x21 || ent > 0xf9)
      अणु
	वापस 0;
      पूर्ण

    db      = (काष्ठा bsd_db *) state;
    hshअगरt  = db->hshअगरt;
    max_ent = db->max_ent;
    n_bits  = db->n_bits;
    bitno   = 32;
    accm    = 0;
    mxcode  = MAXCODE (n_bits);

    /* Initialize the output poपूर्णांकers */
    wptr  = obuf;
    olen  = PPP_HDRLEN + BSD_OVHD;

    अगर (osize > isize)
      अणु
	osize = isize;
      पूर्ण

    /* This is the PPP header inक्रमmation */
    अगर (wptr)
      अणु
	*wptr++ = PPP_ADDRESS(rptr);
	*wptr++ = PPP_CONTROL(rptr);
	*wptr++ = 0;
	*wptr++ = PPP_COMP;
	*wptr++ = db->seqno >> 8;
	*wptr++ = db->seqno;
      पूर्ण

    /* Skip the input header */
    rptr  += PPP_HDRLEN;
    isize -= PPP_HDRLEN;
    ilen   = ++isize;	/* Low byte of protocol is counted as input */

    जबतक (--ilen > 0)
      अणु
	c     = *rptr++;
	fcode = BSD_KEY  (ent, c);
	hval  = BSD_HASH (ent, c, hshअगरt);
	dictp = dict_ptr (db, hval);

	/* Validate and then check the entry. */
	अगर (dictp->codem1 >= max_ent)
	  अणु
	    जाओ nomatch;
	  पूर्ण

	अगर (dictp->f.fcode == fcode)
	  अणु
	    ent = dictp->codem1 + 1;
	    जारी;	/* found (prefix,suffix) */
	  पूर्ण

	/* जारी probing until a match or invalid entry */
	disp = (hval == 0) ? 1 : hval;

	करो
	  अणु
	    hval += disp;
	    अगर (hval >= db->hsize)
	      अणु
		hval -= db->hsize;
	      पूर्ण
	    dictp = dict_ptr (db, hval);
	    अगर (dictp->codem1 >= max_ent)
	      अणु
		जाओ nomatch;
	      पूर्ण
	  पूर्ण
	जबतक (dictp->f.fcode != fcode);

	ent = dictp->codem1 + 1;	/* finally found (prefix,suffix) */
	जारी;

nomatch:
	OUTPUT(ent);		/* output the prefix */

	/* code -> hashtable */
	अगर (max_ent < db->maxmaxcode)
	  अणु
	    काष्ठा bsd_dict *dictp2;
	    काष्ठा bsd_dict *dictp3;
	    पूर्णांक    indx;

	    /* expand code size अगर needed */
	    अगर (max_ent >= mxcode)
	      अणु
		db->n_bits = ++n_bits;
		mxcode     = MAXCODE (n_bits);
	      पूर्ण

	    /* Invalidate old hash table entry using
	     * this code, and then take it over.
	     */

	    dictp2 = dict_ptr (db, max_ent + 1);
	    indx   = dictp2->cptr;
	    dictp3 = dict_ptr (db, indx);

	    अगर (dictp3->codem1 == max_ent)
	      अणु
		dictp3->codem1 = BADCODEM1;
	      पूर्ण

	    dictp2->cptr   = hval;
	    dictp->codem1  = max_ent;
	    dictp->f.fcode = fcode;
	    db->max_ent    = ++max_ent;

	    अगर (db->lens)
	      अणु
		अचिन्हित लघु *len1 = lens_ptr (db, max_ent);
		अचिन्हित लघु *len2 = lens_ptr (db, ent);
		*len1 = *len2 + 1;
	      पूर्ण
	  पूर्ण
	ent = c;
      पूर्ण

    OUTPUT(ent);		/* output the last code */

    db->bytes_out    += olen - PPP_HDRLEN - BSD_OVHD;
    db->uncomp_bytes += isize;
    db->in_count     += isize;
    ++db->uncomp_count;
    ++db->seqno;

    अगर (bitno < 32)
      अणु
	++db->bytes_out; /* must be set beक्रमe calling bsd_check */
      पूर्ण

    /*
     * Generate the clear command अगर needed
     */

    अगर (bsd_check(db))
      अणु
	OUTPUT (CLEAR);
      पूर्ण

    /*
     * Pad dribble bits of last code with ones.
     * Do not emit a completely useless byte of ones.
     */

    अगर (bitno != 32)
      अणु
	PUTBYTE((accm | (0xff << (bitno-8))) >> 24);
      पूर्ण

    /*
     * Increase code size अगर we would have without the packet
     * boundary because the decompressor will करो so.
     */

    अगर (max_ent >= mxcode && max_ent < db->maxmaxcode)
      अणु
	db->n_bits++;
      पूर्ण

    /* If output length is too large then this is an incomplete frame. */
    अगर (wptr == शून्य)
      अणु
	++db->incomp_count;
	db->incomp_bytes += isize;
	olen              = 0;
      पूर्ण
    अन्यथा /* Count the number of compressed frames */
      अणु
	++db->comp_count;
	db->comp_bytes += olen;
      पूर्ण

    /* Return the resulting output length */
    वापस olen;
#अघोषित OUTPUT
#अघोषित PUTBYTE
  पूर्ण

/*
 * Update the "BSD Compress" dictionary on the receiver क्रम
 * incompressible data by pretending to compress the incoming data.
 */

अटल व्योम bsd_incomp (व्योम *state, अचिन्हित अक्षर *ibuf, पूर्णांक icnt)
  अणु
    (व्योम) bsd_compress (state, ibuf, (अक्षर *) 0, icnt, 0);
  पूर्ण

/*
 * Decompress "BSD Compress".
 *
 * Because of patent problems, we वापस DECOMP_ERROR क्रम errors
 * found by inspecting the input data and क्रम प्रणाली problems, but
 * DECOMP_FATALERROR क्रम any errors which could possibly be said to
 * be being detected "after" decompression.  For DECOMP_ERROR,
 * we can issue a CCP reset-request; क्रम DECOMP_FATALERROR, we may be
 * infringing a patent of Motorola's अगर we करो, so we take CCP करोwn
 * instead.
 *
 * Given that the frame has the correct sequence number and a good FCS,
 * errors such as invalid codes in the input most likely indicate a
 * bug, so we वापस DECOMP_FATALERROR क्रम them in order to turn off
 * compression, even though they are detected by inspecting the input.
 */

अटल पूर्णांक bsd_decompress (व्योम *state, अचिन्हित अक्षर *ibuf, पूर्णांक isize,
			   अचिन्हित अक्षर *obuf, पूर्णांक osize)
  अणु
    काष्ठा bsd_db *db;
    अचिन्हित पूर्णांक max_ent;
    अचिन्हित दीर्घ accm;
    अचिन्हित पूर्णांक bitno;		/* 1st valid bit in accm */
    अचिन्हित पूर्णांक n_bits;
    अचिन्हित पूर्णांक tgtbitno;	/* bitno when we have a code */
    काष्ठा bsd_dict *dictp;
    पूर्णांक explen;
    पूर्णांक seq;
    अचिन्हित पूर्णांक incode;
    अचिन्हित पूर्णांक oldcode;
    अचिन्हित पूर्णांक finअक्षर;
    अचिन्हित अक्षर *p;
    अचिन्हित अक्षर *wptr;
    पूर्णांक adrs;
    पूर्णांक ctrl;
    पूर्णांक ilen;
    पूर्णांक codelen;
    पूर्णांक extra;

    db       = (काष्ठा bsd_db *) state;
    max_ent  = db->max_ent;
    accm     = 0;
    bitno    = 32;		/* 1st valid bit in accm */
    n_bits   = db->n_bits;
    tgtbitno = 32 - n_bits;	/* bitno when we have a code */

    /*
     * Save the address/control from the PPP header
     * and then get the sequence number.
     */

    adrs  = PPP_ADDRESS (ibuf);
    ctrl  = PPP_CONTROL (ibuf);

    seq   = (ibuf[4] << 8) + ibuf[5];

    ibuf += (PPP_HDRLEN + 2);
    ilen  = isize - (PPP_HDRLEN + 2);

    /*
     * Check the sequence number and give up अगर it dअगरfers from
     * the value we're expecting.
     */

    अगर (seq != db->seqno)
      अणु
	अगर (db->debug)
	  अणु
	    prपूर्णांकk("bsd_decomp%d: bad sequence # %d, expected %d\n",
		   db->unit, seq, db->seqno - 1);
	  पूर्ण
	वापस DECOMP_ERROR;
      पूर्ण

    ++db->seqno;
    db->bytes_out += ilen;

    /*
     * Fill in the ppp header, but not the last byte of the protocol
     * (that comes from the decompressed data).
     */

    wptr    = obuf;
    *wptr++ = adrs;
    *wptr++ = ctrl;
    *wptr++ = 0;

    oldcode = CLEAR;
    explen  = 3;

    /*
     * Keep the checkpoपूर्णांक correctly so that incompressible packets
     * clear the dictionary at the proper बार.
     */

    क्रम (;;)
      अणु
	अगर (ilen-- <= 0)
	  अणु
	    db->in_count += (explen - 3); /* करोn't count the header */
	    अवरोध;
	  पूर्ण

	/*
	 * Accumulate bytes until we have a complete code.
	 * Then get the next code, relying on the 32-bit,
	 * अचिन्हित accm to mask the result.
	 */

	bitno -= 8;
	accm  |= *ibuf++ << bitno;
	अगर (tgtbitno < bitno)
	  अणु
	    जारी;
	  पूर्ण

	incode = accm >> tgtbitno;
	accm <<= n_bits;
	bitno += n_bits;

	/*
	 * The dictionary must only be cleared at the end of a packet.
	 */

	अगर (incode == CLEAR)
	  अणु
	    अगर (ilen > 0)
	      अणु
		अगर (db->debug)
		  अणु
		    prपूर्णांकk("bsd_decomp%d: bad CLEAR\n", db->unit);
		  पूर्ण
		वापस DECOMP_FATALERROR;	/* probably a bug */
	      पूर्ण

	    bsd_clear(db);
	    अवरोध;
	  पूर्ण

	अगर ((incode > max_ent + 2) || (incode > db->maxmaxcode)
	    || (incode > max_ent && oldcode == CLEAR))
	  अणु
	    अगर (db->debug)
	      अणु
		prपूर्णांकk("bsd_decomp%d: bad code 0x%x oldcode=0x%x ",
		       db->unit, incode, oldcode);
		prपूर्णांकk("max_ent=0x%x explen=%d seqno=%d\n",
		       max_ent, explen, db->seqno);
	      पूर्ण
	    वापस DECOMP_FATALERROR;	/* probably a bug */
	  पूर्ण

	/* Special हाल क्रम KwKwK string. */
	अगर (incode > max_ent)
	  अणु
	    finअक्षर = oldcode;
	    extra   = 1;
	  पूर्ण
	अन्यथा
	  अणु
	    finअक्षर = incode;
	    extra   = 0;
	  पूर्ण

	codelen = *(lens_ptr (db, finअक्षर));
	explen += codelen + extra;
	अगर (explen > osize)
	  अणु
	    अगर (db->debug)
	      अणु
		prपूर्णांकk("bsd_decomp%d: ran out of mru\n", db->unit);
#अगर_घोषित DEBUG
		prपूर्णांकk("  len=%d, finchar=0x%x, codelen=%d, explen=%d\n",
		       ilen, finअक्षर, codelen, explen);
#पूर्ण_अगर
	      पूर्ण
	    वापस DECOMP_FATALERROR;
	  पूर्ण

	/*
	 * Decode this code and install it in the decompressed buffer.
	 */

	wptr += codelen;
	p     = wptr;
	जबतक (finअक्षर > LAST)
	  अणु
	    काष्ठा bsd_dict *dictp2 = dict_ptr (db, finअक्षर);

	    dictp = dict_ptr (db, dictp2->cptr);
#अगर_घोषित DEBUG
	    अगर (--codelen <= 0 || dictp->codem1 != finअक्षर-1)
	      अणु
		अगर (codelen <= 0)
		  अणु
		    prपूर्णांकk("bsd_decomp%d: fell off end of chain ", db->unit);
		    prपूर्णांकk("0x%x at 0x%x by 0x%x, max_ent=0x%x\n",
			   incode, finअक्षर, dictp2->cptr, max_ent);
		  पूर्ण
		अन्यथा
		  अणु
		    अगर (dictp->codem1 != finअक्षर-1)
		      अणु
			prपूर्णांकk("bsd_decomp%d: bad code chain 0x%x "
			       "finchar=0x%x ",
			       db->unit, incode, finअक्षर);

			prपूर्णांकk("oldcode=0x%x cptr=0x%x codem1=0x%x\n",
			       oldcode, dictp2->cptr, dictp->codem1);
		      पूर्ण
		  पूर्ण
		वापस DECOMP_FATALERROR;
	      पूर्ण
#पूर्ण_अगर
	    *--p    = dictp->f.hs.suffix;
	    finअक्षर = dictp->f.hs.prefix;
	  पूर्ण
	*--p = finअक्षर;

#अगर_घोषित DEBUG
	अगर (--codelen != 0)
	  अणु
	    prपूर्णांकk("bsd_decomp%d: short by %d after code 0x%x, max_ent=0x%x\n",
		   db->unit, codelen, incode, max_ent);
	  पूर्ण
#पूर्ण_अगर

	अगर (extra)		/* the KwKwK हाल again */
	  अणु
	    *wptr++ = finअक्षर;
	  पूर्ण

	/*
	 * If not first code in a packet, and
	 * अगर not out of code space, then allocate a new code.
	 *
	 * Keep the hash table correct so it can be used
	 * with uncompressed packets.
	 */

	अगर (oldcode != CLEAR && max_ent < db->maxmaxcode)
	  अणु
	    काष्ठा bsd_dict *dictp2, *dictp3;
	    अचिन्हित लघु  *lens1,  *lens2;
	    अचिन्हित दीर्घ fcode;
	    पूर्णांक hval, disp, indx;

	    fcode = BSD_KEY(oldcode,finअक्षर);
	    hval  = BSD_HASH(oldcode,finअक्षर,db->hshअगरt);
	    dictp = dict_ptr (db, hval);

	    /* look क्रम a मुक्त hash table entry */
	    अगर (dictp->codem1 < max_ent)
	      अणु
		disp = (hval == 0) ? 1 : hval;
		करो
		  अणु
		    hval += disp;
		    अगर (hval >= db->hsize)
		      अणु
			hval -= db->hsize;
		      पूर्ण
		    dictp = dict_ptr (db, hval);
		  पूर्ण
		जबतक (dictp->codem1 < max_ent);
	      पूर्ण

	    /*
	     * Invalidate previous hash table entry
	     * asचिन्हित this code, and then take it over
	     */

	    dictp2 = dict_ptr (db, max_ent + 1);
	    indx   = dictp2->cptr;
	    dictp3 = dict_ptr (db, indx);

	    अगर (dictp3->codem1 == max_ent)
	      अणु
		dictp3->codem1 = BADCODEM1;
	      पूर्ण

	    dictp2->cptr   = hval;
	    dictp->codem1  = max_ent;
	    dictp->f.fcode = fcode;
	    db->max_ent    = ++max_ent;

	    /* Update the length of this string. */
	    lens1  = lens_ptr (db, max_ent);
	    lens2  = lens_ptr (db, oldcode);
	    *lens1 = *lens2 + 1;

	    /* Expand code size अगर needed. */
	    अगर (max_ent >= MAXCODE(n_bits) && max_ent < db->maxmaxcode)
	      अणु
		db->n_bits = ++n_bits;
		tgtbitno   = 32-n_bits;
	      पूर्ण
	  पूर्ण
	oldcode = incode;
      पूर्ण

    ++db->comp_count;
    ++db->uncomp_count;
    db->comp_bytes   += isize - BSD_OVHD - PPP_HDRLEN;
    db->uncomp_bytes += explen;

    अगर (bsd_check(db))
      अणु
	अगर (db->debug)
	  अणु
	    prपूर्णांकk("bsd_decomp%d: peer should have cleared dictionary on %d\n",
		   db->unit, db->seqno - 1);
	  पूर्ण
      पूर्ण
    वापस explen;
  पूर्ण

/*************************************************************
 * Table of addresses क्रम the BSD compression module
 *************************************************************/

अटल काष्ठा compressor ppp_bsd_compress = अणु
	.compress_proto =	CI_BSD_COMPRESS,
	.comp_alloc =		bsd_comp_alloc,
	.comp_मुक्त =		bsd_मुक्त,
	.comp_init =		bsd_comp_init,
	.comp_reset =		bsd_reset,
	.compress =		bsd_compress,
	.comp_stat =		bsd_comp_stats,
	.decomp_alloc =		bsd_decomp_alloc,
	.decomp_मुक्त =		bsd_मुक्त,
	.decomp_init =		bsd_decomp_init,
	.decomp_reset =		bsd_reset,
	.decompress =		bsd_decompress,
	.incomp =		bsd_incomp,
	.decomp_stat =		bsd_comp_stats,
	.owner =		THIS_MODULE
पूर्ण;

/*************************************************************
 * Module support routines
 *************************************************************/

अटल पूर्णांक __init bsdcomp_init(व्योम)
अणु
	पूर्णांक answer = ppp_रेजिस्टर_compressor(&ppp_bsd_compress);
	अगर (answer == 0)
		prपूर्णांकk(KERN_INFO "PPP BSD Compression module registered\n");
	वापस answer;
पूर्ण

अटल व्योम __निकास bsdcomp_cleanup(व्योम)
अणु
	ppp_unरेजिस्टर_compressor(&ppp_bsd_compress);
पूर्ण

module_init(bsdcomp_init);
module_निकास(bsdcomp_cleanup);
MODULE_LICENSE("Dual BSD/GPL");
MODULE_ALIAS("ppp-compress-" __stringअगरy(CI_BSD_COMPRESS));
