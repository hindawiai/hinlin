<शैली गुरु>
/*
 * ppp_mppe.c - पूर्णांकerface MPPE to the PPP code.
 * This version is क्रम use with Linux kernel 2.6.14+
 *
 * By Frank Cusack <fcusack@fcusack.com>.
 * Copyright (c) 2002,2003,2004 Google, Inc.
 * All rights reserved.
 *
 * License:
 * Permission to use, copy, modअगरy, and distribute this software and its
 * करोcumentation is hereby granted, provided that the above copyright
 * notice appears in all copies.  This software is provided without any
 * warranty, express or implied.
 *
 * ALTERNATIVELY, provided that this notice is retained in full, this product
 * may be distributed under the terms of the GNU General Public License (GPL),
 * in which हाल the provisions of the GPL apply INSTEAD OF those given above.
 *
 *   This program is मुक्त software; you can redistribute it and/or modअगरy
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License क्रम more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   aदीर्घ with this program; अगर not, see <http://www.gnu.org/licenses/>.
 *
 *
 * Changelog:
 *      08/12/05 - Matt Domsch <Matt_Domsch@dell.com>
 *                 Only need extra skb padding on transmit, not receive.
 *      06/18/04 - Matt Domsch <Matt_Domsch@dell.com>, Oleg Makarenko <mole@quadra.ru>
 *                 Use Linux kernel 2.6 arc4 and sha1 routines rather than
 *                 providing our own.
 *      2/15/04 - TS: added #समावेश <version.h> and testing क्रम Kernel
 *                    version beक्रमe using
 *                    MOD_DEC_USAGE_COUNT/MOD_INC_USAGE_COUNT which are
 *                    deprecated in 2.6
 */

#समावेश <crypto/arc4.h>
#समावेश <crypto/hash.h>
#समावेश <linux/err.h>
#समावेश <linux/fips.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/ppp_defs.h>
#समावेश <linux/ppp-comp.h>
#समावेश <linux/scatterlist.h>
#समावेश <यंत्र/unaligned.h>

#समावेश "ppp_mppe.h"

MODULE_AUTHOR("Frank Cusack <fcusack@fcusack.com>");
MODULE_DESCRIPTION("Point-to-Point Protocol Microsoft Point-to-Point Encryption support");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_ALIAS("ppp-compress-" __stringअगरy(CI_MPPE));
MODULE_VERSION("1.0.2");

#घोषणा SHA1_PAD_SIZE 40

/*
 * kernel crypto API needs its arguments to be in kदो_स्मृति'd memory, not in the module
 * अटल data area.  That means sha_pad needs to be kदो_स्मृति'd.
 */

काष्ठा sha_pad अणु
	अचिन्हित अक्षर sha_pad1[SHA1_PAD_SIZE];
	अचिन्हित अक्षर sha_pad2[SHA1_PAD_SIZE];
पूर्ण;
अटल काष्ठा sha_pad *sha_pad;

अटल अंतरभूत व्योम sha_pad_init(काष्ठा sha_pad *shapad)
अणु
	स_रखो(shapad->sha_pad1, 0x00, माप(shapad->sha_pad1));
	स_रखो(shapad->sha_pad2, 0xF2, माप(shapad->sha_pad2));
पूर्ण

/*
 * State क्रम an MPPE (de)compressor.
 */
काष्ठा ppp_mppe_state अणु
	काष्ठा arc4_ctx arc4;
	काष्ठा shash_desc *sha1;
	अचिन्हित अक्षर *sha1_digest;
	अचिन्हित अक्षर master_key[MPPE_MAX_KEY_LEN];
	अचिन्हित अक्षर session_key[MPPE_MAX_KEY_LEN];
	अचिन्हित keylen;	/* key length in bytes             */
	/* NB: 128-bit == 16, 40-bit == 8! */
	/* If we want to support 56-bit,   */
	/* the unit has to change to bits  */
	अचिन्हित अक्षर bits;	/* MPPE control bits */
	अचिन्हित ccount;	/* 12-bit coherency count (seqno)  */
	अचिन्हित stateful;	/* stateful mode flag */
	पूर्णांक discard;		/* stateful mode packet loss flag */
	पूर्णांक sanity_errors;	/* take करोwn LCP अगर too many */
	पूर्णांक unit;
	पूर्णांक debug;
	काष्ठा compstat stats;
पूर्ण;

/* काष्ठा ppp_mppe_state.bits definitions */
#घोषणा MPPE_BIT_A	0x80	/* Encryption table were (re)inititalized */
#घोषणा MPPE_BIT_B	0x40	/* MPPC only (not implemented) */
#घोषणा MPPE_BIT_C	0x20	/* MPPC only (not implemented) */
#घोषणा MPPE_BIT_D	0x10	/* This is an encrypted frame */

#घोषणा MPPE_BIT_FLUSHED	MPPE_BIT_A
#घोषणा MPPE_BIT_ENCRYPTED	MPPE_BIT_D

#घोषणा MPPE_BITS(p) ((p)[4] & 0xf0)
#घोषणा MPPE_CCOUNT(p) ((((p)[4] & 0x0f) << 8) + (p)[5])
#घोषणा MPPE_CCOUNT_SPACE 0x1000	/* The size of the ccount space */

#घोषणा MPPE_OVHD	2	/* MPPE overhead/packet */
#घोषणा SANITY_MAX	1600	/* Max bogon factor we will tolerate */

/*
 * Key Derivation, from RFC 3078, RFC 3079.
 * Equivalent to Get_Key() क्रम MS-CHAP as described in RFC 3079.
 */
अटल व्योम get_new_key_from_sha(काष्ठा ppp_mppe_state * state)
अणु
	crypto_shash_init(state->sha1);
	crypto_shash_update(state->sha1, state->master_key,
			    state->keylen);
	crypto_shash_update(state->sha1, sha_pad->sha_pad1,
			    माप(sha_pad->sha_pad1));
	crypto_shash_update(state->sha1, state->session_key,
			    state->keylen);
	crypto_shash_update(state->sha1, sha_pad->sha_pad2,
			    माप(sha_pad->sha_pad2));
	crypto_shash_final(state->sha1, state->sha1_digest);
पूर्ण

/*
 * Perक्रमm the MPPE rekey algorithm, from RFC 3078, sec. 7.3.
 * Well, not what's written there, but rather what they meant.
 */
अटल व्योम mppe_rekey(काष्ठा ppp_mppe_state * state, पूर्णांक initial_key)
अणु
	get_new_key_from_sha(state);
	अगर (!initial_key) अणु
		arc4_setkey(&state->arc4, state->sha1_digest, state->keylen);
		arc4_crypt(&state->arc4, state->session_key, state->sha1_digest,
			   state->keylen);
	पूर्ण अन्यथा अणु
		स_नकल(state->session_key, state->sha1_digest, state->keylen);
	पूर्ण
	अगर (state->keylen == 8) अणु
		/* See RFC 3078 */
		state->session_key[0] = 0xd1;
		state->session_key[1] = 0x26;
		state->session_key[2] = 0x9e;
	पूर्ण
	arc4_setkey(&state->arc4, state->session_key, state->keylen);
पूर्ण

/*
 * Allocate space क्रम a (de)compressor.
 */
अटल व्योम *mppe_alloc(अचिन्हित अक्षर *options, पूर्णांक optlen)
अणु
	काष्ठा ppp_mppe_state *state;
	काष्ठा crypto_shash *shash;
	अचिन्हित पूर्णांक digestsize;

	अगर (optlen != CILEN_MPPE + माप(state->master_key) ||
	    options[0] != CI_MPPE || options[1] != CILEN_MPPE ||
	    fips_enabled)
		जाओ out;

	state = kzalloc(माप(*state), GFP_KERNEL);
	अगर (state == शून्य)
		जाओ out;


	shash = crypto_alloc_shash("sha1", 0, 0);
	अगर (IS_ERR(shash))
		जाओ out_मुक्त;

	state->sha1 = kदो_स्मृति(माप(*state->sha1) +
				     crypto_shash_descsize(shash),
			      GFP_KERNEL);
	अगर (!state->sha1) अणु
		crypto_मुक्त_shash(shash);
		जाओ out_मुक्त;
	पूर्ण
	state->sha1->tfm = shash;

	digestsize = crypto_shash_digestsize(shash);
	अगर (digestsize < MPPE_MAX_KEY_LEN)
		जाओ out_मुक्त;

	state->sha1_digest = kदो_स्मृति(digestsize, GFP_KERNEL);
	अगर (!state->sha1_digest)
		जाओ out_मुक्त;

	/* Save keys. */
	स_नकल(state->master_key, &options[CILEN_MPPE],
	       माप(state->master_key));
	स_नकल(state->session_key, state->master_key,
	       माप(state->master_key));

	/*
	 * We defer initial key generation until mppe_init(), as mppe_alloc()
	 * is called frequently during negotiation.
	 */

	वापस (व्योम *)state;

out_मुक्त:
	kमुक्त(state->sha1_digest);
	अगर (state->sha1) अणु
		crypto_मुक्त_shash(state->sha1->tfm);
		kमुक्त_sensitive(state->sha1);
	पूर्ण
	kमुक्त(state);
out:
	वापस शून्य;
पूर्ण

/*
 * Deallocate space क्रम a (de)compressor.
 */
अटल व्योम mppe_मुक्त(व्योम *arg)
अणु
	काष्ठा ppp_mppe_state *state = (काष्ठा ppp_mppe_state *) arg;
	अगर (state) अणु
		kमुक्त(state->sha1_digest);
		crypto_मुक्त_shash(state->sha1->tfm);
		kमुक्त_sensitive(state->sha1);
		kमुक्त_sensitive(state);
	पूर्ण
पूर्ण

/*
 * Initialize (de)compressor state.
 */
अटल पूर्णांक
mppe_init(व्योम *arg, अचिन्हित अक्षर *options, पूर्णांक optlen, पूर्णांक unit, पूर्णांक debug,
	  स्थिर अक्षर *debugstr)
अणु
	काष्ठा ppp_mppe_state *state = (काष्ठा ppp_mppe_state *) arg;
	अचिन्हित अक्षर mppe_opts;

	अगर (optlen != CILEN_MPPE ||
	    options[0] != CI_MPPE || options[1] != CILEN_MPPE)
		वापस 0;

	MPPE_CI_TO_OPTS(&options[2], mppe_opts);
	अगर (mppe_opts & MPPE_OPT_128)
		state->keylen = 16;
	अन्यथा अगर (mppe_opts & MPPE_OPT_40)
		state->keylen = 8;
	अन्यथा अणु
		prपूर्णांकk(KERN_WARNING "%s[%d]: unknown key length\n", debugstr,
		       unit);
		वापस 0;
	पूर्ण
	अगर (mppe_opts & MPPE_OPT_STATEFUL)
		state->stateful = 1;

	/* Generate the initial session key. */
	mppe_rekey(state, 1);

	अगर (debug) अणु
		prपूर्णांकk(KERN_DEBUG "%s[%d]: initialized with %d-bit %s mode\n",
		       debugstr, unit, (state->keylen == 16) ? 128 : 40,
		       (state->stateful) ? "stateful" : "stateless");
		prपूर्णांकk(KERN_DEBUG
		       "%s[%d]: keys: master: %*phN initial session: %*phN\n",
		       debugstr, unit,
		       (पूर्णांक)माप(state->master_key), state->master_key,
		       (पूर्णांक)माप(state->session_key), state->session_key);
	पूर्ण

	/*
	 * Initialize the coherency count.  The initial value is not specअगरied
	 * in RFC 3078, but we can make a reasonable assumption that it will
	 * start at 0.  Setting it to the max here makes the comp/decomp code
	 * करो the right thing (determined through experiment).
	 */
	state->ccount = MPPE_CCOUNT_SPACE - 1;

	/*
	 * Note that even though we have initialized the key table, we करोn't
	 * set the FLUSHED bit.  This is contrary to RFC 3078, sec. 3.1.
	 */
	state->bits = MPPE_BIT_ENCRYPTED;

	state->unit = unit;
	state->debug = debug;

	वापस 1;
पूर्ण

अटल पूर्णांक
mppe_comp_init(व्योम *arg, अचिन्हित अक्षर *options, पूर्णांक optlen, पूर्णांक unit,
	       पूर्णांक hdrlen, पूर्णांक debug)
अणु
	/* ARGSUSED */
	वापस mppe_init(arg, options, optlen, unit, debug, "mppe_comp_init");
पूर्ण

/*
 * We received a CCP Reset-Request (actually, we are sending a Reset-Ack),
 * tell the compressor to rekey.  Note that we MUST NOT rekey क्रम
 * every CCP Reset-Request; we only rekey on the next xmit packet.
 * We might get multiple CCP Reset-Requests अगर our CCP Reset-Ack is lost.
 * So, rekeying क्रम every CCP Reset-Request is broken as the peer will not
 * know how many बार we've rekeyed.  (If we rekey and THEN get another
 * CCP Reset-Request, we must rekey again.)
 */
अटल व्योम mppe_comp_reset(व्योम *arg)
अणु
	काष्ठा ppp_mppe_state *state = (काष्ठा ppp_mppe_state *) arg;

	state->bits |= MPPE_BIT_FLUSHED;
पूर्ण

/*
 * Compress (encrypt) a packet.
 * It's strange to call this a compressor, since the output is always
 * MPPE_OVHD + 2 bytes larger than the input.
 */
अटल पूर्णांक
mppe_compress(व्योम *arg, अचिन्हित अक्षर *ibuf, अचिन्हित अक्षर *obuf,
	      पूर्णांक isize, पूर्णांक osize)
अणु
	काष्ठा ppp_mppe_state *state = (काष्ठा ppp_mppe_state *) arg;
	पूर्णांक proto;

	/*
	 * Check that the protocol is in the range we handle.
	 */
	proto = PPP_PROTOCOL(ibuf);
	अगर (proto < 0x0021 || proto > 0x00fa)
		वापस 0;

	/* Make sure we have enough room to generate an encrypted packet. */
	अगर (osize < isize + MPPE_OVHD + 2) अणु
		/* Drop the packet अगर we should encrypt it, but can't. */
		prपूर्णांकk(KERN_DEBUG "mppe_compress[%d]: osize too small! "
		       "(have: %d need: %d)\n", state->unit,
		       osize, osize + MPPE_OVHD + 2);
		वापस -1;
	पूर्ण

	osize = isize + MPPE_OVHD + 2;

	/*
	 * Copy over the PPP header and set control bits.
	 */
	obuf[0] = PPP_ADDRESS(ibuf);
	obuf[1] = PPP_CONTROL(ibuf);
	put_unaligned_be16(PPP_COMP, obuf + 2);
	obuf += PPP_HDRLEN;

	state->ccount = (state->ccount + 1) % MPPE_CCOUNT_SPACE;
	अगर (state->debug >= 7)
		prपूर्णांकk(KERN_DEBUG "mppe_compress[%d]: ccount %d\n", state->unit,
		       state->ccount);
	put_unaligned_be16(state->ccount, obuf);

	अगर (!state->stateful ||	/* stateless mode     */
	    ((state->ccount & 0xff) == 0xff) ||	/* "flag" packet      */
	    (state->bits & MPPE_BIT_FLUSHED)) अणु	/* CCP Reset-Request  */
		/* We must rekey */
		अगर (state->debug && state->stateful)
			prपूर्णांकk(KERN_DEBUG "mppe_compress[%d]: rekeying\n",
			       state->unit);
		mppe_rekey(state, 0);
		state->bits |= MPPE_BIT_FLUSHED;
	पूर्ण
	obuf[0] |= state->bits;
	state->bits &= ~MPPE_BIT_FLUSHED;	/* reset क्रम next xmit */

	obuf += MPPE_OVHD;
	ibuf += 2;		/* skip to proto field */
	isize -= 2;

	arc4_crypt(&state->arc4, obuf, ibuf, isize);

	state->stats.unc_bytes += isize;
	state->stats.unc_packets++;
	state->stats.comp_bytes += osize;
	state->stats.comp_packets++;

	वापस osize;
पूर्ण

/*
 * Since every frame grows by MPPE_OVHD + 2 bytes, this is always going
 * to look bad ... and the दीर्घer the link is up the worse it will get.
 */
अटल व्योम mppe_comp_stats(व्योम *arg, काष्ठा compstat *stats)
अणु
	काष्ठा ppp_mppe_state *state = (काष्ठा ppp_mppe_state *) arg;

	*stats = state->stats;
पूर्ण

अटल पूर्णांक
mppe_decomp_init(व्योम *arg, अचिन्हित अक्षर *options, पूर्णांक optlen, पूर्णांक unit,
		 पूर्णांक hdrlen, पूर्णांक mru, पूर्णांक debug)
अणु
	/* ARGSUSED */
	वापस mppe_init(arg, options, optlen, unit, debug, "mppe_decomp_init");
पूर्ण

/*
 * We received a CCP Reset-Ack.  Just ignore it.
 */
अटल व्योम mppe_decomp_reset(व्योम *arg)
अणु
	/* ARGSUSED */
	वापस;
पूर्ण

/*
 * Decompress (decrypt) an MPPE packet.
 */
अटल पूर्णांक
mppe_decompress(व्योम *arg, अचिन्हित अक्षर *ibuf, पूर्णांक isize, अचिन्हित अक्षर *obuf,
		पूर्णांक osize)
अणु
	काष्ठा ppp_mppe_state *state = (काष्ठा ppp_mppe_state *) arg;
	अचिन्हित ccount;
	पूर्णांक flushed = MPPE_BITS(ibuf) & MPPE_BIT_FLUSHED;

	अगर (isize <= PPP_HDRLEN + MPPE_OVHD) अणु
		अगर (state->debug)
			prपूर्णांकk(KERN_DEBUG
			       "mppe_decompress[%d]: short pkt (%d)\n",
			       state->unit, isize);
		वापस DECOMP_ERROR;
	पूर्ण

	/*
	 * Make sure we have enough room to decrypt the packet.
	 * Note that क्रम our test we only subtract 1 byte whereas in
	 * mppe_compress() we added 2 bytes (+MPPE_OVHD);
	 * this is to account क्रम possible PFC.
	 */
	अगर (osize < isize - MPPE_OVHD - 1) अणु
		prपूर्णांकk(KERN_DEBUG "mppe_decompress[%d]: osize too small! "
		       "(have: %d need: %d)\n", state->unit,
		       osize, isize - MPPE_OVHD - 1);
		वापस DECOMP_ERROR;
	पूर्ण
	osize = isize - MPPE_OVHD - 2;	/* assume no PFC */

	ccount = MPPE_CCOUNT(ibuf);
	अगर (state->debug >= 7)
		prपूर्णांकk(KERN_DEBUG "mppe_decompress[%d]: ccount %d\n",
		       state->unit, ccount);

	/* sanity checks -- terminate with extreme prejudice */
	अगर (!(MPPE_BITS(ibuf) & MPPE_BIT_ENCRYPTED)) अणु
		prपूर्णांकk(KERN_DEBUG
		       "mppe_decompress[%d]: ENCRYPTED bit not set!\n",
		       state->unit);
		state->sanity_errors += 100;
		जाओ sanity_error;
	पूर्ण
	अगर (!state->stateful && !flushed) अणु
		prपूर्णांकk(KERN_DEBUG "mppe_decompress[%d]: FLUSHED bit not set in "
		       "stateless mode!\n", state->unit);
		state->sanity_errors += 100;
		जाओ sanity_error;
	पूर्ण
	अगर (state->stateful && ((ccount & 0xff) == 0xff) && !flushed) अणु
		prपूर्णांकk(KERN_DEBUG "mppe_decompress[%d]: FLUSHED bit not set on "
		       "flag packet!\n", state->unit);
		state->sanity_errors += 100;
		जाओ sanity_error;
	पूर्ण

	/*
	 * Check the coherency count.
	 */

	अगर (!state->stateful) अणु
		/* Discard late packet */
		अगर ((ccount - state->ccount) % MPPE_CCOUNT_SPACE
						> MPPE_CCOUNT_SPACE / 2) अणु
			state->sanity_errors++;
			जाओ sanity_error;
		पूर्ण

		/* RFC 3078, sec 8.1.  Rekey क्रम every packet. */
		जबतक (state->ccount != ccount) अणु
			mppe_rekey(state, 0);
			state->ccount = (state->ccount + 1) % MPPE_CCOUNT_SPACE;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* RFC 3078, sec 8.2. */
		अगर (!state->discard) अणु
			/* normal state */
			state->ccount = (state->ccount + 1) % MPPE_CCOUNT_SPACE;
			अगर (ccount != state->ccount) अणु
				/*
				 * (ccount > state->ccount)
				 * Packet loss detected, enter the discard state.
				 * Signal the peer to rekey (by sending a CCP Reset-Request).
				 */
				state->discard = 1;
				वापस DECOMP_ERROR;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* discard state */
			अगर (!flushed) अणु
				/* ccp.c will be silent (no additional CCP Reset-Requests). */
				वापस DECOMP_ERROR;
			पूर्ण अन्यथा अणु
				/* Rekey क्रम every missed "flag" packet. */
				जबतक ((ccount & ~0xff) !=
				       (state->ccount & ~0xff)) अणु
					mppe_rekey(state, 0);
					state->ccount =
					    (state->ccount +
					     256) % MPPE_CCOUNT_SPACE;
				पूर्ण

				/* reset */
				state->discard = 0;
				state->ccount = ccount;
				/*
				 * Another problem with RFC 3078 here.  It implies that the
				 * peer need not send a Reset-Ack packet.  But RFC 1962
				 * requires it.  Hopefully, M$ करोes send a Reset-Ack; even
				 * though it isn't required क्रम MPPE synchronization, it is
				 * required to reset CCP state.
				 */
			पूर्ण
		पूर्ण
		अगर (flushed)
			mppe_rekey(state, 0);
	पूर्ण

	/*
	 * Fill in the first part of the PPP header.  The protocol field
	 * comes from the decrypted data.
	 */
	obuf[0] = PPP_ADDRESS(ibuf);	/* +1 */
	obuf[1] = PPP_CONTROL(ibuf);	/* +1 */
	obuf += 2;
	ibuf += PPP_HDRLEN + MPPE_OVHD;
	isize -= PPP_HDRLEN + MPPE_OVHD;	/* -6 */
	/* net osize: isize-4 */

	/*
	 * Decrypt the first byte in order to check अगर it is
	 * a compressed or uncompressed protocol field.
	 */
	arc4_crypt(&state->arc4, obuf, ibuf, 1);

	/*
	 * Do PFC decompression.
	 * This would be nicer अगर we were given the actual sk_buff
	 * instead of a अक्षर *.
	 */
	अगर ((obuf[0] & 0x01) != 0) अणु
		obuf[1] = obuf[0];
		obuf[0] = 0;
		obuf++;
		osize++;
	पूर्ण

	/* And finally, decrypt the rest of the packet. */
	arc4_crypt(&state->arc4, obuf + 1, ibuf + 1, isize - 1);

	state->stats.unc_bytes += osize;
	state->stats.unc_packets++;
	state->stats.comp_bytes += isize;
	state->stats.comp_packets++;

	/* good packet credit */
	state->sanity_errors >>= 1;

	वापस osize;

sanity_error:
	अगर (state->sanity_errors < SANITY_MAX)
		वापस DECOMP_ERROR;
	अन्यथा
		/* Take LCP करोwn अगर the peer is sending too many bogons.
		 * We करोn't want to करो this क्रम a single or just a few
		 * instances since it could just be due to packet corruption.
		 */
		वापस DECOMP_FATALERROR;
पूर्ण

/*
 * Incompressible data has arrived (this should never happen!).
 * We should probably drop the link अगर the protocol is in the range
 * of what should be encrypted.  At the least, we should drop this
 * packet.  (How to करो this?)
 */
अटल व्योम mppe_incomp(व्योम *arg, अचिन्हित अक्षर *ibuf, पूर्णांक icnt)
अणु
	काष्ठा ppp_mppe_state *state = (काष्ठा ppp_mppe_state *) arg;

	अगर (state->debug &&
	    (PPP_PROTOCOL(ibuf) >= 0x0021 && PPP_PROTOCOL(ibuf) <= 0x00fa))
		prपूर्णांकk(KERN_DEBUG
		       "mppe_incomp[%d]: incompressible (unencrypted) data! "
		       "(proto %04x)\n", state->unit, PPP_PROTOCOL(ibuf));

	state->stats.inc_bytes += icnt;
	state->stats.inc_packets++;
	state->stats.unc_bytes += icnt;
	state->stats.unc_packets++;
पूर्ण

/*************************************************************
 * Module पूर्णांकerface table
 *************************************************************/

/*
 * Procedures exported to अगर_ppp.c.
 */
अटल काष्ठा compressor ppp_mppe = अणु
	.compress_proto = CI_MPPE,
	.comp_alloc     = mppe_alloc,
	.comp_मुक्त      = mppe_मुक्त,
	.comp_init      = mppe_comp_init,
	.comp_reset     = mppe_comp_reset,
	.compress       = mppe_compress,
	.comp_stat      = mppe_comp_stats,
	.decomp_alloc   = mppe_alloc,
	.decomp_मुक्त    = mppe_मुक्त,
	.decomp_init    = mppe_decomp_init,
	.decomp_reset   = mppe_decomp_reset,
	.decompress     = mppe_decompress,
	.incomp         = mppe_incomp,
	.decomp_stat    = mppe_comp_stats,
	.owner          = THIS_MODULE,
	.comp_extra     = MPPE_PAD,
पूर्ण;

/*
 * ppp_mppe_init()
 *
 * Prior to allowing load, try to load the arc4 and sha1 crypto
 * libraries.  The actual use will be allocated later, but
 * this way the module will fail to insmod अगर they aren't available.
 */

अटल पूर्णांक __init ppp_mppe_init(व्योम)
अणु
	पूर्णांक answer;
	अगर (fips_enabled || !crypto_has_ahash("sha1", 0, CRYPTO_ALG_ASYNC))
		वापस -ENODEV;

	sha_pad = kदो_स्मृति(माप(काष्ठा sha_pad), GFP_KERNEL);
	अगर (!sha_pad)
		वापस -ENOMEM;
	sha_pad_init(sha_pad);

	answer = ppp_रेजिस्टर_compressor(&ppp_mppe);

	अगर (answer == 0)
		prपूर्णांकk(KERN_INFO "PPP MPPE Compression module registered\n");
	अन्यथा
		kमुक्त(sha_pad);

	वापस answer;
पूर्ण

अटल व्योम __निकास ppp_mppe_cleanup(व्योम)
अणु
	ppp_unरेजिस्टर_compressor(&ppp_mppe);
	kमुक्त(sha_pad);
पूर्ण

module_init(ppp_mppe_init);
module_निकास(ppp_mppe_cleanup);
