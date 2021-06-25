<शैली गुरु>
/*
 * COPYRIGHT (c) 2008
 * The Regents of the University of Michigan
 * ALL RIGHTS RESERVED
 *
 * Permission is granted to use, copy, create derivative works
 * and redistribute this software and such derivative works
 * क्रम any purpose, so दीर्घ as the name of The University of
 * Michigan is not used in any advertising or खुलाity
 * pertaining to the use of distribution of this software
 * without specअगरic, written prior authorization.  If the
 * above copyright notice or any other identअगरication of the
 * University of Michigan is included in any copy of any
 * portion of this software, then the disclaimer below must
 * also be included.
 *
 * THIS SOFTWARE IS PROVIDED AS IS, WITHOUT REPRESENTATION
 * FROM THE UNIVERSITY OF MICHIGAN AS TO ITS FITNESS FOR ANY
 * PURPOSE, AND WITHOUT WARRANTY BY THE UNIVERSITY OF
 * MICHIGAN OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING
 * WITHOUT LIMITATION THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. THE
 * REGENTS OF THE UNIVERSITY OF MICHIGAN SHALL NOT BE LIABLE
 * FOR ANY DAMAGES, INCLUDING SPECIAL, INसूचीECT, INCIDENTAL, OR
 * CONSEQUENTIAL DAMAGES, WITH RESPECT TO ANY CLAIM ARISING
 * OUT OF OR IN CONNECTION WITH THE USE OF THE SOFTWARE, EVEN
 * IF IT HAS BEEN OR IS HEREAFTER ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGES.
 */

/*
 * Copyright (C) 1998 by the FundsXpress, INC.
 *
 * All rights reserved.
 *
 * Export of this software from the United States of America may require
 * a specअगरic license from the United States Government.  It is the
 * responsibility of any person or organization contemplating export to
 * obtain such a license beक्रमe exporting.
 *
 * WITHIN THAT CONSTRAINT, permission to use, copy, modअगरy, and
 * distribute this software and its करोcumentation क्रम any purpose and
 * without fee is hereby granted, provided that the above copyright
 * notice appear in all copies and that both that copyright notice and
 * this permission notice appear in supporting करोcumentation, and that
 * the name of FundsXpress. not be used in advertising or खुलाity pertaining
 * to distribution of the software without specअगरic, written prior
 * permission.  FundsXpress makes no representations about the suitability of
 * this software क्रम any purpose.  It is provided "as is" without express
 * or implied warranty.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */

#समावेश <crypto/skcipher.h>
#समावेश <linux/err.h>
#समावेश <linux/types.h>
#समावेश <linux/sunrpc/gss_krb5.h>
#समावेश <linux/sunrpc/xdr.h>
#समावेश <linux/lcm.h>

#अगर IS_ENABLED(CONFIG_SUNRPC_DEBUG)
# define RPCDBG_FACILITY        RPCDBG_AUTH
#पूर्ण_अगर

/*
 * This is the n-fold function as described in rfc3961, sec 5.1
 * Taken from MIT Kerberos and modअगरied.
 */

अटल व्योम krb5_nfold(u32 inbits, स्थिर u8 *in,
		       u32 outbits, u8 *out)
अणु
	अचिन्हित दीर्घ ulcm;
	पूर्णांक byte, i, msbit;

	/* the code below is more पढ़ोable अगर I make these bytes
	   instead of bits */

	inbits >>= 3;
	outbits >>= 3;

	/* first compute lcm(n,k) */
	ulcm = lcm(inbits, outbits);

	/* now करो the real work */

	स_रखो(out, 0, outbits);
	byte = 0;

	/* this will end up cycling through k lcm(k,n)/k बार, which
	   is correct */
	क्रम (i = ulcm-1; i >= 0; i--) अणु
		/* compute the msbit in k which माला_लो added पूर्णांकo this byte */
		msbit = (
			/* first, start with the msbit in the first,
			 * unrotated byte */
			 ((inbits << 3) - 1)
			 /* then, क्रम each byte, shअगरt to the right
			  * क्रम each repetition */
			 + (((inbits << 3) + 13) * (i/inbits))
			 /* last, pick out the correct byte within
			  * that shअगरted repetition */
			 + ((inbits - (i % inbits)) << 3)
			 ) % (inbits << 3);

		/* pull out the byte value itself */
		byte += (((in[((inbits - 1) - (msbit >> 3)) % inbits] << 8)|
				  (in[((inbits) - (msbit >> 3)) % inbits]))
				 >> ((msbit & 7) + 1)) & 0xff;

		/* करो the addition */
		byte += out[i % outbits];
		out[i % outbits] = byte & 0xff;

		/* keep around the carry bit, अगर any */
		byte >>= 8;

	पूर्ण

	/* अगर there's a carry bit left over, add it back in */
	अगर (byte) अणु
		क्रम (i = outbits - 1; i >= 0; i--) अणु
			/* करो the addition */
			byte += out[i];
			out[i] = byte & 0xff;

			/* keep around the carry bit, अगर any */
			byte >>= 8;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * This is the DK (derive_key) function as described in rfc3961, sec 5.1
 * Taken from MIT Kerberos and modअगरied.
 */

u32 krb5_derive_key(स्थिर काष्ठा gss_krb5_enctype *gk5e,
		    स्थिर काष्ठा xdr_netobj *inkey,
		    काष्ठा xdr_netobj *outkey,
		    स्थिर काष्ठा xdr_netobj *in_स्थिरant,
		    gfp_t gfp_mask)
अणु
	माप_प्रकार blocksize, keybytes, keylength, n;
	अचिन्हित अक्षर *inblockdata, *outblockdata, *rawkey;
	काष्ठा xdr_netobj inblock, outblock;
	काष्ठा crypto_sync_skcipher *cipher;
	u32 ret = EINVAL;

	blocksize = gk5e->blocksize;
	keybytes = gk5e->keybytes;
	keylength = gk5e->keylength;

	अगर ((inkey->len != keylength) || (outkey->len != keylength))
		जाओ err_वापस;

	cipher = crypto_alloc_sync_skcipher(gk5e->encrypt_name, 0, 0);
	अगर (IS_ERR(cipher))
		जाओ err_वापस;
	अगर (crypto_sync_skcipher_setkey(cipher, inkey->data, inkey->len))
		जाओ err_वापस;

	/* allocate and set up buffers */

	ret = ENOMEM;
	inblockdata = kदो_स्मृति(blocksize, gfp_mask);
	अगर (inblockdata == शून्य)
		जाओ err_मुक्त_cipher;

	outblockdata = kदो_स्मृति(blocksize, gfp_mask);
	अगर (outblockdata == शून्य)
		जाओ err_मुक्त_in;

	rawkey = kदो_स्मृति(keybytes, gfp_mask);
	अगर (rawkey == शून्य)
		जाओ err_मुक्त_out;

	inblock.data = (अक्षर *) inblockdata;
	inblock.len = blocksize;

	outblock.data = (अक्षर *) outblockdata;
	outblock.len = blocksize;

	/* initialize the input block */

	अगर (in_स्थिरant->len == inblock.len) अणु
		स_नकल(inblock.data, in_स्थिरant->data, inblock.len);
	पूर्ण अन्यथा अणु
		krb5_nfold(in_स्थिरant->len * 8, in_स्थिरant->data,
			   inblock.len * 8, inblock.data);
	पूर्ण

	/* loop encrypting the blocks until enough key bytes are generated */

	n = 0;
	जबतक (n < keybytes) अणु
		(*(gk5e->encrypt))(cipher, शून्य, inblock.data,
				   outblock.data, inblock.len);

		अगर ((keybytes - n) <= outblock.len) अणु
			स_नकल(rawkey + n, outblock.data, (keybytes - n));
			अवरोध;
		पूर्ण

		स_नकल(rawkey + n, outblock.data, outblock.len);
		स_नकल(inblock.data, outblock.data, outblock.len);
		n += outblock.len;
	पूर्ण

	/* postprocess the key */

	inblock.data = (अक्षर *) rawkey;
	inblock.len = keybytes;

	BUG_ON(gk5e->mk_key == शून्य);
	ret = (*(gk5e->mk_key))(gk5e, &inblock, outkey);
	अगर (ret) अणु
		dprपूर्णांकk("%s: got %d from mk_key function for '%s'\n",
			__func__, ret, gk5e->encrypt_name);
		जाओ err_मुक्त_raw;
	पूर्ण

	/* clean memory, मुक्त resources and निकास */

	ret = 0;

err_मुक्त_raw:
	kमुक्त_sensitive(rawkey);
err_मुक्त_out:
	kमुक्त_sensitive(outblockdata);
err_मुक्त_in:
	kमुक्त_sensitive(inblockdata);
err_मुक्त_cipher:
	crypto_मुक्त_sync_skcipher(cipher);
err_वापस:
	वापस ret;
पूर्ण

#घोषणा smask(step) ((1<<step)-1)
#घोषणा pstep(x, step) (((x)&smask(step))^(((x)>>step)&smask(step)))
#घोषणा parity_अक्षर(x) pstep(pstep(pstep((x), 4), 2), 1)

अटल व्योम mit_des_fixup_key_parity(u8 key[8])
अणु
	पूर्णांक i;
	क्रम (i = 0; i < 8; i++) अणु
		key[i] &= 0xfe;
		key[i] |= 1^parity_अक्षर(key[i]);
	पूर्ण
पूर्ण

/*
 * This is the des3 key derivation postprocess function
 */
u32 gss_krb5_des3_make_key(स्थिर काष्ठा gss_krb5_enctype *gk5e,
			   काष्ठा xdr_netobj *अक्रमombits,
			   काष्ठा xdr_netobj *key)
अणु
	पूर्णांक i;
	u32 ret = EINVAL;

	अगर (key->len != 24) अणु
		dprपूर्णांकk("%s: key->len is %d\n", __func__, key->len);
		जाओ err_out;
	पूर्ण
	अगर (अक्रमombits->len != 21) अणु
		dprपूर्णांकk("%s: randombits->len is %d\n",
			__func__, अक्रमombits->len);
		जाओ err_out;
	पूर्ण

	/* take the seven bytes, move them around पूर्णांकo the top 7 bits of the
	   8 key bytes, then compute the parity bits.  Do this three बार. */

	क्रम (i = 0; i < 3; i++) अणु
		स_नकल(key->data + i*8, अक्रमombits->data + i*7, 7);
		key->data[i*8+7] = (((key->data[i*8]&1)<<1) |
				    ((key->data[i*8+1]&1)<<2) |
				    ((key->data[i*8+2]&1)<<3) |
				    ((key->data[i*8+3]&1)<<4) |
				    ((key->data[i*8+4]&1)<<5) |
				    ((key->data[i*8+5]&1)<<6) |
				    ((key->data[i*8+6]&1)<<7));

		mit_des_fixup_key_parity(key->data + i*8);
	पूर्ण
	ret = 0;
err_out:
	वापस ret;
पूर्ण

/*
 * This is the aes key derivation postprocess function
 */
u32 gss_krb5_aes_make_key(स्थिर काष्ठा gss_krb5_enctype *gk5e,
			  काष्ठा xdr_netobj *अक्रमombits,
			  काष्ठा xdr_netobj *key)
अणु
	u32 ret = EINVAL;

	अगर (key->len != 16 && key->len != 32) अणु
		dprपूर्णांकk("%s: key->len is %d\n", __func__, key->len);
		जाओ err_out;
	पूर्ण
	अगर (अक्रमombits->len != 16 && अक्रमombits->len != 32) अणु
		dprपूर्णांकk("%s: randombits->len is %d\n",
			__func__, अक्रमombits->len);
		जाओ err_out;
	पूर्ण
	अगर (अक्रमombits->len != key->len) अणु
		dprपूर्णांकk("%s: randombits->len is %d, key->len is %d\n",
			__func__, अक्रमombits->len, key->len);
		जाओ err_out;
	पूर्ण
	स_नकल(key->data, अक्रमombits->data, key->len);
	ret = 0;
err_out:
	वापस ret;
पूर्ण
