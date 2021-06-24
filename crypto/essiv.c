<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ESSIV skcipher and aead ढाँचा क्रम block encryption
 *
 * This ढाँचा encapsulates the ESSIV IV generation algorithm used by
 * dm-crypt and fscrypt, which converts the initial vector क्रम the skcipher
 * used क्रम block encryption, by encrypting it using the hash of the
 * skcipher key as encryption key. Usually, the input IV is a 64-bit sector
 * number in LE representation zero-padded to the size of the IV, but this
 * is not assumed by this driver.
 *
 * The typical use of this ढाँचा is to instantiate the skcipher
 * 'essiv(cbc(aes),sha256)', which is the only instantiation used by
 * fscrypt, and the most relevant one क्रम dm-crypt. However, dm-crypt
 * also permits ESSIV to be used in combination with the authenc ढाँचा,
 * e.g., 'essiv(authenc(hmac(sha256),cbc(aes)),sha256)', in which हाल
 * we need to instantiate an aead that accepts the same special key क्रमmat
 * as the authenc ढाँचा, and deals with the way the encrypted IV is
 * embedded पूर्णांकo the AAD area of the aead request. This means the AEAD
 * flavor produced by this ढाँचा is tightly coupled to the way dm-crypt
 * happens to use it.
 *
 * Copyright (c) 2019 Linaro, Ltd. <ard.biesheuvel@linaro.org>
 *
 * Heavily based on:
 * adiantum length-preserving encryption mode
 *
 * Copyright 2018 Google LLC
 */

#समावेश <crypto/authenc.h>
#समावेश <crypto/पूर्णांकernal/aead.h>
#समावेश <crypto/पूर्णांकernal/cipher.h>
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश <crypto/scatterwalk.h>
#समावेश <linux/module.h>

#समावेश "internal.h"

काष्ठा essiv_instance_ctx अणु
	जोड़ अणु
		काष्ठा crypto_skcipher_spawn	skcipher_spawn;
		काष्ठा crypto_aead_spawn	aead_spawn;
	पूर्ण u;
	अक्षर	essiv_cipher_name[CRYPTO_MAX_ALG_NAME];
	अक्षर	shash_driver_name[CRYPTO_MAX_ALG_NAME];
पूर्ण;

काष्ठा essiv_tfm_ctx अणु
	जोड़ अणु
		काष्ठा crypto_skcipher	*skcipher;
		काष्ठा crypto_aead	*aead;
	पूर्ण u;
	काष्ठा crypto_cipher		*essiv_cipher;
	काष्ठा crypto_shash		*hash;
	पूर्णांक				ivoffset;
पूर्ण;

काष्ठा essiv_aead_request_ctx अणु
	काष्ठा scatterlist		sg[4];
	u8				*assoc;
	काष्ठा aead_request		aead_req;
पूर्ण;

अटल पूर्णांक essiv_skcipher_setkey(काष्ठा crypto_skcipher *tfm,
				 स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा essiv_tfm_ctx *tctx = crypto_skcipher_ctx(tfm);
	u8 salt[HASH_MAX_DIGESTSIZE];
	पूर्णांक err;

	crypto_skcipher_clear_flags(tctx->u.skcipher, CRYPTO_TFM_REQ_MASK);
	crypto_skcipher_set_flags(tctx->u.skcipher,
				  crypto_skcipher_get_flags(tfm) &
				  CRYPTO_TFM_REQ_MASK);
	err = crypto_skcipher_setkey(tctx->u.skcipher, key, keylen);
	अगर (err)
		वापस err;

	err = crypto_shash_tfm_digest(tctx->hash, key, keylen, salt);
	अगर (err)
		वापस err;

	crypto_cipher_clear_flags(tctx->essiv_cipher, CRYPTO_TFM_REQ_MASK);
	crypto_cipher_set_flags(tctx->essiv_cipher,
				crypto_skcipher_get_flags(tfm) &
				CRYPTO_TFM_REQ_MASK);
	वापस crypto_cipher_setkey(tctx->essiv_cipher, salt,
				    crypto_shash_digestsize(tctx->hash));
पूर्ण

अटल पूर्णांक essiv_aead_setkey(काष्ठा crypto_aead *tfm, स्थिर u8 *key,
			     अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा essiv_tfm_ctx *tctx = crypto_aead_ctx(tfm);
	SHASH_DESC_ON_STACK(desc, tctx->hash);
	काष्ठा crypto_authenc_keys keys;
	u8 salt[HASH_MAX_DIGESTSIZE];
	पूर्णांक err;

	crypto_aead_clear_flags(tctx->u.aead, CRYPTO_TFM_REQ_MASK);
	crypto_aead_set_flags(tctx->u.aead, crypto_aead_get_flags(tfm) &
					    CRYPTO_TFM_REQ_MASK);
	err = crypto_aead_setkey(tctx->u.aead, key, keylen);
	अगर (err)
		वापस err;

	अगर (crypto_authenc_extractkeys(&keys, key, keylen) != 0)
		वापस -EINVAL;

	desc->tfm = tctx->hash;
	err = crypto_shash_init(desc) ?:
	      crypto_shash_update(desc, keys.enckey, keys.enckeylen) ?:
	      crypto_shash_finup(desc, keys.authkey, keys.authkeylen, salt);
	अगर (err)
		वापस err;

	crypto_cipher_clear_flags(tctx->essiv_cipher, CRYPTO_TFM_REQ_MASK);
	crypto_cipher_set_flags(tctx->essiv_cipher, crypto_aead_get_flags(tfm) &
						    CRYPTO_TFM_REQ_MASK);
	वापस crypto_cipher_setkey(tctx->essiv_cipher, salt,
				    crypto_shash_digestsize(tctx->hash));
पूर्ण

अटल पूर्णांक essiv_aead_setauthsize(काष्ठा crypto_aead *tfm,
				  अचिन्हित पूर्णांक authsize)
अणु
	काष्ठा essiv_tfm_ctx *tctx = crypto_aead_ctx(tfm);

	वापस crypto_aead_setauthsize(tctx->u.aead, authsize);
पूर्ण

अटल व्योम essiv_skcipher_करोne(काष्ठा crypto_async_request *areq, पूर्णांक err)
अणु
	काष्ठा skcipher_request *req = areq->data;

	skcipher_request_complete(req, err);
पूर्ण

अटल पूर्णांक essiv_skcipher_crypt(काष्ठा skcipher_request *req, bool enc)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	स्थिर काष्ठा essiv_tfm_ctx *tctx = crypto_skcipher_ctx(tfm);
	काष्ठा skcipher_request *subreq = skcipher_request_ctx(req);

	crypto_cipher_encrypt_one(tctx->essiv_cipher, req->iv, req->iv);

	skcipher_request_set_tfm(subreq, tctx->u.skcipher);
	skcipher_request_set_crypt(subreq, req->src, req->dst, req->cryptlen,
				   req->iv);
	skcipher_request_set_callback(subreq, skcipher_request_flags(req),
				      essiv_skcipher_करोne, req);

	वापस enc ? crypto_skcipher_encrypt(subreq) :
		     crypto_skcipher_decrypt(subreq);
पूर्ण

अटल पूर्णांक essiv_skcipher_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस essiv_skcipher_crypt(req, true);
पूर्ण

अटल पूर्णांक essiv_skcipher_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस essiv_skcipher_crypt(req, false);
पूर्ण

अटल व्योम essiv_aead_करोne(काष्ठा crypto_async_request *areq, पूर्णांक err)
अणु
	काष्ठा aead_request *req = areq->data;
	काष्ठा essiv_aead_request_ctx *rctx = aead_request_ctx(req);

	kमुक्त(rctx->assoc);
	aead_request_complete(req, err);
पूर्ण

अटल पूर्णांक essiv_aead_crypt(काष्ठा aead_request *req, bool enc)
अणु
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	स्थिर काष्ठा essiv_tfm_ctx *tctx = crypto_aead_ctx(tfm);
	काष्ठा essiv_aead_request_ctx *rctx = aead_request_ctx(req);
	काष्ठा aead_request *subreq = &rctx->aead_req;
	काष्ठा scatterlist *src = req->src;
	पूर्णांक err;

	crypto_cipher_encrypt_one(tctx->essiv_cipher, req->iv, req->iv);

	/*
	 * dm-crypt embeds the sector number and the IV in the AAD region, so
	 * we have to copy the converted IV पूर्णांकo the right scatterlist beक्रमe
	 * we pass it on.
	 */
	rctx->assoc = शून्य;
	अगर (req->src == req->dst || !enc) अणु
		scatterwalk_map_and_copy(req->iv, req->dst,
					 req->assoclen - crypto_aead_ivsize(tfm),
					 crypto_aead_ivsize(tfm), 1);
	पूर्ण अन्यथा अणु
		u8 *iv = (u8 *)aead_request_ctx(req) + tctx->ivoffset;
		पूर्णांक ivsize = crypto_aead_ivsize(tfm);
		पूर्णांक ssize = req->assoclen - ivsize;
		काष्ठा scatterlist *sg;
		पूर्णांक nents;

		अगर (ssize < 0)
			वापस -EINVAL;

		nents = sg_nents_क्रम_len(req->src, ssize);
		अगर (nents < 0)
			वापस -EINVAL;

		स_नकल(iv, req->iv, ivsize);
		sg_init_table(rctx->sg, 4);

		अगर (unlikely(nents > 1)) अणु
			/*
			 * This is a हाल that rarely occurs in practice, but
			 * क्रम correctness, we have to deal with it nonetheless.
			 */
			rctx->assoc = kदो_स्मृति(ssize, GFP_ATOMIC);
			अगर (!rctx->assoc)
				वापस -ENOMEM;

			scatterwalk_map_and_copy(rctx->assoc, req->src, 0,
						 ssize, 0);
			sg_set_buf(rctx->sg, rctx->assoc, ssize);
		पूर्ण अन्यथा अणु
			sg_set_page(rctx->sg, sg_page(req->src), ssize,
				    req->src->offset);
		पूर्ण

		sg_set_buf(rctx->sg + 1, iv, ivsize);
		sg = scatterwalk_ffwd(rctx->sg + 2, req->src, req->assoclen);
		अगर (sg != rctx->sg + 2)
			sg_chain(rctx->sg, 3, sg);

		src = rctx->sg;
	पूर्ण

	aead_request_set_tfm(subreq, tctx->u.aead);
	aead_request_set_ad(subreq, req->assoclen);
	aead_request_set_callback(subreq, aead_request_flags(req),
				  essiv_aead_करोne, req);
	aead_request_set_crypt(subreq, src, req->dst, req->cryptlen, req->iv);

	err = enc ? crypto_aead_encrypt(subreq) :
		    crypto_aead_decrypt(subreq);

	अगर (rctx->assoc && err != -EINPROGRESS)
		kमुक्त(rctx->assoc);
	वापस err;
पूर्ण

अटल पूर्णांक essiv_aead_encrypt(काष्ठा aead_request *req)
अणु
	वापस essiv_aead_crypt(req, true);
पूर्ण

अटल पूर्णांक essiv_aead_decrypt(काष्ठा aead_request *req)
अणु
	वापस essiv_aead_crypt(req, false);
पूर्ण

अटल पूर्णांक essiv_init_tfm(काष्ठा essiv_instance_ctx *ictx,
			  काष्ठा essiv_tfm_ctx *tctx)
अणु
	काष्ठा crypto_cipher *essiv_cipher;
	काष्ठा crypto_shash *hash;
	पूर्णांक err;

	essiv_cipher = crypto_alloc_cipher(ictx->essiv_cipher_name, 0, 0);
	अगर (IS_ERR(essiv_cipher))
		वापस PTR_ERR(essiv_cipher);

	hash = crypto_alloc_shash(ictx->shash_driver_name, 0, 0);
	अगर (IS_ERR(hash)) अणु
		err = PTR_ERR(hash);
		जाओ err_मुक्त_essiv_cipher;
	पूर्ण

	tctx->essiv_cipher = essiv_cipher;
	tctx->hash = hash;

	वापस 0;

err_मुक्त_essiv_cipher:
	crypto_मुक्त_cipher(essiv_cipher);
	वापस err;
पूर्ण

अटल पूर्णांक essiv_skcipher_init_tfm(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा skcipher_instance *inst = skcipher_alg_instance(tfm);
	काष्ठा essiv_instance_ctx *ictx = skcipher_instance_ctx(inst);
	काष्ठा essiv_tfm_ctx *tctx = crypto_skcipher_ctx(tfm);
	काष्ठा crypto_skcipher *skcipher;
	पूर्णांक err;

	skcipher = crypto_spawn_skcipher(&ictx->u.skcipher_spawn);
	अगर (IS_ERR(skcipher))
		वापस PTR_ERR(skcipher);

	crypto_skcipher_set_reqsize(tfm, माप(काष्ठा skcipher_request) +
				         crypto_skcipher_reqsize(skcipher));

	err = essiv_init_tfm(ictx, tctx);
	अगर (err) अणु
		crypto_मुक्त_skcipher(skcipher);
		वापस err;
	पूर्ण

	tctx->u.skcipher = skcipher;
	वापस 0;
पूर्ण

अटल पूर्णांक essiv_aead_init_tfm(काष्ठा crypto_aead *tfm)
अणु
	काष्ठा aead_instance *inst = aead_alg_instance(tfm);
	काष्ठा essiv_instance_ctx *ictx = aead_instance_ctx(inst);
	काष्ठा essiv_tfm_ctx *tctx = crypto_aead_ctx(tfm);
	काष्ठा crypto_aead *aead;
	अचिन्हित पूर्णांक subreq_size;
	पूर्णांक err;

	BUILD_BUG_ON(दुरत्वend(काष्ठा essiv_aead_request_ctx, aead_req) !=
		     माप(काष्ठा essiv_aead_request_ctx));

	aead = crypto_spawn_aead(&ictx->u.aead_spawn);
	अगर (IS_ERR(aead))
		वापस PTR_ERR(aead);

	subreq_size = माप_field(काष्ठा essiv_aead_request_ctx, aead_req) +
		      crypto_aead_reqsize(aead);

	tctx->ivoffset = दुरत्व(काष्ठा essiv_aead_request_ctx, aead_req) +
			 subreq_size;
	crypto_aead_set_reqsize(tfm, tctx->ivoffset + crypto_aead_ivsize(aead));

	err = essiv_init_tfm(ictx, tctx);
	अगर (err) अणु
		crypto_मुक्त_aead(aead);
		वापस err;
	पूर्ण

	tctx->u.aead = aead;
	वापस 0;
पूर्ण

अटल व्योम essiv_skcipher_निकास_tfm(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा essiv_tfm_ctx *tctx = crypto_skcipher_ctx(tfm);

	crypto_मुक्त_skcipher(tctx->u.skcipher);
	crypto_मुक्त_cipher(tctx->essiv_cipher);
	crypto_मुक्त_shash(tctx->hash);
पूर्ण

अटल व्योम essiv_aead_निकास_tfm(काष्ठा crypto_aead *tfm)
अणु
	काष्ठा essiv_tfm_ctx *tctx = crypto_aead_ctx(tfm);

	crypto_मुक्त_aead(tctx->u.aead);
	crypto_मुक्त_cipher(tctx->essiv_cipher);
	crypto_मुक्त_shash(tctx->hash);
पूर्ण

अटल व्योम essiv_skcipher_मुक्त_instance(काष्ठा skcipher_instance *inst)
अणु
	काष्ठा essiv_instance_ctx *ictx = skcipher_instance_ctx(inst);

	crypto_drop_skcipher(&ictx->u.skcipher_spawn);
	kमुक्त(inst);
पूर्ण

अटल व्योम essiv_aead_मुक्त_instance(काष्ठा aead_instance *inst)
अणु
	काष्ठा essiv_instance_ctx *ictx = aead_instance_ctx(inst);

	crypto_drop_aead(&ictx->u.aead_spawn);
	kमुक्त(inst);
पूर्ण

अटल bool parse_cipher_name(अक्षर *essiv_cipher_name, स्थिर अक्षर *cra_name)
अणु
	स्थिर अक्षर *p, *q;
	पूर्णांक len;

	/* find the last खोलोing parens */
	p = म_खोजप(cra_name, '(');
	अगर (!p++)
		वापस false;

	/* find the first closing parens in the tail of the string */
	q = म_अक्षर(p, ')');
	अगर (!q)
		वापस false;

	len = q - p;
	अगर (len >= CRYPTO_MAX_ALG_NAME)
		वापस false;

	स_नकल(essiv_cipher_name, p, len);
	essiv_cipher_name[len] = '\0';
	वापस true;
पूर्ण

अटल bool essiv_supported_algorithms(स्थिर अक्षर *essiv_cipher_name,
				       काष्ठा shash_alg *hash_alg,
				       पूर्णांक ivsize)
अणु
	काष्ठा crypto_alg *alg;
	bool ret = false;

	alg = crypto_alg_mod_lookup(essiv_cipher_name,
				    CRYPTO_ALG_TYPE_CIPHER,
				    CRYPTO_ALG_TYPE_MASK);
	अगर (IS_ERR(alg))
		वापस false;

	अगर (hash_alg->digestsize < alg->cra_cipher.cia_min_keysize ||
	    hash_alg->digestsize > alg->cra_cipher.cia_max_keysize)
		जाओ out;

	अगर (ivsize != alg->cra_blocksize)
		जाओ out;

	अगर (crypto_shash_alg_needs_key(hash_alg))
		जाओ out;

	ret = true;

out:
	crypto_mod_put(alg);
	वापस ret;
पूर्ण

अटल पूर्णांक essiv_create(काष्ठा crypto_ढाँचा *पंचांगpl, काष्ठा rtattr **tb)
अणु
	काष्ठा crypto_attr_type *algt;
	स्थिर अक्षर *inner_cipher_name;
	स्थिर अक्षर *shash_name;
	काष्ठा skcipher_instance *skcipher_inst = शून्य;
	काष्ठा aead_instance *aead_inst = शून्य;
	काष्ठा crypto_instance *inst;
	काष्ठा crypto_alg *base, *block_base;
	काष्ठा essiv_instance_ctx *ictx;
	काष्ठा skcipher_alg *skcipher_alg = शून्य;
	काष्ठा aead_alg *aead_alg = शून्य;
	काष्ठा crypto_alg *_hash_alg;
	काष्ठा shash_alg *hash_alg;
	पूर्णांक ivsize;
	u32 type;
	u32 mask;
	पूर्णांक err;

	algt = crypto_get_attr_type(tb);
	अगर (IS_ERR(algt))
		वापस PTR_ERR(algt);

	inner_cipher_name = crypto_attr_alg_name(tb[1]);
	अगर (IS_ERR(inner_cipher_name))
		वापस PTR_ERR(inner_cipher_name);

	shash_name = crypto_attr_alg_name(tb[2]);
	अगर (IS_ERR(shash_name))
		वापस PTR_ERR(shash_name);

	type = algt->type & algt->mask;
	mask = crypto_algt_inherited_mask(algt);

	चयन (type) अणु
	हाल CRYPTO_ALG_TYPE_SKCIPHER:
		skcipher_inst = kzalloc(माप(*skcipher_inst) +
					माप(*ictx), GFP_KERNEL);
		अगर (!skcipher_inst)
			वापस -ENOMEM;
		inst = skcipher_crypto_instance(skcipher_inst);
		base = &skcipher_inst->alg.base;
		ictx = crypto_instance_ctx(inst);

		/* Symmetric cipher, e.g., "cbc(aes)" */
		err = crypto_grab_skcipher(&ictx->u.skcipher_spawn, inst,
					   inner_cipher_name, 0, mask);
		अगर (err)
			जाओ out_मुक्त_inst;
		skcipher_alg = crypto_spawn_skcipher_alg(&ictx->u.skcipher_spawn);
		block_base = &skcipher_alg->base;
		ivsize = crypto_skcipher_alg_ivsize(skcipher_alg);
		अवरोध;

	हाल CRYPTO_ALG_TYPE_AEAD:
		aead_inst = kzalloc(माप(*aead_inst) +
				    माप(*ictx), GFP_KERNEL);
		अगर (!aead_inst)
			वापस -ENOMEM;
		inst = aead_crypto_instance(aead_inst);
		base = &aead_inst->alg.base;
		ictx = crypto_instance_ctx(inst);

		/* AEAD cipher, e.g., "authenc(hmac(sha256),cbc(aes))" */
		err = crypto_grab_aead(&ictx->u.aead_spawn, inst,
				       inner_cipher_name, 0, mask);
		अगर (err)
			जाओ out_मुक्त_inst;
		aead_alg = crypto_spawn_aead_alg(&ictx->u.aead_spawn);
		block_base = &aead_alg->base;
		अगर (!strstarts(block_base->cra_name, "authenc(")) अणु
			pr_warn("Only authenc() type AEADs are supported by ESSIV\n");
			err = -EINVAL;
			जाओ out_drop_skcipher;
		पूर्ण
		ivsize = aead_alg->ivsize;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (!parse_cipher_name(ictx->essiv_cipher_name, block_base->cra_name)) अणु
		pr_warn("Failed to parse ESSIV cipher name from skcipher cra_name\n");
		err = -EINVAL;
		जाओ out_drop_skcipher;
	पूर्ण

	/* Synchronous hash, e.g., "sha256" */
	_hash_alg = crypto_alg_mod_lookup(shash_name,
					  CRYPTO_ALG_TYPE_SHASH,
					  CRYPTO_ALG_TYPE_MASK | mask);
	अगर (IS_ERR(_hash_alg)) अणु
		err = PTR_ERR(_hash_alg);
		जाओ out_drop_skcipher;
	पूर्ण
	hash_alg = __crypto_shash_alg(_hash_alg);

	/* Check the set of algorithms */
	अगर (!essiv_supported_algorithms(ictx->essiv_cipher_name, hash_alg,
					ivsize)) अणु
		pr_warn("Unsupported essiv instantiation: essiv(%s,%s)\n",
			block_base->cra_name, hash_alg->base.cra_name);
		err = -EINVAL;
		जाओ out_मुक्त_hash;
	पूर्ण

	/* record the driver name so we can instantiate this exact algo later */
	strlcpy(ictx->shash_driver_name, hash_alg->base.cra_driver_name,
		CRYPTO_MAX_ALG_NAME);

	/* Instance fields */

	err = -ENAMETOOLONG;
	अगर (snम_लिखो(base->cra_name, CRYPTO_MAX_ALG_NAME,
		     "essiv(%s,%s)", block_base->cra_name,
		     hash_alg->base.cra_name) >= CRYPTO_MAX_ALG_NAME)
		जाओ out_मुक्त_hash;
	अगर (snम_लिखो(base->cra_driver_name, CRYPTO_MAX_ALG_NAME,
		     "essiv(%s,%s)", block_base->cra_driver_name,
		     hash_alg->base.cra_driver_name) >= CRYPTO_MAX_ALG_NAME)
		जाओ out_मुक्त_hash;

	/*
	 * hash_alg wasn't gotten via crypto_grab*(), so we need to inherit its
	 * flags manually.
	 */
	base->cra_flags        |= (hash_alg->base.cra_flags &
				   CRYPTO_ALG_INHERITED_FLAGS);
	base->cra_blocksize	= block_base->cra_blocksize;
	base->cra_ctxsize	= माप(काष्ठा essiv_tfm_ctx);
	base->cra_alignmask	= block_base->cra_alignmask;
	base->cra_priority	= block_base->cra_priority;

	अगर (type == CRYPTO_ALG_TYPE_SKCIPHER) अणु
		skcipher_inst->alg.setkey	= essiv_skcipher_setkey;
		skcipher_inst->alg.encrypt	= essiv_skcipher_encrypt;
		skcipher_inst->alg.decrypt	= essiv_skcipher_decrypt;
		skcipher_inst->alg.init		= essiv_skcipher_init_tfm;
		skcipher_inst->alg.निकास		= essiv_skcipher_निकास_tfm;

		skcipher_inst->alg.min_keysize	= crypto_skcipher_alg_min_keysize(skcipher_alg);
		skcipher_inst->alg.max_keysize	= crypto_skcipher_alg_max_keysize(skcipher_alg);
		skcipher_inst->alg.ivsize	= ivsize;
		skcipher_inst->alg.chunksize	= crypto_skcipher_alg_chunksize(skcipher_alg);
		skcipher_inst->alg.walksize	= crypto_skcipher_alg_walksize(skcipher_alg);

		skcipher_inst->मुक्त		= essiv_skcipher_मुक्त_instance;

		err = skcipher_रेजिस्टर_instance(पंचांगpl, skcipher_inst);
	पूर्ण अन्यथा अणु
		aead_inst->alg.setkey		= essiv_aead_setkey;
		aead_inst->alg.setauthsize	= essiv_aead_setauthsize;
		aead_inst->alg.encrypt		= essiv_aead_encrypt;
		aead_inst->alg.decrypt		= essiv_aead_decrypt;
		aead_inst->alg.init		= essiv_aead_init_tfm;
		aead_inst->alg.निकास		= essiv_aead_निकास_tfm;

		aead_inst->alg.ivsize		= ivsize;
		aead_inst->alg.maxauthsize	= crypto_aead_alg_maxauthsize(aead_alg);
		aead_inst->alg.chunksize	= crypto_aead_alg_chunksize(aead_alg);

		aead_inst->मुक्त			= essiv_aead_मुक्त_instance;

		err = aead_रेजिस्टर_instance(पंचांगpl, aead_inst);
	पूर्ण

	अगर (err)
		जाओ out_मुक्त_hash;

	crypto_mod_put(_hash_alg);
	वापस 0;

out_मुक्त_hash:
	crypto_mod_put(_hash_alg);
out_drop_skcipher:
	अगर (type == CRYPTO_ALG_TYPE_SKCIPHER)
		crypto_drop_skcipher(&ictx->u.skcipher_spawn);
	अन्यथा
		crypto_drop_aead(&ictx->u.aead_spawn);
out_मुक्त_inst:
	kमुक्त(skcipher_inst);
	kमुक्त(aead_inst);
	वापस err;
पूर्ण

/* essiv(cipher_name, shash_name) */
अटल काष्ठा crypto_ढाँचा essiv_पंचांगpl = अणु
	.name	= "essiv",
	.create	= essiv_create,
	.module	= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init essiv_module_init(व्योम)
अणु
	वापस crypto_रेजिस्टर_ढाँचा(&essiv_पंचांगpl);
पूर्ण

अटल व्योम __निकास essiv_module_निकास(व्योम)
अणु
	crypto_unरेजिस्टर_ढाँचा(&essiv_पंचांगpl);
पूर्ण

subsys_initcall(essiv_module_init);
module_निकास(essiv_module_निकास);

MODULE_DESCRIPTION("ESSIV skcipher/aead wrapper for block encryption");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS_CRYPTO("essiv");
MODULE_IMPORT_NS(CRYPTO_INTERNAL);
