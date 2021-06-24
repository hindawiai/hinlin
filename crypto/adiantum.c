<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Adiantum length-preserving encryption mode
 *
 * Copyright 2018 Google LLC
 */

/*
 * Adiantum is a tweakable, length-preserving encryption mode deचिन्हित क्रम fast
 * and secure disk encryption, especially on CPUs without dedicated crypto
 * inकाष्ठाions.  Adiantum encrypts each sector using the XChaCha12 stream
 * cipher, two passes of an Nग-almost-ै-universal (Nग-ैU) hash function based on
 * NH and Poly1305, and an invocation of the AES-256 block cipher on a single
 * 16-byte block.  See the paper क्रम details:
 *
 *	Adiantum: length-preserving encryption क्रम entry-level processors
 *      (https://eprपूर्णांक.iacr.org/2018/720.pdf)
 *
 * For flexibility, this implementation also allows other ciphers:
 *
 *	- Stream cipher: XChaCha12 or XChaCha20
 *	- Block cipher: any with a 128-bit block size and 256-bit key
 *
 * This implementation करोesn't currently allow other Nग-ैU hash functions, i.e.
 * HPolyC is not supported.  This is because Adiantum is ~20% faster than HPolyC
 * but still provably as secure, and also the Nग-ैU hash function of HBSH is
 * क्रमmally defined to take two inमाला_दो (tweak, message) which makes it dअगरficult
 * to wrap with the crypto_shash API.  Rather, some details need to be handled
 * here.  Nevertheless, अगर needed in the future, support क्रम other Nग-ैU hash
 * functions could be added here.
 */

#समावेश <crypto/b128ops.h>
#समावेश <crypto/chacha.h>
#समावेश <crypto/पूर्णांकernal/cipher.h>
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/पूर्णांकernal/poly1305.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश <crypto/nhpoly1305.h>
#समावेश <crypto/scatterwalk.h>
#समावेश <linux/module.h>

/*
 * Size of right-hand part of input data, in bytes; also the size of the block
 * cipher's block size and the hash function's output.
 */
#घोषणा BLOCKCIPHER_BLOCK_SIZE		16

/* Size of the block cipher key (K_E) in bytes */
#घोषणा BLOCKCIPHER_KEY_SIZE		32

/* Size of the hash key (K_H) in bytes */
#घोषणा HASH_KEY_SIZE		(POLY1305_BLOCK_SIZE + NHPOLY1305_KEY_SIZE)

/*
 * The specअगरication allows variable-length tweaks, but Linux's crypto API
 * currently only allows algorithms to support a single length.  The "natural"
 * tweak length क्रम Adiantum is 16, since that fits पूर्णांकo one Poly1305 block क्रम
 * the best perक्रमmance.  But दीर्घer tweaks are useful क्रम fscrypt, to aव्योम
 * needing to derive per-file keys.  So instead we use two blocks, or 32 bytes.
 */
#घोषणा TWEAK_SIZE		32

काष्ठा adiantum_instance_ctx अणु
	काष्ठा crypto_skcipher_spawn streamcipher_spawn;
	काष्ठा crypto_cipher_spawn blockcipher_spawn;
	काष्ठा crypto_shash_spawn hash_spawn;
पूर्ण;

काष्ठा adiantum_tfm_ctx अणु
	काष्ठा crypto_skcipher *streamcipher;
	काष्ठा crypto_cipher *blockcipher;
	काष्ठा crypto_shash *hash;
	काष्ठा poly1305_core_key header_hash_key;
पूर्ण;

काष्ठा adiantum_request_ctx अणु

	/*
	 * Buffer क्रम right-hand part of data, i.e.
	 *
	 *    P_L => P_M => C_M => C_R when encrypting, or
	 *    C_R => C_M => P_M => P_L when decrypting.
	 *
	 * Also used to build the IV क्रम the stream cipher.
	 */
	जोड़ अणु
		u8 bytes[XCHACHA_IV_SIZE];
		__le32 words[XCHACHA_IV_SIZE / माप(__le32)];
		le128 bignum;	/* पूर्णांकerpret as element of Z/(2^अणु128पूर्णZ) */
	पूर्ण rbuf;

	bool enc; /* true अगर encrypting, false अगर decrypting */

	/*
	 * The result of the Poly1305 Nग-ैU hash function applied to
	 * (bulk length, tweak)
	 */
	le128 header_hash;

	/* Sub-requests, must be last */
	जोड़ अणु
		काष्ठा shash_desc hash_desc;
		काष्ठा skcipher_request streamcipher_req;
	पूर्ण u;
पूर्ण;

/*
 * Given the XChaCha stream key K_S, derive the block cipher key K_E and the
 * hash key K_H as follows:
 *
 *     K_E || K_H || ... = XChaCha(key=K_S, nonce=1||0^191)
 *
 * Note that this denotes using bits from the XChaCha keystream, which here we
 * get indirectly by encrypting a buffer containing all 0's.
 */
अटल पूर्णांक adiantum_setkey(काष्ठा crypto_skcipher *tfm, स्थिर u8 *key,
			   अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा adiantum_tfm_ctx *tctx = crypto_skcipher_ctx(tfm);
	काष्ठा अणु
		u8 iv[XCHACHA_IV_SIZE];
		u8 derived_keys[BLOCKCIPHER_KEY_SIZE + HASH_KEY_SIZE];
		काष्ठा scatterlist sg;
		काष्ठा crypto_रुको रुको;
		काष्ठा skcipher_request req; /* must be last */
	पूर्ण *data;
	u8 *keyp;
	पूर्णांक err;

	/* Set the stream cipher key (K_S) */
	crypto_skcipher_clear_flags(tctx->streamcipher, CRYPTO_TFM_REQ_MASK);
	crypto_skcipher_set_flags(tctx->streamcipher,
				  crypto_skcipher_get_flags(tfm) &
				  CRYPTO_TFM_REQ_MASK);
	err = crypto_skcipher_setkey(tctx->streamcipher, key, keylen);
	अगर (err)
		वापस err;

	/* Derive the subkeys */
	data = kzalloc(माप(*data) +
		       crypto_skcipher_reqsize(tctx->streamcipher), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;
	data->iv[0] = 1;
	sg_init_one(&data->sg, data->derived_keys, माप(data->derived_keys));
	crypto_init_रुको(&data->रुको);
	skcipher_request_set_tfm(&data->req, tctx->streamcipher);
	skcipher_request_set_callback(&data->req, CRYPTO_TFM_REQ_MAY_SLEEP |
						  CRYPTO_TFM_REQ_MAY_BACKLOG,
				      crypto_req_करोne, &data->रुको);
	skcipher_request_set_crypt(&data->req, &data->sg, &data->sg,
				   माप(data->derived_keys), data->iv);
	err = crypto_रुको_req(crypto_skcipher_encrypt(&data->req), &data->रुको);
	अगर (err)
		जाओ out;
	keyp = data->derived_keys;

	/* Set the block cipher key (K_E) */
	crypto_cipher_clear_flags(tctx->blockcipher, CRYPTO_TFM_REQ_MASK);
	crypto_cipher_set_flags(tctx->blockcipher,
				crypto_skcipher_get_flags(tfm) &
				CRYPTO_TFM_REQ_MASK);
	err = crypto_cipher_setkey(tctx->blockcipher, keyp,
				   BLOCKCIPHER_KEY_SIZE);
	अगर (err)
		जाओ out;
	keyp += BLOCKCIPHER_KEY_SIZE;

	/* Set the hash key (K_H) */
	poly1305_core_setkey(&tctx->header_hash_key, keyp);
	keyp += POLY1305_BLOCK_SIZE;

	crypto_shash_clear_flags(tctx->hash, CRYPTO_TFM_REQ_MASK);
	crypto_shash_set_flags(tctx->hash, crypto_skcipher_get_flags(tfm) &
					   CRYPTO_TFM_REQ_MASK);
	err = crypto_shash_setkey(tctx->hash, keyp, NHPOLY1305_KEY_SIZE);
	keyp += NHPOLY1305_KEY_SIZE;
	WARN_ON(keyp != &data->derived_keys[ARRAY_SIZE(data->derived_keys)]);
out:
	kमुक्त_sensitive(data);
	वापस err;
पूर्ण

/* Addition in Z/(2^अणु128पूर्णZ) */
अटल अंतरभूत व्योम le128_add(le128 *r, स्थिर le128 *v1, स्थिर le128 *v2)
अणु
	u64 x = le64_to_cpu(v1->b);
	u64 y = le64_to_cpu(v2->b);

	r->b = cpu_to_le64(x + y);
	r->a = cpu_to_le64(le64_to_cpu(v1->a) + le64_to_cpu(v2->a) +
			   (x + y < x));
पूर्ण

/* Subtraction in Z/(2^अणु128पूर्णZ) */
अटल अंतरभूत व्योम le128_sub(le128 *r, स्थिर le128 *v1, स्थिर le128 *v2)
अणु
	u64 x = le64_to_cpu(v1->b);
	u64 y = le64_to_cpu(v2->b);

	r->b = cpu_to_le64(x - y);
	r->a = cpu_to_le64(le64_to_cpu(v1->a) - le64_to_cpu(v2->a) -
			   (x - y > x));
पूर्ण

/*
 * Apply the Poly1305 Nग-ैU hash function to (bulk length, tweak) and save the
 * result to rctx->header_hash.  This is the calculation
 *
 *	H_T ै Poly1305_अणुK_Tपूर्ण(bin_अणु128पूर्ण(|L|) || T)
 *
 * from the procedure in section 6.4 of the Adiantum paper.  The resulting value
 * is reused in both the first and second hash steps.  Specअगरically, it's added
 * to the result of an independently keyed Nग-ैU hash function (क्रम equal length
 * inमाला_दो only) taken over the left-hand part (the "bulk") of the message, to
 * give the overall Adiantum hash of the (tweak, left-hand part) pair.
 */
अटल व्योम adiantum_hash_header(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	स्थिर काष्ठा adiantum_tfm_ctx *tctx = crypto_skcipher_ctx(tfm);
	काष्ठा adiantum_request_ctx *rctx = skcipher_request_ctx(req);
	स्थिर अचिन्हित पूर्णांक bulk_len = req->cryptlen - BLOCKCIPHER_BLOCK_SIZE;
	काष्ठा अणु
		__le64 message_bits;
		__le64 padding;
	पूर्ण header = अणु
		.message_bits = cpu_to_le64((u64)bulk_len * 8)
	पूर्ण;
	काष्ठा poly1305_state state;

	poly1305_core_init(&state);

	BUILD_BUG_ON(माप(header) % POLY1305_BLOCK_SIZE != 0);
	poly1305_core_blocks(&state, &tctx->header_hash_key,
			     &header, माप(header) / POLY1305_BLOCK_SIZE, 1);

	BUILD_BUG_ON(TWEAK_SIZE % POLY1305_BLOCK_SIZE != 0);
	poly1305_core_blocks(&state, &tctx->header_hash_key, req->iv,
			     TWEAK_SIZE / POLY1305_BLOCK_SIZE, 1);

	poly1305_core_emit(&state, शून्य, &rctx->header_hash);
पूर्ण

/* Hash the left-hand part (the "bulk") of the message using NHPoly1305 */
अटल पूर्णांक adiantum_hash_message(काष्ठा skcipher_request *req,
				 काष्ठा scatterlist *sgl, le128 *digest)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	स्थिर काष्ठा adiantum_tfm_ctx *tctx = crypto_skcipher_ctx(tfm);
	काष्ठा adiantum_request_ctx *rctx = skcipher_request_ctx(req);
	स्थिर अचिन्हित पूर्णांक bulk_len = req->cryptlen - BLOCKCIPHER_BLOCK_SIZE;
	काष्ठा shash_desc *hash_desc = &rctx->u.hash_desc;
	काष्ठा sg_mapping_iter miter;
	अचिन्हित पूर्णांक i, n;
	पूर्णांक err;

	hash_desc->tfm = tctx->hash;

	err = crypto_shash_init(hash_desc);
	अगर (err)
		वापस err;

	sg_miter_start(&miter, sgl, sg_nents(sgl),
		       SG_MITER_FROM_SG | SG_MITER_ATOMIC);
	क्रम (i = 0; i < bulk_len; i += n) अणु
		sg_miter_next(&miter);
		n = min_t(अचिन्हित पूर्णांक, miter.length, bulk_len - i);
		err = crypto_shash_update(hash_desc, miter.addr, n);
		अगर (err)
			अवरोध;
	पूर्ण
	sg_miter_stop(&miter);
	अगर (err)
		वापस err;

	वापस crypto_shash_final(hash_desc, (u8 *)digest);
पूर्ण

/* Continue Adiantum encryption/decryption after the stream cipher step */
अटल पूर्णांक adiantum_finish(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	स्थिर काष्ठा adiantum_tfm_ctx *tctx = crypto_skcipher_ctx(tfm);
	काष्ठा adiantum_request_ctx *rctx = skcipher_request_ctx(req);
	स्थिर अचिन्हित पूर्णांक bulk_len = req->cryptlen - BLOCKCIPHER_BLOCK_SIZE;
	le128 digest;
	पूर्णांक err;

	/* If decrypting, decrypt C_M with the block cipher to get P_M */
	अगर (!rctx->enc)
		crypto_cipher_decrypt_one(tctx->blockcipher, rctx->rbuf.bytes,
					  rctx->rbuf.bytes);

	/*
	 * Second hash step
	 *	enc: C_R = C_M - H_अणुK_Hपूर्ण(T, C_L)
	 *	dec: P_R = P_M - H_अणुK_Hपूर्ण(T, P_L)
	 */
	err = adiantum_hash_message(req, req->dst, &digest);
	अगर (err)
		वापस err;
	le128_add(&digest, &digest, &rctx->header_hash);
	le128_sub(&rctx->rbuf.bignum, &rctx->rbuf.bignum, &digest);
	scatterwalk_map_and_copy(&rctx->rbuf.bignum, req->dst,
				 bulk_len, BLOCKCIPHER_BLOCK_SIZE, 1);
	वापस 0;
पूर्ण

अटल व्योम adiantum_streamcipher_करोne(काष्ठा crypto_async_request *areq,
				       पूर्णांक err)
अणु
	काष्ठा skcipher_request *req = areq->data;

	अगर (!err)
		err = adiantum_finish(req);

	skcipher_request_complete(req, err);
पूर्ण

अटल पूर्णांक adiantum_crypt(काष्ठा skcipher_request *req, bool enc)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	स्थिर काष्ठा adiantum_tfm_ctx *tctx = crypto_skcipher_ctx(tfm);
	काष्ठा adiantum_request_ctx *rctx = skcipher_request_ctx(req);
	स्थिर अचिन्हित पूर्णांक bulk_len = req->cryptlen - BLOCKCIPHER_BLOCK_SIZE;
	अचिन्हित पूर्णांक stream_len;
	le128 digest;
	पूर्णांक err;

	अगर (req->cryptlen < BLOCKCIPHER_BLOCK_SIZE)
		वापस -EINVAL;

	rctx->enc = enc;

	/*
	 * First hash step
	 *	enc: P_M = P_R + H_अणुK_Hपूर्ण(T, P_L)
	 *	dec: C_M = C_R + H_अणुK_Hपूर्ण(T, C_L)
	 */
	adiantum_hash_header(req);
	err = adiantum_hash_message(req, req->src, &digest);
	अगर (err)
		वापस err;
	le128_add(&digest, &digest, &rctx->header_hash);
	scatterwalk_map_and_copy(&rctx->rbuf.bignum, req->src,
				 bulk_len, BLOCKCIPHER_BLOCK_SIZE, 0);
	le128_add(&rctx->rbuf.bignum, &rctx->rbuf.bignum, &digest);

	/* If encrypting, encrypt P_M with the block cipher to get C_M */
	अगर (enc)
		crypto_cipher_encrypt_one(tctx->blockcipher, rctx->rbuf.bytes,
					  rctx->rbuf.bytes);

	/* Initialize the rest of the XChaCha IV (first part is C_M) */
	BUILD_BUG_ON(BLOCKCIPHER_BLOCK_SIZE != 16);
	BUILD_BUG_ON(XCHACHA_IV_SIZE != 32);	/* nonce || stream position */
	rctx->rbuf.words[4] = cpu_to_le32(1);
	rctx->rbuf.words[5] = 0;
	rctx->rbuf.words[6] = 0;
	rctx->rbuf.words[7] = 0;

	/*
	 * XChaCha needs to be करोne on all the data except the last 16 bytes;
	 * क्रम disk encryption that usually means 4080 or 496 bytes.  But ChaCha
	 * implementations tend to be most efficient when passed a whole number
	 * of 64-byte ChaCha blocks, or someबार even a multiple of 256 bytes.
	 * And here it करोesn't matter whether the last 16 bytes are written to,
	 * as the second hash step will overग_लिखो them.  Thus, round the XChaCha
	 * length up to the next 64-byte boundary अगर possible.
	 */
	stream_len = bulk_len;
	अगर (round_up(stream_len, CHACHA_BLOCK_SIZE) <= req->cryptlen)
		stream_len = round_up(stream_len, CHACHA_BLOCK_SIZE);

	skcipher_request_set_tfm(&rctx->u.streamcipher_req, tctx->streamcipher);
	skcipher_request_set_crypt(&rctx->u.streamcipher_req, req->src,
				   req->dst, stream_len, &rctx->rbuf);
	skcipher_request_set_callback(&rctx->u.streamcipher_req,
				      req->base.flags,
				      adiantum_streamcipher_करोne, req);
	वापस crypto_skcipher_encrypt(&rctx->u.streamcipher_req) ?:
		adiantum_finish(req);
पूर्ण

अटल पूर्णांक adiantum_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस adiantum_crypt(req, true);
पूर्ण

अटल पूर्णांक adiantum_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस adiantum_crypt(req, false);
पूर्ण

अटल पूर्णांक adiantum_init_tfm(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा skcipher_instance *inst = skcipher_alg_instance(tfm);
	काष्ठा adiantum_instance_ctx *ictx = skcipher_instance_ctx(inst);
	काष्ठा adiantum_tfm_ctx *tctx = crypto_skcipher_ctx(tfm);
	काष्ठा crypto_skcipher *streamcipher;
	काष्ठा crypto_cipher *blockcipher;
	काष्ठा crypto_shash *hash;
	अचिन्हित पूर्णांक subreq_size;
	पूर्णांक err;

	streamcipher = crypto_spawn_skcipher(&ictx->streamcipher_spawn);
	अगर (IS_ERR(streamcipher))
		वापस PTR_ERR(streamcipher);

	blockcipher = crypto_spawn_cipher(&ictx->blockcipher_spawn);
	अगर (IS_ERR(blockcipher)) अणु
		err = PTR_ERR(blockcipher);
		जाओ err_मुक्त_streamcipher;
	पूर्ण

	hash = crypto_spawn_shash(&ictx->hash_spawn);
	अगर (IS_ERR(hash)) अणु
		err = PTR_ERR(hash);
		जाओ err_मुक्त_blockcipher;
	पूर्ण

	tctx->streamcipher = streamcipher;
	tctx->blockcipher = blockcipher;
	tctx->hash = hash;

	BUILD_BUG_ON(दुरत्वend(काष्ठा adiantum_request_ctx, u) !=
		     माप(काष्ठा adiantum_request_ctx));
	subreq_size = max(माप_field(काष्ठा adiantum_request_ctx,
				       u.hash_desc) +
			  crypto_shash_descsize(hash),
			  माप_field(काष्ठा adiantum_request_ctx,
				       u.streamcipher_req) +
			  crypto_skcipher_reqsize(streamcipher));

	crypto_skcipher_set_reqsize(tfm,
				    दुरत्व(काष्ठा adiantum_request_ctx, u) +
				    subreq_size);
	वापस 0;

err_मुक्त_blockcipher:
	crypto_मुक्त_cipher(blockcipher);
err_मुक्त_streamcipher:
	crypto_मुक्त_skcipher(streamcipher);
	वापस err;
पूर्ण

अटल व्योम adiantum_निकास_tfm(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा adiantum_tfm_ctx *tctx = crypto_skcipher_ctx(tfm);

	crypto_मुक्त_skcipher(tctx->streamcipher);
	crypto_मुक्त_cipher(tctx->blockcipher);
	crypto_मुक्त_shash(tctx->hash);
पूर्ण

अटल व्योम adiantum_मुक्त_instance(काष्ठा skcipher_instance *inst)
अणु
	काष्ठा adiantum_instance_ctx *ictx = skcipher_instance_ctx(inst);

	crypto_drop_skcipher(&ictx->streamcipher_spawn);
	crypto_drop_cipher(&ictx->blockcipher_spawn);
	crypto_drop_shash(&ictx->hash_spawn);
	kमुक्त(inst);
पूर्ण

/*
 * Check क्रम a supported set of inner algorithms.
 * See the comment at the beginning of this file.
 */
अटल bool adiantum_supported_algorithms(काष्ठा skcipher_alg *streamcipher_alg,
					  काष्ठा crypto_alg *blockcipher_alg,
					  काष्ठा shash_alg *hash_alg)
अणु
	अगर (म_भेद(streamcipher_alg->base.cra_name, "xchacha12") != 0 &&
	    म_भेद(streamcipher_alg->base.cra_name, "xchacha20") != 0)
		वापस false;

	अगर (blockcipher_alg->cra_cipher.cia_min_keysize > BLOCKCIPHER_KEY_SIZE ||
	    blockcipher_alg->cra_cipher.cia_max_keysize < BLOCKCIPHER_KEY_SIZE)
		वापस false;
	अगर (blockcipher_alg->cra_blocksize != BLOCKCIPHER_BLOCK_SIZE)
		वापस false;

	अगर (म_भेद(hash_alg->base.cra_name, "nhpoly1305") != 0)
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक adiantum_create(काष्ठा crypto_ढाँचा *पंचांगpl, काष्ठा rtattr **tb)
अणु
	u32 mask;
	स्थिर अक्षर *nhpoly1305_name;
	काष्ठा skcipher_instance *inst;
	काष्ठा adiantum_instance_ctx *ictx;
	काष्ठा skcipher_alg *streamcipher_alg;
	काष्ठा crypto_alg *blockcipher_alg;
	काष्ठा shash_alg *hash_alg;
	पूर्णांक err;

	err = crypto_check_attr_type(tb, CRYPTO_ALG_TYPE_SKCIPHER, &mask);
	अगर (err)
		वापस err;

	inst = kzalloc(माप(*inst) + माप(*ictx), GFP_KERNEL);
	अगर (!inst)
		वापस -ENOMEM;
	ictx = skcipher_instance_ctx(inst);

	/* Stream cipher, e.g. "xchacha12" */
	err = crypto_grab_skcipher(&ictx->streamcipher_spawn,
				   skcipher_crypto_instance(inst),
				   crypto_attr_alg_name(tb[1]), 0, mask);
	अगर (err)
		जाओ err_मुक्त_inst;
	streamcipher_alg = crypto_spawn_skcipher_alg(&ictx->streamcipher_spawn);

	/* Block cipher, e.g. "aes" */
	err = crypto_grab_cipher(&ictx->blockcipher_spawn,
				 skcipher_crypto_instance(inst),
				 crypto_attr_alg_name(tb[2]), 0, mask);
	अगर (err)
		जाओ err_मुक्त_inst;
	blockcipher_alg = crypto_spawn_cipher_alg(&ictx->blockcipher_spawn);

	/* NHPoly1305 Nग-ैU hash function */
	nhpoly1305_name = crypto_attr_alg_name(tb[3]);
	अगर (nhpoly1305_name == ERR_PTR(-ENOENT))
		nhpoly1305_name = "nhpoly1305";
	err = crypto_grab_shash(&ictx->hash_spawn,
				skcipher_crypto_instance(inst),
				nhpoly1305_name, 0, mask);
	अगर (err)
		जाओ err_मुक्त_inst;
	hash_alg = crypto_spawn_shash_alg(&ictx->hash_spawn);

	/* Check the set of algorithms */
	अगर (!adiantum_supported_algorithms(streamcipher_alg, blockcipher_alg,
					   hash_alg)) अणु
		pr_warn("Unsupported Adiantum instantiation: (%s,%s,%s)\n",
			streamcipher_alg->base.cra_name,
			blockcipher_alg->cra_name, hash_alg->base.cra_name);
		err = -EINVAL;
		जाओ err_मुक्त_inst;
	पूर्ण

	/* Instance fields */

	err = -ENAMETOOLONG;
	अगर (snम_लिखो(inst->alg.base.cra_name, CRYPTO_MAX_ALG_NAME,
		     "adiantum(%s,%s)", streamcipher_alg->base.cra_name,
		     blockcipher_alg->cra_name) >= CRYPTO_MAX_ALG_NAME)
		जाओ err_मुक्त_inst;
	अगर (snम_लिखो(inst->alg.base.cra_driver_name, CRYPTO_MAX_ALG_NAME,
		     "adiantum(%s,%s,%s)",
		     streamcipher_alg->base.cra_driver_name,
		     blockcipher_alg->cra_driver_name,
		     hash_alg->base.cra_driver_name) >= CRYPTO_MAX_ALG_NAME)
		जाओ err_मुक्त_inst;

	inst->alg.base.cra_blocksize = BLOCKCIPHER_BLOCK_SIZE;
	inst->alg.base.cra_ctxsize = माप(काष्ठा adiantum_tfm_ctx);
	inst->alg.base.cra_alignmask = streamcipher_alg->base.cra_alignmask |
				       hash_alg->base.cra_alignmask;
	/*
	 * The block cipher is only invoked once per message, so क्रम दीर्घ
	 * messages (e.g. sectors क्रम disk encryption) its perक्रमmance करोesn't
	 * matter as much as that of the stream cipher and hash function.  Thus,
	 * weigh the block cipher's ->cra_priority less.
	 */
	inst->alg.base.cra_priority = (4 * streamcipher_alg->base.cra_priority +
				       2 * hash_alg->base.cra_priority +
				       blockcipher_alg->cra_priority) / 7;

	inst->alg.setkey = adiantum_setkey;
	inst->alg.encrypt = adiantum_encrypt;
	inst->alg.decrypt = adiantum_decrypt;
	inst->alg.init = adiantum_init_tfm;
	inst->alg.निकास = adiantum_निकास_tfm;
	inst->alg.min_keysize = crypto_skcipher_alg_min_keysize(streamcipher_alg);
	inst->alg.max_keysize = crypto_skcipher_alg_max_keysize(streamcipher_alg);
	inst->alg.ivsize = TWEAK_SIZE;

	inst->मुक्त = adiantum_मुक्त_instance;

	err = skcipher_रेजिस्टर_instance(पंचांगpl, inst);
	अगर (err) अणु
err_मुक्त_inst:
		adiantum_मुक्त_instance(inst);
	पूर्ण
	वापस err;
पूर्ण

/* adiantum(streamcipher_name, blockcipher_name [, nhpoly1305_name]) */
अटल काष्ठा crypto_ढाँचा adiantum_पंचांगpl = अणु
	.name = "adiantum",
	.create = adiantum_create,
	.module = THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init adiantum_module_init(व्योम)
अणु
	वापस crypto_रेजिस्टर_ढाँचा(&adiantum_पंचांगpl);
पूर्ण

अटल व्योम __निकास adiantum_module_निकास(व्योम)
अणु
	crypto_unरेजिस्टर_ढाँचा(&adiantum_पंचांगpl);
पूर्ण

subsys_initcall(adiantum_module_init);
module_निकास(adiantum_module_निकास);

MODULE_DESCRIPTION("Adiantum length-preserving encryption mode");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Eric Biggers <ebiggers@google.com>");
MODULE_ALIAS_CRYPTO("adiantum");
MODULE_IMPORT_NS(CRYPTO_INTERNAL);
