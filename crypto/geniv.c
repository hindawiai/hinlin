<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * geniv: Shared IV generator code
 *
 * This file provides common code to IV generators such as seqiv.
 *
 * Copyright (c) 2007-2019 Herbert Xu <herbert@gonकरोr.apana.org.au>
 */

#समावेश <crypto/पूर्णांकernal/geniv.h>
#समावेश <crypto/पूर्णांकernal/rng.h>
#समावेश <crypto/null.h>
#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/slab.h>

अटल पूर्णांक aead_geniv_setkey(काष्ठा crypto_aead *tfm,
			     स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा aead_geniv_ctx *ctx = crypto_aead_ctx(tfm);

	वापस crypto_aead_setkey(ctx->child, key, keylen);
पूर्ण

अटल पूर्णांक aead_geniv_setauthsize(काष्ठा crypto_aead *tfm,
				  अचिन्हित पूर्णांक authsize)
अणु
	काष्ठा aead_geniv_ctx *ctx = crypto_aead_ctx(tfm);

	वापस crypto_aead_setauthsize(ctx->child, authsize);
पूर्ण

अटल व्योम aead_geniv_मुक्त(काष्ठा aead_instance *inst)
अणु
	crypto_drop_aead(aead_instance_ctx(inst));
	kमुक्त(inst);
पूर्ण

काष्ठा aead_instance *aead_geniv_alloc(काष्ठा crypto_ढाँचा *पंचांगpl,
				       काष्ठा rtattr **tb)
अणु
	काष्ठा crypto_aead_spawn *spawn;
	काष्ठा aead_instance *inst;
	काष्ठा aead_alg *alg;
	अचिन्हित पूर्णांक ivsize;
	अचिन्हित पूर्णांक maxauthsize;
	u32 mask;
	पूर्णांक err;

	err = crypto_check_attr_type(tb, CRYPTO_ALG_TYPE_AEAD, &mask);
	अगर (err)
		वापस ERR_PTR(err);

	inst = kzalloc(माप(*inst) + माप(*spawn), GFP_KERNEL);
	अगर (!inst)
		वापस ERR_PTR(-ENOMEM);

	spawn = aead_instance_ctx(inst);

	err = crypto_grab_aead(spawn, aead_crypto_instance(inst),
			       crypto_attr_alg_name(tb[1]), 0, mask);
	अगर (err)
		जाओ err_मुक्त_inst;

	alg = crypto_spawn_aead_alg(spawn);

	ivsize = crypto_aead_alg_ivsize(alg);
	maxauthsize = crypto_aead_alg_maxauthsize(alg);

	err = -EINVAL;
	अगर (ivsize < माप(u64))
		जाओ err_मुक्त_inst;

	err = -ENAMETOOLONG;
	अगर (snम_लिखो(inst->alg.base.cra_name, CRYPTO_MAX_ALG_NAME,
		     "%s(%s)", पंचांगpl->name, alg->base.cra_name) >=
	    CRYPTO_MAX_ALG_NAME)
		जाओ err_मुक्त_inst;
	अगर (snम_लिखो(inst->alg.base.cra_driver_name, CRYPTO_MAX_ALG_NAME,
		     "%s(%s)", पंचांगpl->name, alg->base.cra_driver_name) >=
	    CRYPTO_MAX_ALG_NAME)
		जाओ err_मुक्त_inst;

	inst->alg.base.cra_priority = alg->base.cra_priority;
	inst->alg.base.cra_blocksize = alg->base.cra_blocksize;
	inst->alg.base.cra_alignmask = alg->base.cra_alignmask;
	inst->alg.base.cra_ctxsize = माप(काष्ठा aead_geniv_ctx);

	inst->alg.setkey = aead_geniv_setkey;
	inst->alg.setauthsize = aead_geniv_setauthsize;

	inst->alg.ivsize = ivsize;
	inst->alg.maxauthsize = maxauthsize;

	inst->मुक्त = aead_geniv_मुक्त;

out:
	वापस inst;

err_मुक्त_inst:
	aead_geniv_मुक्त(inst);
	inst = ERR_PTR(err);
	जाओ out;
पूर्ण
EXPORT_SYMBOL_GPL(aead_geniv_alloc);

पूर्णांक aead_init_geniv(काष्ठा crypto_aead *aead)
अणु
	काष्ठा aead_geniv_ctx *ctx = crypto_aead_ctx(aead);
	काष्ठा aead_instance *inst = aead_alg_instance(aead);
	काष्ठा crypto_aead *child;
	पूर्णांक err;

	spin_lock_init(&ctx->lock);

	err = crypto_get_शेष_rng();
	अगर (err)
		जाओ out;

	err = crypto_rng_get_bytes(crypto_शेष_rng, ctx->salt,
				   crypto_aead_ivsize(aead));
	crypto_put_शेष_rng();
	अगर (err)
		जाओ out;

	ctx->sknull = crypto_get_शेष_null_skcipher();
	err = PTR_ERR(ctx->sknull);
	अगर (IS_ERR(ctx->sknull))
		जाओ out;

	child = crypto_spawn_aead(aead_instance_ctx(inst));
	err = PTR_ERR(child);
	अगर (IS_ERR(child))
		जाओ drop_null;

	ctx->child = child;
	crypto_aead_set_reqsize(aead, crypto_aead_reqsize(child) +
				      माप(काष्ठा aead_request));

	err = 0;

out:
	वापस err;

drop_null:
	crypto_put_शेष_null_skcipher();
	जाओ out;
पूर्ण
EXPORT_SYMBOL_GPL(aead_init_geniv);

व्योम aead_निकास_geniv(काष्ठा crypto_aead *tfm)
अणु
	काष्ठा aead_geniv_ctx *ctx = crypto_aead_ctx(tfm);

	crypto_मुक्त_aead(ctx->child);
	crypto_put_शेष_null_skcipher();
पूर्ण
EXPORT_SYMBOL_GPL(aead_निकास_geniv);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Shared IV generator code");
