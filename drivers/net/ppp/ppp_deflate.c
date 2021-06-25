<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ppp_deflate.c - पूर्णांकerface the zlib procedures क्रम Deflate compression
 * and decompression (as used by gzip) to the PPP code.
 *
 * Copyright 1994-1998 Paul Mackerras.
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/init.h>
#समावेश <linux/माला.स>

#समावेश <linux/ppp_defs.h>
#समावेश <linux/ppp-comp.h>

#समावेश <linux/zlib.h>
#समावेश <यंत्र/unaligned.h>

/*
 * State क्रम a Deflate (de)compressor.
 */
काष्ठा ppp_deflate_state अणु
    पूर्णांक		seqno;
    पूर्णांक		w_size;
    पूर्णांक		unit;
    पूर्णांक		mru;
    पूर्णांक		debug;
    z_stream	strm;
    काष्ठा compstat stats;
पूर्ण;

#घोषणा DEFLATE_OVHD	2		/* Deflate overhead/packet */

अटल व्योम	*z_comp_alloc(अचिन्हित अक्षर *options, पूर्णांक opt_len);
अटल व्योम	*z_decomp_alloc(अचिन्हित अक्षर *options, पूर्णांक opt_len);
अटल व्योम	z_comp_मुक्त(व्योम *state);
अटल व्योम	z_decomp_मुक्त(व्योम *state);
अटल पूर्णांक	z_comp_init(व्योम *state, अचिन्हित अक्षर *options,
				 पूर्णांक opt_len,
				 पूर्णांक unit, पूर्णांक hdrlen, पूर्णांक debug);
अटल पूर्णांक	z_decomp_init(व्योम *state, अचिन्हित अक्षर *options,
				   पूर्णांक opt_len,
				   पूर्णांक unit, पूर्णांक hdrlen, पूर्णांक mru, पूर्णांक debug);
अटल पूर्णांक	z_compress(व्योम *state, अचिन्हित अक्षर *rptr,
				अचिन्हित अक्षर *obuf,
				पूर्णांक isize, पूर्णांक osize);
अटल व्योम	z_incomp(व्योम *state, अचिन्हित अक्षर *ibuf, पूर्णांक icnt);
अटल पूर्णांक	z_decompress(व्योम *state, अचिन्हित अक्षर *ibuf,
				पूर्णांक isize, अचिन्हित अक्षर *obuf, पूर्णांक osize);
अटल व्योम	z_comp_reset(व्योम *state);
अटल व्योम	z_decomp_reset(व्योम *state);
अटल व्योम	z_comp_stats(व्योम *state, काष्ठा compstat *stats);

/**
 *	z_comp_मुक्त - मुक्त the memory used by a compressor
 *	@arg:	poपूर्णांकer to the निजी state क्रम the compressor.
 */
अटल व्योम z_comp_मुक्त(व्योम *arg)
अणु
	काष्ठा ppp_deflate_state *state = (काष्ठा ppp_deflate_state *) arg;

	अगर (state) अणु
		zlib_deflateEnd(&state->strm);
		vमुक्त(state->strm.workspace);
		kमुक्त(state);
	पूर्ण
पूर्ण

/**
 *	z_comp_alloc - allocate space क्रम a compressor.
 *	@options: poपूर्णांकer to CCP option data
 *	@opt_len: length of the CCP option at @options.
 *
 *	The @options poपूर्णांकer poपूर्णांकs to the a buffer containing the
 *	CCP option data क्रम the compression being negotiated.  It is
 *	क्रमmatted according to RFC1979, and describes the winकरोw
 *	size that the peer is requesting that we use in compressing
 *	data to be sent to it.
 *
 *	Returns the poपूर्णांकer to the निजी state क्रम the compressor,
 *	or शून्य अगर we could not allocate enough memory.
 */
अटल व्योम *z_comp_alloc(अचिन्हित अक्षर *options, पूर्णांक opt_len)
अणु
	काष्ठा ppp_deflate_state *state;
	पूर्णांक w_size;

	अगर (opt_len != CILEN_DEFLATE ||
	    (options[0] != CI_DEFLATE && options[0] != CI_DEFLATE_DRAFT) ||
	    options[1] != CILEN_DEFLATE ||
	    DEFLATE_METHOD(options[2]) != DEFLATE_METHOD_VAL ||
	    options[3] != DEFLATE_CHK_SEQUENCE)
		वापस शून्य;
	w_size = DEFLATE_SIZE(options[2]);
	अगर (w_size < DEFLATE_MIN_SIZE || w_size > DEFLATE_MAX_SIZE)
		वापस शून्य;

	state = kzalloc(माप(*state),
						     GFP_KERNEL);
	अगर (state == शून्य)
		वापस शून्य;

	state->strm.next_in   = शून्य;
	state->w_size         = w_size;
	state->strm.workspace = vदो_स्मृति(zlib_deflate_workspacesize(-w_size, 8));
	अगर (state->strm.workspace == शून्य)
		जाओ out_मुक्त;

	अगर (zlib_deflateInit2(&state->strm, Z_DEFAULT_COMPRESSION,
			 DEFLATE_METHOD_VAL, -w_size, 8, Z_DEFAULT_STRATEGY)
	    != Z_OK)
		जाओ out_मुक्त;
	वापस (व्योम *) state;

out_मुक्त:
	z_comp_मुक्त(state);
	वापस शून्य;
पूर्ण

/**
 *	z_comp_init - initialize a previously-allocated compressor.
 *	@arg:	poपूर्णांकer to the निजी state क्रम the compressor
 *	@options: poपूर्णांकer to the CCP option data describing the
 *		compression that was negotiated with the peer
 *	@opt_len: length of the CCP option data at @options
 *	@unit:	PPP unit number क्रम diagnostic messages
 *	@hdrlen: ignored (present क्रम backwards compatibility)
 *	@debug:	debug flag; अगर non-zero, debug messages are prपूर्णांकed.
 *
 *	The CCP options described by @options must match the options
 *	specअगरied when the compressor was allocated.  The compressor
 *	history is reset.  Returns 0 क्रम failure (CCP options करोn't
 *	match) or 1 क्रम success.
 */
अटल पूर्णांक z_comp_init(व्योम *arg, अचिन्हित अक्षर *options, पूर्णांक opt_len,
		       पूर्णांक unit, पूर्णांक hdrlen, पूर्णांक debug)
अणु
	काष्ठा ppp_deflate_state *state = (काष्ठा ppp_deflate_state *) arg;

	अगर (opt_len < CILEN_DEFLATE ||
	    (options[0] != CI_DEFLATE && options[0] != CI_DEFLATE_DRAFT) ||
	    options[1] != CILEN_DEFLATE ||
	    DEFLATE_METHOD(options[2]) != DEFLATE_METHOD_VAL ||
	    DEFLATE_SIZE(options[2]) != state->w_size ||
	    options[3] != DEFLATE_CHK_SEQUENCE)
		वापस 0;

	state->seqno = 0;
	state->unit  = unit;
	state->debug = debug;

	zlib_deflateReset(&state->strm);

	वापस 1;
पूर्ण

/**
 *	z_comp_reset - reset a previously-allocated compressor.
 *	@arg:	poपूर्णांकer to निजी state क्रम the compressor.
 *
 *	This clears the history क्रम the compressor and makes it
 *	पढ़ोy to start emitting a new compressed stream.
 */
अटल व्योम z_comp_reset(व्योम *arg)
अणु
	काष्ठा ppp_deflate_state *state = (काष्ठा ppp_deflate_state *) arg;

	state->seqno = 0;
	zlib_deflateReset(&state->strm);
पूर्ण

/**
 *	z_compress - compress a PPP packet with Deflate compression.
 *	@arg:	poपूर्णांकer to निजी state क्रम the compressor
 *	@rptr:	uncompressed packet (input)
 *	@obuf:	compressed packet (output)
 *	@isize:	size of uncompressed packet
 *	@osize:	space available at @obuf
 *
 *	Returns the length of the compressed packet, or 0 अगर the
 *	packet is incompressible.
 */
अटल पूर्णांक z_compress(व्योम *arg, अचिन्हित अक्षर *rptr, अचिन्हित अक्षर *obuf,
	       पूर्णांक isize, पूर्णांक osize)
अणु
	काष्ठा ppp_deflate_state *state = (काष्ठा ppp_deflate_state *) arg;
	पूर्णांक r, proto, off, olen, oavail;
	अचिन्हित अक्षर *wptr;

	/*
	 * Check that the protocol is in the range we handle.
	 */
	proto = PPP_PROTOCOL(rptr);
	अगर (proto > 0x3fff || proto == 0xfd || proto == 0xfb)
		वापस 0;

	/* Don't generate compressed packets which are larger than
	   the uncompressed packet. */
	अगर (osize > isize)
		osize = isize;

	wptr = obuf;

	/*
	 * Copy over the PPP header and store the 2-byte sequence number.
	 */
	wptr[0] = PPP_ADDRESS(rptr);
	wptr[1] = PPP_CONTROL(rptr);
	put_unaligned_be16(PPP_COMP, wptr + 2);
	wptr += PPP_HDRLEN;
	put_unaligned_be16(state->seqno, wptr);
	wptr += DEFLATE_OVHD;
	olen = PPP_HDRLEN + DEFLATE_OVHD;
	state->strm.next_out = wptr;
	state->strm.avail_out = oavail = osize - olen;
	++state->seqno;

	off = (proto > 0xff) ? 2 : 3;	/* skip 1st proto byte अगर 0 */
	rptr += off;
	state->strm.next_in = rptr;
	state->strm.avail_in = (isize - off);

	क्रम (;;) अणु
		r = zlib_deflate(&state->strm, Z_PACKET_FLUSH);
		अगर (r != Z_OK) अणु
			अगर (state->debug)
				prपूर्णांकk(KERN_ERR
				       "z_compress: deflate returned %d\n", r);
			अवरोध;
		पूर्ण
		अगर (state->strm.avail_out == 0) अणु
			olen += oavail;
			state->strm.next_out = शून्य;
			state->strm.avail_out = oavail = 1000000;
		पूर्ण अन्यथा अणु
			अवरोध;		/* all करोne */
		पूर्ण
	पूर्ण
	olen += oavail - state->strm.avail_out;

	/*
	 * See अगर we managed to reduce the size of the packet.
	 */
	अगर (olen < isize && olen <= osize) अणु
		state->stats.comp_bytes += olen;
		state->stats.comp_packets++;
	पूर्ण अन्यथा अणु
		state->stats.inc_bytes += isize;
		state->stats.inc_packets++;
		olen = 0;
	पूर्ण
	state->stats.unc_bytes += isize;
	state->stats.unc_packets++;

	वापस olen;
पूर्ण

/**
 *	z_comp_stats - वापस compression statistics क्रम a compressor
 *		or decompressor.
 *	@arg:	poपूर्णांकer to निजी space क्रम the (de)compressor
 *	@stats:	poपूर्णांकer to a काष्ठा compstat to receive the result.
 */
अटल व्योम z_comp_stats(व्योम *arg, काष्ठा compstat *stats)
अणु
	काष्ठा ppp_deflate_state *state = (काष्ठा ppp_deflate_state *) arg;

	*stats = state->stats;
पूर्ण

/**
 *	z_decomp_मुक्त - Free the memory used by a decompressor.
 *	@arg:	poपूर्णांकer to निजी space क्रम the decompressor.
 */
अटल व्योम z_decomp_मुक्त(व्योम *arg)
अणु
	काष्ठा ppp_deflate_state *state = (काष्ठा ppp_deflate_state *) arg;

	अगर (state) अणु
		vमुक्त(state->strm.workspace);
		kमुक्त(state);
	पूर्ण
पूर्ण

/**
 *	z_decomp_alloc - allocate space क्रम a decompressor.
 *	@options: poपूर्णांकer to CCP option data
 *	@opt_len: length of the CCP option at @options.
 *
 *	The @options poपूर्णांकer poपूर्णांकs to the a buffer containing the
 *	CCP option data क्रम the compression being negotiated.  It is
 *	क्रमmatted according to RFC1979, and describes the winकरोw
 *	size that we are requesting the peer to use in compressing
 *	data to be sent to us.
 *
 *	Returns the poपूर्णांकer to the निजी state क्रम the decompressor,
 *	or शून्य अगर we could not allocate enough memory.
 */
अटल व्योम *z_decomp_alloc(अचिन्हित अक्षर *options, पूर्णांक opt_len)
अणु
	काष्ठा ppp_deflate_state *state;
	पूर्णांक w_size;

	अगर (opt_len != CILEN_DEFLATE ||
	    (options[0] != CI_DEFLATE && options[0] != CI_DEFLATE_DRAFT) ||
	    options[1] != CILEN_DEFLATE ||
	    DEFLATE_METHOD(options[2]) != DEFLATE_METHOD_VAL ||
	    options[3] != DEFLATE_CHK_SEQUENCE)
		वापस शून्य;
	w_size = DEFLATE_SIZE(options[2]);
	अगर (w_size < DEFLATE_MIN_SIZE || w_size > DEFLATE_MAX_SIZE)
		वापस शून्य;

	state = kzalloc(माप(*state), GFP_KERNEL);
	अगर (state == शून्य)
		वापस शून्य;

	state->w_size         = w_size;
	state->strm.next_out  = शून्य;
	state->strm.workspace = vदो_स्मृति(zlib_inflate_workspacesize());
	अगर (state->strm.workspace == शून्य)
		जाओ out_मुक्त;

	अगर (zlib_inflateInit2(&state->strm, -w_size) != Z_OK)
		जाओ out_मुक्त;
	वापस (व्योम *) state;

out_मुक्त:
	z_decomp_मुक्त(state);
	वापस शून्य;
पूर्ण

/**
 *	z_decomp_init - initialize a previously-allocated decompressor.
 *	@arg:	poपूर्णांकer to the निजी state क्रम the decompressor
 *	@options: poपूर्णांकer to the CCP option data describing the
 *		compression that was negotiated with the peer
 *	@opt_len: length of the CCP option data at @options
 *	@unit:	PPP unit number क्रम diagnostic messages
 *	@hdrlen: ignored (present क्रम backwards compatibility)
 *	@mru:	maximum length of decompressed packets
 *	@debug:	debug flag; अगर non-zero, debug messages are prपूर्णांकed.
 *
 *	The CCP options described by @options must match the options
 *	specअगरied when the decompressor was allocated.  The decompressor
 *	history is reset.  Returns 0 क्रम failure (CCP options करोn't
 *	match) or 1 क्रम success.
 */
अटल पूर्णांक z_decomp_init(व्योम *arg, अचिन्हित अक्षर *options, पूर्णांक opt_len,
			 पूर्णांक unit, पूर्णांक hdrlen, पूर्णांक mru, पूर्णांक debug)
अणु
	काष्ठा ppp_deflate_state *state = (काष्ठा ppp_deflate_state *) arg;

	अगर (opt_len < CILEN_DEFLATE ||
	    (options[0] != CI_DEFLATE && options[0] != CI_DEFLATE_DRAFT) ||
	    options[1] != CILEN_DEFLATE ||
	    DEFLATE_METHOD(options[2]) != DEFLATE_METHOD_VAL ||
	    DEFLATE_SIZE(options[2]) != state->w_size ||
	    options[3] != DEFLATE_CHK_SEQUENCE)
		वापस 0;

	state->seqno = 0;
	state->unit  = unit;
	state->debug = debug;
	state->mru   = mru;

	zlib_inflateReset(&state->strm);

	वापस 1;
पूर्ण

/**
 *	z_decomp_reset - reset a previously-allocated decompressor.
 *	@arg:	poपूर्णांकer to निजी state क्रम the decompressor.
 *
 *	This clears the history क्रम the decompressor and makes it
 *	पढ़ोy to receive a new compressed stream.
 */
अटल व्योम z_decomp_reset(व्योम *arg)
अणु
	काष्ठा ppp_deflate_state *state = (काष्ठा ppp_deflate_state *) arg;

	state->seqno = 0;
	zlib_inflateReset(&state->strm);
पूर्ण

/**
 *	z_decompress - decompress a Deflate-compressed packet.
 *	@arg:	poपूर्णांकer to निजी state क्रम the decompressor
 *	@ibuf:	poपूर्णांकer to input (compressed) packet data
 *	@isize:	length of input packet
 *	@obuf:	poपूर्णांकer to space क्रम output (decompressed) packet
 *	@osize:	amount of space available at @obuf
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
अटल पूर्णांक z_decompress(व्योम *arg, अचिन्हित अक्षर *ibuf, पूर्णांक isize,
		 अचिन्हित अक्षर *obuf, पूर्णांक osize)
अणु
	काष्ठा ppp_deflate_state *state = (काष्ठा ppp_deflate_state *) arg;
	पूर्णांक olen, seq, r;
	पूर्णांक decode_proto, overflow;
	अचिन्हित अक्षर overflow_buf[1];

	अगर (isize <= PPP_HDRLEN + DEFLATE_OVHD) अणु
		अगर (state->debug)
			prपूर्णांकk(KERN_DEBUG "z_decompress%d: short pkt (%d)\n",
			       state->unit, isize);
		वापस DECOMP_ERROR;
	पूर्ण

	/* Check the sequence number. */
	seq = get_unaligned_be16(ibuf + PPP_HDRLEN);
	अगर (seq != (state->seqno & 0xffff)) अणु
		अगर (state->debug)
			prपूर्णांकk(KERN_DEBUG "z_decompress%d: bad seq # %d, expected %d\n",
			       state->unit, seq, state->seqno & 0xffff);
		वापस DECOMP_ERROR;
	पूर्ण
	++state->seqno;

	/*
	 * Fill in the first part of the PPP header.  The protocol field
	 * comes from the decompressed data.
	 */
	obuf[0] = PPP_ADDRESS(ibuf);
	obuf[1] = PPP_CONTROL(ibuf);
	obuf[2] = 0;

	/*
	 * Set up to call inflate.  We set avail_out to 1 initially so we can
	 * look at the first byte of the output and decide whether we have
	 * a 1-byte or 2-byte protocol field.
	 */
	state->strm.next_in = ibuf + PPP_HDRLEN + DEFLATE_OVHD;
	state->strm.avail_in = isize - (PPP_HDRLEN + DEFLATE_OVHD);
	state->strm.next_out = obuf + 3;
	state->strm.avail_out = 1;
	decode_proto = 1;
	overflow = 0;

	/*
	 * Call inflate, supplying more input or output as needed.
	 */
	क्रम (;;) अणु
		r = zlib_inflate(&state->strm, Z_PACKET_FLUSH);
		अगर (r != Z_OK) अणु
			अगर (state->debug)
				prपूर्णांकk(KERN_DEBUG "z_decompress%d: inflate returned %d (%s)\n",
				       state->unit, r, (state->strm.msg? state->strm.msg: ""));
			वापस DECOMP_FATALERROR;
		पूर्ण
		अगर (state->strm.avail_out != 0)
			अवरोध;		/* all करोne */
		अगर (decode_proto) अणु
			state->strm.avail_out = osize - PPP_HDRLEN;
			अगर ((obuf[3] & 1) == 0) अणु
				/* 2-byte protocol field */
				obuf[2] = obuf[3];
				--state->strm.next_out;
				++state->strm.avail_out;
			पूर्ण
			decode_proto = 0;
		पूर्ण अन्यथा अगर (!overflow) अणु
			/*
			 * We've filled up the output buffer; the only way to
			 * find out whether inflate has any more अक्षरacters
			 * left is to give it another byte of output space.
			 */
			state->strm.next_out = overflow_buf;
			state->strm.avail_out = 1;
			overflow = 1;
		पूर्ण अन्यथा अणु
			अगर (state->debug)
				prपूर्णांकk(KERN_DEBUG "z_decompress%d: ran out of mru\n",
				       state->unit);
			वापस DECOMP_FATALERROR;
		पूर्ण
	पूर्ण

	अगर (decode_proto) अणु
		अगर (state->debug)
			prपूर्णांकk(KERN_DEBUG "z_decompress%d: didn't get proto\n",
			       state->unit);
		वापस DECOMP_ERROR;
	पूर्ण

	olen = osize + overflow - state->strm.avail_out;
	state->stats.unc_bytes += olen;
	state->stats.unc_packets++;
	state->stats.comp_bytes += isize;
	state->stats.comp_packets++;

	वापस olen;
पूर्ण

/**
 *	z_incomp - add incompressible input data to the history.
 *	@arg:	poपूर्णांकer to निजी state क्रम the decompressor
 *	@ibuf:	poपूर्णांकer to input packet data
 *	@icnt:	length of input data.
 */
अटल व्योम z_incomp(व्योम *arg, अचिन्हित अक्षर *ibuf, पूर्णांक icnt)
अणु
	काष्ठा ppp_deflate_state *state = (काष्ठा ppp_deflate_state *) arg;
	पूर्णांक proto, r;

	/*
	 * Check that the protocol is one we handle.
	 */
	proto = PPP_PROTOCOL(ibuf);
	अगर (proto > 0x3fff || proto == 0xfd || proto == 0xfb)
		वापस;

	++state->seqno;

	/*
	 * We start at the either the 1st or 2nd byte of the protocol field,
	 * depending on whether the protocol value is compressible.
	 */
	state->strm.next_in = ibuf + 3;
	state->strm.avail_in = icnt - 3;
	अगर (proto > 0xff) अणु
		--state->strm.next_in;
		++state->strm.avail_in;
	पूर्ण

	r = zlib_inflateIncomp(&state->strm);
	अगर (r != Z_OK) अणु
		/* gak! */
		अगर (state->debug) अणु
			prपूर्णांकk(KERN_DEBUG "z_incomp%d: inflateIncomp returned %d (%s)\n",
			       state->unit, r, (state->strm.msg? state->strm.msg: ""));
		पूर्ण
		वापस;
	पूर्ण

	/*
	 * Update stats.
	 */
	state->stats.inc_bytes += icnt;
	state->stats.inc_packets++;
	state->stats.unc_bytes += icnt;
	state->stats.unc_packets++;
पूर्ण

/*************************************************************
 * Module पूर्णांकerface table
 *************************************************************/

/* These are in ppp_generic.c */
बाह्य पूर्णांक  ppp_रेजिस्टर_compressor   (काष्ठा compressor *cp);
बाह्य व्योम ppp_unरेजिस्टर_compressor (काष्ठा compressor *cp);

/*
 * Procedures exported to अगर_ppp.c.
 */
अटल काष्ठा compressor ppp_deflate = अणु
	.compress_proto =	CI_DEFLATE,
	.comp_alloc =		z_comp_alloc,
	.comp_मुक्त =		z_comp_मुक्त,
	.comp_init =		z_comp_init,
	.comp_reset =		z_comp_reset,
	.compress =		z_compress,
	.comp_stat =		z_comp_stats,
	.decomp_alloc =		z_decomp_alloc,
	.decomp_मुक्त =		z_decomp_मुक्त,
	.decomp_init =		z_decomp_init,
	.decomp_reset =		z_decomp_reset,
	.decompress =		z_decompress,
	.incomp =		z_incomp,
	.decomp_stat =		z_comp_stats,
	.owner =		THIS_MODULE
पूर्ण;

अटल काष्ठा compressor ppp_deflate_draft = अणु
	.compress_proto =	CI_DEFLATE_DRAFT,
	.comp_alloc =		z_comp_alloc,
	.comp_मुक्त =		z_comp_मुक्त,
	.comp_init =		z_comp_init,
	.comp_reset =		z_comp_reset,
	.compress =		z_compress,
	.comp_stat =		z_comp_stats,
	.decomp_alloc =		z_decomp_alloc,
	.decomp_मुक्त =		z_decomp_मुक्त,
	.decomp_init =		z_decomp_init,
	.decomp_reset =		z_decomp_reset,
	.decompress =		z_decompress,
	.incomp =		z_incomp,
	.decomp_stat =		z_comp_stats,
	.owner =		THIS_MODULE
पूर्ण;

अटल पूर्णांक __init deflate_init(व्योम)
अणु
	पूर्णांक rc;

	rc = ppp_रेजिस्टर_compressor(&ppp_deflate);
	अगर (rc)
		वापस rc;

	rc = ppp_रेजिस्टर_compressor(&ppp_deflate_draft);
	अगर (rc) अणु
		ppp_unरेजिस्टर_compressor(&ppp_deflate);
		वापस rc;
	पूर्ण

	pr_info("PPP Deflate Compression module registered\n");
	वापस 0;
पूर्ण

अटल व्योम __निकास deflate_cleanup(व्योम)
अणु
	ppp_unरेजिस्टर_compressor(&ppp_deflate);
	ppp_unरेजिस्टर_compressor(&ppp_deflate_draft);
पूर्ण

module_init(deflate_init);
module_निकास(deflate_cleanup);
MODULE_LICENSE("Dual BSD/GPL");
MODULE_ALIAS("ppp-compress-" __stringअगरy(CI_DEFLATE));
MODULE_ALIAS("ppp-compress-" __stringअगरy(CI_DEFLATE_DRAFT));
