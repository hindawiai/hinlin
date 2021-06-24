<शैली गुरु>
/*
 * CTS: Cipher Text Stealing mode
 *
 * COPYRIGHT (c) 2008
 * The Regents of the University of Michigan
 * ALL RIGHTS RESERVED
 *
 * Permission is granted to use, copy, create derivative works
 * and redistribute this software and such derivative works
 * क्रम any purpose, so दीर्घ as the name of The University of
 * Michigan is not used in any advertising or खुलाity
 * pertaining to the use of distribution of this software
 * without specअगरic, written prior authorization.  If the
 * above copyright notice or any other identअगरication of the
 * University of Michigan is included in any copy of any
 * portion of this software, then the disclaimer below must
 * also be included.
 *
 * THIS SOFTWARE IS PROVIDED AS IS, WITHOUT REPRESENTATION
 * FROM THE UNIVERSITY OF MICHIGAN AS TO ITS FITNESS FOR ANY
 * PURPOSE, AND WITHOUT WARRANTY BY THE UNIVERSITY OF
 * MICHIGAN OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING
 * WITHOUT LIMITATION THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. THE
 * REGENTS OF THE UNIVERSITY OF MICHIGAN SHALL NOT BE LIABLE
 * FOR ANY DAMAGES, INCLUDING SPECIAL, INसूचीECT, INCIDENTAL, OR
 * CONSEQUENTIAL DAMAGES, WITH RESPECT TO ANY CLAIM ARISING
 * OUT OF OR IN CONNECTION WITH THE USE OF THE SOFTWARE, EVEN
 * IF IT HAS BEEN OR IS HEREAFTER ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGES.
 */

/* Derived from various:
 *	Copyright (c) 2006 Herbert Xu <herbert@gonकरोr.apana.org.au>
 */

/*
 * This is the Cipher Text Stealing mode as described by
 * Section 8 of rfc2040 and referenced by rfc3962.
 * rfc3962 includes errata inक्रमmation in its Appendix A.
 */

#समावेश <crypto/algapi.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/log2.h>
#समावेश <linux/module.h>
#समावेश <linux/scatterlist.h>
#समावेश <crypto/scatterwalk.h>
#समावेश <linux/slab.h>
#समावेश <linux/compiler.h>

काष्ठा crypto_cts_ctx अणु
	काष्ठा crypto_skcipher *child;
पूर्ण;

काष्ठा crypto_cts_reqctx अणु
	काष्ठा scatterlist sg[2];
	अचिन्हित offset;
	काष्ठा skcipher_request subreq;
पूर्ण;

अटल अंतरभूत u8 *crypto_cts_reqctx_space(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_cts_reqctx *rctx = skcipher_request_ctx(req);
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा crypto_cts_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा crypto_skcipher *child = ctx->child;

	वापस PTR_ALIGN((u8 *)(rctx + 1) + crypto_skcipher_reqsize(child),
			 crypto_skcipher_alignmask(tfm) + 1);
पूर्ण

अटल पूर्णांक crypto_cts_setkey(काष्ठा crypto_skcipher *parent, स्थिर u8 *key,
			     अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा crypto_cts_ctx *ctx = crypto_skcipher_ctx(parent);
	काष्ठा crypto_skcipher *child = ctx->child;

	crypto_skcipher_clear_flags(child, CRYPTO_TFM_REQ_MASK);
	crypto_skcipher_set_flags(child, crypto_skcipher_get_flags(parent) &
					 CRYPTO_TFM_REQ_MASK);
	वापस crypto_skcipher_setkey(child, key, keylen);
पूर्ण

अटल व्योम cts_cbc_crypt_करोne(काष्ठा crypto_async_request *areq, पूर्णांक err)
अणु
	काष्ठा skcipher_request *req = areq->data;

	अगर (err == -EINPROGRESS)
		वापस;

	skcipher_request_complete(req, err);
पूर्ण

अटल पूर्णांक cts_cbc_encrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_cts_reqctx *rctx = skcipher_request_ctx(req);
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा skcipher_request *subreq = &rctx->subreq;
	पूर्णांक bsize = crypto_skcipher_blocksize(tfm);
	u8 d[MAX_CIPHER_BLOCKSIZE * 2] __aligned(__alignof__(u32));
	काष्ठा scatterlist *sg;
	अचिन्हित पूर्णांक offset;
	पूर्णांक lastn;

	offset = rctx->offset;
	lastn = req->cryptlen - offset;

	sg = scatterwalk_ffwd(rctx->sg, req->dst, offset - bsize);
	scatterwalk_map_and_copy(d + bsize, sg, 0, bsize, 0);

	स_रखो(d, 0, bsize);
	scatterwalk_map_and_copy(d, req->src, offset, lastn, 0);

	scatterwalk_map_and_copy(d, sg, 0, bsize + lastn, 1);
	memzero_explicit(d, माप(d));

	skcipher_request_set_callback(subreq, req->base.flags &
					      CRYPTO_TFM_REQ_MAY_BACKLOG,
				      cts_cbc_crypt_करोne, req);
	skcipher_request_set_crypt(subreq, sg, sg, bsize, req->iv);
	वापस crypto_skcipher_encrypt(subreq);
पूर्ण

अटल व्योम crypto_cts_encrypt_करोne(काष्ठा crypto_async_request *areq, पूर्णांक err)
अणु
	काष्ठा skcipher_request *req = areq->data;

	अगर (err)
		जाओ out;

	err = cts_cbc_encrypt(req);
	अगर (err == -EINPROGRESS || err == -EBUSY)
		वापस;

out:
	skcipher_request_complete(req, err);
पूर्ण

अटल पूर्णांक crypto_cts_encrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा crypto_cts_reqctx *rctx = skcipher_request_ctx(req);
	काष्ठा crypto_cts_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा skcipher_request *subreq = &rctx->subreq;
	पूर्णांक bsize = crypto_skcipher_blocksize(tfm);
	अचिन्हित पूर्णांक nbytes = req->cryptlen;
	अचिन्हित पूर्णांक offset;

	skcipher_request_set_tfm(subreq, ctx->child);

	अगर (nbytes < bsize)
		वापस -EINVAL;

	अगर (nbytes == bsize) अणु
		skcipher_request_set_callback(subreq, req->base.flags,
					      req->base.complete,
					      req->base.data);
		skcipher_request_set_crypt(subreq, req->src, req->dst, nbytes,
					   req->iv);
		वापस crypto_skcipher_encrypt(subreq);
	पूर्ण

	offset = roundकरोwn(nbytes - 1, bsize);
	rctx->offset = offset;

	skcipher_request_set_callback(subreq, req->base.flags,
				      crypto_cts_encrypt_करोne, req);
	skcipher_request_set_crypt(subreq, req->src, req->dst,
				   offset, req->iv);

	वापस crypto_skcipher_encrypt(subreq) ?:
	       cts_cbc_encrypt(req);
पूर्ण

अटल पूर्णांक cts_cbc_decrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_cts_reqctx *rctx = skcipher_request_ctx(req);
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा skcipher_request *subreq = &rctx->subreq;
	पूर्णांक bsize = crypto_skcipher_blocksize(tfm);
	u8 d[MAX_CIPHER_BLOCKSIZE * 2] __aligned(__alignof__(u32));
	काष्ठा scatterlist *sg;
	अचिन्हित पूर्णांक offset;
	u8 *space;
	पूर्णांक lastn;

	offset = rctx->offset;
	lastn = req->cryptlen - offset;

	sg = scatterwalk_ffwd(rctx->sg, req->dst, offset - bsize);

	/* 1. Decrypt Cn-1 (s) to create Dn */
	scatterwalk_map_and_copy(d + bsize, sg, 0, bsize, 0);
	space = crypto_cts_reqctx_space(req);
	crypto_xor(d + bsize, space, bsize);
	/* 2. Pad Cn with zeros at the end to create C of length BB */
	स_रखो(d, 0, bsize);
	scatterwalk_map_and_copy(d, req->src, offset, lastn, 0);
	/* 3. Exclusive-or Dn with C to create Xn */
	/* 4. Select the first Ln bytes of Xn to create Pn */
	crypto_xor(d + bsize, d, lastn);

	/* 5. Append the tail (BB - Ln) bytes of Xn to Cn to create En */
	स_नकल(d + lastn, d + bsize + lastn, bsize - lastn);
	/* 6. Decrypt En to create Pn-1 */

	scatterwalk_map_and_copy(d, sg, 0, bsize + lastn, 1);
	memzero_explicit(d, माप(d));

	skcipher_request_set_callback(subreq, req->base.flags &
					      CRYPTO_TFM_REQ_MAY_BACKLOG,
				      cts_cbc_crypt_करोne, req);

	skcipher_request_set_crypt(subreq, sg, sg, bsize, space);
	वापस crypto_skcipher_decrypt(subreq);
पूर्ण

अटल व्योम crypto_cts_decrypt_करोne(काष्ठा crypto_async_request *areq, पूर्णांक err)
अणु
	काष्ठा skcipher_request *req = areq->data;

	अगर (err)
		जाओ out;

	err = cts_cbc_decrypt(req);
	अगर (err == -EINPROGRESS || err == -EBUSY)
		वापस;

out:
	skcipher_request_complete(req, err);
पूर्ण

अटल पूर्णांक crypto_cts_decrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा crypto_cts_reqctx *rctx = skcipher_request_ctx(req);
	काष्ठा crypto_cts_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा skcipher_request *subreq = &rctx->subreq;
	पूर्णांक bsize = crypto_skcipher_blocksize(tfm);
	अचिन्हित पूर्णांक nbytes = req->cryptlen;
	अचिन्हित पूर्णांक offset;
	u8 *space;

	skcipher_request_set_tfm(subreq, ctx->child);

	अगर (nbytes < bsize)
		वापस -EINVAL;

	अगर (nbytes == bsize) अणु
		skcipher_request_set_callback(subreq, req->base.flags,
					      req->base.complete,
					      req->base.data);
		skcipher_request_set_crypt(subreq, req->src, req->dst, nbytes,
					   req->iv);
		वापस crypto_skcipher_decrypt(subreq);
	पूर्ण

	skcipher_request_set_callback(subreq, req->base.flags,
				      crypto_cts_decrypt_करोne, req);

	space = crypto_cts_reqctx_space(req);

	offset = roundकरोwn(nbytes - 1, bsize);
	rctx->offset = offset;

	अगर (offset <= bsize)
		स_नकल(space, req->iv, bsize);
	अन्यथा
		scatterwalk_map_and_copy(space, req->src, offset - 2 * bsize,
					 bsize, 0);

	skcipher_request_set_crypt(subreq, req->src, req->dst,
				   offset, req->iv);

	वापस crypto_skcipher_decrypt(subreq) ?:
	       cts_cbc_decrypt(req);
पूर्ण

अटल पूर्णांक crypto_cts_init_tfm(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा skcipher_instance *inst = skcipher_alg_instance(tfm);
	काष्ठा crypto_skcipher_spawn *spawn = skcipher_instance_ctx(inst);
	काष्ठा crypto_cts_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा crypto_skcipher *cipher;
	अचिन्हित reqsize;
	अचिन्हित bsize;
	अचिन्हित align;

	cipher = crypto_spawn_skcipher(spawn);
	अगर (IS_ERR(cipher))
		वापस PTR_ERR(cipher);

	ctx->child = cipher;

	align = crypto_skcipher_alignmask(tfm);
	bsize = crypto_skcipher_blocksize(cipher);
	reqsize = ALIGN(माप(काष्ठा crypto_cts_reqctx) +
			crypto_skcipher_reqsize(cipher),
			crypto_tfm_ctx_alignment()) +
		  (align & ~(crypto_tfm_ctx_alignment() - 1)) + bsize;

	crypto_skcipher_set_reqsize(tfm, reqsize);

	वापस 0;
पूर्ण

अटल व्योम crypto_cts_निकास_tfm(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा crypto_cts_ctx *ctx = crypto_skcipher_ctx(tfm);

	crypto_मुक्त_skcipher(ctx->child);
पूर्ण

अटल व्योम crypto_cts_मुक्त(काष्ठा skcipher_instance *inst)
अणु
	crypto_drop_skcipher(skcipher_instance_ctx(inst));
	kमुक्त(inst);
पूर्ण

अटल पूर्णांक crypto_cts_create(काष्ठा crypto_ढाँचा *पंचांगpl, काष्ठा rtattr **tb)
अणु
	काष्ठा crypto_skcipher_spawn *spawn;
	काष्ठा skcipher_instance *inst;
	काष्ठा skcipher_alg *alg;
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

	err = -EINVAL;
	अगर (crypto_skcipher_alg_ivsize(alg) != alg->base.cra_blocksize)
		जाओ err_मुक्त_inst;

	अगर (म_भेदन(alg->base.cra_name, "cbc(", 4))
		जाओ err_मुक्त_inst;

	err = crypto_inst_setname(skcipher_crypto_instance(inst), "cts",
				  &alg->base);
	अगर (err)
		जाओ err_मुक्त_inst;

	inst->alg.base.cra_priority = alg->base.cra_priority;
	inst->alg.base.cra_blocksize = alg->base.cra_blocksize;
	inst->alg.base.cra_alignmask = alg->base.cra_alignmask;

	inst->alg.ivsize = alg->base.cra_blocksize;
	inst->alg.chunksize = crypto_skcipher_alg_chunksize(alg);
	inst->alg.min_keysize = crypto_skcipher_alg_min_keysize(alg);
	inst->alg.max_keysize = crypto_skcipher_alg_max_keysize(alg);

	inst->alg.base.cra_ctxsize = माप(काष्ठा crypto_cts_ctx);

	inst->alg.init = crypto_cts_init_tfm;
	inst->alg.निकास = crypto_cts_निकास_tfm;

	inst->alg.setkey = crypto_cts_setkey;
	inst->alg.encrypt = crypto_cts_encrypt;
	inst->alg.decrypt = crypto_cts_decrypt;

	inst->मुक्त = crypto_cts_मुक्त;

	err = skcipher_रेजिस्टर_instance(पंचांगpl, inst);
	अगर (err) अणु
err_मुक्त_inst:
		crypto_cts_मुक्त(inst);
	पूर्ण
	वापस err;
पूर्ण

अटल काष्ठा crypto_ढाँचा crypto_cts_पंचांगpl = अणु
	.name = "cts",
	.create = crypto_cts_create,
	.module = THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init crypto_cts_module_init(व्योम)
अणु
	वापस crypto_रेजिस्टर_ढाँचा(&crypto_cts_पंचांगpl);
पूर्ण

अटल व्योम __निकास crypto_cts_module_निकास(व्योम)
अणु
	crypto_unरेजिस्टर_ढाँचा(&crypto_cts_पंचांगpl);
पूर्ण

subsys_initcall(crypto_cts_module_init);
module_निकास(crypto_cts_module_निकास);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("CTS-CBC CipherText Stealing for CBC");
MODULE_ALIAS_CRYPTO("cts");
