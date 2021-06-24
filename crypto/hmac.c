<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Cryptographic API.
 *
 * HMAC: Keyed-Hashing क्रम Message Authentication (RFC2104).
 *
 * Copyright (c) 2002 James Morris <jmorris@पूर्णांकercode.com.au>
 * Copyright (c) 2006 Herbert Xu <herbert@gonकरोr.apana.org.au>
 *
 * The HMAC implementation is derived from USAGI.
 * Copyright (c) 2002 Kazunori Miyazawa <miyazawa@linux-ipv6.org> / USAGI
 */

#समावेश <crypto/hmac.h>
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/scatterwalk.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/माला.स>

काष्ठा hmac_ctx अणु
	काष्ठा crypto_shash *hash;
पूर्ण;

अटल अंतरभूत व्योम *align_ptr(व्योम *p, अचिन्हित पूर्णांक align)
अणु
	वापस (व्योम *)ALIGN((अचिन्हित दीर्घ)p, align);
पूर्ण

अटल अंतरभूत काष्ठा hmac_ctx *hmac_ctx(काष्ठा crypto_shash *tfm)
अणु
	वापस align_ptr(crypto_shash_ctx_aligned(tfm) +
			 crypto_shash_statesize(tfm) * 2,
			 crypto_tfm_ctx_alignment());
पूर्ण

अटल पूर्णांक hmac_setkey(काष्ठा crypto_shash *parent,
		       स्थिर u8 *inkey, अचिन्हित पूर्णांक keylen)
अणु
	पूर्णांक bs = crypto_shash_blocksize(parent);
	पूर्णांक ds = crypto_shash_digestsize(parent);
	पूर्णांक ss = crypto_shash_statesize(parent);
	अक्षर *ipad = crypto_shash_ctx_aligned(parent);
	अक्षर *opad = ipad + ss;
	काष्ठा hmac_ctx *ctx = align_ptr(opad + ss,
					 crypto_tfm_ctx_alignment());
	काष्ठा crypto_shash *hash = ctx->hash;
	SHASH_DESC_ON_STACK(shash, hash);
	अचिन्हित पूर्णांक i;

	shash->tfm = hash;

	अगर (keylen > bs) अणु
		पूर्णांक err;

		err = crypto_shash_digest(shash, inkey, keylen, ipad);
		अगर (err)
			वापस err;

		keylen = ds;
	पूर्ण अन्यथा
		स_नकल(ipad, inkey, keylen);

	स_रखो(ipad + keylen, 0, bs - keylen);
	स_नकल(opad, ipad, bs);

	क्रम (i = 0; i < bs; i++) अणु
		ipad[i] ^= HMAC_IPAD_VALUE;
		opad[i] ^= HMAC_OPAD_VALUE;
	पूर्ण

	वापस crypto_shash_init(shash) ?:
	       crypto_shash_update(shash, ipad, bs) ?:
	       crypto_shash_export(shash, ipad) ?:
	       crypto_shash_init(shash) ?:
	       crypto_shash_update(shash, opad, bs) ?:
	       crypto_shash_export(shash, opad);
पूर्ण

अटल पूर्णांक hmac_export(काष्ठा shash_desc *pdesc, व्योम *out)
अणु
	काष्ठा shash_desc *desc = shash_desc_ctx(pdesc);

	वापस crypto_shash_export(desc, out);
पूर्ण

अटल पूर्णांक hmac_import(काष्ठा shash_desc *pdesc, स्थिर व्योम *in)
अणु
	काष्ठा shash_desc *desc = shash_desc_ctx(pdesc);
	काष्ठा hmac_ctx *ctx = hmac_ctx(pdesc->tfm);

	desc->tfm = ctx->hash;

	वापस crypto_shash_import(desc, in);
पूर्ण

अटल पूर्णांक hmac_init(काष्ठा shash_desc *pdesc)
अणु
	वापस hmac_import(pdesc, crypto_shash_ctx_aligned(pdesc->tfm));
पूर्ण

अटल पूर्णांक hmac_update(काष्ठा shash_desc *pdesc,
		       स्थिर u8 *data, अचिन्हित पूर्णांक nbytes)
अणु
	काष्ठा shash_desc *desc = shash_desc_ctx(pdesc);

	वापस crypto_shash_update(desc, data, nbytes);
पूर्ण

अटल पूर्णांक hmac_final(काष्ठा shash_desc *pdesc, u8 *out)
अणु
	काष्ठा crypto_shash *parent = pdesc->tfm;
	पूर्णांक ds = crypto_shash_digestsize(parent);
	पूर्णांक ss = crypto_shash_statesize(parent);
	अक्षर *opad = crypto_shash_ctx_aligned(parent) + ss;
	काष्ठा shash_desc *desc = shash_desc_ctx(pdesc);

	वापस crypto_shash_final(desc, out) ?:
	       crypto_shash_import(desc, opad) ?:
	       crypto_shash_finup(desc, out, ds, out);
पूर्ण

अटल पूर्णांक hmac_finup(काष्ठा shash_desc *pdesc, स्थिर u8 *data,
		      अचिन्हित पूर्णांक nbytes, u8 *out)
अणु

	काष्ठा crypto_shash *parent = pdesc->tfm;
	पूर्णांक ds = crypto_shash_digestsize(parent);
	पूर्णांक ss = crypto_shash_statesize(parent);
	अक्षर *opad = crypto_shash_ctx_aligned(parent) + ss;
	काष्ठा shash_desc *desc = shash_desc_ctx(pdesc);

	वापस crypto_shash_finup(desc, data, nbytes, out) ?:
	       crypto_shash_import(desc, opad) ?:
	       crypto_shash_finup(desc, out, ds, out);
पूर्ण

अटल पूर्णांक hmac_init_tfm(काष्ठा crypto_shash *parent)
अणु
	काष्ठा crypto_shash *hash;
	काष्ठा shash_instance *inst = shash_alg_instance(parent);
	काष्ठा crypto_shash_spawn *spawn = shash_instance_ctx(inst);
	काष्ठा hmac_ctx *ctx = hmac_ctx(parent);

	hash = crypto_spawn_shash(spawn);
	अगर (IS_ERR(hash))
		वापस PTR_ERR(hash);

	parent->descsize = माप(काष्ठा shash_desc) +
			   crypto_shash_descsize(hash);

	ctx->hash = hash;
	वापस 0;
पूर्ण

अटल व्योम hmac_निकास_tfm(काष्ठा crypto_shash *parent)
अणु
	काष्ठा hmac_ctx *ctx = hmac_ctx(parent);
	crypto_मुक्त_shash(ctx->hash);
पूर्ण

अटल पूर्णांक hmac_create(काष्ठा crypto_ढाँचा *पंचांगpl, काष्ठा rtattr **tb)
अणु
	काष्ठा shash_instance *inst;
	काष्ठा crypto_shash_spawn *spawn;
	काष्ठा crypto_alg *alg;
	काष्ठा shash_alg *salg;
	u32 mask;
	पूर्णांक err;
	पूर्णांक ds;
	पूर्णांक ss;

	err = crypto_check_attr_type(tb, CRYPTO_ALG_TYPE_SHASH, &mask);
	अगर (err)
		वापस err;

	inst = kzalloc(माप(*inst) + माप(*spawn), GFP_KERNEL);
	अगर (!inst)
		वापस -ENOMEM;
	spawn = shash_instance_ctx(inst);

	err = crypto_grab_shash(spawn, shash_crypto_instance(inst),
				crypto_attr_alg_name(tb[1]), 0, mask);
	अगर (err)
		जाओ err_मुक्त_inst;
	salg = crypto_spawn_shash_alg(spawn);
	alg = &salg->base;

	/* The underlying hash algorithm must not require a key */
	err = -EINVAL;
	अगर (crypto_shash_alg_needs_key(salg))
		जाओ err_मुक्त_inst;

	ds = salg->digestsize;
	ss = salg->statesize;
	अगर (ds > alg->cra_blocksize ||
	    ss < alg->cra_blocksize)
		जाओ err_मुक्त_inst;

	err = crypto_inst_setname(shash_crypto_instance(inst), पंचांगpl->name, alg);
	अगर (err)
		जाओ err_मुक्त_inst;

	inst->alg.base.cra_priority = alg->cra_priority;
	inst->alg.base.cra_blocksize = alg->cra_blocksize;
	inst->alg.base.cra_alignmask = alg->cra_alignmask;

	ss = ALIGN(ss, alg->cra_alignmask + 1);
	inst->alg.digestsize = ds;
	inst->alg.statesize = ss;

	inst->alg.base.cra_ctxsize = माप(काष्ठा hmac_ctx) +
				     ALIGN(ss * 2, crypto_tfm_ctx_alignment());

	inst->alg.init = hmac_init;
	inst->alg.update = hmac_update;
	inst->alg.final = hmac_final;
	inst->alg.finup = hmac_finup;
	inst->alg.export = hmac_export;
	inst->alg.import = hmac_import;
	inst->alg.setkey = hmac_setkey;
	inst->alg.init_tfm = hmac_init_tfm;
	inst->alg.निकास_tfm = hmac_निकास_tfm;

	inst->मुक्त = shash_मुक्त_singlespawn_instance;

	err = shash_रेजिस्टर_instance(पंचांगpl, inst);
	अगर (err) अणु
err_मुक्त_inst:
		shash_मुक्त_singlespawn_instance(inst);
	पूर्ण
	वापस err;
पूर्ण

अटल काष्ठा crypto_ढाँचा hmac_पंचांगpl = अणु
	.name = "hmac",
	.create = hmac_create,
	.module = THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init hmac_module_init(व्योम)
अणु
	वापस crypto_रेजिस्टर_ढाँचा(&hmac_पंचांगpl);
पूर्ण

अटल व्योम __निकास hmac_module_निकास(व्योम)
अणु
	crypto_unरेजिस्टर_ढाँचा(&hmac_पंचांगpl);
पूर्ण

subsys_initcall(hmac_module_init);
module_निकास(hmac_module_निकास);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("HMAC hash algorithm");
MODULE_ALIAS_CRYPTO("hmac");
