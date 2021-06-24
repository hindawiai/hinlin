<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * CMAC: Cipher Block Mode क्रम Authentication
 *
 * Copyright तऊ 2013 Jussi Kivilinna <jussi.kivilinna@iki.fi>
 *
 * Based on work by:
 *  Copyright तऊ 2013 Tom St Denis <tstdenis@elliptictech.com>
 * Based on crypto/xcbc.c:
 *  Copyright तऊ 2006 USAGI/WIDE Project,
 *   Author: Kazunori Miyazawa <miyazawa@linux-ipv6.org>
 */

#समावेश <crypto/पूर्णांकernal/cipher.h>
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>

/*
 * +------------------------
 * | <parent tfm>
 * +------------------------
 * | cmac_tfm_ctx
 * +------------------------
 * | स्थिरs (block size * 2)
 * +------------------------
 */
काष्ठा cmac_tfm_ctx अणु
	काष्ठा crypto_cipher *child;
	u8 ctx[];
पूर्ण;

/*
 * +------------------------
 * | <shash desc>
 * +------------------------
 * | cmac_desc_ctx
 * +------------------------
 * | odds (block size)
 * +------------------------
 * | prev (block size)
 * +------------------------
 */
काष्ठा cmac_desc_ctx अणु
	अचिन्हित पूर्णांक len;
	u8 ctx[];
पूर्ण;

अटल पूर्णांक crypto_cmac_digest_setkey(काष्ठा crypto_shash *parent,
				     स्थिर u8 *inkey, अचिन्हित पूर्णांक keylen)
अणु
	अचिन्हित दीर्घ alignmask = crypto_shash_alignmask(parent);
	काष्ठा cmac_tfm_ctx *ctx = crypto_shash_ctx(parent);
	अचिन्हित पूर्णांक bs = crypto_shash_blocksize(parent);
	__be64 *स्थिरs = PTR_ALIGN((व्योम *)ctx->ctx,
				   (alignmask | (__alignof__(__be64) - 1)) + 1);
	u64 _स्थिर[2];
	पूर्णांक i, err = 0;
	u8 msb_mask, gfmask;

	err = crypto_cipher_setkey(ctx->child, inkey, keylen);
	अगर (err)
		वापस err;

	/* encrypt the zero block */
	स_रखो(स्थिरs, 0, bs);
	crypto_cipher_encrypt_one(ctx->child, (u8 *)स्थिरs, (u8 *)स्थिरs);

	चयन (bs) अणु
	हाल 16:
		gfmask = 0x87;
		_स्थिर[0] = be64_to_cpu(स्थिरs[1]);
		_स्थिर[1] = be64_to_cpu(स्थिरs[0]);

		/* gf(2^128) multiply zero-ciphertext with u and u^2 */
		क्रम (i = 0; i < 4; i += 2) अणु
			msb_mask = ((s64)_स्थिर[1] >> 63) & gfmask;
			_स्थिर[1] = (_स्थिर[1] << 1) | (_स्थिर[0] >> 63);
			_स्थिर[0] = (_स्थिर[0] << 1) ^ msb_mask;

			स्थिरs[i + 0] = cpu_to_be64(_स्थिर[1]);
			स्थिरs[i + 1] = cpu_to_be64(_स्थिर[0]);
		पूर्ण

		अवरोध;
	हाल 8:
		gfmask = 0x1B;
		_स्थिर[0] = be64_to_cpu(स्थिरs[0]);

		/* gf(2^64) multiply zero-ciphertext with u and u^2 */
		क्रम (i = 0; i < 2; i++) अणु
			msb_mask = ((s64)_स्थिर[0] >> 63) & gfmask;
			_स्थिर[0] = (_स्थिर[0] << 1) ^ msb_mask;

			स्थिरs[i] = cpu_to_be64(_स्थिर[0]);
		पूर्ण

		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक crypto_cmac_digest_init(काष्ठा shash_desc *pdesc)
अणु
	अचिन्हित दीर्घ alignmask = crypto_shash_alignmask(pdesc->tfm);
	काष्ठा cmac_desc_ctx *ctx = shash_desc_ctx(pdesc);
	पूर्णांक bs = crypto_shash_blocksize(pdesc->tfm);
	u8 *prev = PTR_ALIGN((व्योम *)ctx->ctx, alignmask + 1) + bs;

	ctx->len = 0;
	स_रखो(prev, 0, bs);

	वापस 0;
पूर्ण

अटल पूर्णांक crypto_cmac_digest_update(काष्ठा shash_desc *pdesc, स्थिर u8 *p,
				     अचिन्हित पूर्णांक len)
अणु
	काष्ठा crypto_shash *parent = pdesc->tfm;
	अचिन्हित दीर्घ alignmask = crypto_shash_alignmask(parent);
	काष्ठा cmac_tfm_ctx *tctx = crypto_shash_ctx(parent);
	काष्ठा cmac_desc_ctx *ctx = shash_desc_ctx(pdesc);
	काष्ठा crypto_cipher *tfm = tctx->child;
	पूर्णांक bs = crypto_shash_blocksize(parent);
	u8 *odds = PTR_ALIGN((व्योम *)ctx->ctx, alignmask + 1);
	u8 *prev = odds + bs;

	/* checking the data can fill the block */
	अगर ((ctx->len + len) <= bs) अणु
		स_नकल(odds + ctx->len, p, len);
		ctx->len += len;
		वापस 0;
	पूर्ण

	/* filling odds with new data and encrypting it */
	स_नकल(odds + ctx->len, p, bs - ctx->len);
	len -= bs - ctx->len;
	p += bs - ctx->len;

	crypto_xor(prev, odds, bs);
	crypto_cipher_encrypt_one(tfm, prev, prev);

	/* clearing the length */
	ctx->len = 0;

	/* encrypting the rest of data */
	जबतक (len > bs) अणु
		crypto_xor(prev, p, bs);
		crypto_cipher_encrypt_one(tfm, prev, prev);
		p += bs;
		len -= bs;
	पूर्ण

	/* keeping the surplus of blocksize */
	अगर (len) अणु
		स_नकल(odds, p, len);
		ctx->len = len;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक crypto_cmac_digest_final(काष्ठा shash_desc *pdesc, u8 *out)
अणु
	काष्ठा crypto_shash *parent = pdesc->tfm;
	अचिन्हित दीर्घ alignmask = crypto_shash_alignmask(parent);
	काष्ठा cmac_tfm_ctx *tctx = crypto_shash_ctx(parent);
	काष्ठा cmac_desc_ctx *ctx = shash_desc_ctx(pdesc);
	काष्ठा crypto_cipher *tfm = tctx->child;
	पूर्णांक bs = crypto_shash_blocksize(parent);
	u8 *स्थिरs = PTR_ALIGN((व्योम *)tctx->ctx,
			       (alignmask | (__alignof__(__be64) - 1)) + 1);
	u8 *odds = PTR_ALIGN((व्योम *)ctx->ctx, alignmask + 1);
	u8 *prev = odds + bs;
	अचिन्हित पूर्णांक offset = 0;

	अगर (ctx->len != bs) अणु
		अचिन्हित पूर्णांक rlen;
		u8 *p = odds + ctx->len;

		*p = 0x80;
		p++;

		rlen = bs - ctx->len - 1;
		अगर (rlen)
			स_रखो(p, 0, rlen);

		offset += bs;
	पूर्ण

	crypto_xor(prev, odds, bs);
	crypto_xor(prev, स्थिरs + offset, bs);

	crypto_cipher_encrypt_one(tfm, out, prev);

	वापस 0;
पूर्ण

अटल पूर्णांक cmac_init_tfm(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा crypto_cipher *cipher;
	काष्ठा crypto_instance *inst = (व्योम *)tfm->__crt_alg;
	काष्ठा crypto_cipher_spawn *spawn = crypto_instance_ctx(inst);
	काष्ठा cmac_tfm_ctx *ctx = crypto_tfm_ctx(tfm);

	cipher = crypto_spawn_cipher(spawn);
	अगर (IS_ERR(cipher))
		वापस PTR_ERR(cipher);

	ctx->child = cipher;

	वापस 0;
पूर्ण;

अटल व्योम cmac_निकास_tfm(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा cmac_tfm_ctx *ctx = crypto_tfm_ctx(tfm);
	crypto_मुक्त_cipher(ctx->child);
पूर्ण

अटल पूर्णांक cmac_create(काष्ठा crypto_ढाँचा *पंचांगpl, काष्ठा rtattr **tb)
अणु
	काष्ठा shash_instance *inst;
	काष्ठा crypto_cipher_spawn *spawn;
	काष्ठा crypto_alg *alg;
	अचिन्हित दीर्घ alignmask;
	u32 mask;
	पूर्णांक err;

	err = crypto_check_attr_type(tb, CRYPTO_ALG_TYPE_SHASH, &mask);
	अगर (err)
		वापस err;

	inst = kzalloc(माप(*inst) + माप(*spawn), GFP_KERNEL);
	अगर (!inst)
		वापस -ENOMEM;
	spawn = shash_instance_ctx(inst);

	err = crypto_grab_cipher(spawn, shash_crypto_instance(inst),
				 crypto_attr_alg_name(tb[1]), 0, mask);
	अगर (err)
		जाओ err_मुक्त_inst;
	alg = crypto_spawn_cipher_alg(spawn);

	चयन (alg->cra_blocksize) अणु
	हाल 16:
	हाल 8:
		अवरोध;
	शेष:
		err = -EINVAL;
		जाओ err_मुक्त_inst;
	पूर्ण

	err = crypto_inst_setname(shash_crypto_instance(inst), पंचांगpl->name, alg);
	अगर (err)
		जाओ err_मुक्त_inst;

	alignmask = alg->cra_alignmask;
	inst->alg.base.cra_alignmask = alignmask;
	inst->alg.base.cra_priority = alg->cra_priority;
	inst->alg.base.cra_blocksize = alg->cra_blocksize;

	inst->alg.digestsize = alg->cra_blocksize;
	inst->alg.descsize =
		ALIGN(माप(काष्ठा cmac_desc_ctx), crypto_tfm_ctx_alignment())
		+ (alignmask & ~(crypto_tfm_ctx_alignment() - 1))
		+ alg->cra_blocksize * 2;

	inst->alg.base.cra_ctxsize =
		ALIGN(माप(काष्ठा cmac_tfm_ctx), crypto_tfm_ctx_alignment())
		+ ((alignmask | (__alignof__(__be64) - 1)) &
		   ~(crypto_tfm_ctx_alignment() - 1))
		+ alg->cra_blocksize * 2;

	inst->alg.base.cra_init = cmac_init_tfm;
	inst->alg.base.cra_निकास = cmac_निकास_tfm;

	inst->alg.init = crypto_cmac_digest_init;
	inst->alg.update = crypto_cmac_digest_update;
	inst->alg.final = crypto_cmac_digest_final;
	inst->alg.setkey = crypto_cmac_digest_setkey;

	inst->मुक्त = shash_मुक्त_singlespawn_instance;

	err = shash_रेजिस्टर_instance(पंचांगpl, inst);
	अगर (err) अणु
err_मुक्त_inst:
		shash_मुक्त_singlespawn_instance(inst);
	पूर्ण
	वापस err;
पूर्ण

अटल काष्ठा crypto_ढाँचा crypto_cmac_पंचांगpl = अणु
	.name = "cmac",
	.create = cmac_create,
	.module = THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init crypto_cmac_module_init(व्योम)
अणु
	वापस crypto_रेजिस्टर_ढाँचा(&crypto_cmac_पंचांगpl);
पूर्ण

अटल व्योम __निकास crypto_cmac_module_निकास(व्योम)
अणु
	crypto_unरेजिस्टर_ढाँचा(&crypto_cmac_पंचांगpl);
पूर्ण

subsys_initcall(crypto_cmac_module_init);
module_निकास(crypto_cmac_module_निकास);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("CMAC keyed hash algorithm");
MODULE_ALIAS_CRYPTO("cmac");
MODULE_IMPORT_NS(CRYPTO_INTERNAL);
