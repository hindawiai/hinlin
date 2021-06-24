<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Hash algorithms supported by the CESA: MD5, SHA1 and SHA256.
 *
 * Author: Boris Brezillon <boris.brezillon@मुक्त-electrons.com>
 * Author: Arnaud Ebalard <arno@natisbad.org>
 *
 * This work is based on an initial version written by
 * Sebastian Andrzej Siewior < sebastian at अवरोधpoपूर्णांक करोt cc >
 */

#समावेश <crypto/hmac.h>
#समावेश <crypto/md5.h>
#समावेश <crypto/sha1.h>
#समावेश <crypto/sha2.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>

#समावेश "cesa.h"

काष्ठा mv_cesa_ahash_dma_iter अणु
	काष्ठा mv_cesa_dma_iter base;
	काष्ठा mv_cesa_sg_dma_iter src;
पूर्ण;

अटल अंतरभूत व्योम
mv_cesa_ahash_req_iter_init(काष्ठा mv_cesa_ahash_dma_iter *iter,
			    काष्ठा ahash_request *req)
अणु
	काष्ठा mv_cesa_ahash_req *creq = ahash_request_ctx(req);
	अचिन्हित पूर्णांक len = req->nbytes + creq->cache_ptr;

	अगर (!creq->last_req)
		len &= ~CESA_HASH_BLOCK_SIZE_MSK;

	mv_cesa_req_dma_iter_init(&iter->base, len);
	mv_cesa_sg_dma_iter_init(&iter->src, req->src, DMA_TO_DEVICE);
	iter->src.op_offset = creq->cache_ptr;
पूर्ण

अटल अंतरभूत bool
mv_cesa_ahash_req_iter_next_op(काष्ठा mv_cesa_ahash_dma_iter *iter)
अणु
	iter->src.op_offset = 0;

	वापस mv_cesa_req_dma_iter_next_op(&iter->base);
पूर्ण

अटल अंतरभूत पूर्णांक
mv_cesa_ahash_dma_alloc_cache(काष्ठा mv_cesa_ahash_dma_req *req, gfp_t flags)
अणु
	req->cache = dma_pool_alloc(cesa_dev->dma->cache_pool, flags,
				    &req->cache_dma);
	अगर (!req->cache)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम
mv_cesa_ahash_dma_मुक्त_cache(काष्ठा mv_cesa_ahash_dma_req *req)
अणु
	अगर (!req->cache)
		वापस;

	dma_pool_मुक्त(cesa_dev->dma->cache_pool, req->cache,
		      req->cache_dma);
पूर्ण

अटल पूर्णांक mv_cesa_ahash_dma_alloc_padding(काष्ठा mv_cesa_ahash_dma_req *req,
					   gfp_t flags)
अणु
	अगर (req->padding)
		वापस 0;

	req->padding = dma_pool_alloc(cesa_dev->dma->padding_pool, flags,
				      &req->padding_dma);
	अगर (!req->padding)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम mv_cesa_ahash_dma_मुक्त_padding(काष्ठा mv_cesa_ahash_dma_req *req)
अणु
	अगर (!req->padding)
		वापस;

	dma_pool_मुक्त(cesa_dev->dma->padding_pool, req->padding,
		      req->padding_dma);
	req->padding = शून्य;
पूर्ण

अटल अंतरभूत व्योम mv_cesa_ahash_dma_last_cleanup(काष्ठा ahash_request *req)
अणु
	काष्ठा mv_cesa_ahash_req *creq = ahash_request_ctx(req);

	mv_cesa_ahash_dma_मुक्त_padding(&creq->req.dma);
पूर्ण

अटल अंतरभूत व्योम mv_cesa_ahash_dma_cleanup(काष्ठा ahash_request *req)
अणु
	काष्ठा mv_cesa_ahash_req *creq = ahash_request_ctx(req);

	dma_unmap_sg(cesa_dev->dev, req->src, creq->src_nents, DMA_TO_DEVICE);
	mv_cesa_ahash_dma_मुक्त_cache(&creq->req.dma);
	mv_cesa_dma_cleanup(&creq->base);
पूर्ण

अटल अंतरभूत व्योम mv_cesa_ahash_cleanup(काष्ठा ahash_request *req)
अणु
	काष्ठा mv_cesa_ahash_req *creq = ahash_request_ctx(req);

	अगर (mv_cesa_req_get_type(&creq->base) == CESA_DMA_REQ)
		mv_cesa_ahash_dma_cleanup(req);
पूर्ण

अटल व्योम mv_cesa_ahash_last_cleanup(काष्ठा ahash_request *req)
अणु
	काष्ठा mv_cesa_ahash_req *creq = ahash_request_ctx(req);

	अगर (mv_cesa_req_get_type(&creq->base) == CESA_DMA_REQ)
		mv_cesa_ahash_dma_last_cleanup(req);
पूर्ण

अटल पूर्णांक mv_cesa_ahash_pad_len(काष्ठा mv_cesa_ahash_req *creq)
अणु
	अचिन्हित पूर्णांक index, padlen;

	index = creq->len & CESA_HASH_BLOCK_SIZE_MSK;
	padlen = (index < 56) ? (56 - index) : (64 + 56 - index);

	वापस padlen;
पूर्ण

अटल पूर्णांक mv_cesa_ahash_pad_req(काष्ठा mv_cesa_ahash_req *creq, u8 *buf)
अणु
	अचिन्हित पूर्णांक padlen;

	buf[0] = 0x80;
	/* Pad out to 56 mod 64 */
	padlen = mv_cesa_ahash_pad_len(creq);
	स_रखो(buf + 1, 0, padlen - 1);

	अगर (creq->algo_le) अणु
		__le64 bits = cpu_to_le64(creq->len << 3);

		स_नकल(buf + padlen, &bits, माप(bits));
	पूर्ण अन्यथा अणु
		__be64 bits = cpu_to_be64(creq->len << 3);

		स_नकल(buf + padlen, &bits, माप(bits));
	पूर्ण

	वापस padlen + 8;
पूर्ण

अटल व्योम mv_cesa_ahash_std_step(काष्ठा ahash_request *req)
अणु
	काष्ठा mv_cesa_ahash_req *creq = ahash_request_ctx(req);
	काष्ठा mv_cesa_ahash_std_req *sreq = &creq->req.std;
	काष्ठा mv_cesa_engine *engine = creq->base.engine;
	काष्ठा mv_cesa_op_ctx *op;
	अचिन्हित पूर्णांक new_cache_ptr = 0;
	u32 frag_mode;
	माप_प्रकार  len;
	अचिन्हित पूर्णांक digsize;
	पूर्णांक i;

	mv_cesa_adjust_op(engine, &creq->op_पंचांगpl);
	अगर (engine->pool)
		स_नकल(engine->sram_pool, &creq->op_पंचांगpl,
		       माप(creq->op_पंचांगpl));
	अन्यथा
		स_नकल_toio(engine->sram, &creq->op_पंचांगpl,
			    माप(creq->op_पंचांगpl));

	अगर (!sreq->offset) अणु
		digsize = crypto_ahash_digestsize(crypto_ahash_reqtfm(req));
		क्रम (i = 0; i < digsize / 4; i++)
			ग_लिखोl_relaxed(creq->state[i],
				       engine->regs + CESA_IVDIG(i));
	पूर्ण

	अगर (creq->cache_ptr) अणु
		अगर (engine->pool)
			स_नकल(engine->sram_pool + CESA_SA_DATA_SRAM_OFFSET,
			       creq->cache, creq->cache_ptr);
		अन्यथा
			स_नकल_toio(engine->sram + CESA_SA_DATA_SRAM_OFFSET,
				    creq->cache, creq->cache_ptr);
	पूर्ण

	len = min_t(माप_प्रकार, req->nbytes + creq->cache_ptr - sreq->offset,
		    CESA_SA_SRAM_PAYLOAD_SIZE);

	अगर (!creq->last_req) अणु
		new_cache_ptr = len & CESA_HASH_BLOCK_SIZE_MSK;
		len &= ~CESA_HASH_BLOCK_SIZE_MSK;
	पूर्ण

	अगर (len - creq->cache_ptr)
		sreq->offset += mv_cesa_sg_copy_to_sram(
			engine, req->src, creq->src_nents,
			CESA_SA_DATA_SRAM_OFFSET + creq->cache_ptr,
			len - creq->cache_ptr, sreq->offset);

	op = &creq->op_पंचांगpl;

	frag_mode = mv_cesa_get_op_cfg(op) & CESA_SA_DESC_CFG_FRAG_MSK;

	अगर (creq->last_req && sreq->offset == req->nbytes &&
	    creq->len <= CESA_SA_DESC_MAC_SRC_TOTAL_LEN_MAX) अणु
		अगर (frag_mode == CESA_SA_DESC_CFG_FIRST_FRAG)
			frag_mode = CESA_SA_DESC_CFG_NOT_FRAG;
		अन्यथा अगर (frag_mode == CESA_SA_DESC_CFG_MID_FRAG)
			frag_mode = CESA_SA_DESC_CFG_LAST_FRAG;
	पूर्ण

	अगर (frag_mode == CESA_SA_DESC_CFG_NOT_FRAG ||
	    frag_mode == CESA_SA_DESC_CFG_LAST_FRAG) अणु
		अगर (len &&
		    creq->len <= CESA_SA_DESC_MAC_SRC_TOTAL_LEN_MAX) अणु
			mv_cesa_set_mac_op_total_len(op, creq->len);
		पूर्ण अन्यथा अणु
			पूर्णांक trailerlen = mv_cesa_ahash_pad_len(creq) + 8;

			अगर (len + trailerlen > CESA_SA_SRAM_PAYLOAD_SIZE) अणु
				len &= CESA_HASH_BLOCK_SIZE_MSK;
				new_cache_ptr = 64 - trailerlen;
				अगर (engine->pool)
					स_नकल(creq->cache,
					       engine->sram_pool +
					       CESA_SA_DATA_SRAM_OFFSET + len,
					       new_cache_ptr);
				अन्यथा
					स_नकल_fromio(creq->cache,
						      engine->sram +
						      CESA_SA_DATA_SRAM_OFFSET +
						      len,
						      new_cache_ptr);
			पूर्ण अन्यथा अणु
				i = mv_cesa_ahash_pad_req(creq, creq->cache);
				len += i;
				अगर (engine->pool)
					स_नकल(engine->sram_pool + len +
					       CESA_SA_DATA_SRAM_OFFSET,
					       creq->cache, i);
				अन्यथा
					स_नकल_toio(engine->sram + len +
						    CESA_SA_DATA_SRAM_OFFSET,
						    creq->cache, i);
			पूर्ण

			अगर (frag_mode == CESA_SA_DESC_CFG_LAST_FRAG)
				frag_mode = CESA_SA_DESC_CFG_MID_FRAG;
			अन्यथा
				frag_mode = CESA_SA_DESC_CFG_FIRST_FRAG;
		पूर्ण
	पूर्ण

	mv_cesa_set_mac_op_frag_len(op, len);
	mv_cesa_update_op_cfg(op, frag_mode, CESA_SA_DESC_CFG_FRAG_MSK);

	/* FIXME: only update enc_len field */
	अगर (engine->pool)
		स_नकल(engine->sram_pool, op, माप(*op));
	अन्यथा
		स_नकल_toio(engine->sram, op, माप(*op));

	अगर (frag_mode == CESA_SA_DESC_CFG_FIRST_FRAG)
		mv_cesa_update_op_cfg(op, CESA_SA_DESC_CFG_MID_FRAG,
				      CESA_SA_DESC_CFG_FRAG_MSK);

	creq->cache_ptr = new_cache_ptr;

	mv_cesa_set_पूर्णांक_mask(engine, CESA_SA_INT_ACCEL0_DONE);
	ग_लिखोl_relaxed(CESA_SA_CFG_PARA_DIS, engine->regs + CESA_SA_CFG);
	WARN_ON(पढ़ोl(engine->regs + CESA_SA_CMD) &
		CESA_SA_CMD_EN_CESA_SA_ACCL0);
	ग_लिखोl(CESA_SA_CMD_EN_CESA_SA_ACCL0, engine->regs + CESA_SA_CMD);
पूर्ण

अटल पूर्णांक mv_cesa_ahash_std_process(काष्ठा ahash_request *req, u32 status)
अणु
	काष्ठा mv_cesa_ahash_req *creq = ahash_request_ctx(req);
	काष्ठा mv_cesa_ahash_std_req *sreq = &creq->req.std;

	अगर (sreq->offset < (req->nbytes - creq->cache_ptr))
		वापस -EINPROGRESS;

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम mv_cesa_ahash_dma_prepare(काष्ठा ahash_request *req)
अणु
	काष्ठा mv_cesa_ahash_req *creq = ahash_request_ctx(req);
	काष्ठा mv_cesa_req *basereq = &creq->base;

	mv_cesa_dma_prepare(basereq, basereq->engine);
पूर्ण

अटल व्योम mv_cesa_ahash_std_prepare(काष्ठा ahash_request *req)
अणु
	काष्ठा mv_cesa_ahash_req *creq = ahash_request_ctx(req);
	काष्ठा mv_cesa_ahash_std_req *sreq = &creq->req.std;

	sreq->offset = 0;
पूर्ण

अटल व्योम mv_cesa_ahash_dma_step(काष्ठा ahash_request *req)
अणु
	काष्ठा mv_cesa_ahash_req *creq = ahash_request_ctx(req);
	काष्ठा mv_cesa_req *base = &creq->base;

	/* We must explicitly set the digest state. */
	अगर (base->chain.first->flags & CESA_TDMA_SET_STATE) अणु
		काष्ठा mv_cesa_engine *engine = base->engine;
		पूर्णांक i;

		/* Set the hash state in the IVDIG regs. */
		क्रम (i = 0; i < ARRAY_SIZE(creq->state); i++)
			ग_लिखोl_relaxed(creq->state[i], engine->regs +
				       CESA_IVDIG(i));
	पूर्ण

	mv_cesa_dma_step(base);
पूर्ण

अटल व्योम mv_cesa_ahash_step(काष्ठा crypto_async_request *req)
अणु
	काष्ठा ahash_request *ahashreq = ahash_request_cast(req);
	काष्ठा mv_cesa_ahash_req *creq = ahash_request_ctx(ahashreq);

	अगर (mv_cesa_req_get_type(&creq->base) == CESA_DMA_REQ)
		mv_cesa_ahash_dma_step(ahashreq);
	अन्यथा
		mv_cesa_ahash_std_step(ahashreq);
पूर्ण

अटल पूर्णांक mv_cesa_ahash_process(काष्ठा crypto_async_request *req, u32 status)
अणु
	काष्ठा ahash_request *ahashreq = ahash_request_cast(req);
	काष्ठा mv_cesa_ahash_req *creq = ahash_request_ctx(ahashreq);

	अगर (mv_cesa_req_get_type(&creq->base) == CESA_DMA_REQ)
		वापस mv_cesa_dma_process(&creq->base, status);

	वापस mv_cesa_ahash_std_process(ahashreq, status);
पूर्ण

अटल व्योम mv_cesa_ahash_complete(काष्ठा crypto_async_request *req)
अणु
	काष्ठा ahash_request *ahashreq = ahash_request_cast(req);
	काष्ठा mv_cesa_ahash_req *creq = ahash_request_ctx(ahashreq);
	काष्ठा mv_cesa_engine *engine = creq->base.engine;
	अचिन्हित पूर्णांक digsize;
	पूर्णांक i;

	digsize = crypto_ahash_digestsize(crypto_ahash_reqtfm(ahashreq));

	अगर (mv_cesa_req_get_type(&creq->base) == CESA_DMA_REQ &&
	    (creq->base.chain.last->flags & CESA_TDMA_TYPE_MSK) ==
	     CESA_TDMA_RESULT) अणु
		__le32 *data = शून्य;

		/*
		 * Result is alपढ़ोy in the correct endianness when the SA is
		 * used
		 */
		data = creq->base.chain.last->op->ctx.hash.hash;
		क्रम (i = 0; i < digsize / 4; i++)
			creq->state[i] = le32_to_cpu(data[i]);

		स_नकल(ahashreq->result, data, digsize);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < digsize / 4; i++)
			creq->state[i] = पढ़ोl_relaxed(engine->regs +
						       CESA_IVDIG(i));
		अगर (creq->last_req) अणु
			/*
			 * Hardware's MD5 digest is in little endian क्रमmat, but
			 * SHA in big endian क्रमmat
			 */
			अगर (creq->algo_le) अणु
				__le32 *result = (व्योम *)ahashreq->result;

				क्रम (i = 0; i < digsize / 4; i++)
					result[i] = cpu_to_le32(creq->state[i]);
			पूर्ण अन्यथा अणु
				__be32 *result = (व्योम *)ahashreq->result;

				क्रम (i = 0; i < digsize / 4; i++)
					result[i] = cpu_to_be32(creq->state[i]);
			पूर्ण
		पूर्ण
	पूर्ण

	atomic_sub(ahashreq->nbytes, &engine->load);
पूर्ण

अटल व्योम mv_cesa_ahash_prepare(काष्ठा crypto_async_request *req,
				  काष्ठा mv_cesa_engine *engine)
अणु
	काष्ठा ahash_request *ahashreq = ahash_request_cast(req);
	काष्ठा mv_cesa_ahash_req *creq = ahash_request_ctx(ahashreq);

	creq->base.engine = engine;

	अगर (mv_cesa_req_get_type(&creq->base) == CESA_DMA_REQ)
		mv_cesa_ahash_dma_prepare(ahashreq);
	अन्यथा
		mv_cesa_ahash_std_prepare(ahashreq);
पूर्ण

अटल व्योम mv_cesa_ahash_req_cleanup(काष्ठा crypto_async_request *req)
अणु
	काष्ठा ahash_request *ahashreq = ahash_request_cast(req);
	काष्ठा mv_cesa_ahash_req *creq = ahash_request_ctx(ahashreq);

	अगर (creq->last_req)
		mv_cesa_ahash_last_cleanup(ahashreq);

	mv_cesa_ahash_cleanup(ahashreq);

	अगर (creq->cache_ptr)
		sg_pcopy_to_buffer(ahashreq->src, creq->src_nents,
				   creq->cache,
				   creq->cache_ptr,
				   ahashreq->nbytes - creq->cache_ptr);
पूर्ण

अटल स्थिर काष्ठा mv_cesa_req_ops mv_cesa_ahash_req_ops = अणु
	.step = mv_cesa_ahash_step,
	.process = mv_cesa_ahash_process,
	.cleanup = mv_cesa_ahash_req_cleanup,
	.complete = mv_cesa_ahash_complete,
पूर्ण;

अटल व्योम mv_cesa_ahash_init(काष्ठा ahash_request *req,
			      काष्ठा mv_cesa_op_ctx *पंचांगpl, bool algo_le)
अणु
	काष्ठा mv_cesa_ahash_req *creq = ahash_request_ctx(req);

	स_रखो(creq, 0, माप(*creq));
	mv_cesa_update_op_cfg(पंचांगpl,
			      CESA_SA_DESC_CFG_OP_MAC_ONLY |
			      CESA_SA_DESC_CFG_FIRST_FRAG,
			      CESA_SA_DESC_CFG_OP_MSK |
			      CESA_SA_DESC_CFG_FRAG_MSK);
	mv_cesa_set_mac_op_total_len(पंचांगpl, 0);
	mv_cesa_set_mac_op_frag_len(पंचांगpl, 0);
	creq->op_पंचांगpl = *पंचांगpl;
	creq->len = 0;
	creq->algo_le = algo_le;
पूर्ण

अटल अंतरभूत पूर्णांक mv_cesa_ahash_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा mv_cesa_hash_ctx *ctx = crypto_tfm_ctx(tfm);

	ctx->base.ops = &mv_cesa_ahash_req_ops;

	crypto_ahash_set_reqsize(__crypto_ahash_cast(tfm),
				 माप(काष्ठा mv_cesa_ahash_req));
	वापस 0;
पूर्ण

अटल bool mv_cesa_ahash_cache_req(काष्ठा ahash_request *req)
अणु
	काष्ठा mv_cesa_ahash_req *creq = ahash_request_ctx(req);
	bool cached = false;

	अगर (creq->cache_ptr + req->nbytes < CESA_MAX_HASH_BLOCK_SIZE &&
	    !creq->last_req) अणु
		cached = true;

		अगर (!req->nbytes)
			वापस cached;

		sg_pcopy_to_buffer(req->src, creq->src_nents,
				   creq->cache + creq->cache_ptr,
				   req->nbytes, 0);

		creq->cache_ptr += req->nbytes;
	पूर्ण

	वापस cached;
पूर्ण

अटल काष्ठा mv_cesa_op_ctx *
mv_cesa_dma_add_frag(काष्ठा mv_cesa_tdma_chain *chain,
		     काष्ठा mv_cesa_op_ctx *पंचांगpl, अचिन्हित पूर्णांक frag_len,
		     gfp_t flags)
अणु
	काष्ठा mv_cesa_op_ctx *op;
	पूर्णांक ret;

	op = mv_cesa_dma_add_op(chain, पंचांगpl, false, flags);
	अगर (IS_ERR(op))
		वापस op;

	/* Set the operation block fragment length. */
	mv_cesa_set_mac_op_frag_len(op, frag_len);

	/* Append dummy desc to launch operation */
	ret = mv_cesa_dma_add_dummy_launch(chain, flags);
	अगर (ret)
		वापस ERR_PTR(ret);

	अगर (mv_cesa_mac_op_is_first_frag(पंचांगpl))
		mv_cesa_update_op_cfg(पंचांगpl,
				      CESA_SA_DESC_CFG_MID_FRAG,
				      CESA_SA_DESC_CFG_FRAG_MSK);

	वापस op;
पूर्ण

अटल पूर्णांक
mv_cesa_ahash_dma_add_cache(काष्ठा mv_cesa_tdma_chain *chain,
			    काष्ठा mv_cesa_ahash_req *creq,
			    gfp_t flags)
अणु
	काष्ठा mv_cesa_ahash_dma_req *ahashdreq = &creq->req.dma;
	पूर्णांक ret;

	अगर (!creq->cache_ptr)
		वापस 0;

	ret = mv_cesa_ahash_dma_alloc_cache(ahashdreq, flags);
	अगर (ret)
		वापस ret;

	स_नकल(ahashdreq->cache, creq->cache, creq->cache_ptr);

	वापस mv_cesa_dma_add_data_transfer(chain,
					     CESA_SA_DATA_SRAM_OFFSET,
					     ahashdreq->cache_dma,
					     creq->cache_ptr,
					     CESA_TDMA_DST_IN_SRAM,
					     flags);
पूर्ण

अटल काष्ठा mv_cesa_op_ctx *
mv_cesa_ahash_dma_last_req(काष्ठा mv_cesa_tdma_chain *chain,
			   काष्ठा mv_cesa_ahash_dma_iter *dma_iter,
			   काष्ठा mv_cesa_ahash_req *creq,
			   अचिन्हित पूर्णांक frag_len, gfp_t flags)
अणु
	काष्ठा mv_cesa_ahash_dma_req *ahashdreq = &creq->req.dma;
	अचिन्हित पूर्णांक len, trailerlen, paकरोff = 0;
	काष्ठा mv_cesa_op_ctx *op;
	पूर्णांक ret;

	/*
	 * If the transfer is smaller than our maximum length, and we have
	 * some data outstanding, we can ask the engine to finish the hash.
	 */
	अगर (creq->len <= CESA_SA_DESC_MAC_SRC_TOTAL_LEN_MAX && frag_len) अणु
		op = mv_cesa_dma_add_frag(chain, &creq->op_पंचांगpl, frag_len,
					  flags);
		अगर (IS_ERR(op))
			वापस op;

		mv_cesa_set_mac_op_total_len(op, creq->len);
		mv_cesa_update_op_cfg(op, mv_cesa_mac_op_is_first_frag(op) ?
						CESA_SA_DESC_CFG_NOT_FRAG :
						CESA_SA_DESC_CFG_LAST_FRAG,
				      CESA_SA_DESC_CFG_FRAG_MSK);

		ret = mv_cesa_dma_add_result_op(chain,
						CESA_SA_CFG_SRAM_OFFSET,
						CESA_SA_DATA_SRAM_OFFSET,
						CESA_TDMA_SRC_IN_SRAM, flags);
		अगर (ret)
			वापस ERR_PTR(-ENOMEM);
		वापस op;
	पूर्ण

	/*
	 * The request is दीर्घer than the engine can handle, or we have
	 * no data outstanding. Manually generate the padding, adding it
	 * as a "mid" fragment.
	 */
	ret = mv_cesa_ahash_dma_alloc_padding(ahashdreq, flags);
	अगर (ret)
		वापस ERR_PTR(ret);

	trailerlen = mv_cesa_ahash_pad_req(creq, ahashdreq->padding);

	len = min(CESA_SA_SRAM_PAYLOAD_SIZE - frag_len, trailerlen);
	अगर (len) अणु
		ret = mv_cesa_dma_add_data_transfer(chain,
						CESA_SA_DATA_SRAM_OFFSET +
						frag_len,
						ahashdreq->padding_dma,
						len, CESA_TDMA_DST_IN_SRAM,
						flags);
		अगर (ret)
			वापस ERR_PTR(ret);

		op = mv_cesa_dma_add_frag(chain, &creq->op_पंचांगpl, frag_len + len,
					  flags);
		अगर (IS_ERR(op))
			वापस op;

		अगर (len == trailerlen)
			वापस op;

		paकरोff += len;
	पूर्ण

	ret = mv_cesa_dma_add_data_transfer(chain,
					    CESA_SA_DATA_SRAM_OFFSET,
					    ahashdreq->padding_dma +
					    paकरोff,
					    trailerlen - paकरोff,
					    CESA_TDMA_DST_IN_SRAM,
					    flags);
	अगर (ret)
		वापस ERR_PTR(ret);

	वापस mv_cesa_dma_add_frag(chain, &creq->op_पंचांगpl, trailerlen - paकरोff,
				    flags);
पूर्ण

अटल पूर्णांक mv_cesa_ahash_dma_req_init(काष्ठा ahash_request *req)
अणु
	काष्ठा mv_cesa_ahash_req *creq = ahash_request_ctx(req);
	gfp_t flags = (req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP) ?
		      GFP_KERNEL : GFP_ATOMIC;
	काष्ठा mv_cesa_req *basereq = &creq->base;
	काष्ठा mv_cesa_ahash_dma_iter iter;
	काष्ठा mv_cesa_op_ctx *op = शून्य;
	अचिन्हित पूर्णांक frag_len;
	bool set_state = false;
	पूर्णांक ret;
	u32 type;

	basereq->chain.first = शून्य;
	basereq->chain.last = शून्य;

	अगर (!mv_cesa_mac_op_is_first_frag(&creq->op_पंचांगpl))
		set_state = true;

	अगर (creq->src_nents) अणु
		ret = dma_map_sg(cesa_dev->dev, req->src, creq->src_nents,
				 DMA_TO_DEVICE);
		अगर (!ret) अणु
			ret = -ENOMEM;
			जाओ err;
		पूर्ण
	पूर्ण

	mv_cesa_tdma_desc_iter_init(&basereq->chain);
	mv_cesa_ahash_req_iter_init(&iter, req);

	/*
	 * Add the cache (left-over data from a previous block) first.
	 * This will never overflow the SRAM size.
	 */
	ret = mv_cesa_ahash_dma_add_cache(&basereq->chain, creq, flags);
	अगर (ret)
		जाओ err_मुक्त_tdma;

	अगर (iter.src.sg) अणु
		/*
		 * Add all the new data, inserting an operation block and
		 * launch command between each full SRAM block-worth of
		 * data. We पूर्णांकentionally करो not add the final op block.
		 */
		जबतक (true) अणु
			ret = mv_cesa_dma_add_op_transfers(&basereq->chain,
							   &iter.base,
							   &iter.src, flags);
			अगर (ret)
				जाओ err_मुक्त_tdma;

			frag_len = iter.base.op_len;

			अगर (!mv_cesa_ahash_req_iter_next_op(&iter))
				अवरोध;

			op = mv_cesa_dma_add_frag(&basereq->chain,
						  &creq->op_पंचांगpl,
						  frag_len, flags);
			अगर (IS_ERR(op)) अणु
				ret = PTR_ERR(op);
				जाओ err_मुक्त_tdma;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Account क्रम the data that was in the cache. */
		frag_len = iter.base.op_len;
	पूर्ण

	/*
	 * At this poपूर्णांक, frag_len indicates whether we have any data
	 * outstanding which needs an operation.  Queue up the final
	 * operation, which depends whether this is the final request.
	 */
	अगर (creq->last_req)
		op = mv_cesa_ahash_dma_last_req(&basereq->chain, &iter, creq,
						frag_len, flags);
	अन्यथा अगर (frag_len)
		op = mv_cesa_dma_add_frag(&basereq->chain, &creq->op_पंचांगpl,
					  frag_len, flags);

	अगर (IS_ERR(op)) अणु
		ret = PTR_ERR(op);
		जाओ err_मुक्त_tdma;
	पूर्ण

	/*
	 * If results are copied via DMA, this means that this
	 * request can be directly processed by the engine,
	 * without partial updates. So we can chain it at the
	 * DMA level with other requests.
	 */
	type = basereq->chain.last->flags & CESA_TDMA_TYPE_MSK;

	अगर (op && type != CESA_TDMA_RESULT) अणु
		/* Add dummy desc to रुको क्रम crypto operation end */
		ret = mv_cesa_dma_add_dummy_end(&basereq->chain, flags);
		अगर (ret)
			जाओ err_मुक्त_tdma;
	पूर्ण

	अगर (!creq->last_req)
		creq->cache_ptr = req->nbytes + creq->cache_ptr -
				  iter.base.len;
	अन्यथा
		creq->cache_ptr = 0;

	basereq->chain.last->flags |= CESA_TDMA_END_OF_REQ;

	अगर (type != CESA_TDMA_RESULT)
		basereq->chain.last->flags |= CESA_TDMA_BREAK_CHAIN;

	अगर (set_state) अणु
		/*
		 * Put the CESA_TDMA_SET_STATE flag on the first tdma desc to
		 * let the step logic know that the IVDIG रेजिस्टरs should be
		 * explicitly set beक्रमe launching a TDMA chain.
		 */
		basereq->chain.first->flags |= CESA_TDMA_SET_STATE;
	पूर्ण

	वापस 0;

err_मुक्त_tdma:
	mv_cesa_dma_cleanup(basereq);
	dma_unmap_sg(cesa_dev->dev, req->src, creq->src_nents, DMA_TO_DEVICE);

err:
	mv_cesa_ahash_last_cleanup(req);

	वापस ret;
पूर्ण

अटल पूर्णांक mv_cesa_ahash_req_init(काष्ठा ahash_request *req, bool *cached)
अणु
	काष्ठा mv_cesa_ahash_req *creq = ahash_request_ctx(req);

	creq->src_nents = sg_nents_क्रम_len(req->src, req->nbytes);
	अगर (creq->src_nents < 0) अणु
		dev_err(cesa_dev->dev, "Invalid number of src SG");
		वापस creq->src_nents;
	पूर्ण

	*cached = mv_cesa_ahash_cache_req(req);

	अगर (*cached)
		वापस 0;

	अगर (cesa_dev->caps->has_tdma)
		वापस mv_cesa_ahash_dma_req_init(req);
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक mv_cesa_ahash_queue_req(काष्ठा ahash_request *req)
अणु
	काष्ठा mv_cesa_ahash_req *creq = ahash_request_ctx(req);
	काष्ठा mv_cesa_engine *engine;
	bool cached = false;
	पूर्णांक ret;

	ret = mv_cesa_ahash_req_init(req, &cached);
	अगर (ret)
		वापस ret;

	अगर (cached)
		वापस 0;

	engine = mv_cesa_select_engine(req->nbytes);
	mv_cesa_ahash_prepare(&req->base, engine);

	ret = mv_cesa_queue_req(&req->base, &creq->base);

	अगर (mv_cesa_req_needs_cleanup(&req->base, ret))
		mv_cesa_ahash_cleanup(req);

	वापस ret;
पूर्ण

अटल पूर्णांक mv_cesa_ahash_update(काष्ठा ahash_request *req)
अणु
	काष्ठा mv_cesa_ahash_req *creq = ahash_request_ctx(req);

	creq->len += req->nbytes;

	वापस mv_cesa_ahash_queue_req(req);
पूर्ण

अटल पूर्णांक mv_cesa_ahash_final(काष्ठा ahash_request *req)
अणु
	काष्ठा mv_cesa_ahash_req *creq = ahash_request_ctx(req);
	काष्ठा mv_cesa_op_ctx *पंचांगpl = &creq->op_पंचांगpl;

	mv_cesa_set_mac_op_total_len(पंचांगpl, creq->len);
	creq->last_req = true;
	req->nbytes = 0;

	वापस mv_cesa_ahash_queue_req(req);
पूर्ण

अटल पूर्णांक mv_cesa_ahash_finup(काष्ठा ahash_request *req)
अणु
	काष्ठा mv_cesa_ahash_req *creq = ahash_request_ctx(req);
	काष्ठा mv_cesa_op_ctx *पंचांगpl = &creq->op_पंचांगpl;

	creq->len += req->nbytes;
	mv_cesa_set_mac_op_total_len(पंचांगpl, creq->len);
	creq->last_req = true;

	वापस mv_cesa_ahash_queue_req(req);
पूर्ण

अटल पूर्णांक mv_cesa_ahash_export(काष्ठा ahash_request *req, व्योम *hash,
				u64 *len, व्योम *cache)
अणु
	काष्ठा crypto_ahash *ahash = crypto_ahash_reqtfm(req);
	काष्ठा mv_cesa_ahash_req *creq = ahash_request_ctx(req);
	अचिन्हित पूर्णांक digsize = crypto_ahash_digestsize(ahash);
	अचिन्हित पूर्णांक blocksize;

	blocksize = crypto_ahash_blocksize(ahash);

	*len = creq->len;
	स_नकल(hash, creq->state, digsize);
	स_रखो(cache, 0, blocksize);
	स_नकल(cache, creq->cache, creq->cache_ptr);

	वापस 0;
पूर्ण

अटल पूर्णांक mv_cesa_ahash_import(काष्ठा ahash_request *req, स्थिर व्योम *hash,
				u64 len, स्थिर व्योम *cache)
अणु
	काष्ठा crypto_ahash *ahash = crypto_ahash_reqtfm(req);
	काष्ठा mv_cesa_ahash_req *creq = ahash_request_ctx(req);
	अचिन्हित पूर्णांक digsize = crypto_ahash_digestsize(ahash);
	अचिन्हित पूर्णांक blocksize;
	अचिन्हित पूर्णांक cache_ptr;
	पूर्णांक ret;

	ret = crypto_ahash_init(req);
	अगर (ret)
		वापस ret;

	blocksize = crypto_ahash_blocksize(ahash);
	अगर (len >= blocksize)
		mv_cesa_update_op_cfg(&creq->op_पंचांगpl,
				      CESA_SA_DESC_CFG_MID_FRAG,
				      CESA_SA_DESC_CFG_FRAG_MSK);

	creq->len = len;
	स_नकल(creq->state, hash, digsize);
	creq->cache_ptr = 0;

	cache_ptr = करो_भाग(len, blocksize);
	अगर (!cache_ptr)
		वापस 0;

	स_नकल(creq->cache, cache, cache_ptr);
	creq->cache_ptr = cache_ptr;

	वापस 0;
पूर्ण

अटल पूर्णांक mv_cesa_md5_init(काष्ठा ahash_request *req)
अणु
	काष्ठा mv_cesa_ahash_req *creq = ahash_request_ctx(req);
	काष्ठा mv_cesa_op_ctx पंचांगpl = अणु पूर्ण;

	mv_cesa_set_op_cfg(&पंचांगpl, CESA_SA_DESC_CFG_MACM_MD5);

	mv_cesa_ahash_init(req, &पंचांगpl, true);

	creq->state[0] = MD5_H0;
	creq->state[1] = MD5_H1;
	creq->state[2] = MD5_H2;
	creq->state[3] = MD5_H3;

	वापस 0;
पूर्ण

अटल पूर्णांक mv_cesa_md5_export(काष्ठा ahash_request *req, व्योम *out)
अणु
	काष्ठा md5_state *out_state = out;

	वापस mv_cesa_ahash_export(req, out_state->hash,
				    &out_state->byte_count, out_state->block);
पूर्ण

अटल पूर्णांक mv_cesa_md5_import(काष्ठा ahash_request *req, स्थिर व्योम *in)
अणु
	स्थिर काष्ठा md5_state *in_state = in;

	वापस mv_cesa_ahash_import(req, in_state->hash, in_state->byte_count,
				    in_state->block);
पूर्ण

अटल पूर्णांक mv_cesa_md5_digest(काष्ठा ahash_request *req)
अणु
	पूर्णांक ret;

	ret = mv_cesa_md5_init(req);
	अगर (ret)
		वापस ret;

	वापस mv_cesa_ahash_finup(req);
पूर्ण

काष्ठा ahash_alg mv_md5_alg = अणु
	.init = mv_cesa_md5_init,
	.update = mv_cesa_ahash_update,
	.final = mv_cesa_ahash_final,
	.finup = mv_cesa_ahash_finup,
	.digest = mv_cesa_md5_digest,
	.export = mv_cesa_md5_export,
	.import = mv_cesa_md5_import,
	.halg = अणु
		.digestsize = MD5_DIGEST_SIZE,
		.statesize = माप(काष्ठा md5_state),
		.base = अणु
			.cra_name = "md5",
			.cra_driver_name = "mv-md5",
			.cra_priority = 300,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY |
				     CRYPTO_ALG_KERN_DRIVER_ONLY,
			.cra_blocksize = MD5_HMAC_BLOCK_SIZE,
			.cra_ctxsize = माप(काष्ठा mv_cesa_hash_ctx),
			.cra_init = mv_cesa_ahash_cra_init,
			.cra_module = THIS_MODULE,
		पूर्ण
	पूर्ण
पूर्ण;

अटल पूर्णांक mv_cesa_sha1_init(काष्ठा ahash_request *req)
अणु
	काष्ठा mv_cesa_ahash_req *creq = ahash_request_ctx(req);
	काष्ठा mv_cesa_op_ctx पंचांगpl = अणु पूर्ण;

	mv_cesa_set_op_cfg(&पंचांगpl, CESA_SA_DESC_CFG_MACM_SHA1);

	mv_cesa_ahash_init(req, &पंचांगpl, false);

	creq->state[0] = SHA1_H0;
	creq->state[1] = SHA1_H1;
	creq->state[2] = SHA1_H2;
	creq->state[3] = SHA1_H3;
	creq->state[4] = SHA1_H4;

	वापस 0;
पूर्ण

अटल पूर्णांक mv_cesa_sha1_export(काष्ठा ahash_request *req, व्योम *out)
अणु
	काष्ठा sha1_state *out_state = out;

	वापस mv_cesa_ahash_export(req, out_state->state, &out_state->count,
				    out_state->buffer);
पूर्ण

अटल पूर्णांक mv_cesa_sha1_import(काष्ठा ahash_request *req, स्थिर व्योम *in)
अणु
	स्थिर काष्ठा sha1_state *in_state = in;

	वापस mv_cesa_ahash_import(req, in_state->state, in_state->count,
				    in_state->buffer);
पूर्ण

अटल पूर्णांक mv_cesa_sha1_digest(काष्ठा ahash_request *req)
अणु
	पूर्णांक ret;

	ret = mv_cesa_sha1_init(req);
	अगर (ret)
		वापस ret;

	वापस mv_cesa_ahash_finup(req);
पूर्ण

काष्ठा ahash_alg mv_sha1_alg = अणु
	.init = mv_cesa_sha1_init,
	.update = mv_cesa_ahash_update,
	.final = mv_cesa_ahash_final,
	.finup = mv_cesa_ahash_finup,
	.digest = mv_cesa_sha1_digest,
	.export = mv_cesa_sha1_export,
	.import = mv_cesa_sha1_import,
	.halg = अणु
		.digestsize = SHA1_DIGEST_SIZE,
		.statesize = माप(काष्ठा sha1_state),
		.base = अणु
			.cra_name = "sha1",
			.cra_driver_name = "mv-sha1",
			.cra_priority = 300,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY |
				     CRYPTO_ALG_KERN_DRIVER_ONLY,
			.cra_blocksize = SHA1_BLOCK_SIZE,
			.cra_ctxsize = माप(काष्ठा mv_cesa_hash_ctx),
			.cra_init = mv_cesa_ahash_cra_init,
			.cra_module = THIS_MODULE,
		पूर्ण
	पूर्ण
पूर्ण;

अटल पूर्णांक mv_cesa_sha256_init(काष्ठा ahash_request *req)
अणु
	काष्ठा mv_cesa_ahash_req *creq = ahash_request_ctx(req);
	काष्ठा mv_cesa_op_ctx पंचांगpl = अणु पूर्ण;

	mv_cesa_set_op_cfg(&पंचांगpl, CESA_SA_DESC_CFG_MACM_SHA256);

	mv_cesa_ahash_init(req, &पंचांगpl, false);

	creq->state[0] = SHA256_H0;
	creq->state[1] = SHA256_H1;
	creq->state[2] = SHA256_H2;
	creq->state[3] = SHA256_H3;
	creq->state[4] = SHA256_H4;
	creq->state[5] = SHA256_H5;
	creq->state[6] = SHA256_H6;
	creq->state[7] = SHA256_H7;

	वापस 0;
पूर्ण

अटल पूर्णांक mv_cesa_sha256_digest(काष्ठा ahash_request *req)
अणु
	पूर्णांक ret;

	ret = mv_cesa_sha256_init(req);
	अगर (ret)
		वापस ret;

	वापस mv_cesa_ahash_finup(req);
पूर्ण

अटल पूर्णांक mv_cesa_sha256_export(काष्ठा ahash_request *req, व्योम *out)
अणु
	काष्ठा sha256_state *out_state = out;

	वापस mv_cesa_ahash_export(req, out_state->state, &out_state->count,
				    out_state->buf);
पूर्ण

अटल पूर्णांक mv_cesa_sha256_import(काष्ठा ahash_request *req, स्थिर व्योम *in)
अणु
	स्थिर काष्ठा sha256_state *in_state = in;

	वापस mv_cesa_ahash_import(req, in_state->state, in_state->count,
				    in_state->buf);
पूर्ण

काष्ठा ahash_alg mv_sha256_alg = अणु
	.init = mv_cesa_sha256_init,
	.update = mv_cesa_ahash_update,
	.final = mv_cesa_ahash_final,
	.finup = mv_cesa_ahash_finup,
	.digest = mv_cesa_sha256_digest,
	.export = mv_cesa_sha256_export,
	.import = mv_cesa_sha256_import,
	.halg = अणु
		.digestsize = SHA256_DIGEST_SIZE,
		.statesize = माप(काष्ठा sha256_state),
		.base = अणु
			.cra_name = "sha256",
			.cra_driver_name = "mv-sha256",
			.cra_priority = 300,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY |
				     CRYPTO_ALG_KERN_DRIVER_ONLY,
			.cra_blocksize = SHA256_BLOCK_SIZE,
			.cra_ctxsize = माप(काष्ठा mv_cesa_hash_ctx),
			.cra_init = mv_cesa_ahash_cra_init,
			.cra_module = THIS_MODULE,
		पूर्ण
	पूर्ण
पूर्ण;

काष्ठा mv_cesa_ahash_result अणु
	काष्ठा completion completion;
	पूर्णांक error;
पूर्ण;

अटल व्योम mv_cesa_hmac_ahash_complete(काष्ठा crypto_async_request *req,
					पूर्णांक error)
अणु
	काष्ठा mv_cesa_ahash_result *result = req->data;

	अगर (error == -EINPROGRESS)
		वापस;

	result->error = error;
	complete(&result->completion);
पूर्ण

अटल पूर्णांक mv_cesa_ahmac_iv_state_init(काष्ठा ahash_request *req, u8 *pad,
				       व्योम *state, अचिन्हित पूर्णांक blocksize)
अणु
	काष्ठा mv_cesa_ahash_result result;
	काष्ठा scatterlist sg;
	पूर्णांक ret;

	ahash_request_set_callback(req, CRYPTO_TFM_REQ_MAY_BACKLOG,
				   mv_cesa_hmac_ahash_complete, &result);
	sg_init_one(&sg, pad, blocksize);
	ahash_request_set_crypt(req, &sg, pad, blocksize);
	init_completion(&result.completion);

	ret = crypto_ahash_init(req);
	अगर (ret)
		वापस ret;

	ret = crypto_ahash_update(req);
	अगर (ret && ret != -EINPROGRESS)
		वापस ret;

	रुको_क्रम_completion_पूर्णांकerruptible(&result.completion);
	अगर (result.error)
		वापस result.error;

	ret = crypto_ahash_export(req, state);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक mv_cesa_ahmac_pad_init(काष्ठा ahash_request *req,
				  स्थिर u8 *key, अचिन्हित पूर्णांक keylen,
				  u8 *ipad, u8 *opad,
				  अचिन्हित पूर्णांक blocksize)
अणु
	काष्ठा mv_cesa_ahash_result result;
	काष्ठा scatterlist sg;
	पूर्णांक ret;
	पूर्णांक i;

	अगर (keylen <= blocksize) अणु
		स_नकल(ipad, key, keylen);
	पूर्ण अन्यथा अणु
		u8 *keydup = kmemdup(key, keylen, GFP_KERNEL);

		अगर (!keydup)
			वापस -ENOMEM;

		ahash_request_set_callback(req, CRYPTO_TFM_REQ_MAY_BACKLOG,
					   mv_cesa_hmac_ahash_complete,
					   &result);
		sg_init_one(&sg, keydup, keylen);
		ahash_request_set_crypt(req, &sg, ipad, keylen);
		init_completion(&result.completion);

		ret = crypto_ahash_digest(req);
		अगर (ret == -EINPROGRESS) अणु
			रुको_क्रम_completion_पूर्णांकerruptible(&result.completion);
			ret = result.error;
		पूर्ण

		/* Set the memory region to 0 to aव्योम any leak. */
		kमुक्त_sensitive(keydup);

		अगर (ret)
			वापस ret;

		keylen = crypto_ahash_digestsize(crypto_ahash_reqtfm(req));
	पूर्ण

	स_रखो(ipad + keylen, 0, blocksize - keylen);
	स_नकल(opad, ipad, blocksize);

	क्रम (i = 0; i < blocksize; i++) अणु
		ipad[i] ^= HMAC_IPAD_VALUE;
		opad[i] ^= HMAC_OPAD_VALUE;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mv_cesa_ahmac_setkey(स्थिर अक्षर *hash_alg_name,
				स्थिर u8 *key, अचिन्हित पूर्णांक keylen,
				व्योम *istate, व्योम *ostate)
अणु
	काष्ठा ahash_request *req;
	काष्ठा crypto_ahash *tfm;
	अचिन्हित पूर्णांक blocksize;
	u8 *ipad = शून्य;
	u8 *opad;
	पूर्णांक ret;

	tfm = crypto_alloc_ahash(hash_alg_name, 0, 0);
	अगर (IS_ERR(tfm))
		वापस PTR_ERR(tfm);

	req = ahash_request_alloc(tfm, GFP_KERNEL);
	अगर (!req) अणु
		ret = -ENOMEM;
		जाओ मुक्त_ahash;
	पूर्ण

	crypto_ahash_clear_flags(tfm, ~0);

	blocksize = crypto_tfm_alg_blocksize(crypto_ahash_tfm(tfm));

	ipad = kसुस्मृति(2, blocksize, GFP_KERNEL);
	अगर (!ipad) अणु
		ret = -ENOMEM;
		जाओ मुक्त_req;
	पूर्ण

	opad = ipad + blocksize;

	ret = mv_cesa_ahmac_pad_init(req, key, keylen, ipad, opad, blocksize);
	अगर (ret)
		जाओ मुक्त_ipad;

	ret = mv_cesa_ahmac_iv_state_init(req, ipad, istate, blocksize);
	अगर (ret)
		जाओ मुक्त_ipad;

	ret = mv_cesa_ahmac_iv_state_init(req, opad, ostate, blocksize);

मुक्त_ipad:
	kमुक्त(ipad);
मुक्त_req:
	ahash_request_मुक्त(req);
मुक्त_ahash:
	crypto_मुक्त_ahash(tfm);

	वापस ret;
पूर्ण

अटल पूर्णांक mv_cesa_ahmac_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा mv_cesa_hmac_ctx *ctx = crypto_tfm_ctx(tfm);

	ctx->base.ops = &mv_cesa_ahash_req_ops;

	crypto_ahash_set_reqsize(__crypto_ahash_cast(tfm),
				 माप(काष्ठा mv_cesa_ahash_req));
	वापस 0;
पूर्ण

अटल पूर्णांक mv_cesa_ahmac_md5_init(काष्ठा ahash_request *req)
अणु
	काष्ठा mv_cesa_hmac_ctx *ctx = crypto_tfm_ctx(req->base.tfm);
	काष्ठा mv_cesa_op_ctx पंचांगpl = अणु पूर्ण;

	mv_cesa_set_op_cfg(&पंचांगpl, CESA_SA_DESC_CFG_MACM_HMAC_MD5);
	स_नकल(पंचांगpl.ctx.hash.iv, ctx->iv, माप(ctx->iv));

	mv_cesa_ahash_init(req, &पंचांगpl, true);

	वापस 0;
पूर्ण

अटल पूर्णांक mv_cesa_ahmac_md5_setkey(काष्ठा crypto_ahash *tfm, स्थिर u8 *key,
				    अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा mv_cesa_hmac_ctx *ctx = crypto_tfm_ctx(crypto_ahash_tfm(tfm));
	काष्ठा md5_state istate, ostate;
	पूर्णांक ret, i;

	ret = mv_cesa_ahmac_setkey("mv-md5", key, keylen, &istate, &ostate);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < ARRAY_SIZE(istate.hash); i++)
		ctx->iv[i] = cpu_to_be32(istate.hash[i]);

	क्रम (i = 0; i < ARRAY_SIZE(ostate.hash); i++)
		ctx->iv[i + 8] = cpu_to_be32(ostate.hash[i]);

	वापस 0;
पूर्ण

अटल पूर्णांक mv_cesa_ahmac_md5_digest(काष्ठा ahash_request *req)
अणु
	पूर्णांक ret;

	ret = mv_cesa_ahmac_md5_init(req);
	अगर (ret)
		वापस ret;

	वापस mv_cesa_ahash_finup(req);
पूर्ण

काष्ठा ahash_alg mv_ahmac_md5_alg = अणु
	.init = mv_cesa_ahmac_md5_init,
	.update = mv_cesa_ahash_update,
	.final = mv_cesa_ahash_final,
	.finup = mv_cesa_ahash_finup,
	.digest = mv_cesa_ahmac_md5_digest,
	.setkey = mv_cesa_ahmac_md5_setkey,
	.export = mv_cesa_md5_export,
	.import = mv_cesa_md5_import,
	.halg = अणु
		.digestsize = MD5_DIGEST_SIZE,
		.statesize = माप(काष्ठा md5_state),
		.base = अणु
			.cra_name = "hmac(md5)",
			.cra_driver_name = "mv-hmac-md5",
			.cra_priority = 300,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY |
				     CRYPTO_ALG_KERN_DRIVER_ONLY,
			.cra_blocksize = MD5_HMAC_BLOCK_SIZE,
			.cra_ctxsize = माप(काष्ठा mv_cesa_hmac_ctx),
			.cra_init = mv_cesa_ahmac_cra_init,
			.cra_module = THIS_MODULE,
		पूर्ण
	पूर्ण
पूर्ण;

अटल पूर्णांक mv_cesa_ahmac_sha1_init(काष्ठा ahash_request *req)
अणु
	काष्ठा mv_cesa_hmac_ctx *ctx = crypto_tfm_ctx(req->base.tfm);
	काष्ठा mv_cesa_op_ctx पंचांगpl = अणु पूर्ण;

	mv_cesa_set_op_cfg(&पंचांगpl, CESA_SA_DESC_CFG_MACM_HMAC_SHA1);
	स_नकल(पंचांगpl.ctx.hash.iv, ctx->iv, माप(ctx->iv));

	mv_cesa_ahash_init(req, &पंचांगpl, false);

	वापस 0;
पूर्ण

अटल पूर्णांक mv_cesa_ahmac_sha1_setkey(काष्ठा crypto_ahash *tfm, स्थिर u8 *key,
				     अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा mv_cesa_hmac_ctx *ctx = crypto_tfm_ctx(crypto_ahash_tfm(tfm));
	काष्ठा sha1_state istate, ostate;
	पूर्णांक ret, i;

	ret = mv_cesa_ahmac_setkey("mv-sha1", key, keylen, &istate, &ostate);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < ARRAY_SIZE(istate.state); i++)
		ctx->iv[i] = cpu_to_be32(istate.state[i]);

	क्रम (i = 0; i < ARRAY_SIZE(ostate.state); i++)
		ctx->iv[i + 8] = cpu_to_be32(ostate.state[i]);

	वापस 0;
पूर्ण

अटल पूर्णांक mv_cesa_ahmac_sha1_digest(काष्ठा ahash_request *req)
अणु
	पूर्णांक ret;

	ret = mv_cesa_ahmac_sha1_init(req);
	अगर (ret)
		वापस ret;

	वापस mv_cesa_ahash_finup(req);
पूर्ण

काष्ठा ahash_alg mv_ahmac_sha1_alg = अणु
	.init = mv_cesa_ahmac_sha1_init,
	.update = mv_cesa_ahash_update,
	.final = mv_cesa_ahash_final,
	.finup = mv_cesa_ahash_finup,
	.digest = mv_cesa_ahmac_sha1_digest,
	.setkey = mv_cesa_ahmac_sha1_setkey,
	.export = mv_cesa_sha1_export,
	.import = mv_cesa_sha1_import,
	.halg = अणु
		.digestsize = SHA1_DIGEST_SIZE,
		.statesize = माप(काष्ठा sha1_state),
		.base = अणु
			.cra_name = "hmac(sha1)",
			.cra_driver_name = "mv-hmac-sha1",
			.cra_priority = 300,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY |
				     CRYPTO_ALG_KERN_DRIVER_ONLY,
			.cra_blocksize = SHA1_BLOCK_SIZE,
			.cra_ctxsize = माप(काष्ठा mv_cesa_hmac_ctx),
			.cra_init = mv_cesa_ahmac_cra_init,
			.cra_module = THIS_MODULE,
		पूर्ण
	पूर्ण
पूर्ण;

अटल पूर्णांक mv_cesa_ahmac_sha256_setkey(काष्ठा crypto_ahash *tfm, स्थिर u8 *key,
				       अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा mv_cesa_hmac_ctx *ctx = crypto_tfm_ctx(crypto_ahash_tfm(tfm));
	काष्ठा sha256_state istate, ostate;
	पूर्णांक ret, i;

	ret = mv_cesa_ahmac_setkey("mv-sha256", key, keylen, &istate, &ostate);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < ARRAY_SIZE(istate.state); i++)
		ctx->iv[i] = cpu_to_be32(istate.state[i]);

	क्रम (i = 0; i < ARRAY_SIZE(ostate.state); i++)
		ctx->iv[i + 8] = cpu_to_be32(ostate.state[i]);

	वापस 0;
पूर्ण

अटल पूर्णांक mv_cesa_ahmac_sha256_init(काष्ठा ahash_request *req)
अणु
	काष्ठा mv_cesa_hmac_ctx *ctx = crypto_tfm_ctx(req->base.tfm);
	काष्ठा mv_cesa_op_ctx पंचांगpl = अणु पूर्ण;

	mv_cesa_set_op_cfg(&पंचांगpl, CESA_SA_DESC_CFG_MACM_HMAC_SHA256);
	स_नकल(पंचांगpl.ctx.hash.iv, ctx->iv, माप(ctx->iv));

	mv_cesa_ahash_init(req, &पंचांगpl, false);

	वापस 0;
पूर्ण

अटल पूर्णांक mv_cesa_ahmac_sha256_digest(काष्ठा ahash_request *req)
अणु
	पूर्णांक ret;

	ret = mv_cesa_ahmac_sha256_init(req);
	अगर (ret)
		वापस ret;

	वापस mv_cesa_ahash_finup(req);
पूर्ण

काष्ठा ahash_alg mv_ahmac_sha256_alg = अणु
	.init = mv_cesa_ahmac_sha256_init,
	.update = mv_cesa_ahash_update,
	.final = mv_cesa_ahash_final,
	.finup = mv_cesa_ahash_finup,
	.digest = mv_cesa_ahmac_sha256_digest,
	.setkey = mv_cesa_ahmac_sha256_setkey,
	.export = mv_cesa_sha256_export,
	.import = mv_cesa_sha256_import,
	.halg = अणु
		.digestsize = SHA256_DIGEST_SIZE,
		.statesize = माप(काष्ठा sha256_state),
		.base = अणु
			.cra_name = "hmac(sha256)",
			.cra_driver_name = "mv-hmac-sha256",
			.cra_priority = 300,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY |
				     CRYPTO_ALG_KERN_DRIVER_ONLY,
			.cra_blocksize = SHA256_BLOCK_SIZE,
			.cra_ctxsize = माप(काष्ठा mv_cesa_hmac_ctx),
			.cra_init = mv_cesa_ahmac_cra_init,
			.cra_module = THIS_MODULE,
		पूर्ण
	पूर्ण
पूर्ण;
