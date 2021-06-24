<शैली गुरु>
/*
 * DRBG: Deterministic Ranकरोm Bits Generator
 *       Based on NIST Recommended DRBG from NIST SP800-90A with the following
 *       properties:
 *		* CTR DRBG with DF with AES-128, AES-192, AES-256 cores
 *		* Hash DRBG with DF with SHA-1, SHA-256, SHA-384, SHA-512 cores
 *		* HMAC DRBG with DF with SHA-1, SHA-256, SHA-384, SHA-512 cores
 *		* with and without prediction resistance
 *
 * Copyright Stephan Mueller <smueller@chronox.de>, 2014
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, and the entire permission notice in its entirety,
 *    including the disclaimer of warranties.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to enकरोrse or promote
 *    products derived from this software without specअगरic prior
 *    written permission.
 *
 * ALTERNATIVELY, this product may be distributed under the terms of
 * the GNU General Public License, in which हाल the provisions of the GPL are
 * required INSTEAD OF the above restrictions.  (This clause is
 * necessary due to a potential bad पूर्णांकeraction between the GPL and
 * the restrictions contained in a BSD-style copyright.)
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE, ALL OF
 * WHICH ARE HEREBY DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE
 * LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OF THIS SOFTWARE, EVEN IF NOT ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 *
 * DRBG Usage
 * ==========
 * The SP 800-90A DRBG allows the user to specअगरy a personalization string
 * क्रम initialization as well as an additional inक्रमmation string क्रम each
 * अक्रमom number request. The following code fragments show how a caller
 * uses the kernel crypto API to use the full functionality of the DRBG.
 *
 * Usage without any additional data
 * ---------------------------------
 * काष्ठा crypto_rng *drng;
 * पूर्णांक err;
 * अक्षर data[DATALEN];
 *
 * drng = crypto_alloc_rng(drng_name, 0, 0);
 * err = crypto_rng_get_bytes(drng, &data, DATALEN);
 * crypto_मुक्त_rng(drng);
 *
 *
 * Usage with personalization string during initialization
 * -------------------------------------------------------
 * काष्ठा crypto_rng *drng;
 * पूर्णांक err;
 * अक्षर data[DATALEN];
 * काष्ठा drbg_string pers;
 * अक्षर personalization[11] = "some-string";
 *
 * drbg_string_fill(&pers, personalization, म_माप(personalization));
 * drng = crypto_alloc_rng(drng_name, 0, 0);
 * // The reset completely re-initializes the DRBG with the provided
 * // personalization string
 * err = crypto_rng_reset(drng, &personalization, म_माप(personalization));
 * err = crypto_rng_get_bytes(drng, &data, DATALEN);
 * crypto_मुक्त_rng(drng);
 *
 *
 * Usage with additional inक्रमmation string during अक्रमom number request
 * ---------------------------------------------------------------------
 * काष्ठा crypto_rng *drng;
 * पूर्णांक err;
 * अक्षर data[DATALEN];
 * अक्षर addtl_string[11] = "some-string";
 * string drbg_string addtl;
 *
 * drbg_string_fill(&addtl, addtl_string, म_माप(addtl_string));
 * drng = crypto_alloc_rng(drng_name, 0, 0);
 * // The following call is a wrapper to crypto_rng_get_bytes() and वापसs
 * // the same error codes.
 * err = crypto_drbg_get_bytes_addtl(drng, &data, DATALEN, &addtl);
 * crypto_मुक्त_rng(drng);
 *
 *
 * Usage with personalization and additional inक्रमmation strings
 * -------------------------------------------------------------
 * Just mix both scenarios above.
 */

#समावेश <crypto/drbg.h>
#समावेश <crypto/पूर्णांकernal/cipher.h>
#समावेश <linux/kernel.h>

/***************************************************************
 * Backend cipher definitions available to DRBG
 ***************************************************************/

/*
 * The order of the DRBG definitions here matter: every DRBG is रेजिस्टरed
 * as stdrng. Each DRBG receives an increasing cra_priority values the later
 * they are defined in this array (see drbg_fill_array).
 *
 * HMAC DRBGs are favored over Hash DRBGs over CTR DRBGs, and
 * the SHA256 / AES 256 over other ciphers. Thus, the favored
 * DRBGs are the latest entries in this array.
 */
अटल स्थिर काष्ठा drbg_core drbg_cores[] = अणु
#अगर_घोषित CONFIG_CRYPTO_DRBG_CTR
	अणु
		.flags = DRBG_CTR | DRBG_STRENGTH128,
		.statelen = 32, /* 256 bits as defined in 10.2.1 */
		.blocklen_bytes = 16,
		.cra_name = "ctr_aes128",
		.backend_cra_name = "aes",
	पूर्ण, अणु
		.flags = DRBG_CTR | DRBG_STRENGTH192,
		.statelen = 40, /* 320 bits as defined in 10.2.1 */
		.blocklen_bytes = 16,
		.cra_name = "ctr_aes192",
		.backend_cra_name = "aes",
	पूर्ण, अणु
		.flags = DRBG_CTR | DRBG_STRENGTH256,
		.statelen = 48, /* 384 bits as defined in 10.2.1 */
		.blocklen_bytes = 16,
		.cra_name = "ctr_aes256",
		.backend_cra_name = "aes",
	पूर्ण,
#पूर्ण_अगर /* CONFIG_CRYPTO_DRBG_CTR */
#अगर_घोषित CONFIG_CRYPTO_DRBG_HASH
	अणु
		.flags = DRBG_HASH | DRBG_STRENGTH128,
		.statelen = 55, /* 440 bits */
		.blocklen_bytes = 20,
		.cra_name = "sha1",
		.backend_cra_name = "sha1",
	पूर्ण, अणु
		.flags = DRBG_HASH | DRBG_STRENGTH256,
		.statelen = 111, /* 888 bits */
		.blocklen_bytes = 48,
		.cra_name = "sha384",
		.backend_cra_name = "sha384",
	पूर्ण, अणु
		.flags = DRBG_HASH | DRBG_STRENGTH256,
		.statelen = 111, /* 888 bits */
		.blocklen_bytes = 64,
		.cra_name = "sha512",
		.backend_cra_name = "sha512",
	पूर्ण, अणु
		.flags = DRBG_HASH | DRBG_STRENGTH256,
		.statelen = 55, /* 440 bits */
		.blocklen_bytes = 32,
		.cra_name = "sha256",
		.backend_cra_name = "sha256",
	पूर्ण,
#पूर्ण_अगर /* CONFIG_CRYPTO_DRBG_HASH */
#अगर_घोषित CONFIG_CRYPTO_DRBG_HMAC
	अणु
		.flags = DRBG_HMAC | DRBG_STRENGTH128,
		.statelen = 20, /* block length of cipher */
		.blocklen_bytes = 20,
		.cra_name = "hmac_sha1",
		.backend_cra_name = "hmac(sha1)",
	पूर्ण, अणु
		.flags = DRBG_HMAC | DRBG_STRENGTH256,
		.statelen = 48, /* block length of cipher */
		.blocklen_bytes = 48,
		.cra_name = "hmac_sha384",
		.backend_cra_name = "hmac(sha384)",
	पूर्ण, अणु
		.flags = DRBG_HMAC | DRBG_STRENGTH256,
		.statelen = 64, /* block length of cipher */
		.blocklen_bytes = 64,
		.cra_name = "hmac_sha512",
		.backend_cra_name = "hmac(sha512)",
	पूर्ण, अणु
		.flags = DRBG_HMAC | DRBG_STRENGTH256,
		.statelen = 32, /* block length of cipher */
		.blocklen_bytes = 32,
		.cra_name = "hmac_sha256",
		.backend_cra_name = "hmac(sha256)",
	पूर्ण,
#पूर्ण_अगर /* CONFIG_CRYPTO_DRBG_HMAC */
पूर्ण;

अटल पूर्णांक drbg_uninstantiate(काष्ठा drbg_state *drbg);

/******************************************************************
 * Generic helper functions
 ******************************************************************/

/*
 * Return strength of DRBG according to SP800-90A section 8.4
 *
 * @flags DRBG flags reference
 *
 * Return: normalized strength in *bytes* value or 32 as शेष
 *	   to counter programming errors
 */
अटल अंतरभूत अचिन्हित लघु drbg_sec_strength(drbg_flag_t flags)
अणु
	चयन (flags & DRBG_STRENGTH_MASK) अणु
	हाल DRBG_STRENGTH128:
		वापस 16;
	हाल DRBG_STRENGTH192:
		वापस 24;
	हाल DRBG_STRENGTH256:
		वापस 32;
	शेष:
		वापस 32;
	पूर्ण
पूर्ण

/*
 * FIPS 140-2 continuous self test क्रम the noise source
 * The test is perक्रमmed on the noise source input data. Thus, the function
 * implicitly knows the size of the buffer to be equal to the security
 * strength.
 *
 * Note, this function disregards the nonce trailing the entropy data during
 * initial seeding.
 *
 * drbg->drbg_mutex must have been taken.
 *
 * @drbg DRBG handle
 * @entropy buffer of seed data to be checked
 *
 * वापस:
 *	0 on success
 *	-EAGAIN on when the CTRNG is not yet primed
 *	< 0 on error
 */
अटल पूर्णांक drbg_fips_continuous_test(काष्ठा drbg_state *drbg,
				     स्थिर अचिन्हित अक्षर *entropy)
अणु
	अचिन्हित लघु entropylen = drbg_sec_strength(drbg->core->flags);
	पूर्णांक ret = 0;

	अगर (!IS_ENABLED(CONFIG_CRYPTO_FIPS))
		वापस 0;

	/* skip test अगर we test the overall प्रणाली */
	अगर (list_empty(&drbg->test_data.list))
		वापस 0;
	/* only perक्रमm test in FIPS mode */
	अगर (!fips_enabled)
		वापस 0;

	अगर (!drbg->fips_primed) अणु
		/* Priming of FIPS test */
		स_नकल(drbg->prev, entropy, entropylen);
		drbg->fips_primed = true;
		/* priming: another round is needed */
		वापस -EAGAIN;
	पूर्ण
	ret = स_भेद(drbg->prev, entropy, entropylen);
	अगर (!ret)
		panic("DRBG continuous self test failed\n");
	स_नकल(drbg->prev, entropy, entropylen);

	/* the test shall pass when the two values are not equal */
	वापस 0;
पूर्ण

/*
 * Convert an पूर्णांकeger पूर्णांकo a byte representation of this पूर्णांकeger.
 * The byte representation is big-endian
 *
 * @val value to be converted
 * @buf buffer holding the converted पूर्णांकeger -- caller must ensure that
 *      buffer size is at least 32 bit
 */
#अगर (defined(CONFIG_CRYPTO_DRBG_HASH) || defined(CONFIG_CRYPTO_DRBG_CTR))
अटल अंतरभूत व्योम drbg_cpu_to_be32(__u32 val, अचिन्हित अक्षर *buf)
अणु
	काष्ठा s अणु
		__be32 conv;
	पूर्ण;
	काष्ठा s *conversion = (काष्ठा s *) buf;

	conversion->conv = cpu_to_be32(val);
पूर्ण
#पूर्ण_अगर /* defined(CONFIG_CRYPTO_DRBG_HASH) || defined(CONFIG_CRYPTO_DRBG_CTR) */

/******************************************************************
 * CTR DRBG callback functions
 ******************************************************************/

#अगर_घोषित CONFIG_CRYPTO_DRBG_CTR
#घोषणा CRYPTO_DRBG_CTR_STRING "CTR "
MODULE_ALIAS_CRYPTO("drbg_pr_ctr_aes256");
MODULE_ALIAS_CRYPTO("drbg_nopr_ctr_aes256");
MODULE_ALIAS_CRYPTO("drbg_pr_ctr_aes192");
MODULE_ALIAS_CRYPTO("drbg_nopr_ctr_aes192");
MODULE_ALIAS_CRYPTO("drbg_pr_ctr_aes128");
MODULE_ALIAS_CRYPTO("drbg_nopr_ctr_aes128");

अटल व्योम drbg_kcapi_symsetkey(काष्ठा drbg_state *drbg,
				 स्थिर अचिन्हित अक्षर *key);
अटल पूर्णांक drbg_kcapi_sym(काष्ठा drbg_state *drbg, अचिन्हित अक्षर *outval,
			  स्थिर काष्ठा drbg_string *in);
अटल पूर्णांक drbg_init_sym_kernel(काष्ठा drbg_state *drbg);
अटल पूर्णांक drbg_fini_sym_kernel(काष्ठा drbg_state *drbg);
अटल पूर्णांक drbg_kcapi_sym_ctr(काष्ठा drbg_state *drbg,
			      u8 *inbuf, u32 inbuflen,
			      u8 *outbuf, u32 outlen);
#घोषणा DRBG_OUTSCRATCHLEN 256

/* BCC function क्रम CTR DRBG as defined in 10.4.3 */
अटल पूर्णांक drbg_ctr_bcc(काष्ठा drbg_state *drbg,
			अचिन्हित अक्षर *out, स्थिर अचिन्हित अक्षर *key,
			काष्ठा list_head *in)
अणु
	पूर्णांक ret = 0;
	काष्ठा drbg_string *curr = शून्य;
	काष्ठा drbg_string data;
	लघु cnt = 0;

	drbg_string_fill(&data, out, drbg_blocklen(drbg));

	/* 10.4.3 step 2 / 4 */
	drbg_kcapi_symsetkey(drbg, key);
	list_क्रम_each_entry(curr, in, list) अणु
		स्थिर अचिन्हित अक्षर *pos = curr->buf;
		माप_प्रकार len = curr->len;
		/* 10.4.3 step 4.1 */
		जबतक (len) अणु
			/* 10.4.3 step 4.2 */
			अगर (drbg_blocklen(drbg) == cnt) अणु
				cnt = 0;
				ret = drbg_kcapi_sym(drbg, out, &data);
				अगर (ret)
					वापस ret;
			पूर्ण
			out[cnt] ^= *pos;
			pos++;
			cnt++;
			len--;
		पूर्ण
	पूर्ण
	/* 10.4.3 step 4.2 क्रम last block */
	अगर (cnt)
		ret = drbg_kcapi_sym(drbg, out, &data);

	वापस ret;
पूर्ण

/*
 * scratchpad usage: drbg_ctr_update is पूर्णांकerlinked with drbg_ctr_df
 * (and drbg_ctr_bcc, but this function करोes not need any temporary buffers),
 * the scratchpad is used as follows:
 * drbg_ctr_update:
 *	temp
 *		start: drbg->scratchpad
 *		length: drbg_statelen(drbg) + drbg_blocklen(drbg)
 *			note: the cipher writing पूर्णांकo this variable works
 *			blocklen-wise. Now, when the statelen is not a multiple
 *			of blocklen, the generateion loop below "spills over"
 *			by at most blocklen. Thus, we need to give sufficient
 *			memory.
 *	df_data
 *		start: drbg->scratchpad +
 *				drbg_statelen(drbg) + drbg_blocklen(drbg)
 *		length: drbg_statelen(drbg)
 *
 * drbg_ctr_df:
 *	pad
 *		start: df_data + drbg_statelen(drbg)
 *		length: drbg_blocklen(drbg)
 *	iv
 *		start: pad + drbg_blocklen(drbg)
 *		length: drbg_blocklen(drbg)
 *	temp
 *		start: iv + drbg_blocklen(drbg)
 *		length: drbg_satelen(drbg) + drbg_blocklen(drbg)
 *			note: temp is the buffer that the BCC function operates
 *			on. BCC operates blockwise. drbg_statelen(drbg)
 *			is sufficient when the DRBG state length is a multiple
 *			of the block size. For AES192 (and maybe other ciphers)
 *			this is not correct and the length क्रम temp is
 *			insufficient (yes, that also means क्रम such ciphers,
 *			the final output of all BCC rounds are truncated).
 *			Thereक्रमe, add drbg_blocklen(drbg) to cover all
 *			possibilities.
 */

/* Derivation Function क्रम CTR DRBG as defined in 10.4.2 */
अटल पूर्णांक drbg_ctr_df(काष्ठा drbg_state *drbg,
		       अचिन्हित अक्षर *df_data, माप_प्रकार bytes_to_वापस,
		       काष्ठा list_head *seedlist)
अणु
	पूर्णांक ret = -EFAULT;
	अचिन्हित अक्षर L_N[8];
	/* S3 is input */
	काष्ठा drbg_string S1, S2, S4, cipherin;
	LIST_HEAD(bcc_list);
	अचिन्हित अक्षर *pad = df_data + drbg_statelen(drbg);
	अचिन्हित अक्षर *iv = pad + drbg_blocklen(drbg);
	अचिन्हित अक्षर *temp = iv + drbg_blocklen(drbg);
	माप_प्रकार padlen = 0;
	अचिन्हित पूर्णांक templen = 0;
	/* 10.4.2 step 7 */
	अचिन्हित पूर्णांक i = 0;
	/* 10.4.2 step 8 */
	स्थिर अचिन्हित अक्षर *K = (अचिन्हित अक्षर *)
			   "\x00\x01\x02\x03\x04\x05\x06\x07"
			   "\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f"
			   "\x10\x11\x12\x13\x14\x15\x16\x17"
			   "\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f";
	अचिन्हित अक्षर *X;
	माप_प्रकार generated_len = 0;
	माप_प्रकार inputlen = 0;
	काष्ठा drbg_string *seed = शून्य;

	स_रखो(pad, 0, drbg_blocklen(drbg));
	स_रखो(iv, 0, drbg_blocklen(drbg));

	/* 10.4.2 step 1 is implicit as we work byte-wise */

	/* 10.4.2 step 2 */
	अगर ((512/8) < bytes_to_वापस)
		वापस -EINVAL;

	/* 10.4.2 step 2 -- calculate the entire length of all input data */
	list_क्रम_each_entry(seed, seedlist, list)
		inputlen += seed->len;
	drbg_cpu_to_be32(inputlen, &L_N[0]);

	/* 10.4.2 step 3 */
	drbg_cpu_to_be32(bytes_to_वापस, &L_N[4]);

	/* 10.4.2 step 5: length is L_N, input_string, one byte, padding */
	padlen = (inputlen + माप(L_N) + 1) % (drbg_blocklen(drbg));
	/* wrap the padlen appropriately */
	अगर (padlen)
		padlen = drbg_blocklen(drbg) - padlen;
	/*
	 * pad / padlen contains the 0x80 byte and the following zero bytes.
	 * As the calculated padlen value only covers the number of zero
	 * bytes, this value has to be incremented by one क्रम the 0x80 byte.
	 */
	padlen++;
	pad[0] = 0x80;

	/* 10.4.2 step 4 -- first fill the linked list and then order it */
	drbg_string_fill(&S1, iv, drbg_blocklen(drbg));
	list_add_tail(&S1.list, &bcc_list);
	drbg_string_fill(&S2, L_N, माप(L_N));
	list_add_tail(&S2.list, &bcc_list);
	list_splice_tail(seedlist, &bcc_list);
	drbg_string_fill(&S4, pad, padlen);
	list_add_tail(&S4.list, &bcc_list);

	/* 10.4.2 step 9 */
	जबतक (templen < (drbg_keylen(drbg) + (drbg_blocklen(drbg)))) अणु
		/*
		 * 10.4.2 step 9.1 - the padding is implicit as the buffer
		 * holds zeros after allocation -- even the increment of i
		 * is irrelevant as the increment reमुख्यs within length of i
		 */
		drbg_cpu_to_be32(i, iv);
		/* 10.4.2 step 9.2 -- BCC and concatenation with temp */
		ret = drbg_ctr_bcc(drbg, temp + templen, K, &bcc_list);
		अगर (ret)
			जाओ out;
		/* 10.4.2 step 9.3 */
		i++;
		templen += drbg_blocklen(drbg);
	पूर्ण

	/* 10.4.2 step 11 */
	X = temp + (drbg_keylen(drbg));
	drbg_string_fill(&cipherin, X, drbg_blocklen(drbg));

	/* 10.4.2 step 12: overwriting of outval is implemented in next step */

	/* 10.4.2 step 13 */
	drbg_kcapi_symsetkey(drbg, temp);
	जबतक (generated_len < bytes_to_वापस) अणु
		लघु blocklen = 0;
		/*
		 * 10.4.2 step 13.1: the truncation of the key length is
		 * implicit as the key is only drbg_blocklen in size based on
		 * the implementation of the cipher function callback
		 */
		ret = drbg_kcapi_sym(drbg, X, &cipherin);
		अगर (ret)
			जाओ out;
		blocklen = (drbg_blocklen(drbg) <
				(bytes_to_वापस - generated_len)) ?
			    drbg_blocklen(drbg) :
				(bytes_to_वापस - generated_len);
		/* 10.4.2 step 13.2 and 14 */
		स_नकल(df_data + generated_len, X, blocklen);
		generated_len += blocklen;
	पूर्ण

	ret = 0;

out:
	स_रखो(iv, 0, drbg_blocklen(drbg));
	स_रखो(temp, 0, drbg_statelen(drbg) + drbg_blocklen(drbg));
	स_रखो(pad, 0, drbg_blocklen(drbg));
	वापस ret;
पूर्ण

/*
 * update function of CTR DRBG as defined in 10.2.1.2
 *
 * The reseed variable has an enhanced meaning compared to the update
 * functions of the other DRBGs as follows:
 * 0 => initial seed from initialization
 * 1 => reseed via drbg_seed
 * 2 => first invocation from drbg_ctr_update when addtl is present. In
 *      this हाल, the df_data scratchpad is not deleted so that it is
 *      available क्रम another calls to prevent calling the DF function
 *      again.
 * 3 => second invocation from drbg_ctr_update. When the update function
 *      was called with addtl, the df_data memory alपढ़ोy contains the
 *      DFed addtl inक्रमmation and we करो not need to call DF again.
 */
अटल पूर्णांक drbg_ctr_update(काष्ठा drbg_state *drbg, काष्ठा list_head *seed,
			   पूर्णांक reseed)
अणु
	पूर्णांक ret = -EFAULT;
	/* 10.2.1.2 step 1 */
	अचिन्हित अक्षर *temp = drbg->scratchpad;
	अचिन्हित अक्षर *df_data = drbg->scratchpad + drbg_statelen(drbg) +
				 drbg_blocklen(drbg);

	अगर (3 > reseed)
		स_रखो(df_data, 0, drbg_statelen(drbg));

	अगर (!reseed) अणु
		/*
		 * The DRBG uses the CTR mode of the underlying AES cipher. The
		 * CTR mode increments the counter value after the AES operation
		 * but SP800-90A requires that the counter is incremented beक्रमe
		 * the AES operation. Hence, we increment it at the समय we set
		 * it by one.
		 */
		crypto_inc(drbg->V, drbg_blocklen(drbg));

		ret = crypto_skcipher_setkey(drbg->ctr_handle, drbg->C,
					     drbg_keylen(drbg));
		अगर (ret)
			जाओ out;
	पूर्ण

	/* 10.2.1.3.2 step 2 and 10.2.1.4.2 step 2 */
	अगर (seed) अणु
		ret = drbg_ctr_df(drbg, df_data, drbg_statelen(drbg), seed);
		अगर (ret)
			जाओ out;
	पूर्ण

	ret = drbg_kcapi_sym_ctr(drbg, df_data, drbg_statelen(drbg),
				 temp, drbg_statelen(drbg));
	अगर (ret)
		वापस ret;

	/* 10.2.1.2 step 5 */
	ret = crypto_skcipher_setkey(drbg->ctr_handle, temp,
				     drbg_keylen(drbg));
	अगर (ret)
		जाओ out;
	/* 10.2.1.2 step 6 */
	स_नकल(drbg->V, temp + drbg_keylen(drbg), drbg_blocklen(drbg));
	/* See above: increment counter by one to compensate timing of CTR op */
	crypto_inc(drbg->V, drbg_blocklen(drbg));
	ret = 0;

out:
	स_रखो(temp, 0, drbg_statelen(drbg) + drbg_blocklen(drbg));
	अगर (2 != reseed)
		स_रखो(df_data, 0, drbg_statelen(drbg));
	वापस ret;
पूर्ण

/*
 * scratchpad use: drbg_ctr_update is called independently from
 * drbg_ctr_extract_bytes. Thereक्रमe, the scratchpad is reused
 */
/* Generate function of CTR DRBG as defined in 10.2.1.5.2 */
अटल पूर्णांक drbg_ctr_generate(काष्ठा drbg_state *drbg,
			     अचिन्हित अक्षर *buf, अचिन्हित पूर्णांक buflen,
			     काष्ठा list_head *addtl)
अणु
	पूर्णांक ret;
	पूर्णांक len = min_t(पूर्णांक, buflen, पूर्णांक_उच्च);

	/* 10.2.1.5.2 step 2 */
	अगर (addtl && !list_empty(addtl)) अणु
		ret = drbg_ctr_update(drbg, addtl, 2);
		अगर (ret)
			वापस 0;
	पूर्ण

	/* 10.2.1.5.2 step 4.1 */
	ret = drbg_kcapi_sym_ctr(drbg, शून्य, 0, buf, len);
	अगर (ret)
		वापस ret;

	/* 10.2.1.5.2 step 6 */
	ret = drbg_ctr_update(drbg, शून्य, 3);
	अगर (ret)
		len = ret;

	वापस len;
पूर्ण

अटल स्थिर काष्ठा drbg_state_ops drbg_ctr_ops = अणु
	.update		= drbg_ctr_update,
	.generate	= drbg_ctr_generate,
	.crypto_init	= drbg_init_sym_kernel,
	.crypto_fini	= drbg_fini_sym_kernel,
पूर्ण;
#पूर्ण_अगर /* CONFIG_CRYPTO_DRBG_CTR */

/******************************************************************
 * HMAC DRBG callback functions
 ******************************************************************/

#अगर defined(CONFIG_CRYPTO_DRBG_HASH) || defined(CONFIG_CRYPTO_DRBG_HMAC)
अटल पूर्णांक drbg_kcapi_hash(काष्ठा drbg_state *drbg, अचिन्हित अक्षर *outval,
			   स्थिर काष्ठा list_head *in);
अटल व्योम drbg_kcapi_hmacsetkey(काष्ठा drbg_state *drbg,
				  स्थिर अचिन्हित अक्षर *key);
अटल पूर्णांक drbg_init_hash_kernel(काष्ठा drbg_state *drbg);
अटल पूर्णांक drbg_fini_hash_kernel(काष्ठा drbg_state *drbg);
#पूर्ण_अगर /* (CONFIG_CRYPTO_DRBG_HASH || CONFIG_CRYPTO_DRBG_HMAC) */

#अगर_घोषित CONFIG_CRYPTO_DRBG_HMAC
#घोषणा CRYPTO_DRBG_HMAC_STRING "HMAC "
MODULE_ALIAS_CRYPTO("drbg_pr_hmac_sha512");
MODULE_ALIAS_CRYPTO("drbg_nopr_hmac_sha512");
MODULE_ALIAS_CRYPTO("drbg_pr_hmac_sha384");
MODULE_ALIAS_CRYPTO("drbg_nopr_hmac_sha384");
MODULE_ALIAS_CRYPTO("drbg_pr_hmac_sha256");
MODULE_ALIAS_CRYPTO("drbg_nopr_hmac_sha256");
MODULE_ALIAS_CRYPTO("drbg_pr_hmac_sha1");
MODULE_ALIAS_CRYPTO("drbg_nopr_hmac_sha1");

/* update function of HMAC DRBG as defined in 10.1.2.2 */
अटल पूर्णांक drbg_hmac_update(काष्ठा drbg_state *drbg, काष्ठा list_head *seed,
			    पूर्णांक reseed)
अणु
	पूर्णांक ret = -EFAULT;
	पूर्णांक i = 0;
	काष्ठा drbg_string seed1, seed2, vdata;
	LIST_HEAD(seedlist);
	LIST_HEAD(vdatalist);

	अगर (!reseed) अणु
		/* 10.1.2.3 step 2 -- स_रखो(0) of C is implicit with kzalloc */
		स_रखो(drbg->V, 1, drbg_statelen(drbg));
		drbg_kcapi_hmacsetkey(drbg, drbg->C);
	पूर्ण

	drbg_string_fill(&seed1, drbg->V, drbg_statelen(drbg));
	list_add_tail(&seed1.list, &seedlist);
	/* buffer of seed2 will be filled in क्रम loop below with one byte */
	drbg_string_fill(&seed2, शून्य, 1);
	list_add_tail(&seed2.list, &seedlist);
	/* input data of seed is allowed to be शून्य at this poपूर्णांक */
	अगर (seed)
		list_splice_tail(seed, &seedlist);

	drbg_string_fill(&vdata, drbg->V, drbg_statelen(drbg));
	list_add_tail(&vdata.list, &vdatalist);
	क्रम (i = 2; 0 < i; i--) अणु
		/* first round uses 0x0, second 0x1 */
		अचिन्हित अक्षर prefix = DRBG_PREFIX0;
		अगर (1 == i)
			prefix = DRBG_PREFIX1;
		/* 10.1.2.2 step 1 and 4 -- concatenation and HMAC क्रम key */
		seed2.buf = &prefix;
		ret = drbg_kcapi_hash(drbg, drbg->C, &seedlist);
		अगर (ret)
			वापस ret;
		drbg_kcapi_hmacsetkey(drbg, drbg->C);

		/* 10.1.2.2 step 2 and 5 -- HMAC क्रम V */
		ret = drbg_kcapi_hash(drbg, drbg->V, &vdatalist);
		अगर (ret)
			वापस ret;

		/* 10.1.2.2 step 3 */
		अगर (!seed)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/* generate function of HMAC DRBG as defined in 10.1.2.5 */
अटल पूर्णांक drbg_hmac_generate(काष्ठा drbg_state *drbg,
			      अचिन्हित अक्षर *buf,
			      अचिन्हित पूर्णांक buflen,
			      काष्ठा list_head *addtl)
अणु
	पूर्णांक len = 0;
	पूर्णांक ret = 0;
	काष्ठा drbg_string data;
	LIST_HEAD(datalist);

	/* 10.1.2.5 step 2 */
	अगर (addtl && !list_empty(addtl)) अणु
		ret = drbg_hmac_update(drbg, addtl, 1);
		अगर (ret)
			वापस ret;
	पूर्ण

	drbg_string_fill(&data, drbg->V, drbg_statelen(drbg));
	list_add_tail(&data.list, &datalist);
	जबतक (len < buflen) अणु
		अचिन्हित पूर्णांक outlen = 0;
		/* 10.1.2.5 step 4.1 */
		ret = drbg_kcapi_hash(drbg, drbg->V, &datalist);
		अगर (ret)
			वापस ret;
		outlen = (drbg_blocklen(drbg) < (buflen - len)) ?
			  drbg_blocklen(drbg) : (buflen - len);

		/* 10.1.2.5 step 4.2 */
		स_नकल(buf + len, drbg->V, outlen);
		len += outlen;
	पूर्ण

	/* 10.1.2.5 step 6 */
	अगर (addtl && !list_empty(addtl))
		ret = drbg_hmac_update(drbg, addtl, 1);
	अन्यथा
		ret = drbg_hmac_update(drbg, शून्य, 1);
	अगर (ret)
		वापस ret;

	वापस len;
पूर्ण

अटल स्थिर काष्ठा drbg_state_ops drbg_hmac_ops = अणु
	.update		= drbg_hmac_update,
	.generate	= drbg_hmac_generate,
	.crypto_init	= drbg_init_hash_kernel,
	.crypto_fini	= drbg_fini_hash_kernel,
पूर्ण;
#पूर्ण_अगर /* CONFIG_CRYPTO_DRBG_HMAC */

/******************************************************************
 * Hash DRBG callback functions
 ******************************************************************/

#अगर_घोषित CONFIG_CRYPTO_DRBG_HASH
#घोषणा CRYPTO_DRBG_HASH_STRING "HASH "
MODULE_ALIAS_CRYPTO("drbg_pr_sha512");
MODULE_ALIAS_CRYPTO("drbg_nopr_sha512");
MODULE_ALIAS_CRYPTO("drbg_pr_sha384");
MODULE_ALIAS_CRYPTO("drbg_nopr_sha384");
MODULE_ALIAS_CRYPTO("drbg_pr_sha256");
MODULE_ALIAS_CRYPTO("drbg_nopr_sha256");
MODULE_ALIAS_CRYPTO("drbg_pr_sha1");
MODULE_ALIAS_CRYPTO("drbg_nopr_sha1");

/*
 * Increment buffer
 *
 * @dst buffer to increment
 * @add value to add
 */
अटल अंतरभूत व्योम drbg_add_buf(अचिन्हित अक्षर *dst, माप_प्रकार dstlen,
				स्थिर अचिन्हित अक्षर *add, माप_प्रकार addlen)
अणु
	/* implied: dstlen > addlen */
	अचिन्हित अक्षर *dstptr;
	स्थिर अचिन्हित अक्षर *addptr;
	अचिन्हित पूर्णांक reमुख्यder = 0;
	माप_प्रकार len = addlen;

	dstptr = dst + (dstlen-1);
	addptr = add + (addlen-1);
	जबतक (len) अणु
		reमुख्यder += *dstptr + *addptr;
		*dstptr = reमुख्यder & 0xff;
		reमुख्यder >>= 8;
		len--; dstptr--; addptr--;
	पूर्ण
	len = dstlen - addlen;
	जबतक (len && reमुख्यder > 0) अणु
		reमुख्यder = *dstptr + 1;
		*dstptr = reमुख्यder & 0xff;
		reमुख्यder >>= 8;
		len--; dstptr--;
	पूर्ण
पूर्ण

/*
 * scratchpad usage: as drbg_hash_update and drbg_hash_df are used
 * पूर्णांकerlinked, the scratchpad is used as follows:
 * drbg_hash_update
 *	start: drbg->scratchpad
 *	length: drbg_statelen(drbg)
 * drbg_hash_df:
 *	start: drbg->scratchpad + drbg_statelen(drbg)
 *	length: drbg_blocklen(drbg)
 *
 * drbg_hash_process_addtl uses the scratchpad, but fully completes
 * beक्रमe either of the functions mentioned beक्रमe are invoked. Thereक्रमe,
 * drbg_hash_process_addtl करोes not need to be specअगरically considered.
 */

/* Derivation Function क्रम Hash DRBG as defined in 10.4.1 */
अटल पूर्णांक drbg_hash_df(काष्ठा drbg_state *drbg,
			अचिन्हित अक्षर *outval, माप_प्रकार outlen,
			काष्ठा list_head *entropylist)
अणु
	पूर्णांक ret = 0;
	माप_प्रकार len = 0;
	अचिन्हित अक्षर input[5];
	अचिन्हित अक्षर *पंचांगp = drbg->scratchpad + drbg_statelen(drbg);
	काष्ठा drbg_string data;

	/* 10.4.1 step 3 */
	input[0] = 1;
	drbg_cpu_to_be32((outlen * 8), &input[1]);

	/* 10.4.1 step 4.1 -- concatenation of data क्रम input पूर्णांकo hash */
	drbg_string_fill(&data, input, 5);
	list_add(&data.list, entropylist);

	/* 10.4.1 step 4 */
	जबतक (len < outlen) अणु
		लघु blocklen = 0;
		/* 10.4.1 step 4.1 */
		ret = drbg_kcapi_hash(drbg, पंचांगp, entropylist);
		अगर (ret)
			जाओ out;
		/* 10.4.1 step 4.2 */
		input[0]++;
		blocklen = (drbg_blocklen(drbg) < (outlen - len)) ?
			    drbg_blocklen(drbg) : (outlen - len);
		स_नकल(outval + len, पंचांगp, blocklen);
		len += blocklen;
	पूर्ण

out:
	स_रखो(पंचांगp, 0, drbg_blocklen(drbg));
	वापस ret;
पूर्ण

/* update function क्रम Hash DRBG as defined in 10.1.1.2 / 10.1.1.3 */
अटल पूर्णांक drbg_hash_update(काष्ठा drbg_state *drbg, काष्ठा list_head *seed,
			    पूर्णांक reseed)
अणु
	पूर्णांक ret = 0;
	काष्ठा drbg_string data1, data2;
	LIST_HEAD(datalist);
	LIST_HEAD(datalist2);
	अचिन्हित अक्षर *V = drbg->scratchpad;
	अचिन्हित अक्षर prefix = DRBG_PREFIX1;

	अगर (!seed)
		वापस -EINVAL;

	अगर (reseed) अणु
		/* 10.1.1.3 step 1 */
		स_नकल(V, drbg->V, drbg_statelen(drbg));
		drbg_string_fill(&data1, &prefix, 1);
		list_add_tail(&data1.list, &datalist);
		drbg_string_fill(&data2, V, drbg_statelen(drbg));
		list_add_tail(&data2.list, &datalist);
	पूर्ण
	list_splice_tail(seed, &datalist);

	/* 10.1.1.2 / 10.1.1.3 step 2 and 3 */
	ret = drbg_hash_df(drbg, drbg->V, drbg_statelen(drbg), &datalist);
	अगर (ret)
		जाओ out;

	/* 10.1.1.2 / 10.1.1.3 step 4  */
	prefix = DRBG_PREFIX0;
	drbg_string_fill(&data1, &prefix, 1);
	list_add_tail(&data1.list, &datalist2);
	drbg_string_fill(&data2, drbg->V, drbg_statelen(drbg));
	list_add_tail(&data2.list, &datalist2);
	/* 10.1.1.2 / 10.1.1.3 step 4 */
	ret = drbg_hash_df(drbg, drbg->C, drbg_statelen(drbg), &datalist2);

out:
	स_रखो(drbg->scratchpad, 0, drbg_statelen(drbg));
	वापस ret;
पूर्ण

/* processing of additional inक्रमmation string क्रम Hash DRBG */
अटल पूर्णांक drbg_hash_process_addtl(काष्ठा drbg_state *drbg,
				   काष्ठा list_head *addtl)
अणु
	पूर्णांक ret = 0;
	काष्ठा drbg_string data1, data2;
	LIST_HEAD(datalist);
	अचिन्हित अक्षर prefix = DRBG_PREFIX2;

	/* 10.1.1.4 step 2 */
	अगर (!addtl || list_empty(addtl))
		वापस 0;

	/* 10.1.1.4 step 2a */
	drbg_string_fill(&data1, &prefix, 1);
	drbg_string_fill(&data2, drbg->V, drbg_statelen(drbg));
	list_add_tail(&data1.list, &datalist);
	list_add_tail(&data2.list, &datalist);
	list_splice_tail(addtl, &datalist);
	ret = drbg_kcapi_hash(drbg, drbg->scratchpad, &datalist);
	अगर (ret)
		जाओ out;

	/* 10.1.1.4 step 2b */
	drbg_add_buf(drbg->V, drbg_statelen(drbg),
		     drbg->scratchpad, drbg_blocklen(drbg));

out:
	स_रखो(drbg->scratchpad, 0, drbg_blocklen(drbg));
	वापस ret;
पूर्ण

/* Hashgen defined in 10.1.1.4 */
अटल पूर्णांक drbg_hash_hashgen(काष्ठा drbg_state *drbg,
			     अचिन्हित अक्षर *buf,
			     अचिन्हित पूर्णांक buflen)
अणु
	पूर्णांक len = 0;
	पूर्णांक ret = 0;
	अचिन्हित अक्षर *src = drbg->scratchpad;
	अचिन्हित अक्षर *dst = drbg->scratchpad + drbg_statelen(drbg);
	काष्ठा drbg_string data;
	LIST_HEAD(datalist);

	/* 10.1.1.4 step hashgen 2 */
	स_नकल(src, drbg->V, drbg_statelen(drbg));

	drbg_string_fill(&data, src, drbg_statelen(drbg));
	list_add_tail(&data.list, &datalist);
	जबतक (len < buflen) अणु
		अचिन्हित पूर्णांक outlen = 0;
		/* 10.1.1.4 step hashgen 4.1 */
		ret = drbg_kcapi_hash(drbg, dst, &datalist);
		अगर (ret) अणु
			len = ret;
			जाओ out;
		पूर्ण
		outlen = (drbg_blocklen(drbg) < (buflen - len)) ?
			  drbg_blocklen(drbg) : (buflen - len);
		/* 10.1.1.4 step hashgen 4.2 */
		स_नकल(buf + len, dst, outlen);
		len += outlen;
		/* 10.1.1.4 hashgen step 4.3 */
		अगर (len < buflen)
			crypto_inc(src, drbg_statelen(drbg));
	पूर्ण

out:
	स_रखो(drbg->scratchpad, 0,
	       (drbg_statelen(drbg) + drbg_blocklen(drbg)));
	वापस len;
पूर्ण

/* generate function क्रम Hash DRBG as defined in  10.1.1.4 */
अटल पूर्णांक drbg_hash_generate(काष्ठा drbg_state *drbg,
			      अचिन्हित अक्षर *buf, अचिन्हित पूर्णांक buflen,
			      काष्ठा list_head *addtl)
अणु
	पूर्णांक len = 0;
	पूर्णांक ret = 0;
	जोड़ अणु
		अचिन्हित अक्षर req[8];
		__be64 req_पूर्णांक;
	पूर्ण u;
	अचिन्हित अक्षर prefix = DRBG_PREFIX3;
	काष्ठा drbg_string data1, data2;
	LIST_HEAD(datalist);

	/* 10.1.1.4 step 2 */
	ret = drbg_hash_process_addtl(drbg, addtl);
	अगर (ret)
		वापस ret;
	/* 10.1.1.4 step 3 */
	len = drbg_hash_hashgen(drbg, buf, buflen);

	/* this is the value H as करोcumented in 10.1.1.4 */
	/* 10.1.1.4 step 4 */
	drbg_string_fill(&data1, &prefix, 1);
	list_add_tail(&data1.list, &datalist);
	drbg_string_fill(&data2, drbg->V, drbg_statelen(drbg));
	list_add_tail(&data2.list, &datalist);
	ret = drbg_kcapi_hash(drbg, drbg->scratchpad, &datalist);
	अगर (ret) अणु
		len = ret;
		जाओ out;
	पूर्ण

	/* 10.1.1.4 step 5 */
	drbg_add_buf(drbg->V, drbg_statelen(drbg),
		     drbg->scratchpad, drbg_blocklen(drbg));
	drbg_add_buf(drbg->V, drbg_statelen(drbg),
		     drbg->C, drbg_statelen(drbg));
	u.req_पूर्णांक = cpu_to_be64(drbg->reseed_ctr);
	drbg_add_buf(drbg->V, drbg_statelen(drbg), u.req, 8);

out:
	स_रखो(drbg->scratchpad, 0, drbg_blocklen(drbg));
	वापस len;
पूर्ण

/*
 * scratchpad usage: as update and generate are used isolated, both
 * can use the scratchpad
 */
अटल स्थिर काष्ठा drbg_state_ops drbg_hash_ops = अणु
	.update		= drbg_hash_update,
	.generate	= drbg_hash_generate,
	.crypto_init	= drbg_init_hash_kernel,
	.crypto_fini	= drbg_fini_hash_kernel,
पूर्ण;
#पूर्ण_अगर /* CONFIG_CRYPTO_DRBG_HASH */

/******************************************************************
 * Functions common क्रम DRBG implementations
 ******************************************************************/

अटल अंतरभूत पूर्णांक __drbg_seed(काष्ठा drbg_state *drbg, काष्ठा list_head *seed,
			      पूर्णांक reseed)
अणु
	पूर्णांक ret = drbg->d_ops->update(drbg, seed, reseed);

	अगर (ret)
		वापस ret;

	drbg->seeded = true;
	/* 10.1.1.2 / 10.1.1.3 step 5 */
	drbg->reseed_ctr = 1;

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक drbg_get_अक्रमom_bytes(काष्ठा drbg_state *drbg,
					अचिन्हित अक्षर *entropy,
					अचिन्हित पूर्णांक entropylen)
अणु
	पूर्णांक ret;

	करो अणु
		get_अक्रमom_bytes(entropy, entropylen);
		ret = drbg_fips_continuous_test(drbg, entropy);
		अगर (ret && ret != -EAGAIN)
			वापस ret;
	पूर्ण जबतक (ret);

	वापस 0;
पूर्ण

अटल व्योम drbg_async_seed(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा drbg_string data;
	LIST_HEAD(seedlist);
	काष्ठा drbg_state *drbg = container_of(work, काष्ठा drbg_state,
					       seed_work);
	अचिन्हित पूर्णांक entropylen = drbg_sec_strength(drbg->core->flags);
	अचिन्हित अक्षर entropy[32];
	पूर्णांक ret;

	BUG_ON(!entropylen);
	BUG_ON(entropylen > माप(entropy));

	drbg_string_fill(&data, entropy, entropylen);
	list_add_tail(&data.list, &seedlist);

	mutex_lock(&drbg->drbg_mutex);

	ret = drbg_get_अक्रमom_bytes(drbg, entropy, entropylen);
	अगर (ret)
		जाओ unlock;

	/* Set seeded to false so that अगर __drbg_seed fails the
	 * next generate call will trigger a reseed.
	 */
	drbg->seeded = false;

	__drbg_seed(drbg, &seedlist, true);

	अगर (drbg->seeded)
		drbg->reseed_threshold = drbg_max_requests(drbg);

unlock:
	mutex_unlock(&drbg->drbg_mutex);

	memzero_explicit(entropy, entropylen);
पूर्ण

/*
 * Seeding or reseeding of the DRBG
 *
 * @drbg: DRBG state काष्ठा
 * @pers: personalization / additional inक्रमmation buffer
 * @reseed: 0 क्रम initial seed process, 1 क्रम reseeding
 *
 * वापस:
 *	0 on success
 *	error value otherwise
 */
अटल पूर्णांक drbg_seed(काष्ठा drbg_state *drbg, काष्ठा drbg_string *pers,
		     bool reseed)
अणु
	पूर्णांक ret;
	अचिन्हित अक्षर entropy[((32 + 16) * 2)];
	अचिन्हित पूर्णांक entropylen = drbg_sec_strength(drbg->core->flags);
	काष्ठा drbg_string data1;
	LIST_HEAD(seedlist);

	/* 9.1 / 9.2 / 9.3.1 step 3 */
	अगर (pers && pers->len > (drbg_max_addtl(drbg))) अणु
		pr_devel("DRBG: personalization string too long %zu\n",
			 pers->len);
		वापस -EINVAL;
	पूर्ण

	अगर (list_empty(&drbg->test_data.list)) अणु
		drbg_string_fill(&data1, drbg->test_data.buf,
				 drbg->test_data.len);
		pr_devel("DRBG: using test entropy\n");
	पूर्ण अन्यथा अणु
		/*
		 * Gather entropy equal to the security strength of the DRBG.
		 * With a derivation function, a nonce is required in addition
		 * to the entropy. A nonce must be at least 1/2 of the security
		 * strength of the DRBG in size. Thus, entropy + nonce is 3/2
		 * of the strength. The consideration of a nonce is only
		 * applicable during initial seeding.
		 */
		BUG_ON(!entropylen);
		अगर (!reseed)
			entropylen = ((entropylen + 1) / 2) * 3;
		BUG_ON((entropylen * 2) > माप(entropy));

		/* Get seed from in-kernel /dev/uअक्रमom */
		ret = drbg_get_अक्रमom_bytes(drbg, entropy, entropylen);
		अगर (ret)
			जाओ out;

		अगर (!drbg->jent) अणु
			drbg_string_fill(&data1, entropy, entropylen);
			pr_devel("DRBG: (re)seeding with %u bytes of entropy\n",
				 entropylen);
		पूर्ण अन्यथा अणु
			/* Get seed from Jitter RNG */
			ret = crypto_rng_get_bytes(drbg->jent,
						   entropy + entropylen,
						   entropylen);
			अगर (ret) अणु
				pr_devel("DRBG: jent failed with %d\n", ret);

				/*
				 * Do not treat the transient failure of the
				 * Jitter RNG as an error that needs to be
				 * reported. The combined number of the
				 * maximum reseed threshold बार the maximum
				 * number of Jitter RNG transient errors is
				 * less than the reseed threshold required by
				 * SP800-90A allowing us to treat the
				 * transient errors as such.
				 *
				 * However, we mandate that at least the first
				 * seeding operation must succeed with the
				 * Jitter RNG.
				 */
				अगर (!reseed || ret != -EAGAIN)
					जाओ out;
			पूर्ण

			drbg_string_fill(&data1, entropy, entropylen * 2);
			pr_devel("DRBG: (re)seeding with %u bytes of entropy\n",
				 entropylen * 2);
		पूर्ण
	पूर्ण
	list_add_tail(&data1.list, &seedlist);

	/*
	 * concatenation of entropy with personalization str / addtl input)
	 * the variable pers is directly handed in by the caller, so check its
	 * contents whether it is appropriate
	 */
	अगर (pers && pers->buf && 0 < pers->len) अणु
		list_add_tail(&pers->list, &seedlist);
		pr_devel("DRBG: using personalization string\n");
	पूर्ण

	अगर (!reseed) अणु
		स_रखो(drbg->V, 0, drbg_statelen(drbg));
		स_रखो(drbg->C, 0, drbg_statelen(drbg));
	पूर्ण

	ret = __drbg_seed(drbg, &seedlist, reseed);

out:
	memzero_explicit(entropy, entropylen * 2);

	वापस ret;
पूर्ण

/* Free all subकाष्ठाures in a DRBG state without the DRBG state काष्ठाure */
अटल अंतरभूत व्योम drbg_dealloc_state(काष्ठा drbg_state *drbg)
अणु
	अगर (!drbg)
		वापस;
	kमुक्त_sensitive(drbg->Vbuf);
	drbg->Vbuf = शून्य;
	drbg->V = शून्य;
	kमुक्त_sensitive(drbg->Cbuf);
	drbg->Cbuf = शून्य;
	drbg->C = शून्य;
	kमुक्त_sensitive(drbg->scratchpadbuf);
	drbg->scratchpadbuf = शून्य;
	drbg->reseed_ctr = 0;
	drbg->d_ops = शून्य;
	drbg->core = शून्य;
	अगर (IS_ENABLED(CONFIG_CRYPTO_FIPS)) अणु
		kमुक्त_sensitive(drbg->prev);
		drbg->prev = शून्य;
		drbg->fips_primed = false;
	पूर्ण
पूर्ण

/*
 * Allocate all sub-काष्ठाures क्रम a DRBG state.
 * The DRBG state काष्ठाure must alपढ़ोy be allocated.
 */
अटल अंतरभूत पूर्णांक drbg_alloc_state(काष्ठा drbg_state *drbg)
अणु
	पूर्णांक ret = -ENOMEM;
	अचिन्हित पूर्णांक sb_size = 0;

	चयन (drbg->core->flags & DRBG_TYPE_MASK) अणु
#अगर_घोषित CONFIG_CRYPTO_DRBG_HMAC
	हाल DRBG_HMAC:
		drbg->d_ops = &drbg_hmac_ops;
		अवरोध;
#पूर्ण_अगर /* CONFIG_CRYPTO_DRBG_HMAC */
#अगर_घोषित CONFIG_CRYPTO_DRBG_HASH
	हाल DRBG_HASH:
		drbg->d_ops = &drbg_hash_ops;
		अवरोध;
#पूर्ण_अगर /* CONFIG_CRYPTO_DRBG_HASH */
#अगर_घोषित CONFIG_CRYPTO_DRBG_CTR
	हाल DRBG_CTR:
		drbg->d_ops = &drbg_ctr_ops;
		अवरोध;
#पूर्ण_अगर /* CONFIG_CRYPTO_DRBG_CTR */
	शेष:
		ret = -EOPNOTSUPP;
		जाओ err;
	पूर्ण

	ret = drbg->d_ops->crypto_init(drbg);
	अगर (ret < 0)
		जाओ err;

	drbg->Vbuf = kदो_स्मृति(drbg_statelen(drbg) + ret, GFP_KERNEL);
	अगर (!drbg->Vbuf) अणु
		ret = -ENOMEM;
		जाओ fini;
	पूर्ण
	drbg->V = PTR_ALIGN(drbg->Vbuf, ret + 1);
	drbg->Cbuf = kदो_स्मृति(drbg_statelen(drbg) + ret, GFP_KERNEL);
	अगर (!drbg->Cbuf) अणु
		ret = -ENOMEM;
		जाओ fini;
	पूर्ण
	drbg->C = PTR_ALIGN(drbg->Cbuf, ret + 1);
	/* scratchpad is only generated क्रम CTR and Hash */
	अगर (drbg->core->flags & DRBG_HMAC)
		sb_size = 0;
	अन्यथा अगर (drbg->core->flags & DRBG_CTR)
		sb_size = drbg_statelen(drbg) + drbg_blocklen(drbg) + /* temp */
			  drbg_statelen(drbg) +	/* df_data */
			  drbg_blocklen(drbg) +	/* pad */
			  drbg_blocklen(drbg) +	/* iv */
			  drbg_statelen(drbg) + drbg_blocklen(drbg); /* temp */
	अन्यथा
		sb_size = drbg_statelen(drbg) + drbg_blocklen(drbg);

	अगर (0 < sb_size) अणु
		drbg->scratchpadbuf = kzalloc(sb_size + ret, GFP_KERNEL);
		अगर (!drbg->scratchpadbuf) अणु
			ret = -ENOMEM;
			जाओ fini;
		पूर्ण
		drbg->scratchpad = PTR_ALIGN(drbg->scratchpadbuf, ret + 1);
	पूर्ण

	अगर (IS_ENABLED(CONFIG_CRYPTO_FIPS)) अणु
		drbg->prev = kzalloc(drbg_sec_strength(drbg->core->flags),
				     GFP_KERNEL);
		अगर (!drbg->prev) अणु
			ret = -ENOMEM;
			जाओ fini;
		पूर्ण
		drbg->fips_primed = false;
	पूर्ण

	वापस 0;

fini:
	drbg->d_ops->crypto_fini(drbg);
err:
	drbg_dealloc_state(drbg);
	वापस ret;
पूर्ण

/*************************************************************************
 * DRBG पूर्णांकerface functions
 *************************************************************************/

/*
 * DRBG generate function as required by SP800-90A - this function
 * generates अक्रमom numbers
 *
 * @drbg DRBG state handle
 * @buf Buffer where to store the अक्रमom numbers -- the buffer must alपढ़ोy
 *      be pre-allocated by caller
 * @buflen Length of output buffer - this value defines the number of अक्रमom
 *	   bytes pulled from DRBG
 * @addtl Additional input that is mixed पूर्णांकo state, may be शून्य -- note
 *	  the entropy is pulled by the DRBG पूर्णांकernally unconditionally
 *	  as defined in SP800-90A. The additional input is mixed पूर्णांकo
 *	  the state in addition to the pulled entropy.
 *
 * वापस: 0 when all bytes are generated; < 0 in हाल of an error
 */
अटल पूर्णांक drbg_generate(काष्ठा drbg_state *drbg,
			 अचिन्हित अक्षर *buf, अचिन्हित पूर्णांक buflen,
			 काष्ठा drbg_string *addtl)
अणु
	पूर्णांक len = 0;
	LIST_HEAD(addtllist);

	अगर (!drbg->core) अणु
		pr_devel("DRBG: not yet seeded\n");
		वापस -EINVAL;
	पूर्ण
	अगर (0 == buflen || !buf) अणु
		pr_devel("DRBG: no output buffer provided\n");
		वापस -EINVAL;
	पूर्ण
	अगर (addtl && शून्य == addtl->buf && 0 < addtl->len) अणु
		pr_devel("DRBG: wrong format of additional information\n");
		वापस -EINVAL;
	पूर्ण

	/* 9.3.1 step 2 */
	len = -EINVAL;
	अगर (buflen > (drbg_max_request_bytes(drbg))) अणु
		pr_devel("DRBG: requested random numbers too large %u\n",
			 buflen);
		जाओ err;
	पूर्ण

	/* 9.3.1 step 3 is implicit with the chosen DRBG */

	/* 9.3.1 step 4 */
	अगर (addtl && addtl->len > (drbg_max_addtl(drbg))) अणु
		pr_devel("DRBG: additional information string too long %zu\n",
			 addtl->len);
		जाओ err;
	पूर्ण
	/* 9.3.1 step 5 is implicit with the chosen DRBG */

	/*
	 * 9.3.1 step 6 and 9 supplemented by 9.3.2 step c is implemented
	 * here. The spec is a bit convoluted here, we make it simpler.
	 */
	अगर (drbg->reseed_threshold < drbg->reseed_ctr)
		drbg->seeded = false;

	अगर (drbg->pr || !drbg->seeded) अणु
		pr_devel("DRBG: reseeding before generation (prediction "
			 "resistance: %s, state %s)\n",
			 drbg->pr ? "true" : "false",
			 drbg->seeded ? "seeded" : "unseeded");
		/* 9.3.1 steps 7.1 through 7.3 */
		len = drbg_seed(drbg, addtl, true);
		अगर (len)
			जाओ err;
		/* 9.3.1 step 7.4 */
		addtl = शून्य;
	पूर्ण

	अगर (addtl && 0 < addtl->len)
		list_add_tail(&addtl->list, &addtllist);
	/* 9.3.1 step 8 and 10 */
	len = drbg->d_ops->generate(drbg, buf, buflen, &addtllist);

	/* 10.1.1.4 step 6, 10.1.2.5 step 7, 10.2.1.5.2 step 7 */
	drbg->reseed_ctr++;
	अगर (0 >= len)
		जाओ err;

	/*
	 * Section 11.3.3 requires to re-perक्रमm self tests after some
	 * generated अक्रमom numbers. The chosen value after which self
	 * test is perक्रमmed is arbitrary, but it should be reasonable.
	 * However, we करो not perक्रमm the self tests because of the following
	 * reasons: it is mathematically impossible that the initial self tests
	 * were successfully and the following are not. If the initial would
	 * pass and the following would not, the kernel पूर्णांकegrity is violated.
	 * In this हाल, the entire kernel operation is questionable and it
	 * is unlikely that the पूर्णांकegrity violation only affects the
	 * correct operation of the DRBG.
	 *
	 * Albeit the following code is commented out, it is provided in
	 * हाल somebody has a need to implement the test of 11.3.3.
	 */
#अगर 0
	अगर (drbg->reseed_ctr && !(drbg->reseed_ctr % 4096)) अणु
		पूर्णांक err = 0;
		pr_devel("DRBG: start to perform self test\n");
		अगर (drbg->core->flags & DRBG_HMAC)
			err = alg_test("drbg_pr_hmac_sha256",
				       "drbg_pr_hmac_sha256", 0, 0);
		अन्यथा अगर (drbg->core->flags & DRBG_CTR)
			err = alg_test("drbg_pr_ctr_aes128",
				       "drbg_pr_ctr_aes128", 0, 0);
		अन्यथा
			err = alg_test("drbg_pr_sha256",
				       "drbg_pr_sha256", 0, 0);
		अगर (err) अणु
			pr_err("DRBG: periodical self test failed\n");
			/*
			 * uninstantiate implies that from now on, only errors
			 * are वापसed when reusing this DRBG cipher handle
			 */
			drbg_uninstantiate(drbg);
			वापस 0;
		पूर्ण अन्यथा अणु
			pr_devel("DRBG: self test successful\n");
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	/*
	 * All operations were successful, वापस 0 as mandated by
	 * the kernel crypto API पूर्णांकerface.
	 */
	len = 0;
err:
	वापस len;
पूर्ण

/*
 * Wrapper around drbg_generate which can pull arbitrary दीर्घ strings
 * from the DRBG without hitting the maximum request limitation.
 *
 * Parameters: see drbg_generate
 * Return codes: see drbg_generate -- अगर one drbg_generate request fails,
 *		 the entire drbg_generate_दीर्घ request fails
 */
अटल पूर्णांक drbg_generate_दीर्घ(काष्ठा drbg_state *drbg,
			      अचिन्हित अक्षर *buf, अचिन्हित पूर्णांक buflen,
			      काष्ठा drbg_string *addtl)
अणु
	अचिन्हित पूर्णांक len = 0;
	अचिन्हित पूर्णांक slice = 0;
	करो अणु
		पूर्णांक err = 0;
		अचिन्हित पूर्णांक chunk = 0;
		slice = ((buflen - len) / drbg_max_request_bytes(drbg));
		chunk = slice ? drbg_max_request_bytes(drbg) : (buflen - len);
		mutex_lock(&drbg->drbg_mutex);
		err = drbg_generate(drbg, buf + len, chunk, addtl);
		mutex_unlock(&drbg->drbg_mutex);
		अगर (0 > err)
			वापस err;
		len += chunk;
	पूर्ण जबतक (slice > 0 && (len < buflen));
	वापस 0;
पूर्ण

अटल व्योम drbg_schedule_async_seed(काष्ठा अक्रमom_पढ़ोy_callback *rdy)
अणु
	काष्ठा drbg_state *drbg = container_of(rdy, काष्ठा drbg_state,
					       अक्रमom_पढ़ोy);

	schedule_work(&drbg->seed_work);
पूर्ण

अटल पूर्णांक drbg_prepare_hrng(काष्ठा drbg_state *drbg)
अणु
	पूर्णांक err;

	/* We करो not need an HRNG in test mode. */
	अगर (list_empty(&drbg->test_data.list))
		वापस 0;

	drbg->jent = crypto_alloc_rng("jitterentropy_rng", 0, 0);

	INIT_WORK(&drbg->seed_work, drbg_async_seed);

	drbg->अक्रमom_पढ़ोy.owner = THIS_MODULE;
	drbg->अक्रमom_पढ़ोy.func = drbg_schedule_async_seed;

	err = add_अक्रमom_पढ़ोy_callback(&drbg->अक्रमom_पढ़ोy);

	चयन (err) अणु
	हाल 0:
		अवरोध;

	हाल -EALREADY:
		err = 0;
		fallthrough;

	शेष:
		drbg->अक्रमom_पढ़ोy.func = शून्य;
		वापस err;
	पूर्ण

	/*
	 * Require frequent reseeds until the seed source is fully
	 * initialized.
	 */
	drbg->reseed_threshold = 50;

	वापस err;
पूर्ण

/*
 * DRBG instantiation function as required by SP800-90A - this function
 * sets up the DRBG handle, perक्रमms the initial seeding and all sanity
 * checks required by SP800-90A
 *
 * @drbg memory of state -- अगर शून्य, new memory is allocated
 * @pers Personalization string that is mixed पूर्णांकo state, may be शून्य -- note
 *	 the entropy is pulled by the DRBG पूर्णांकernally unconditionally
 *	 as defined in SP800-90A. The additional input is mixed पूर्णांकo
 *	 the state in addition to the pulled entropy.
 * @coreref reference to core
 * @pr prediction resistance enabled
 *
 * वापस
 *	0 on success
 *	error value otherwise
 */
अटल पूर्णांक drbg_instantiate(काष्ठा drbg_state *drbg, काष्ठा drbg_string *pers,
			    पूर्णांक coreref, bool pr)
अणु
	पूर्णांक ret;
	bool reseed = true;

	pr_devel("DRBG: Initializing DRBG core %d with prediction resistance "
		 "%s\n", coreref, pr ? "enabled" : "disabled");
	mutex_lock(&drbg->drbg_mutex);

	/* 9.1 step 1 is implicit with the selected DRBG type */

	/*
	 * 9.1 step 2 is implicit as caller can select prediction resistance
	 * and the flag is copied पूर्णांकo drbg->flags --
	 * all DRBG types support prediction resistance
	 */

	/* 9.1 step 4 is implicit in  drbg_sec_strength */

	अगर (!drbg->core) अणु
		drbg->core = &drbg_cores[coreref];
		drbg->pr = pr;
		drbg->seeded = false;
		drbg->reseed_threshold = drbg_max_requests(drbg);

		ret = drbg_alloc_state(drbg);
		अगर (ret)
			जाओ unlock;

		ret = drbg_prepare_hrng(drbg);
		अगर (ret)
			जाओ मुक्त_everything;

		अगर (IS_ERR(drbg->jent)) अणु
			ret = PTR_ERR(drbg->jent);
			drbg->jent = शून्य;
			अगर (fips_enabled || ret != -ENOENT)
				जाओ मुक्त_everything;
			pr_info("DRBG: Continuing without Jitter RNG\n");
		पूर्ण

		reseed = false;
	पूर्ण

	ret = drbg_seed(drbg, pers, reseed);

	अगर (ret && !reseed)
		जाओ मुक्त_everything;

	mutex_unlock(&drbg->drbg_mutex);
	वापस ret;

unlock:
	mutex_unlock(&drbg->drbg_mutex);
	वापस ret;

मुक्त_everything:
	mutex_unlock(&drbg->drbg_mutex);
	drbg_uninstantiate(drbg);
	वापस ret;
पूर्ण

/*
 * DRBG uninstantiate function as required by SP800-90A - this function
 * मुक्तs all buffers and the DRBG handle
 *
 * @drbg DRBG state handle
 *
 * वापस
 *	0 on success
 */
अटल पूर्णांक drbg_uninstantiate(काष्ठा drbg_state *drbg)
अणु
	अगर (drbg->अक्रमom_पढ़ोy.func) अणु
		del_अक्रमom_पढ़ोy_callback(&drbg->अक्रमom_पढ़ोy);
		cancel_work_sync(&drbg->seed_work);
	पूर्ण

	अगर (!IS_ERR_OR_शून्य(drbg->jent))
		crypto_मुक्त_rng(drbg->jent);
	drbg->jent = शून्य;

	अगर (drbg->d_ops)
		drbg->d_ops->crypto_fini(drbg);
	drbg_dealloc_state(drbg);
	/* no scrubbing of test_data -- this shall survive an uninstantiate */
	वापस 0;
पूर्ण

/*
 * Helper function क्रम setting the test data in the DRBG
 *
 * @drbg DRBG state handle
 * @data test data
 * @len test data length
 */
अटल व्योम drbg_kcapi_set_entropy(काष्ठा crypto_rng *tfm,
				   स्थिर u8 *data, अचिन्हित पूर्णांक len)
अणु
	काष्ठा drbg_state *drbg = crypto_rng_ctx(tfm);

	mutex_lock(&drbg->drbg_mutex);
	drbg_string_fill(&drbg->test_data, data, len);
	mutex_unlock(&drbg->drbg_mutex);
पूर्ण

/***************************************************************
 * Kernel crypto API cipher invocations requested by DRBG
 ***************************************************************/

#अगर defined(CONFIG_CRYPTO_DRBG_HASH) || defined(CONFIG_CRYPTO_DRBG_HMAC)
काष्ठा sdesc अणु
	काष्ठा shash_desc shash;
	अक्षर ctx[];
पूर्ण;

अटल पूर्णांक drbg_init_hash_kernel(काष्ठा drbg_state *drbg)
अणु
	काष्ठा sdesc *sdesc;
	काष्ठा crypto_shash *tfm;

	tfm = crypto_alloc_shash(drbg->core->backend_cra_name, 0, 0);
	अगर (IS_ERR(tfm)) अणु
		pr_info("DRBG: could not allocate digest TFM handle: %s\n",
				drbg->core->backend_cra_name);
		वापस PTR_ERR(tfm);
	पूर्ण
	BUG_ON(drbg_blocklen(drbg) != crypto_shash_digestsize(tfm));
	sdesc = kzalloc(माप(काष्ठा shash_desc) + crypto_shash_descsize(tfm),
			GFP_KERNEL);
	अगर (!sdesc) अणु
		crypto_मुक्त_shash(tfm);
		वापस -ENOMEM;
	पूर्ण

	sdesc->shash.tfm = tfm;
	drbg->priv_data = sdesc;

	वापस crypto_shash_alignmask(tfm);
पूर्ण

अटल पूर्णांक drbg_fini_hash_kernel(काष्ठा drbg_state *drbg)
अणु
	काष्ठा sdesc *sdesc = (काष्ठा sdesc *)drbg->priv_data;
	अगर (sdesc) अणु
		crypto_मुक्त_shash(sdesc->shash.tfm);
		kमुक्त_sensitive(sdesc);
	पूर्ण
	drbg->priv_data = शून्य;
	वापस 0;
पूर्ण

अटल व्योम drbg_kcapi_hmacsetkey(काष्ठा drbg_state *drbg,
				  स्थिर अचिन्हित अक्षर *key)
अणु
	काष्ठा sdesc *sdesc = (काष्ठा sdesc *)drbg->priv_data;

	crypto_shash_setkey(sdesc->shash.tfm, key, drbg_statelen(drbg));
पूर्ण

अटल पूर्णांक drbg_kcapi_hash(काष्ठा drbg_state *drbg, अचिन्हित अक्षर *outval,
			   स्थिर काष्ठा list_head *in)
अणु
	काष्ठा sdesc *sdesc = (काष्ठा sdesc *)drbg->priv_data;
	काष्ठा drbg_string *input = शून्य;

	crypto_shash_init(&sdesc->shash);
	list_क्रम_each_entry(input, in, list)
		crypto_shash_update(&sdesc->shash, input->buf, input->len);
	वापस crypto_shash_final(&sdesc->shash, outval);
पूर्ण
#पूर्ण_अगर /* (CONFIG_CRYPTO_DRBG_HASH || CONFIG_CRYPTO_DRBG_HMAC) */

#अगर_घोषित CONFIG_CRYPTO_DRBG_CTR
अटल पूर्णांक drbg_fini_sym_kernel(काष्ठा drbg_state *drbg)
अणु
	काष्ठा crypto_cipher *tfm =
		(काष्ठा crypto_cipher *)drbg->priv_data;
	अगर (tfm)
		crypto_मुक्त_cipher(tfm);
	drbg->priv_data = शून्य;

	अगर (drbg->ctr_handle)
		crypto_मुक्त_skcipher(drbg->ctr_handle);
	drbg->ctr_handle = शून्य;

	अगर (drbg->ctr_req)
		skcipher_request_मुक्त(drbg->ctr_req);
	drbg->ctr_req = शून्य;

	kमुक्त(drbg->outscratchpadbuf);
	drbg->outscratchpadbuf = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक drbg_init_sym_kernel(काष्ठा drbg_state *drbg)
अणु
	काष्ठा crypto_cipher *tfm;
	काष्ठा crypto_skcipher *sk_tfm;
	काष्ठा skcipher_request *req;
	अचिन्हित पूर्णांक alignmask;
	अक्षर ctr_name[CRYPTO_MAX_ALG_NAME];

	tfm = crypto_alloc_cipher(drbg->core->backend_cra_name, 0, 0);
	अगर (IS_ERR(tfm)) अणु
		pr_info("DRBG: could not allocate cipher TFM handle: %s\n",
				drbg->core->backend_cra_name);
		वापस PTR_ERR(tfm);
	पूर्ण
	BUG_ON(drbg_blocklen(drbg) != crypto_cipher_blocksize(tfm));
	drbg->priv_data = tfm;

	अगर (snम_लिखो(ctr_name, CRYPTO_MAX_ALG_NAME, "ctr(%s)",
	    drbg->core->backend_cra_name) >= CRYPTO_MAX_ALG_NAME) अणु
		drbg_fini_sym_kernel(drbg);
		वापस -EINVAL;
	पूर्ण
	sk_tfm = crypto_alloc_skcipher(ctr_name, 0, 0);
	अगर (IS_ERR(sk_tfm)) अणु
		pr_info("DRBG: could not allocate CTR cipher TFM handle: %s\n",
				ctr_name);
		drbg_fini_sym_kernel(drbg);
		वापस PTR_ERR(sk_tfm);
	पूर्ण
	drbg->ctr_handle = sk_tfm;
	crypto_init_रुको(&drbg->ctr_रुको);

	req = skcipher_request_alloc(sk_tfm, GFP_KERNEL);
	अगर (!req) अणु
		pr_info("DRBG: could not allocate request queue\n");
		drbg_fini_sym_kernel(drbg);
		वापस -ENOMEM;
	पूर्ण
	drbg->ctr_req = req;
	skcipher_request_set_callback(req, CRYPTO_TFM_REQ_MAY_BACKLOG |
						CRYPTO_TFM_REQ_MAY_SLEEP,
					crypto_req_करोne, &drbg->ctr_रुको);

	alignmask = crypto_skcipher_alignmask(sk_tfm);
	drbg->outscratchpadbuf = kदो_स्मृति(DRBG_OUTSCRATCHLEN + alignmask,
					 GFP_KERNEL);
	अगर (!drbg->outscratchpadbuf) अणु
		drbg_fini_sym_kernel(drbg);
		वापस -ENOMEM;
	पूर्ण
	drbg->outscratchpad = (u8 *)PTR_ALIGN(drbg->outscratchpadbuf,
					      alignmask + 1);

	sg_init_table(&drbg->sg_in, 1);
	sg_init_one(&drbg->sg_out, drbg->outscratchpad, DRBG_OUTSCRATCHLEN);

	वापस alignmask;
पूर्ण

अटल व्योम drbg_kcapi_symsetkey(काष्ठा drbg_state *drbg,
				 स्थिर अचिन्हित अक्षर *key)
अणु
	काष्ठा crypto_cipher *tfm =
		(काष्ठा crypto_cipher *)drbg->priv_data;

	crypto_cipher_setkey(tfm, key, (drbg_keylen(drbg)));
पूर्ण

अटल पूर्णांक drbg_kcapi_sym(काष्ठा drbg_state *drbg, अचिन्हित अक्षर *outval,
			  स्थिर काष्ठा drbg_string *in)
अणु
	काष्ठा crypto_cipher *tfm =
		(काष्ठा crypto_cipher *)drbg->priv_data;

	/* there is only component in *in */
	BUG_ON(in->len < drbg_blocklen(drbg));
	crypto_cipher_encrypt_one(tfm, outval, in->buf);
	वापस 0;
पूर्ण

अटल पूर्णांक drbg_kcapi_sym_ctr(काष्ठा drbg_state *drbg,
			      u8 *inbuf, u32 inlen,
			      u8 *outbuf, u32 outlen)
अणु
	काष्ठा scatterlist *sg_in = &drbg->sg_in, *sg_out = &drbg->sg_out;
	u32 scratchpad_use = min_t(u32, outlen, DRBG_OUTSCRATCHLEN);
	पूर्णांक ret;

	अगर (inbuf) अणु
		/* Use caller-provided input buffer */
		sg_set_buf(sg_in, inbuf, inlen);
	पूर्ण अन्यथा अणु
		/* Use scratchpad क्रम in-place operation */
		inlen = scratchpad_use;
		स_रखो(drbg->outscratchpad, 0, scratchpad_use);
		sg_set_buf(sg_in, drbg->outscratchpad, scratchpad_use);
	पूर्ण

	जबतक (outlen) अणु
		u32 cryptlen = min3(inlen, outlen, (u32)DRBG_OUTSCRATCHLEN);

		/* Output buffer may not be valid क्रम SGL, use scratchpad */
		skcipher_request_set_crypt(drbg->ctr_req, sg_in, sg_out,
					   cryptlen, drbg->V);
		ret = crypto_रुको_req(crypto_skcipher_encrypt(drbg->ctr_req),
					&drbg->ctr_रुको);
		अगर (ret)
			जाओ out;

		crypto_init_रुको(&drbg->ctr_रुको);

		स_नकल(outbuf, drbg->outscratchpad, cryptlen);
		memzero_explicit(drbg->outscratchpad, cryptlen);

		outlen -= cryptlen;
		outbuf += cryptlen;
	पूर्ण
	ret = 0;

out:
	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_CRYPTO_DRBG_CTR */

/***************************************************************
 * Kernel crypto API पूर्णांकerface to रेजिस्टर DRBG
 ***************************************************************/

/*
 * Look up the DRBG flags by given kernel crypto API cra_name
 * The code uses the drbg_cores definition to करो this
 *
 * @cra_name kernel crypto API cra_name
 * @coreref reference to पूर्णांकeger which is filled with the poपूर्णांकer to
 *  the applicable core
 * @pr reference क्रम setting prediction resistance
 *
 * वापस: flags
 */
अटल अंतरभूत व्योम drbg_convert_tfm_core(स्थिर अक्षर *cra_driver_name,
					 पूर्णांक *coreref, bool *pr)
अणु
	पूर्णांक i = 0;
	माप_प्रकार start = 0;
	पूर्णांक len = 0;

	*pr = true;
	/* disassemble the names */
	अगर (!स_भेद(cra_driver_name, "drbg_nopr_", 10)) अणु
		start = 10;
		*pr = false;
	पूर्ण अन्यथा अगर (!स_भेद(cra_driver_name, "drbg_pr_", 8)) अणु
		start = 8;
	पूर्ण अन्यथा अणु
		वापस;
	पूर्ण

	/* हटाओ the first part */
	len = म_माप(cra_driver_name) - start;
	क्रम (i = 0; ARRAY_SIZE(drbg_cores) > i; i++) अणु
		अगर (!स_भेद(cra_driver_name + start, drbg_cores[i].cra_name,
			    len)) अणु
			*coreref = i;
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक drbg_kcapi_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा drbg_state *drbg = crypto_tfm_ctx(tfm);

	mutex_init(&drbg->drbg_mutex);

	वापस 0;
पूर्ण

अटल व्योम drbg_kcapi_cleanup(काष्ठा crypto_tfm *tfm)
अणु
	drbg_uninstantiate(crypto_tfm_ctx(tfm));
पूर्ण

/*
 * Generate अक्रमom numbers invoked by the kernel crypto API:
 * The API of the kernel crypto API is extended as follows:
 *
 * src is additional input supplied to the RNG.
 * slen is the length of src.
 * dst is the output buffer where अक्रमom data is to be stored.
 * dlen is the length of dst.
 */
अटल पूर्णांक drbg_kcapi_अक्रमom(काष्ठा crypto_rng *tfm,
			     स्थिर u8 *src, अचिन्हित पूर्णांक slen,
			     u8 *dst, अचिन्हित पूर्णांक dlen)
अणु
	काष्ठा drbg_state *drbg = crypto_rng_ctx(tfm);
	काष्ठा drbg_string *addtl = शून्य;
	काष्ठा drbg_string string;

	अगर (slen) अणु
		/* linked list variable is now local to allow modअगरication */
		drbg_string_fill(&string, src, slen);
		addtl = &string;
	पूर्ण

	वापस drbg_generate_दीर्घ(drbg, dst, dlen, addtl);
पूर्ण

/*
 * Seed the DRBG invoked by the kernel crypto API
 */
अटल पूर्णांक drbg_kcapi_seed(काष्ठा crypto_rng *tfm,
			   स्थिर u8 *seed, अचिन्हित पूर्णांक slen)
अणु
	काष्ठा drbg_state *drbg = crypto_rng_ctx(tfm);
	काष्ठा crypto_tfm *tfm_base = crypto_rng_tfm(tfm);
	bool pr = false;
	काष्ठा drbg_string string;
	काष्ठा drbg_string *seed_string = शून्य;
	पूर्णांक coreref = 0;

	drbg_convert_tfm_core(crypto_tfm_alg_driver_name(tfm_base), &coreref,
			      &pr);
	अगर (0 < slen) अणु
		drbg_string_fill(&string, seed, slen);
		seed_string = &string;
	पूर्ण

	वापस drbg_instantiate(drbg, seed_string, coreref, pr);
पूर्ण

/***************************************************************
 * Kernel module: code to load the module
 ***************************************************************/

/*
 * Tests as defined in 11.3.2 in addition to the cipher tests: testing
 * of the error handling.
 *
 * Note: testing of failing seed source as defined in 11.3.2 is not applicable
 * as seed source of get_अक्रमom_bytes करोes not fail.
 *
 * Note 2: There is no sensible way of testing the reseed counter
 * enक्रमcement, so skip it.
 */
अटल अंतरभूत पूर्णांक __init drbg_healthcheck_sanity(व्योम)
अणु
	पूर्णांक len = 0;
#घोषणा OUTBUFLEN 16
	अचिन्हित अक्षर buf[OUTBUFLEN];
	काष्ठा drbg_state *drbg = शून्य;
	पूर्णांक ret = -EFAULT;
	पूर्णांक rc = -EFAULT;
	bool pr = false;
	पूर्णांक coreref = 0;
	काष्ठा drbg_string addtl;
	माप_प्रकार max_addtllen, max_request_bytes;

	/* only perक्रमm test in FIPS mode */
	अगर (!fips_enabled)
		वापस 0;

#अगर_घोषित CONFIG_CRYPTO_DRBG_CTR
	drbg_convert_tfm_core("drbg_nopr_ctr_aes128", &coreref, &pr);
#या_अगर defined CONFIG_CRYPTO_DRBG_HASH
	drbg_convert_tfm_core("drbg_nopr_sha256", &coreref, &pr);
#अन्यथा
	drbg_convert_tfm_core("drbg_nopr_hmac_sha256", &coreref, &pr);
#पूर्ण_अगर

	drbg = kzalloc(माप(काष्ठा drbg_state), GFP_KERNEL);
	अगर (!drbg)
		वापस -ENOMEM;

	mutex_init(&drbg->drbg_mutex);
	drbg->core = &drbg_cores[coreref];
	drbg->reseed_threshold = drbg_max_requests(drbg);

	/*
	 * अगर the following tests fail, it is likely that there is a buffer
	 * overflow as buf is much smaller than the requested or provided
	 * string lengths -- in हाल the error handling करोes not succeed
	 * we may get an OOPS. And we want to get an OOPS as this is a
	 * grave bug.
	 */

	max_addtllen = drbg_max_addtl(drbg);
	max_request_bytes = drbg_max_request_bytes(drbg);
	drbg_string_fill(&addtl, buf, max_addtllen + 1);
	/* overflow addtllen with additonal info string */
	len = drbg_generate(drbg, buf, OUTBUFLEN, &addtl);
	BUG_ON(0 < len);
	/* overflow max_bits */
	len = drbg_generate(drbg, buf, (max_request_bytes + 1), शून्य);
	BUG_ON(0 < len);

	/* overflow max addtllen with personalization string */
	ret = drbg_seed(drbg, &addtl, false);
	BUG_ON(0 == ret);
	/* all tests passed */
	rc = 0;

	pr_devel("DRBG: Sanity tests for failure code paths successfully "
		 "completed\n");

	kमुक्त(drbg);
	वापस rc;
पूर्ण

अटल काष्ठा rng_alg drbg_algs[22];

/*
 * Fill the array drbg_algs used to रेजिस्टर the dअगरferent DRBGs
 * with the kernel crypto API. To fill the array, the inक्रमmation
 * from drbg_cores[] is used.
 */
अटल अंतरभूत व्योम __init drbg_fill_array(काष्ठा rng_alg *alg,
					  स्थिर काष्ठा drbg_core *core, पूर्णांक pr)
अणु
	पूर्णांक pos = 0;
	अटल पूर्णांक priority = 200;

	स_नकल(alg->base.cra_name, "stdrng", 6);
	अगर (pr) अणु
		स_नकल(alg->base.cra_driver_name, "drbg_pr_", 8);
		pos = 8;
	पूर्ण अन्यथा अणु
		स_नकल(alg->base.cra_driver_name, "drbg_nopr_", 10);
		pos = 10;
	पूर्ण
	स_नकल(alg->base.cra_driver_name + pos, core->cra_name,
	       म_माप(core->cra_name));

	alg->base.cra_priority = priority;
	priority++;
	/*
	 * If FIPS mode enabled, the selected DRBG shall have the
	 * highest cra_priority over other stdrng instances to ensure
	 * it is selected.
	 */
	अगर (fips_enabled)
		alg->base.cra_priority += 200;

	alg->base.cra_ctxsize 	= माप(काष्ठा drbg_state);
	alg->base.cra_module	= THIS_MODULE;
	alg->base.cra_init	= drbg_kcapi_init;
	alg->base.cra_निकास	= drbg_kcapi_cleanup;
	alg->generate		= drbg_kcapi_अक्रमom;
	alg->seed		= drbg_kcapi_seed;
	alg->set_ent		= drbg_kcapi_set_entropy;
	alg->seedsize		= 0;
पूर्ण

अटल पूर्णांक __init drbg_init(व्योम)
अणु
	अचिन्हित पूर्णांक i = 0; /* poपूर्णांकer to drbg_algs */
	अचिन्हित पूर्णांक j = 0; /* poपूर्णांकer to drbg_cores */
	पूर्णांक ret;

	ret = drbg_healthcheck_sanity();
	अगर (ret)
		वापस ret;

	अगर (ARRAY_SIZE(drbg_cores) * 2 > ARRAY_SIZE(drbg_algs)) अणु
		pr_info("DRBG: Cannot register all DRBG types"
			"(slots needed: %zu, slots available: %zu)\n",
			ARRAY_SIZE(drbg_cores) * 2, ARRAY_SIZE(drbg_algs));
		वापस -EFAULT;
	पूर्ण

	/*
	 * each DRBG definition can be used with PR and without PR, thus
	 * we instantiate each DRBG in drbg_cores[] twice.
	 *
	 * As the order of placing them पूर्णांकo the drbg_algs array matters
	 * (the later DRBGs receive a higher cra_priority) we रेजिस्टर the
	 * prediction resistance DRBGs first as the should not be too
	 * पूर्णांकeresting.
	 */
	क्रम (j = 0; ARRAY_SIZE(drbg_cores) > j; j++, i++)
		drbg_fill_array(&drbg_algs[i], &drbg_cores[j], 1);
	क्रम (j = 0; ARRAY_SIZE(drbg_cores) > j; j++, i++)
		drbg_fill_array(&drbg_algs[i], &drbg_cores[j], 0);
	वापस crypto_रेजिस्टर_rngs(drbg_algs, (ARRAY_SIZE(drbg_cores) * 2));
पूर्ण

अटल व्योम __निकास drbg_निकास(व्योम)
अणु
	crypto_unरेजिस्टर_rngs(drbg_algs, (ARRAY_SIZE(drbg_cores) * 2));
पूर्ण

subsys_initcall(drbg_init);
module_निकास(drbg_निकास);
#अगर_अघोषित CRYPTO_DRBG_HASH_STRING
#घोषणा CRYPTO_DRBG_HASH_STRING ""
#पूर्ण_अगर
#अगर_अघोषित CRYPTO_DRBG_HMAC_STRING
#घोषणा CRYPTO_DRBG_HMAC_STRING ""
#पूर्ण_अगर
#अगर_अघोषित CRYPTO_DRBG_CTR_STRING
#घोषणा CRYPTO_DRBG_CTR_STRING ""
#पूर्ण_अगर
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Stephan Mueller <smueller@chronox.de>");
MODULE_DESCRIPTION("NIST SP800-90A Deterministic Random Bit Generator (DRBG) "
		   "using following cores: "
		   CRYPTO_DRBG_HASH_STRING
		   CRYPTO_DRBG_HMAC_STRING
		   CRYPTO_DRBG_CTR_STRING);
MODULE_ALIAS_CRYPTO("stdrng");
MODULE_IMPORT_NS(CRYPTO_INTERNAL);
