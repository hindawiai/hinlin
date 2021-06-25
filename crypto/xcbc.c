<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C)2006 USAGI/WIDE Project
 *
 * Author:
 * 	Kazunori Miyazawa <miyazawa@linux-ipv6.org>
 */

#समावेश <crypto/पूर्णांकernal/cipher.h>
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>

अटल u_पूर्णांक32_t ks[12] = अणु0x01010101, 0x01010101, 0x01010101, 0x01010101,
			   0x02020202, 0x02020202, 0x02020202, 0x02020202,
			   0x03030303, 0x03030303, 0x03030303, 0x03030303पूर्ण;

/*
 * +------------------------
 * | <parent tfm>
 * +------------------------
 * | xcbc_tfm_ctx
 * +------------------------
 * | स्थिरs (block size * 2)
 * +------------------------
 */
काष्ठा xcbc_tfm_ctx अणु
	काष्ठा crypto_cipher *child;
	u8 ctx[];
पूर्ण;

/*
 * +------------------------
 * | <shash desc>
 * +------------------------
 * | xcbc_desc_ctx
 * +------------------------
 * | odds (block size)
 * +------------------------
 * | prev (block size)
 * +------------------------
 */
काष्ठा xcbc_desc_ctx अणु
	अचिन्हित पूर्णांक len;
	u8 ctx[];
पूर्ण;

#घोषणा XCBC_BLOCKSIZE	16

अटल पूर्णांक crypto_xcbc_digest_setkey(काष्ठा crypto_shash *parent,
				     स्थिर u8 *inkey, अचिन्हित पूर्णांक keylen)
अणु
	अचिन्हित दीर्घ alignmask = crypto_shash_alignmask(parent);
	काष्ठा xcbc_tfm_ctx *ctx = crypto_shash_ctx(parent);
	u8 *स्थिरs = PTR_ALIGN(&ctx->ctx[0], alignmask + 1);
	पूर्णांक err = 0;
	u8 key1[XCBC_BLOCKSIZE];
	पूर्णांक bs = माप(key1);

	अगर ((err = crypto_cipher_setkey(ctx->child, inkey, keylen)))
		वापस err;

	crypto_cipher_encrypt_one(ctx->child, स्थिरs, (u8 *)ks + bs);
	crypto_cipher_encrypt_one(ctx->child, स्थिरs + bs, (u8 *)ks + bs * 2);
	crypto_cipher_encrypt_one(ctx->child, key1, (u8 *)ks);

	वापस crypto_cipher_setkey(ctx->child, key1, bs);

पूर्ण

अटल पूर्णांक crypto_xcbc_digest_init(काष्ठा shash_desc *pdesc)
अणु
	अचिन्हित दीर्घ alignmask = crypto_shash_alignmask(pdesc->tfm);
	काष्ठा xcbc_desc_ctx *ctx = shash_desc_ctx(pdesc);
	पूर्णांक bs = crypto_shash_blocksize(pdesc->tfm);
	u8 *prev = PTR_ALIGN(&ctx->ctx[0], alignmask + 1) + bs;

	ctx->len = 0;
	स_रखो(prev, 0, bs);

	वापस 0;
पूर्ण

अटल पूर्णांक crypto_xcbc_digest_update(काष्ठा shash_desc *pdesc, स्थिर u8 *p,
				     अचिन्हित पूर्णांक len)
अणु
	काष्ठा crypto_shash *parent = pdesc->tfm;
	अचिन्हित दीर्घ alignmask = crypto_shash_alignmask(parent);
	काष्ठा xcbc_tfm_ctx *tctx = crypto_shash_ctx(parent);
	काष्ठा xcbc_desc_ctx *ctx = shash_desc_ctx(pdesc);
	काष्ठा crypto_cipher *tfm = tctx->child;
	पूर्णांक bs = crypto_shash_blocksize(parent);
	u8 *odds = PTR_ALIGN(&ctx->ctx[0], alignmask + 1);
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

अटल पूर्णांक crypto_xcbc_digest_final(काष्ठा shash_desc *pdesc, u8 *out)
अणु
	काष्ठा crypto_shash *parent = pdesc->tfm;
	अचिन्हित दीर्घ alignmask = crypto_shash_alignmask(parent);
	काष्ठा xcbc_tfm_ctx *tctx = crypto_shash_ctx(parent);
	काष्ठा xcbc_desc_ctx *ctx = shash_desc_ctx(pdesc);
	काष्ठा crypto_cipher *tfm = tctx->child;
	पूर्णांक bs = crypto_shash_blocksize(parent);
	u8 *स्थिरs = PTR_ALIGN(&tctx->ctx[0], alignmask + 1);
	u8 *odds = PTR_ALIGN(&ctx->ctx[0], alignmask + 1);
	u8 *prev = odds + bs;
	अचिन्हित पूर्णांक offset = 0;

	अगर (ctx->len != bs) अणु
		अचिन्हित पूर्णांक rlen;
		u8 *p = odds + ctx->len;

		*p = 0x80;
		p++;

		rlen = bs - ctx->len -1;
		अगर (rlen)
			स_रखो(p, 0, rlen);

		offset += bs;
	पूर्ण

	crypto_xor(prev, odds, bs);
	crypto_xor(prev, स्थिरs + offset, bs);

	crypto_cipher_encrypt_one(tfm, out, prev);

	वापस 0;
पूर्ण

अटल पूर्णांक xcbc_init_tfm(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा crypto_cipher *cipher;
	काष्ठा crypto_instance *inst = (व्योम *)tfm->__crt_alg;
	काष्ठा crypto_cipher_spawn *spawn = crypto_instance_ctx(inst);
	काष्ठा xcbc_tfm_ctx *ctx = crypto_tfm_ctx(tfm);

	cipher = crypto_spawn_cipher(spawn);
	अगर (IS_ERR(cipher))
		वापस PTR_ERR(cipher);

	ctx->child = cipher;

	वापस 0;
पूर्ण;

अटल व्योम xcbc_निकास_tfm(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा xcbc_tfm_ctx *ctx = crypto_tfm_ctx(tfm);
	crypto_मुक्त_cipher(ctx->child);
पूर्ण

अटल पूर्णांक xcbc_create(काष्ठा crypto_ढाँचा *पंचांगpl, काष्ठा rtattr **tb)
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

	err = -EINVAL;
	अगर (alg->cra_blocksize != XCBC_BLOCKSIZE)
		जाओ err_मुक्त_inst;

	err = crypto_inst_setname(shash_crypto_instance(inst), पंचांगpl->name, alg);
	अगर (err)
		जाओ err_मुक्त_inst;

	alignmask = alg->cra_alignmask | 3;
	inst->alg.base.cra_alignmask = alignmask;
	inst->alg.base.cra_priority = alg->cra_priority;
	inst->alg.base.cra_blocksize = alg->cra_blocksize;

	inst->alg.digestsize = alg->cra_blocksize;
	inst->alg.descsize = ALIGN(माप(काष्ठा xcbc_desc_ctx),
				   crypto_tfm_ctx_alignment()) +
			     (alignmask &
			      ~(crypto_tfm_ctx_alignment() - 1)) +
			     alg->cra_blocksize * 2;

	inst->alg.base.cra_ctxsize = ALIGN(माप(काष्ठा xcbc_tfm_ctx),
					   alignmask + 1) +
				     alg->cra_blocksize * 2;
	inst->alg.base.cra_init = xcbc_init_tfm;
	inst->alg.base.cra_निकास = xcbc_निकास_tfm;

	inst->alg.init = crypto_xcbc_digest_init;
	inst->alg.update = crypto_xcbc_digest_update;
	inst->alg.final = crypto_xcbc_digest_final;
	inst->alg.setkey = crypto_xcbc_digest_setkey;

	inst->मुक्त = shash_मुक्त_singlespawn_instance;

	err = shash_रेजिस्टर_instance(पंचांगpl, inst);
	अगर (err) अणु
err_मुक्त_inst:
		shash_मुक्त_singlespawn_instance(inst);
	पूर्ण
	वापस err;
पूर्ण

अटल काष्ठा crypto_ढाँचा crypto_xcbc_पंचांगpl = अणु
	.name = "xcbc",
	.create = xcbc_create,
	.module = THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init crypto_xcbc_module_init(व्योम)
अणु
	वापस crypto_रेजिस्टर_ढाँचा(&crypto_xcbc_पंचांगpl);
पूर्ण

अटल व्योम __निकास crypto_xcbc_module_निकास(व्योम)
अणु
	crypto_unरेजिस्टर_ढाँचा(&crypto_xcbc_पंचांगpl);
पूर्ण

subsys_initcall(crypto_xcbc_module_init);
module_निकास(crypto_xcbc_module_निकास);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("XCBC keyed hash algorithm");
MODULE_ALIAS_CRYPTO("xcbc");
MODULE_IMPORT_NS(CRYPTO_INTERNAL);
