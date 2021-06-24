<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * CTR: Counter mode
 *
 * (C) Copyright IBM Corp. 2007 - Joy Latten <latten@us.ibm.com>
 */

#समावेश <crypto/algapi.h>
#समावेश <crypto/ctr.h>
#समावेश <crypto/पूर्णांकernal/cipher.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

काष्ठा crypto_rfc3686_ctx अणु
	काष्ठा crypto_skcipher *child;
	u8 nonce[CTR_RFC3686_NONCE_SIZE];
पूर्ण;

काष्ठा crypto_rfc3686_req_ctx अणु
	u8 iv[CTR_RFC3686_BLOCK_SIZE];
	काष्ठा skcipher_request subreq CRYPTO_MINALIGN_ATTR;
पूर्ण;

अटल व्योम crypto_ctr_crypt_final(काष्ठा skcipher_walk *walk,
				   काष्ठा crypto_cipher *tfm)
अणु
	अचिन्हित पूर्णांक bsize = crypto_cipher_blocksize(tfm);
	अचिन्हित दीर्घ alignmask = crypto_cipher_alignmask(tfm);
	u8 *ctrblk = walk->iv;
	u8 पंचांगp[MAX_CIPHER_BLOCKSIZE + MAX_CIPHER_ALIGNMASK];
	u8 *keystream = PTR_ALIGN(पंचांगp + 0, alignmask + 1);
	u8 *src = walk->src.virt.addr;
	u8 *dst = walk->dst.virt.addr;
	अचिन्हित पूर्णांक nbytes = walk->nbytes;

	crypto_cipher_encrypt_one(tfm, keystream, ctrblk);
	crypto_xor_cpy(dst, keystream, src, nbytes);

	crypto_inc(ctrblk, bsize);
पूर्ण

अटल पूर्णांक crypto_ctr_crypt_segment(काष्ठा skcipher_walk *walk,
				    काष्ठा crypto_cipher *tfm)
अणु
	व्योम (*fn)(काष्ठा crypto_tfm *, u8 *, स्थिर u8 *) =
		   crypto_cipher_alg(tfm)->cia_encrypt;
	अचिन्हित पूर्णांक bsize = crypto_cipher_blocksize(tfm);
	u8 *ctrblk = walk->iv;
	u8 *src = walk->src.virt.addr;
	u8 *dst = walk->dst.virt.addr;
	अचिन्हित पूर्णांक nbytes = walk->nbytes;

	करो अणु
		/* create keystream */
		fn(crypto_cipher_tfm(tfm), dst, ctrblk);
		crypto_xor(dst, src, bsize);

		/* increment counter in counterblock */
		crypto_inc(ctrblk, bsize);

		src += bsize;
		dst += bsize;
	पूर्ण जबतक ((nbytes -= bsize) >= bsize);

	वापस nbytes;
पूर्ण

अटल पूर्णांक crypto_ctr_crypt_inplace(काष्ठा skcipher_walk *walk,
				    काष्ठा crypto_cipher *tfm)
अणु
	व्योम (*fn)(काष्ठा crypto_tfm *, u8 *, स्थिर u8 *) =
		   crypto_cipher_alg(tfm)->cia_encrypt;
	अचिन्हित पूर्णांक bsize = crypto_cipher_blocksize(tfm);
	अचिन्हित दीर्घ alignmask = crypto_cipher_alignmask(tfm);
	अचिन्हित पूर्णांक nbytes = walk->nbytes;
	u8 *ctrblk = walk->iv;
	u8 *src = walk->src.virt.addr;
	u8 पंचांगp[MAX_CIPHER_BLOCKSIZE + MAX_CIPHER_ALIGNMASK];
	u8 *keystream = PTR_ALIGN(पंचांगp + 0, alignmask + 1);

	करो अणु
		/* create keystream */
		fn(crypto_cipher_tfm(tfm), keystream, ctrblk);
		crypto_xor(src, keystream, bsize);

		/* increment counter in counterblock */
		crypto_inc(ctrblk, bsize);

		src += bsize;
	पूर्ण जबतक ((nbytes -= bsize) >= bsize);

	वापस nbytes;
पूर्ण

अटल पूर्णांक crypto_ctr_crypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा crypto_cipher *cipher = skcipher_cipher_simple(tfm);
	स्थिर अचिन्हित पूर्णांक bsize = crypto_cipher_blocksize(cipher);
	काष्ठा skcipher_walk walk;
	अचिन्हित पूर्णांक nbytes;
	पूर्णांक err;

	err = skcipher_walk_virt(&walk, req, false);

	जबतक (walk.nbytes >= bsize) अणु
		अगर (walk.src.virt.addr == walk.dst.virt.addr)
			nbytes = crypto_ctr_crypt_inplace(&walk, cipher);
		अन्यथा
			nbytes = crypto_ctr_crypt_segment(&walk, cipher);

		err = skcipher_walk_करोne(&walk, nbytes);
	पूर्ण

	अगर (walk.nbytes) अणु
		crypto_ctr_crypt_final(&walk, cipher);
		err = skcipher_walk_करोne(&walk, 0);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक crypto_ctr_create(काष्ठा crypto_ढाँचा *पंचांगpl, काष्ठा rtattr **tb)
अणु
	काष्ठा skcipher_instance *inst;
	काष्ठा crypto_alg *alg;
	पूर्णांक err;

	inst = skcipher_alloc_instance_simple(पंचांगpl, tb);
	अगर (IS_ERR(inst))
		वापस PTR_ERR(inst);

	alg = skcipher_ialg_simple(inst);

	/* Block size must be >= 4 bytes. */
	err = -EINVAL;
	अगर (alg->cra_blocksize < 4)
		जाओ out_मुक्त_inst;

	/* If this is false we'd fail the alignment of crypto_inc. */
	अगर (alg->cra_blocksize % 4)
		जाओ out_मुक्त_inst;

	/* CTR mode is a stream cipher. */
	inst->alg.base.cra_blocksize = 1;

	/*
	 * To simplअगरy the implementation, configure the skcipher walk to only
	 * give a partial block at the very end, never earlier.
	 */
	inst->alg.chunksize = alg->cra_blocksize;

	inst->alg.encrypt = crypto_ctr_crypt;
	inst->alg.decrypt = crypto_ctr_crypt;

	err = skcipher_रेजिस्टर_instance(पंचांगpl, inst);
	अगर (err) अणु
out_मुक्त_inst:
		inst->मुक्त(inst);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक crypto_rfc3686_setkey(काष्ठा crypto_skcipher *parent,
				 स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा crypto_rfc3686_ctx *ctx = crypto_skcipher_ctx(parent);
	काष्ठा crypto_skcipher *child = ctx->child;

	/* the nonce is stored in bytes at end of key */
	अगर (keylen < CTR_RFC3686_NONCE_SIZE)
		वापस -EINVAL;

	स_नकल(ctx->nonce, key + (keylen - CTR_RFC3686_NONCE_SIZE),
	       CTR_RFC3686_NONCE_SIZE);

	keylen -= CTR_RFC3686_NONCE_SIZE;

	crypto_skcipher_clear_flags(child, CRYPTO_TFM_REQ_MASK);
	crypto_skcipher_set_flags(child, crypto_skcipher_get_flags(parent) &
					 CRYPTO_TFM_REQ_MASK);
	वापस crypto_skcipher_setkey(child, key, keylen);
पूर्ण

अटल पूर्णांक crypto_rfc3686_crypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा crypto_rfc3686_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा crypto_skcipher *child = ctx->child;
	अचिन्हित दीर्घ align = crypto_skcipher_alignmask(tfm);
	काष्ठा crypto_rfc3686_req_ctx *rctx =
		(व्योम *)PTR_ALIGN((u8 *)skcipher_request_ctx(req), align + 1);
	काष्ठा skcipher_request *subreq = &rctx->subreq;
	u8 *iv = rctx->iv;

	/* set up counter block */
	स_नकल(iv, ctx->nonce, CTR_RFC3686_NONCE_SIZE);
	स_नकल(iv + CTR_RFC3686_NONCE_SIZE, req->iv, CTR_RFC3686_IV_SIZE);

	/* initialize counter portion of counter block */
	*(__be32 *)(iv + CTR_RFC3686_NONCE_SIZE + CTR_RFC3686_IV_SIZE) =
		cpu_to_be32(1);

	skcipher_request_set_tfm(subreq, child);
	skcipher_request_set_callback(subreq, req->base.flags,
				      req->base.complete, req->base.data);
	skcipher_request_set_crypt(subreq, req->src, req->dst,
				   req->cryptlen, iv);

	वापस crypto_skcipher_encrypt(subreq);
पूर्ण

अटल पूर्णांक crypto_rfc3686_init_tfm(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा skcipher_instance *inst = skcipher_alg_instance(tfm);
	काष्ठा crypto_skcipher_spawn *spawn = skcipher_instance_ctx(inst);
	काष्ठा crypto_rfc3686_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा crypto_skcipher *cipher;
	अचिन्हित दीर्घ align;
	अचिन्हित पूर्णांक reqsize;

	cipher = crypto_spawn_skcipher(spawn);
	अगर (IS_ERR(cipher))
		वापस PTR_ERR(cipher);

	ctx->child = cipher;

	align = crypto_skcipher_alignmask(tfm);
	align &= ~(crypto_tfm_ctx_alignment() - 1);
	reqsize = align + माप(काष्ठा crypto_rfc3686_req_ctx) +
		  crypto_skcipher_reqsize(cipher);
	crypto_skcipher_set_reqsize(tfm, reqsize);

	वापस 0;
पूर्ण

अटल व्योम crypto_rfc3686_निकास_tfm(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा crypto_rfc3686_ctx *ctx = crypto_skcipher_ctx(tfm);

	crypto_मुक्त_skcipher(ctx->child);
पूर्ण

अटल व्योम crypto_rfc3686_मुक्त(काष्ठा skcipher_instance *inst)
अणु
	काष्ठा crypto_skcipher_spawn *spawn = skcipher_instance_ctx(inst);

	crypto_drop_skcipher(spawn);
	kमुक्त(inst);
पूर्ण

अटल पूर्णांक crypto_rfc3686_create(काष्ठा crypto_ढाँचा *पंचांगpl,
				 काष्ठा rtattr **tb)
अणु
	काष्ठा skcipher_instance *inst;
	काष्ठा skcipher_alg *alg;
	काष्ठा crypto_skcipher_spawn *spawn;
	u32 mask;
	पूर्णांक err;

	err = crypto_check_attr_type(tb, CRYPTO_ALG_TYPE_SKCIPHER, &mask);
	अगर (err)
		वापस err;

	inst = kzalloc(माप(*inst) + माप(*spawn), GFP_KERNEL);
	अगर (!inst)
		वापस -ENOMEM;

	spawn = skcipher_instance_ctx(inst);

	err = crypto_grab_skcipher(spawn, skcipher_crypto_instance(inst),
				   crypto_attr_alg_name(tb[1]), 0, mask);
	अगर (err)
		जाओ err_मुक्त_inst;

	alg = crypto_spawn_skcipher_alg(spawn);

	/* We only support 16-byte blocks. */
	err = -EINVAL;
	अगर (crypto_skcipher_alg_ivsize(alg) != CTR_RFC3686_BLOCK_SIZE)
		जाओ err_मुक्त_inst;

	/* Not a stream cipher? */
	अगर (alg->base.cra_blocksize != 1)
		जाओ err_मुक्त_inst;

	err = -ENAMETOOLONG;
	अगर (snम_लिखो(inst->alg.base.cra_name, CRYPTO_MAX_ALG_NAME,
		     "rfc3686(%s)", alg->base.cra_name) >= CRYPTO_MAX_ALG_NAME)
		जाओ err_मुक्त_inst;
	अगर (snम_लिखो(inst->alg.base.cra_driver_name, CRYPTO_MAX_ALG_NAME,
		     "rfc3686(%s)", alg->base.cra_driver_name) >=
	    CRYPTO_MAX_ALG_NAME)
		जाओ err_मुक्त_inst;

	inst->alg.base.cra_priority = alg->base.cra_priority;
	inst->alg.base.cra_blocksize = 1;
	inst->alg.base.cra_alignmask = alg->base.cra_alignmask;

	inst->alg.ivsize = CTR_RFC3686_IV_SIZE;
	inst->alg.chunksize = crypto_skcipher_alg_chunksize(alg);
	inst->alg.min_keysize = crypto_skcipher_alg_min_keysize(alg) +
				CTR_RFC3686_NONCE_SIZE;
	inst->alg.max_keysize = crypto_skcipher_alg_max_keysize(alg) +
				CTR_RFC3686_NONCE_SIZE;

	inst->alg.setkey = crypto_rfc3686_setkey;
	inst->alg.encrypt = crypto_rfc3686_crypt;
	inst->alg.decrypt = crypto_rfc3686_crypt;

	inst->alg.base.cra_ctxsize = माप(काष्ठा crypto_rfc3686_ctx);

	inst->alg.init = crypto_rfc3686_init_tfm;
	inst->alg.निकास = crypto_rfc3686_निकास_tfm;

	inst->मुक्त = crypto_rfc3686_मुक्त;

	err = skcipher_रेजिस्टर_instance(पंचांगpl, inst);
	अगर (err) अणु
err_मुक्त_inst:
		crypto_rfc3686_मुक्त(inst);
	पूर्ण
	वापस err;
पूर्ण

अटल काष्ठा crypto_ढाँचा crypto_ctr_पंचांगpls[] = अणु
	अणु
		.name = "ctr",
		.create = crypto_ctr_create,
		.module = THIS_MODULE,
	पूर्ण, अणु
		.name = "rfc3686",
		.create = crypto_rfc3686_create,
		.module = THIS_MODULE,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init crypto_ctr_module_init(व्योम)
अणु
	वापस crypto_रेजिस्टर_ढाँचाs(crypto_ctr_पंचांगpls,
					 ARRAY_SIZE(crypto_ctr_पंचांगpls));
पूर्ण

अटल व्योम __निकास crypto_ctr_module_निकास(व्योम)
अणु
	crypto_unरेजिस्टर_ढाँचाs(crypto_ctr_पंचांगpls,
				    ARRAY_SIZE(crypto_ctr_पंचांगpls));
पूर्ण

subsys_initcall(crypto_ctr_module_init);
module_निकास(crypto_ctr_module_निकास);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("CTR block cipher mode of operation");
MODULE_ALIAS_CRYPTO("rfc3686");
MODULE_ALIAS_CRYPTO("ctr");
MODULE_IMPORT_NS(CRYPTO_INTERNAL);
