<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Glue code क्रम AES implementation क्रम SPE inकाष्ठाions (PPC)
 *
 * Based on generic implementation. The assembler module takes care
 * about the SPE रेजिस्टरs so it can run from पूर्णांकerrupt context.
 *
 * Copyright (c) 2015 Markus Stockhausen <stockhausen@collogia.de>
 */

#समावेश <crypto/aes.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/crypto.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/चयन_to.h>
#समावेश <crypto/algapi.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश <crypto/xts.h>
#समावेश <crypto/gf128mul.h>
#समावेश <crypto/scatterwalk.h>

/*
 * MAX_BYTES defines the number of bytes that are allowed to be processed
 * between preempt_disable() and preempt_enable(). e500 cores can issue two
 * inकाष्ठाions per घड़ी cycle using one 32/64 bit unit (SU1) and one 32
 * bit unit (SU2). One of these can be a memory access that is executed via
 * a single load and store unit (LSU). XTS-AES-256 takes ~780 operations per
 * 16 byte block block or 25 cycles per byte. Thus 768 bytes of input data
 * will need an estimated maximum of 20,000 cycles. Headroom क्रम cache misses
 * included. Even with the low end model घड़ीed at 667 MHz this equals to a
 * critical समय winकरोw of less than 30us. The value has been chosen to
 * process a 512 byte disk block in one or a large 1400 bytes IPsec network
 * packet in two runs.
 *
 */
#घोषणा MAX_BYTES 768

काष्ठा ppc_aes_ctx अणु
	u32 key_enc[AES_MAX_KEYLENGTH_U32];
	u32 key_dec[AES_MAX_KEYLENGTH_U32];
	u32 rounds;
पूर्ण;

काष्ठा ppc_xts_ctx अणु
	u32 key_enc[AES_MAX_KEYLENGTH_U32];
	u32 key_dec[AES_MAX_KEYLENGTH_U32];
	u32 key_twk[AES_MAX_KEYLENGTH_U32];
	u32 rounds;
पूर्ण;

बाह्य व्योम ppc_encrypt_aes(u8 *out, स्थिर u8 *in, u32 *key_enc, u32 rounds);
बाह्य व्योम ppc_decrypt_aes(u8 *out, स्थिर u8 *in, u32 *key_dec, u32 rounds);
बाह्य व्योम ppc_encrypt_ecb(u8 *out, स्थिर u8 *in, u32 *key_enc, u32 rounds,
			    u32 bytes);
बाह्य व्योम ppc_decrypt_ecb(u8 *out, स्थिर u8 *in, u32 *key_dec, u32 rounds,
			    u32 bytes);
बाह्य व्योम ppc_encrypt_cbc(u8 *out, स्थिर u8 *in, u32 *key_enc, u32 rounds,
			    u32 bytes, u8 *iv);
बाह्य व्योम ppc_decrypt_cbc(u8 *out, स्थिर u8 *in, u32 *key_dec, u32 rounds,
			    u32 bytes, u8 *iv);
बाह्य व्योम ppc_crypt_ctr  (u8 *out, स्थिर u8 *in, u32 *key_enc, u32 rounds,
			    u32 bytes, u8 *iv);
बाह्य व्योम ppc_encrypt_xts(u8 *out, स्थिर u8 *in, u32 *key_enc, u32 rounds,
			    u32 bytes, u8 *iv, u32 *key_twk);
बाह्य व्योम ppc_decrypt_xts(u8 *out, स्थिर u8 *in, u32 *key_dec, u32 rounds,
			    u32 bytes, u8 *iv, u32 *key_twk);

बाह्य व्योम ppc_expand_key_128(u32 *key_enc, स्थिर u8 *key);
बाह्य व्योम ppc_expand_key_192(u32 *key_enc, स्थिर u8 *key);
बाह्य व्योम ppc_expand_key_256(u32 *key_enc, स्थिर u8 *key);

बाह्य व्योम ppc_generate_decrypt_key(u32 *key_dec,u32 *key_enc,
				     अचिन्हित पूर्णांक key_len);

अटल व्योम spe_begin(व्योम)
अणु
	/* disable preemption and save users SPE रेजिस्टरs अगर required */
	preempt_disable();
	enable_kernel_spe();
पूर्ण

अटल व्योम spe_end(व्योम)
अणु
	disable_kernel_spe();
	/* reenable preemption */
	preempt_enable();
पूर्ण

अटल पूर्णांक ppc_aes_setkey(काष्ठा crypto_tfm *tfm, स्थिर u8 *in_key,
		अचिन्हित पूर्णांक key_len)
अणु
	काष्ठा ppc_aes_ctx *ctx = crypto_tfm_ctx(tfm);

	चयन (key_len) अणु
	हाल AES_KEYSIZE_128:
		ctx->rounds = 4;
		ppc_expand_key_128(ctx->key_enc, in_key);
		अवरोध;
	हाल AES_KEYSIZE_192:
		ctx->rounds = 5;
		ppc_expand_key_192(ctx->key_enc, in_key);
		अवरोध;
	हाल AES_KEYSIZE_256:
		ctx->rounds = 6;
		ppc_expand_key_256(ctx->key_enc, in_key);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ppc_generate_decrypt_key(ctx->key_dec, ctx->key_enc, key_len);

	वापस 0;
पूर्ण

अटल पूर्णांक ppc_aes_setkey_skcipher(काष्ठा crypto_skcipher *tfm,
				   स्थिर u8 *in_key, अचिन्हित पूर्णांक key_len)
अणु
	वापस ppc_aes_setkey(crypto_skcipher_tfm(tfm), in_key, key_len);
पूर्ण

अटल पूर्णांक ppc_xts_setkey(काष्ठा crypto_skcipher *tfm, स्थिर u8 *in_key,
		   अचिन्हित पूर्णांक key_len)
अणु
	काष्ठा ppc_xts_ctx *ctx = crypto_skcipher_ctx(tfm);
	पूर्णांक err;

	err = xts_verअगरy_key(tfm, in_key, key_len);
	अगर (err)
		वापस err;

	key_len >>= 1;

	चयन (key_len) अणु
	हाल AES_KEYSIZE_128:
		ctx->rounds = 4;
		ppc_expand_key_128(ctx->key_enc, in_key);
		ppc_expand_key_128(ctx->key_twk, in_key + AES_KEYSIZE_128);
		अवरोध;
	हाल AES_KEYSIZE_192:
		ctx->rounds = 5;
		ppc_expand_key_192(ctx->key_enc, in_key);
		ppc_expand_key_192(ctx->key_twk, in_key + AES_KEYSIZE_192);
		अवरोध;
	हाल AES_KEYSIZE_256:
		ctx->rounds = 6;
		ppc_expand_key_256(ctx->key_enc, in_key);
		ppc_expand_key_256(ctx->key_twk, in_key + AES_KEYSIZE_256);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ppc_generate_decrypt_key(ctx->key_dec, ctx->key_enc, key_len);

	वापस 0;
पूर्ण

अटल व्योम ppc_aes_encrypt(काष्ठा crypto_tfm *tfm, u8 *out, स्थिर u8 *in)
अणु
	काष्ठा ppc_aes_ctx *ctx = crypto_tfm_ctx(tfm);

	spe_begin();
	ppc_encrypt_aes(out, in, ctx->key_enc, ctx->rounds);
	spe_end();
पूर्ण

अटल व्योम ppc_aes_decrypt(काष्ठा crypto_tfm *tfm, u8 *out, स्थिर u8 *in)
अणु
	काष्ठा ppc_aes_ctx *ctx = crypto_tfm_ctx(tfm);

	spe_begin();
	ppc_decrypt_aes(out, in, ctx->key_dec, ctx->rounds);
	spe_end();
पूर्ण

अटल पूर्णांक ppc_ecb_crypt(काष्ठा skcipher_request *req, bool enc)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा ppc_aes_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा skcipher_walk walk;
	अचिन्हित पूर्णांक nbytes;
	पूर्णांक err;

	err = skcipher_walk_virt(&walk, req, false);

	जबतक ((nbytes = walk.nbytes) != 0) अणु
		nbytes = min_t(अचिन्हित पूर्णांक, nbytes, MAX_BYTES);
		nbytes = round_करोwn(nbytes, AES_BLOCK_SIZE);

		spe_begin();
		अगर (enc)
			ppc_encrypt_ecb(walk.dst.virt.addr, walk.src.virt.addr,
					ctx->key_enc, ctx->rounds, nbytes);
		अन्यथा
			ppc_decrypt_ecb(walk.dst.virt.addr, walk.src.virt.addr,
					ctx->key_dec, ctx->rounds, nbytes);
		spe_end();

		err = skcipher_walk_करोne(&walk, walk.nbytes - nbytes);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक ppc_ecb_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस ppc_ecb_crypt(req, true);
पूर्ण

अटल पूर्णांक ppc_ecb_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस ppc_ecb_crypt(req, false);
पूर्ण

अटल पूर्णांक ppc_cbc_crypt(काष्ठा skcipher_request *req, bool enc)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा ppc_aes_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा skcipher_walk walk;
	अचिन्हित पूर्णांक nbytes;
	पूर्णांक err;

	err = skcipher_walk_virt(&walk, req, false);

	जबतक ((nbytes = walk.nbytes) != 0) अणु
		nbytes = min_t(अचिन्हित पूर्णांक, nbytes, MAX_BYTES);
		nbytes = round_करोwn(nbytes, AES_BLOCK_SIZE);

		spe_begin();
		अगर (enc)
			ppc_encrypt_cbc(walk.dst.virt.addr, walk.src.virt.addr,
					ctx->key_enc, ctx->rounds, nbytes,
					walk.iv);
		अन्यथा
			ppc_decrypt_cbc(walk.dst.virt.addr, walk.src.virt.addr,
					ctx->key_dec, ctx->rounds, nbytes,
					walk.iv);
		spe_end();

		err = skcipher_walk_करोne(&walk, walk.nbytes - nbytes);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक ppc_cbc_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस ppc_cbc_crypt(req, true);
पूर्ण

अटल पूर्णांक ppc_cbc_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस ppc_cbc_crypt(req, false);
पूर्ण

अटल पूर्णांक ppc_ctr_crypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा ppc_aes_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा skcipher_walk walk;
	अचिन्हित पूर्णांक nbytes;
	पूर्णांक err;

	err = skcipher_walk_virt(&walk, req, false);

	जबतक ((nbytes = walk.nbytes) != 0) अणु
		nbytes = min_t(अचिन्हित पूर्णांक, nbytes, MAX_BYTES);
		अगर (nbytes < walk.total)
			nbytes = round_करोwn(nbytes, AES_BLOCK_SIZE);

		spe_begin();
		ppc_crypt_ctr(walk.dst.virt.addr, walk.src.virt.addr,
			      ctx->key_enc, ctx->rounds, nbytes, walk.iv);
		spe_end();

		err = skcipher_walk_करोne(&walk, walk.nbytes - nbytes);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक ppc_xts_crypt(काष्ठा skcipher_request *req, bool enc)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा ppc_xts_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा skcipher_walk walk;
	अचिन्हित पूर्णांक nbytes;
	पूर्णांक err;
	u32 *twk;

	err = skcipher_walk_virt(&walk, req, false);
	twk = ctx->key_twk;

	जबतक ((nbytes = walk.nbytes) != 0) अणु
		nbytes = min_t(अचिन्हित पूर्णांक, nbytes, MAX_BYTES);
		nbytes = round_करोwn(nbytes, AES_BLOCK_SIZE);

		spe_begin();
		अगर (enc)
			ppc_encrypt_xts(walk.dst.virt.addr, walk.src.virt.addr,
					ctx->key_enc, ctx->rounds, nbytes,
					walk.iv, twk);
		अन्यथा
			ppc_decrypt_xts(walk.dst.virt.addr, walk.src.virt.addr,
					ctx->key_dec, ctx->rounds, nbytes,
					walk.iv, twk);
		spe_end();

		twk = शून्य;
		err = skcipher_walk_करोne(&walk, walk.nbytes - nbytes);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक ppc_xts_encrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा ppc_xts_ctx *ctx = crypto_skcipher_ctx(tfm);
	पूर्णांक tail = req->cryptlen % AES_BLOCK_SIZE;
	पूर्णांक offset = req->cryptlen - tail - AES_BLOCK_SIZE;
	काष्ठा skcipher_request subreq;
	u8 b[2][AES_BLOCK_SIZE];
	पूर्णांक err;

	अगर (req->cryptlen < AES_BLOCK_SIZE)
		वापस -EINVAL;

	अगर (tail) अणु
		subreq = *req;
		skcipher_request_set_crypt(&subreq, req->src, req->dst,
					   req->cryptlen - tail, req->iv);
		req = &subreq;
	पूर्ण

	err = ppc_xts_crypt(req, true);
	अगर (err || !tail)
		वापस err;

	scatterwalk_map_and_copy(b[0], req->dst, offset, AES_BLOCK_SIZE, 0);
	स_नकल(b[1], b[0], tail);
	scatterwalk_map_and_copy(b[0], req->src, offset + AES_BLOCK_SIZE, tail, 0);

	spe_begin();
	ppc_encrypt_xts(b[0], b[0], ctx->key_enc, ctx->rounds, AES_BLOCK_SIZE,
			req->iv, शून्य);
	spe_end();

	scatterwalk_map_and_copy(b[0], req->dst, offset, AES_BLOCK_SIZE + tail, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक ppc_xts_decrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा ppc_xts_ctx *ctx = crypto_skcipher_ctx(tfm);
	पूर्णांक tail = req->cryptlen % AES_BLOCK_SIZE;
	पूर्णांक offset = req->cryptlen - tail - AES_BLOCK_SIZE;
	काष्ठा skcipher_request subreq;
	u8 b[3][AES_BLOCK_SIZE];
	le128 twk;
	पूर्णांक err;

	अगर (req->cryptlen < AES_BLOCK_SIZE)
		वापस -EINVAL;

	अगर (tail) अणु
		subreq = *req;
		skcipher_request_set_crypt(&subreq, req->src, req->dst,
					   offset, req->iv);
		req = &subreq;
	पूर्ण

	err = ppc_xts_crypt(req, false);
	अगर (err || !tail)
		वापस err;

	scatterwalk_map_and_copy(b[1], req->src, offset, AES_BLOCK_SIZE + tail, 0);

	spe_begin();
	अगर (!offset)
		ppc_encrypt_ecb(req->iv, req->iv, ctx->key_twk, ctx->rounds,
				AES_BLOCK_SIZE);

	gf128mul_x_ble(&twk, (le128 *)req->iv);

	ppc_decrypt_xts(b[1], b[1], ctx->key_dec, ctx->rounds, AES_BLOCK_SIZE,
			(u8 *)&twk, शून्य);
	स_नकल(b[0], b[2], tail);
	स_नकल(b[0] + tail, b[1] + tail, AES_BLOCK_SIZE - tail);
	ppc_decrypt_xts(b[0], b[0], ctx->key_dec, ctx->rounds, AES_BLOCK_SIZE,
			req->iv, शून्य);
	spe_end();

	scatterwalk_map_and_copy(b[0], req->dst, offset, AES_BLOCK_SIZE + tail, 1);

	वापस 0;
पूर्ण

/*
 * Algorithm definitions. Disabling alignment (cra_alignmask=0) was chosen
 * because the e500 platक्रमm can handle unaligned पढ़ोs/ग_लिखोs very efficently.
 * This improves IPsec thoughput by another few percent. Additionally we assume
 * that AES context is always aligned to at least 8 bytes because it is created
 * with kदो_स्मृति() in the crypto infraकाष्ठाure
 */

अटल काष्ठा crypto_alg aes_cipher_alg = अणु
	.cra_name		=	"aes",
	.cra_driver_name	=	"aes-ppc-spe",
	.cra_priority		=	300,
	.cra_flags		=	CRYPTO_ALG_TYPE_CIPHER,
	.cra_blocksize		=	AES_BLOCK_SIZE,
	.cra_ctxsize		=	माप(काष्ठा ppc_aes_ctx),
	.cra_alignmask		=	0,
	.cra_module		=	THIS_MODULE,
	.cra_u			=	अणु
		.cipher = अणु
			.cia_min_keysize	=	AES_MIN_KEY_SIZE,
			.cia_max_keysize	=	AES_MAX_KEY_SIZE,
			.cia_setkey		=	ppc_aes_setkey,
			.cia_encrypt		=	ppc_aes_encrypt,
			.cia_decrypt		=	ppc_aes_decrypt
		पूर्ण
	पूर्ण
पूर्ण;

अटल काष्ठा skcipher_alg aes_skcipher_algs[] = अणु
	अणु
		.base.cra_name		=	"ecb(aes)",
		.base.cra_driver_name	=	"ecb-ppc-spe",
		.base.cra_priority	=	300,
		.base.cra_blocksize	=	AES_BLOCK_SIZE,
		.base.cra_ctxsize	=	माप(काष्ठा ppc_aes_ctx),
		.base.cra_module	=	THIS_MODULE,
		.min_keysize		=	AES_MIN_KEY_SIZE,
		.max_keysize		=	AES_MAX_KEY_SIZE,
		.setkey			=	ppc_aes_setkey_skcipher,
		.encrypt		=	ppc_ecb_encrypt,
		.decrypt		=	ppc_ecb_decrypt,
	पूर्ण, अणु
		.base.cra_name		=	"cbc(aes)",
		.base.cra_driver_name	=	"cbc-ppc-spe",
		.base.cra_priority	=	300,
		.base.cra_blocksize	=	AES_BLOCK_SIZE,
		.base.cra_ctxsize	=	माप(काष्ठा ppc_aes_ctx),
		.base.cra_module	=	THIS_MODULE,
		.min_keysize		=	AES_MIN_KEY_SIZE,
		.max_keysize		=	AES_MAX_KEY_SIZE,
		.ivsize			=	AES_BLOCK_SIZE,
		.setkey			=	ppc_aes_setkey_skcipher,
		.encrypt		=	ppc_cbc_encrypt,
		.decrypt		=	ppc_cbc_decrypt,
	पूर्ण, अणु
		.base.cra_name		=	"ctr(aes)",
		.base.cra_driver_name	=	"ctr-ppc-spe",
		.base.cra_priority	=	300,
		.base.cra_blocksize	=	1,
		.base.cra_ctxsize	=	माप(काष्ठा ppc_aes_ctx),
		.base.cra_module	=	THIS_MODULE,
		.min_keysize		=	AES_MIN_KEY_SIZE,
		.max_keysize		=	AES_MAX_KEY_SIZE,
		.ivsize			=	AES_BLOCK_SIZE,
		.setkey			=	ppc_aes_setkey_skcipher,
		.encrypt		=	ppc_ctr_crypt,
		.decrypt		=	ppc_ctr_crypt,
		.chunksize		=	AES_BLOCK_SIZE,
	पूर्ण, अणु
		.base.cra_name		=	"xts(aes)",
		.base.cra_driver_name	=	"xts-ppc-spe",
		.base.cra_priority	=	300,
		.base.cra_blocksize	=	AES_BLOCK_SIZE,
		.base.cra_ctxsize	=	माप(काष्ठा ppc_xts_ctx),
		.base.cra_module	=	THIS_MODULE,
		.min_keysize		=	AES_MIN_KEY_SIZE * 2,
		.max_keysize		=	AES_MAX_KEY_SIZE * 2,
		.ivsize			=	AES_BLOCK_SIZE,
		.setkey			=	ppc_xts_setkey,
		.encrypt		=	ppc_xts_encrypt,
		.decrypt		=	ppc_xts_decrypt,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init ppc_aes_mod_init(व्योम)
अणु
	पूर्णांक err;

	err = crypto_रेजिस्टर_alg(&aes_cipher_alg);
	अगर (err)
		वापस err;

	err = crypto_रेजिस्टर_skciphers(aes_skcipher_algs,
					ARRAY_SIZE(aes_skcipher_algs));
	अगर (err)
		crypto_unरेजिस्टर_alg(&aes_cipher_alg);
	वापस err;
पूर्ण

अटल व्योम __निकास ppc_aes_mod_fini(व्योम)
अणु
	crypto_unरेजिस्टर_alg(&aes_cipher_alg);
	crypto_unरेजिस्टर_skciphers(aes_skcipher_algs,
				    ARRAY_SIZE(aes_skcipher_algs));
पूर्ण

module_init(ppc_aes_mod_init);
module_निकास(ppc_aes_mod_fini);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("AES-ECB/CBC/CTR/XTS, SPE optimized");

MODULE_ALIAS_CRYPTO("aes");
MODULE_ALIAS_CRYPTO("ecb(aes)");
MODULE_ALIAS_CRYPTO("cbc(aes)");
MODULE_ALIAS_CRYPTO("ctr(aes)");
MODULE_ALIAS_CRYPTO("xts(aes)");
MODULE_ALIAS_CRYPTO("aes-ppc-spe");
