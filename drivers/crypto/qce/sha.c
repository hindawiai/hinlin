<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2010-2014, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <crypto/पूर्णांकernal/hash.h>

#समावेश "common.h"
#समावेश "core.h"
#समावेश "sha.h"

काष्ठा qce_sha_saved_state अणु
	u8 pending_buf[QCE_SHA_MAX_BLOCKSIZE];
	u8 partial_digest[QCE_SHA_MAX_DIGESTSIZE];
	__be32 byte_count[2];
	अचिन्हित पूर्णांक pending_buflen;
	अचिन्हित पूर्णांक flags;
	u64 count;
	bool first_blk;
पूर्ण;

अटल LIST_HEAD(ahash_algs);

अटल स्थिर u32 std_iv_sha1[SHA256_DIGEST_SIZE / माप(u32)] = अणु
	SHA1_H0, SHA1_H1, SHA1_H2, SHA1_H3, SHA1_H4, 0, 0, 0
पूर्ण;

अटल स्थिर u32 std_iv_sha256[SHA256_DIGEST_SIZE / माप(u32)] = अणु
	SHA256_H0, SHA256_H1, SHA256_H2, SHA256_H3,
	SHA256_H4, SHA256_H5, SHA256_H6, SHA256_H7
पूर्ण;

अटल व्योम qce_ahash_करोne(व्योम *data)
अणु
	काष्ठा crypto_async_request *async_req = data;
	काष्ठा ahash_request *req = ahash_request_cast(async_req);
	काष्ठा crypto_ahash *ahash = crypto_ahash_reqtfm(req);
	काष्ठा qce_sha_reqctx *rctx = ahash_request_ctx(req);
	काष्ठा qce_alg_ढाँचा *पंचांगpl = to_ahash_पंचांगpl(async_req->tfm);
	काष्ठा qce_device *qce = पंचांगpl->qce;
	काष्ठा qce_result_dump *result = qce->dma.result_buf;
	अचिन्हित पूर्णांक digestsize = crypto_ahash_digestsize(ahash);
	पूर्णांक error;
	u32 status;

	error = qce_dma_terminate_all(&qce->dma);
	अगर (error)
		dev_dbg(qce->dev, "ahash dma termination error (%d)\n", error);

	dma_unmap_sg(qce->dev, req->src, rctx->src_nents, DMA_TO_DEVICE);
	dma_unmap_sg(qce->dev, &rctx->result_sg, 1, DMA_FROM_DEVICE);

	स_नकल(rctx->digest, result->auth_iv, digestsize);
	अगर (req->result && rctx->last_blk)
		स_नकल(req->result, result->auth_iv, digestsize);

	rctx->byte_count[0] = cpu_to_be32(result->auth_byte_count[0]);
	rctx->byte_count[1] = cpu_to_be32(result->auth_byte_count[1]);

	error = qce_check_status(qce, &status);
	अगर (error < 0)
		dev_dbg(qce->dev, "ahash operation error (%x)\n", status);

	req->src = rctx->src_orig;
	req->nbytes = rctx->nbytes_orig;
	rctx->last_blk = false;
	rctx->first_blk = false;

	qce->async_req_करोne(पंचांगpl->qce, error);
पूर्ण

अटल पूर्णांक qce_ahash_async_req_handle(काष्ठा crypto_async_request *async_req)
अणु
	काष्ठा ahash_request *req = ahash_request_cast(async_req);
	काष्ठा qce_sha_reqctx *rctx = ahash_request_ctx(req);
	काष्ठा qce_sha_ctx *ctx = crypto_tfm_ctx(async_req->tfm);
	काष्ठा qce_alg_ढाँचा *पंचांगpl = to_ahash_पंचांगpl(async_req->tfm);
	काष्ठा qce_device *qce = पंचांगpl->qce;
	अचिन्हित दीर्घ flags = rctx->flags;
	पूर्णांक ret;

	अगर (IS_SHA_HMAC(flags)) अणु
		rctx->authkey = ctx->authkey;
		rctx->authklen = QCE_SHA_HMAC_KEY_SIZE;
	पूर्ण अन्यथा अगर (IS_CMAC(flags)) अणु
		rctx->authkey = ctx->authkey;
		rctx->authklen = AES_KEYSIZE_128;
	पूर्ण

	rctx->src_nents = sg_nents_क्रम_len(req->src, req->nbytes);
	अगर (rctx->src_nents < 0) अणु
		dev_err(qce->dev, "Invalid numbers of src SG.\n");
		वापस rctx->src_nents;
	पूर्ण

	ret = dma_map_sg(qce->dev, req->src, rctx->src_nents, DMA_TO_DEVICE);
	अगर (ret < 0)
		वापस ret;

	sg_init_one(&rctx->result_sg, qce->dma.result_buf, QCE_RESULT_BUF_SZ);

	ret = dma_map_sg(qce->dev, &rctx->result_sg, 1, DMA_FROM_DEVICE);
	अगर (ret < 0)
		जाओ error_unmap_src;

	ret = qce_dma_prep_sgs(&qce->dma, req->src, rctx->src_nents,
			       &rctx->result_sg, 1, qce_ahash_करोne, async_req);
	अगर (ret)
		जाओ error_unmap_dst;

	qce_dma_issue_pending(&qce->dma);

	ret = qce_start(async_req, पंचांगpl->crypto_alg_type);
	अगर (ret)
		जाओ error_terminate;

	वापस 0;

error_terminate:
	qce_dma_terminate_all(&qce->dma);
error_unmap_dst:
	dma_unmap_sg(qce->dev, &rctx->result_sg, 1, DMA_FROM_DEVICE);
error_unmap_src:
	dma_unmap_sg(qce->dev, req->src, rctx->src_nents, DMA_TO_DEVICE);
	वापस ret;
पूर्ण

अटल पूर्णांक qce_ahash_init(काष्ठा ahash_request *req)
अणु
	काष्ठा qce_sha_reqctx *rctx = ahash_request_ctx(req);
	काष्ठा qce_alg_ढाँचा *पंचांगpl = to_ahash_पंचांगpl(req->base.tfm);
	स्थिर u32 *std_iv = पंचांगpl->std_iv;

	स_रखो(rctx, 0, माप(*rctx));
	rctx->first_blk = true;
	rctx->last_blk = false;
	rctx->flags = पंचांगpl->alg_flags;
	स_नकल(rctx->digest, std_iv, माप(rctx->digest));

	वापस 0;
पूर्ण

अटल पूर्णांक qce_ahash_export(काष्ठा ahash_request *req, व्योम *out)
अणु
	काष्ठा qce_sha_reqctx *rctx = ahash_request_ctx(req);
	काष्ठा qce_sha_saved_state *export_state = out;

	स_नकल(export_state->pending_buf, rctx->buf, rctx->buflen);
	स_नकल(export_state->partial_digest, rctx->digest, माप(rctx->digest));
	export_state->byte_count[0] = rctx->byte_count[0];
	export_state->byte_count[1] = rctx->byte_count[1];
	export_state->pending_buflen = rctx->buflen;
	export_state->count = rctx->count;
	export_state->first_blk = rctx->first_blk;
	export_state->flags = rctx->flags;

	वापस 0;
पूर्ण

अटल पूर्णांक qce_ahash_import(काष्ठा ahash_request *req, स्थिर व्योम *in)
अणु
	काष्ठा qce_sha_reqctx *rctx = ahash_request_ctx(req);
	स्थिर काष्ठा qce_sha_saved_state *import_state = in;

	स_रखो(rctx, 0, माप(*rctx));
	rctx->count = import_state->count;
	rctx->buflen = import_state->pending_buflen;
	rctx->first_blk = import_state->first_blk;
	rctx->flags = import_state->flags;
	rctx->byte_count[0] = import_state->byte_count[0];
	rctx->byte_count[1] = import_state->byte_count[1];
	स_नकल(rctx->buf, import_state->pending_buf, rctx->buflen);
	स_नकल(rctx->digest, import_state->partial_digest, माप(rctx->digest));

	वापस 0;
पूर्ण

अटल पूर्णांक qce_ahash_update(काष्ठा ahash_request *req)
अणु
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा qce_sha_reqctx *rctx = ahash_request_ctx(req);
	काष्ठा qce_alg_ढाँचा *पंचांगpl = to_ahash_पंचांगpl(req->base.tfm);
	काष्ठा qce_device *qce = पंचांगpl->qce;
	काष्ठा scatterlist *sg_last, *sg;
	अचिन्हित पूर्णांक total, len;
	अचिन्हित पूर्णांक hash_later;
	अचिन्हित पूर्णांक nbytes;
	अचिन्हित पूर्णांक blocksize;

	blocksize = crypto_tfm_alg_blocksize(crypto_ahash_tfm(tfm));
	rctx->count += req->nbytes;

	/* check क्रम buffer from previous updates and append it */
	total = req->nbytes + rctx->buflen;

	अगर (total <= blocksize) अणु
		scatterwalk_map_and_copy(rctx->buf + rctx->buflen, req->src,
					 0, req->nbytes, 0);
		rctx->buflen += req->nbytes;
		वापस 0;
	पूर्ण

	/* save the original req काष्ठाure fields */
	rctx->src_orig = req->src;
	rctx->nbytes_orig = req->nbytes;

	/*
	 * अगर we have data from previous update copy them on buffer. The old
	 * data will be combined with current request bytes.
	 */
	अगर (rctx->buflen)
		स_नकल(rctx->पंचांगpbuf, rctx->buf, rctx->buflen);

	/* calculate how many bytes will be hashed later */
	hash_later = total % blocksize;

	/*
	 * At this poपूर्णांक, there is more than one block size of data.  If
	 * the available data to transfer is exactly a multiple of block
	 * size, save the last block to be transferred in qce_ahash_final
	 * (with the last block bit set) अगर this is indeed the end of data
	 * stream. If not this saved block will be transferred as part of
	 * next update. If this block is not held back and अगर this is
	 * indeed the end of data stream, the digest obtained will be wrong
	 * since qce_ahash_final will see that rctx->buflen is 0 and वापस
	 * करोing nothing which in turn means that a digest will not be
	 * copied to the destination result buffer.  qce_ahash_final cannot
	 * be made to alter this behavior and allowed to proceed अगर
	 * rctx->buflen is 0 because the crypto engine BAM करोes not allow
	 * क्रम zero length transfers.
	 */
	अगर (!hash_later)
		hash_later = blocksize;

	अगर (hash_later) अणु
		अचिन्हित पूर्णांक src_offset = req->nbytes - hash_later;
		scatterwalk_map_and_copy(rctx->buf, req->src, src_offset,
					 hash_later, 0);
	पूर्ण

	/* here nbytes is multiple of blocksize */
	nbytes = total - hash_later;

	len = rctx->buflen;
	sg = sg_last = req->src;

	जबतक (len < nbytes && sg) अणु
		अगर (len + sg_dma_len(sg) > nbytes)
			अवरोध;
		len += sg_dma_len(sg);
		sg_last = sg;
		sg = sg_next(sg);
	पूर्ण

	अगर (!sg_last)
		वापस -EINVAL;

	अगर (rctx->buflen) अणु
		sg_init_table(rctx->sg, 2);
		sg_set_buf(rctx->sg, rctx->पंचांगpbuf, rctx->buflen);
		sg_chain(rctx->sg, 2, req->src);
		req->src = rctx->sg;
	पूर्ण

	req->nbytes = nbytes;
	rctx->buflen = hash_later;

	वापस qce->async_req_enqueue(पंचांगpl->qce, &req->base);
पूर्ण

अटल पूर्णांक qce_ahash_final(काष्ठा ahash_request *req)
अणु
	काष्ठा qce_sha_reqctx *rctx = ahash_request_ctx(req);
	काष्ठा qce_alg_ढाँचा *पंचांगpl = to_ahash_पंचांगpl(req->base.tfm);
	काष्ठा qce_device *qce = पंचांगpl->qce;

	अगर (!rctx->buflen) अणु
		अगर (पंचांगpl->hash_zero)
			स_नकल(req->result, पंचांगpl->hash_zero,
					पंचांगpl->alg.ahash.halg.digestsize);
		वापस 0;
	पूर्ण

	rctx->last_blk = true;

	rctx->src_orig = req->src;
	rctx->nbytes_orig = req->nbytes;

	स_नकल(rctx->पंचांगpbuf, rctx->buf, rctx->buflen);
	sg_init_one(rctx->sg, rctx->पंचांगpbuf, rctx->buflen);

	req->src = rctx->sg;
	req->nbytes = rctx->buflen;

	वापस qce->async_req_enqueue(पंचांगpl->qce, &req->base);
पूर्ण

अटल पूर्णांक qce_ahash_digest(काष्ठा ahash_request *req)
अणु
	काष्ठा qce_sha_reqctx *rctx = ahash_request_ctx(req);
	काष्ठा qce_alg_ढाँचा *पंचांगpl = to_ahash_पंचांगpl(req->base.tfm);
	काष्ठा qce_device *qce = पंचांगpl->qce;
	पूर्णांक ret;

	ret = qce_ahash_init(req);
	अगर (ret)
		वापस ret;

	rctx->src_orig = req->src;
	rctx->nbytes_orig = req->nbytes;
	rctx->first_blk = true;
	rctx->last_blk = true;

	अगर (!rctx->nbytes_orig) अणु
		अगर (पंचांगpl->hash_zero)
			स_नकल(req->result, पंचांगpl->hash_zero,
					पंचांगpl->alg.ahash.halg.digestsize);
		वापस 0;
	पूर्ण

	वापस qce->async_req_enqueue(पंचांगpl->qce, &req->base);
पूर्ण

अटल पूर्णांक qce_ahash_hmac_setkey(काष्ठा crypto_ahash *tfm, स्थिर u8 *key,
				 अचिन्हित पूर्णांक keylen)
अणु
	अचिन्हित पूर्णांक digestsize = crypto_ahash_digestsize(tfm);
	काष्ठा qce_sha_ctx *ctx = crypto_tfm_ctx(&tfm->base);
	काष्ठा crypto_रुको रुको;
	काष्ठा ahash_request *req;
	काष्ठा scatterlist sg;
	अचिन्हित पूर्णांक blocksize;
	काष्ठा crypto_ahash *ahash_tfm;
	u8 *buf;
	पूर्णांक ret;
	स्थिर अक्षर *alg_name;

	blocksize = crypto_tfm_alg_blocksize(crypto_ahash_tfm(tfm));
	स_रखो(ctx->authkey, 0, माप(ctx->authkey));

	अगर (keylen <= blocksize) अणु
		स_नकल(ctx->authkey, key, keylen);
		वापस 0;
	पूर्ण

	अगर (digestsize == SHA1_DIGEST_SIZE)
		alg_name = "sha1-qce";
	अन्यथा अगर (digestsize == SHA256_DIGEST_SIZE)
		alg_name = "sha256-qce";
	अन्यथा
		वापस -EINVAL;

	ahash_tfm = crypto_alloc_ahash(alg_name, 0, 0);
	अगर (IS_ERR(ahash_tfm))
		वापस PTR_ERR(ahash_tfm);

	req = ahash_request_alloc(ahash_tfm, GFP_KERNEL);
	अगर (!req) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_ahash;
	पूर्ण

	crypto_init_रुको(&रुको);
	ahash_request_set_callback(req, CRYPTO_TFM_REQ_MAY_BACKLOG,
				   crypto_req_करोne, &रुको);
	crypto_ahash_clear_flags(ahash_tfm, ~0);

	buf = kzalloc(keylen + QCE_MAX_ALIGN_SIZE, GFP_KERNEL);
	अगर (!buf) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_req;
	पूर्ण

	स_नकल(buf, key, keylen);
	sg_init_one(&sg, buf, keylen);
	ahash_request_set_crypt(req, &sg, ctx->authkey, keylen);

	ret = crypto_रुको_req(crypto_ahash_digest(req), &रुको);

	kमुक्त(buf);
err_मुक्त_req:
	ahash_request_मुक्त(req);
err_मुक्त_ahash:
	crypto_मुक्त_ahash(ahash_tfm);
	वापस ret;
पूर्ण

अटल पूर्णांक qce_ahash_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा crypto_ahash *ahash = __crypto_ahash_cast(tfm);
	काष्ठा qce_sha_ctx *ctx = crypto_tfm_ctx(tfm);

	crypto_ahash_set_reqsize(ahash, माप(काष्ठा qce_sha_reqctx));
	स_रखो(ctx, 0, माप(*ctx));
	वापस 0;
पूर्ण

काष्ठा qce_ahash_def अणु
	अचिन्हित दीर्घ flags;
	स्थिर अक्षर *name;
	स्थिर अक्षर *drv_name;
	अचिन्हित पूर्णांक digestsize;
	अचिन्हित पूर्णांक blocksize;
	अचिन्हित पूर्णांक statesize;
	स्थिर u32 *std_iv;
पूर्ण;

अटल स्थिर काष्ठा qce_ahash_def ahash_def[] = अणु
	अणु
		.flags		= QCE_HASH_SHA1,
		.name		= "sha1",
		.drv_name	= "sha1-qce",
		.digestsize	= SHA1_DIGEST_SIZE,
		.blocksize	= SHA1_BLOCK_SIZE,
		.statesize	= माप(काष्ठा qce_sha_saved_state),
		.std_iv		= std_iv_sha1,
	पूर्ण,
	अणु
		.flags		= QCE_HASH_SHA256,
		.name		= "sha256",
		.drv_name	= "sha256-qce",
		.digestsize	= SHA256_DIGEST_SIZE,
		.blocksize	= SHA256_BLOCK_SIZE,
		.statesize	= माप(काष्ठा qce_sha_saved_state),
		.std_iv		= std_iv_sha256,
	पूर्ण,
	अणु
		.flags		= QCE_HASH_SHA1_HMAC,
		.name		= "hmac(sha1)",
		.drv_name	= "hmac-sha1-qce",
		.digestsize	= SHA1_DIGEST_SIZE,
		.blocksize	= SHA1_BLOCK_SIZE,
		.statesize	= माप(काष्ठा qce_sha_saved_state),
		.std_iv		= std_iv_sha1,
	पूर्ण,
	अणु
		.flags		= QCE_HASH_SHA256_HMAC,
		.name		= "hmac(sha256)",
		.drv_name	= "hmac-sha256-qce",
		.digestsize	= SHA256_DIGEST_SIZE,
		.blocksize	= SHA256_BLOCK_SIZE,
		.statesize	= माप(काष्ठा qce_sha_saved_state),
		.std_iv		= std_iv_sha256,
	पूर्ण,
पूर्ण;

अटल पूर्णांक qce_ahash_रेजिस्टर_one(स्थिर काष्ठा qce_ahash_def *def,
				  काष्ठा qce_device *qce)
अणु
	काष्ठा qce_alg_ढाँचा *पंचांगpl;
	काष्ठा ahash_alg *alg;
	काष्ठा crypto_alg *base;
	पूर्णांक ret;

	पंचांगpl = kzalloc(माप(*पंचांगpl), GFP_KERNEL);
	अगर (!पंचांगpl)
		वापस -ENOMEM;

	पंचांगpl->std_iv = def->std_iv;

	alg = &पंचांगpl->alg.ahash;
	alg->init = qce_ahash_init;
	alg->update = qce_ahash_update;
	alg->final = qce_ahash_final;
	alg->digest = qce_ahash_digest;
	alg->export = qce_ahash_export;
	alg->import = qce_ahash_import;
	अगर (IS_SHA_HMAC(def->flags))
		alg->setkey = qce_ahash_hmac_setkey;
	alg->halg.digestsize = def->digestsize;
	alg->halg.statesize = def->statesize;

	अगर (IS_SHA1(def->flags))
		पंचांगpl->hash_zero = sha1_zero_message_hash;
	अन्यथा अगर (IS_SHA256(def->flags))
		पंचांगpl->hash_zero = sha256_zero_message_hash;

	base = &alg->halg.base;
	base->cra_blocksize = def->blocksize;
	base->cra_priority = 300;
	base->cra_flags = CRYPTO_ALG_ASYNC | CRYPTO_ALG_KERN_DRIVER_ONLY;
	base->cra_ctxsize = माप(काष्ठा qce_sha_ctx);
	base->cra_alignmask = 0;
	base->cra_module = THIS_MODULE;
	base->cra_init = qce_ahash_cra_init;

	snम_लिखो(base->cra_name, CRYPTO_MAX_ALG_NAME, "%s", def->name);
	snम_लिखो(base->cra_driver_name, CRYPTO_MAX_ALG_NAME, "%s",
		 def->drv_name);

	INIT_LIST_HEAD(&पंचांगpl->entry);
	पंचांगpl->crypto_alg_type = CRYPTO_ALG_TYPE_AHASH;
	पंचांगpl->alg_flags = def->flags;
	पंचांगpl->qce = qce;

	ret = crypto_रेजिस्टर_ahash(alg);
	अगर (ret) अणु
		kमुक्त(पंचांगpl);
		dev_err(qce->dev, "%s registration failed\n", base->cra_name);
		वापस ret;
	पूर्ण

	list_add_tail(&पंचांगpl->entry, &ahash_algs);
	dev_dbg(qce->dev, "%s is registered\n", base->cra_name);
	वापस 0;
पूर्ण

अटल व्योम qce_ahash_unरेजिस्टर(काष्ठा qce_device *qce)
अणु
	काष्ठा qce_alg_ढाँचा *पंचांगpl, *n;

	list_क्रम_each_entry_safe(पंचांगpl, n, &ahash_algs, entry) अणु
		crypto_unरेजिस्टर_ahash(&पंचांगpl->alg.ahash);
		list_del(&पंचांगpl->entry);
		kमुक्त(पंचांगpl);
	पूर्ण
पूर्ण

अटल पूर्णांक qce_ahash_रेजिस्टर(काष्ठा qce_device *qce)
अणु
	पूर्णांक ret, i;

	क्रम (i = 0; i < ARRAY_SIZE(ahash_def); i++) अणु
		ret = qce_ahash_रेजिस्टर_one(&ahash_def[i], qce);
		अगर (ret)
			जाओ err;
	पूर्ण

	वापस 0;
err:
	qce_ahash_unरेजिस्टर(qce);
	वापस ret;
पूर्ण

स्थिर काष्ठा qce_algo_ops ahash_ops = अणु
	.type = CRYPTO_ALG_TYPE_AHASH,
	.रेजिस्टर_algs = qce_ahash_रेजिस्टर,
	.unरेजिस्टर_algs = qce_ahash_unरेजिस्टर,
	.async_req_handle = qce_ahash_async_req_handle,
पूर्ण;
