<शैली गुरु>
/*
 * Key Wrapping: RFC3394 / NIST SP800-38F
 *
 * Copyright (C) 2015, Stephan Mueller <smueller@chronox.de>
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
 * the GNU General Public License, in which हाल the provisions of the GPL2
 * are required INSTEAD OF the above restrictions.  (This clause is
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
 */

/*
 * Note क्रम using key wrapping:
 *
 *	* The result of the encryption operation is the ciphertext starting
 *	  with the 2nd semiblock. The first semiblock is provided as the IV.
 *	  The IV used to start the encryption operation is the शेष IV.
 *
 *	* The input क्रम the decryption is the first semiblock handed in as an
 *	  IV. The ciphertext is the data starting with the 2nd semiblock. The
 *	  वापस code of the decryption operation will be EBADMSG in हाल an
 *	  पूर्णांकegrity error occurs.
 *
 * To obtain the full result of an encryption as expected by SP800-38F, the
 * caller must allocate a buffer of plaपूर्णांकext + 8 bytes:
 *
 *	अचिन्हित पूर्णांक datalen = ptlen + crypto_skcipher_ivsize(tfm);
 *	u8 data[datalen];
 *	u8 *iv = data;
 *	u8 *pt = data + crypto_skcipher_ivsize(tfm);
 *		<ensure that pt contains the plaपूर्णांकext of size ptlen>
 *	sg_init_one(&sg, pt, ptlen);
 *	skcipher_request_set_crypt(req, &sg, &sg, ptlen, iv);
 *
 *	==> After encryption, data now contains full KW result as per SP800-38F.
 *
 * In हाल of decryption, ciphertext now alपढ़ोy has the expected length
 * and must be segmented appropriately:
 *
 *	अचिन्हित पूर्णांक datalen = CTLEN;
 *	u8 data[datalen];
 *		<ensure that data contains full ciphertext>
 *	u8 *iv = data;
 *	u8 *ct = data + crypto_skcipher_ivsize(tfm);
 *	अचिन्हित पूर्णांक ctlen = datalen - crypto_skcipher_ivsize(tfm);
 *	sg_init_one(&sg, ct, ctlen);
 *	skcipher_request_set_crypt(req, &sg, &sg, ctlen, iv);
 *
 *	==> After decryption (which hopefully करोes not वापस EBADMSG), the ct
 *	poपूर्णांकer now poपूर्णांकs to the plaपूर्णांकext of size ctlen.
 *
 * Note 2: KWP is not implemented as this would defy in-place operation.
 *	   If somebody wants to wrap non-aligned data, he should simply pad
 *	   the input with zeros to fill it up to the 8 byte boundary.
 */

#समावेश <linux/module.h>
#समावेश <linux/crypto.h>
#समावेश <linux/scatterlist.h>
#समावेश <crypto/scatterwalk.h>
#समावेश <crypto/पूर्णांकernal/cipher.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>

काष्ठा crypto_kw_block अणु
#घोषणा SEMIBSIZE 8
	__be64 A;
	__be64 R;
पूर्ण;

/*
 * Fast क्रमward the SGL to the "end" length minus SEMIBSIZE.
 * The start in the SGL defined by the fast-क्रमward is वापसed with
 * the walk variable
 */
अटल व्योम crypto_kw_scatterlist_ff(काष्ठा scatter_walk *walk,
				     काष्ठा scatterlist *sg,
				     अचिन्हित पूर्णांक end)
अणु
	अचिन्हित पूर्णांक skip = 0;

	/* The caller should only operate on full SEMIBLOCKs. */
	BUG_ON(end < SEMIBSIZE);

	skip = end - SEMIBSIZE;
	जबतक (sg) अणु
		अगर (sg->length > skip) अणु
			scatterwalk_start(walk, sg);
			scatterwalk_advance(walk, skip);
			अवरोध;
		पूर्ण

		skip -= sg->length;
		sg = sg_next(sg);
	पूर्ण
पूर्ण

अटल पूर्णांक crypto_kw_decrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा crypto_cipher *cipher = skcipher_cipher_simple(tfm);
	काष्ठा crypto_kw_block block;
	काष्ठा scatterlist *src, *dst;
	u64 t = 6 * ((req->cryptlen) >> 3);
	अचिन्हित पूर्णांक i;
	पूर्णांक ret = 0;

	/*
	 * Require at least 2 semiblocks (note, the 3rd semiblock that is
	 * required by SP800-38F is the IV.
	 */
	अगर (req->cryptlen < (2 * SEMIBSIZE) || req->cryptlen % SEMIBSIZE)
		वापस -EINVAL;

	/* Place the IV पूर्णांकo block A */
	स_नकल(&block.A, req->iv, SEMIBSIZE);

	/*
	 * src scatterlist is पढ़ो-only. dst scatterlist is r/w. During the
	 * first loop, src poपूर्णांकs to req->src and dst to req->dst. For any
	 * subsequent round, the code operates on req->dst only.
	 */
	src = req->src;
	dst = req->dst;

	क्रम (i = 0; i < 6; i++) अणु
		काष्ठा scatter_walk src_walk, dst_walk;
		अचिन्हित पूर्णांक nbytes = req->cryptlen;

		जबतक (nbytes) अणु
			/* move poपूर्णांकer by nbytes in the SGL */
			crypto_kw_scatterlist_ff(&src_walk, src, nbytes);
			/* get the source block */
			scatterwalk_copychunks(&block.R, &src_walk, SEMIBSIZE,
					       false);

			/* perक्रमm KW operation: modअगरy IV with counter */
			block.A ^= cpu_to_be64(t);
			t--;
			/* perक्रमm KW operation: decrypt block */
			crypto_cipher_decrypt_one(cipher, (u8 *)&block,
						  (u8 *)&block);

			/* move poपूर्णांकer by nbytes in the SGL */
			crypto_kw_scatterlist_ff(&dst_walk, dst, nbytes);
			/* Copy block->R पूर्णांकo place */
			scatterwalk_copychunks(&block.R, &dst_walk, SEMIBSIZE,
					       true);

			nbytes -= SEMIBSIZE;
		पूर्ण

		/* we now start to operate on the dst SGL only */
		src = req->dst;
		dst = req->dst;
	पूर्ण

	/* Perक्रमm authentication check */
	अगर (block.A != cpu_to_be64(0xa6a6a6a6a6a6a6a6ULL))
		ret = -EBADMSG;

	memzero_explicit(&block, माप(काष्ठा crypto_kw_block));

	वापस ret;
पूर्ण

अटल पूर्णांक crypto_kw_encrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा crypto_cipher *cipher = skcipher_cipher_simple(tfm);
	काष्ठा crypto_kw_block block;
	काष्ठा scatterlist *src, *dst;
	u64 t = 1;
	अचिन्हित पूर्णांक i;

	/*
	 * Require at least 2 semiblocks (note, the 3rd semiblock that is
	 * required by SP800-38F is the IV that occupies the first semiblock.
	 * This means that the dst memory must be one semiblock larger than src.
	 * Also ensure that the given data is aligned to semiblock.
	 */
	अगर (req->cryptlen < (2 * SEMIBSIZE) || req->cryptlen % SEMIBSIZE)
		वापस -EINVAL;

	/*
	 * Place the predefined IV पूर्णांकo block A -- क्रम encrypt, the caller
	 * करोes not need to provide an IV, but he needs to fetch the final IV.
	 */
	block.A = cpu_to_be64(0xa6a6a6a6a6a6a6a6ULL);

	/*
	 * src scatterlist is पढ़ो-only. dst scatterlist is r/w. During the
	 * first loop, src poपूर्णांकs to req->src and dst to req->dst. For any
	 * subsequent round, the code operates on req->dst only.
	 */
	src = req->src;
	dst = req->dst;

	क्रम (i = 0; i < 6; i++) अणु
		काष्ठा scatter_walk src_walk, dst_walk;
		अचिन्हित पूर्णांक nbytes = req->cryptlen;

		scatterwalk_start(&src_walk, src);
		scatterwalk_start(&dst_walk, dst);

		जबतक (nbytes) अणु
			/* get the source block */
			scatterwalk_copychunks(&block.R, &src_walk, SEMIBSIZE,
					       false);

			/* perक्रमm KW operation: encrypt block */
			crypto_cipher_encrypt_one(cipher, (u8 *)&block,
						  (u8 *)&block);
			/* perक्रमm KW operation: modअगरy IV with counter */
			block.A ^= cpu_to_be64(t);
			t++;

			/* Copy block->R पूर्णांकo place */
			scatterwalk_copychunks(&block.R, &dst_walk, SEMIBSIZE,
					       true);

			nbytes -= SEMIBSIZE;
		पूर्ण

		/* we now start to operate on the dst SGL only */
		src = req->dst;
		dst = req->dst;
	पूर्ण

	/* establish the IV क्रम the caller to pick up */
	स_नकल(req->iv, &block.A, SEMIBSIZE);

	memzero_explicit(&block, माप(काष्ठा crypto_kw_block));

	वापस 0;
पूर्ण

अटल पूर्णांक crypto_kw_create(काष्ठा crypto_ढाँचा *पंचांगpl, काष्ठा rtattr **tb)
अणु
	काष्ठा skcipher_instance *inst;
	काष्ठा crypto_alg *alg;
	पूर्णांक err;

	inst = skcipher_alloc_instance_simple(पंचांगpl, tb);
	अगर (IS_ERR(inst))
		वापस PTR_ERR(inst);

	alg = skcipher_ialg_simple(inst);

	err = -EINVAL;
	/* Section 5.1 requirement क्रम KW */
	अगर (alg->cra_blocksize != माप(काष्ठा crypto_kw_block))
		जाओ out_मुक्त_inst;

	inst->alg.base.cra_blocksize = SEMIBSIZE;
	inst->alg.base.cra_alignmask = 0;
	inst->alg.ivsize = SEMIBSIZE;

	inst->alg.encrypt = crypto_kw_encrypt;
	inst->alg.decrypt = crypto_kw_decrypt;

	err = skcipher_रेजिस्टर_instance(पंचांगpl, inst);
	अगर (err) अणु
out_मुक्त_inst:
		inst->मुक्त(inst);
	पूर्ण

	वापस err;
पूर्ण

अटल काष्ठा crypto_ढाँचा crypto_kw_पंचांगpl = अणु
	.name = "kw",
	.create = crypto_kw_create,
	.module = THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init crypto_kw_init(व्योम)
अणु
	वापस crypto_रेजिस्टर_ढाँचा(&crypto_kw_पंचांगpl);
पूर्ण

अटल व्योम __निकास crypto_kw_निकास(व्योम)
अणु
	crypto_unरेजिस्टर_ढाँचा(&crypto_kw_पंचांगpl);
पूर्ण

subsys_initcall(crypto_kw_init);
module_निकास(crypto_kw_निकास);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Stephan Mueller <smueller@chronox.de>");
MODULE_DESCRIPTION("Key Wrapping (RFC3394 / NIST SP800-38F)");
MODULE_ALIAS_CRYPTO("kw");
MODULE_IMPORT_NS(CRYPTO_INTERNAL);
