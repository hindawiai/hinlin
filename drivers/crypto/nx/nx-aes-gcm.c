<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AES GCM routines supporting the Power 7+ Nest Accelerators driver
 *
 * Copyright (C) 2012 International Business Machines Inc.
 *
 * Author: Kent Yoder <yoder1@us.ibm.com>
 */

#समावेश <crypto/पूर्णांकernal/aead.h>
#समावेश <crypto/aes.h>
#समावेश <crypto/algapi.h>
#समावेश <crypto/gcm.h>
#समावेश <crypto/scatterwalk.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <यंत्र/vपन.स>

#समावेश "nx_csbcpb.h"
#समावेश "nx.h"


अटल पूर्णांक gcm_aes_nx_set_key(काष्ठा crypto_aead *tfm,
			      स्थिर u8           *in_key,
			      अचिन्हित पूर्णांक        key_len)
अणु
	काष्ठा nx_crypto_ctx *nx_ctx = crypto_aead_ctx(tfm);
	काष्ठा nx_csbcpb *csbcpb = nx_ctx->csbcpb;
	काष्ठा nx_csbcpb *csbcpb_aead = nx_ctx->csbcpb_aead;

	nx_ctx_init(nx_ctx, HCOP_FC_AES);

	चयन (key_len) अणु
	हाल AES_KEYSIZE_128:
		NX_CPB_SET_KEY_SIZE(csbcpb, NX_KS_AES_128);
		NX_CPB_SET_KEY_SIZE(csbcpb_aead, NX_KS_AES_128);
		nx_ctx->ap = &nx_ctx->props[NX_PROPS_AES_128];
		अवरोध;
	हाल AES_KEYSIZE_192:
		NX_CPB_SET_KEY_SIZE(csbcpb, NX_KS_AES_192);
		NX_CPB_SET_KEY_SIZE(csbcpb_aead, NX_KS_AES_192);
		nx_ctx->ap = &nx_ctx->props[NX_PROPS_AES_192];
		अवरोध;
	हाल AES_KEYSIZE_256:
		NX_CPB_SET_KEY_SIZE(csbcpb, NX_KS_AES_256);
		NX_CPB_SET_KEY_SIZE(csbcpb_aead, NX_KS_AES_256);
		nx_ctx->ap = &nx_ctx->props[NX_PROPS_AES_256];
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	csbcpb->cpb.hdr.mode = NX_MODE_AES_GCM;
	स_नकल(csbcpb->cpb.aes_gcm.key, in_key, key_len);

	csbcpb_aead->cpb.hdr.mode = NX_MODE_AES_GCA;
	स_नकल(csbcpb_aead->cpb.aes_gca.key, in_key, key_len);

	वापस 0;
पूर्ण

अटल पूर्णांक gcm4106_aes_nx_set_key(काष्ठा crypto_aead *tfm,
				  स्थिर u8           *in_key,
				  अचिन्हित पूर्णांक        key_len)
अणु
	काष्ठा nx_crypto_ctx *nx_ctx = crypto_aead_ctx(tfm);
	अक्षर *nonce = nx_ctx->priv.gcm.nonce;
	पूर्णांक rc;

	अगर (key_len < 4)
		वापस -EINVAL;

	key_len -= 4;

	rc = gcm_aes_nx_set_key(tfm, in_key, key_len);
	अगर (rc)
		जाओ out;

	स_नकल(nonce, in_key + key_len, 4);
out:
	वापस rc;
पूर्ण

अटल पूर्णांक gcm4106_aes_nx_setauthsize(काष्ठा crypto_aead *tfm,
				      अचिन्हित पूर्णांक authsize)
अणु
	चयन (authsize) अणु
	हाल 8:
	हाल 12:
	हाल 16:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nx_gca(काष्ठा nx_crypto_ctx  *nx_ctx,
		  काष्ठा aead_request   *req,
		  u8                    *out,
		  अचिन्हित पूर्णांक assoclen)
अणु
	पूर्णांक rc;
	काष्ठा nx_csbcpb *csbcpb_aead = nx_ctx->csbcpb_aead;
	काष्ठा scatter_walk walk;
	काष्ठा nx_sg *nx_sg = nx_ctx->in_sg;
	अचिन्हित पूर्णांक nbytes = assoclen;
	अचिन्हित पूर्णांक processed = 0, to_process;
	अचिन्हित पूर्णांक max_sg_len;

	अगर (nbytes <= AES_BLOCK_SIZE) अणु
		scatterwalk_start(&walk, req->src);
		scatterwalk_copychunks(out, &walk, nbytes, SCATTERWALK_FROM_SG);
		scatterwalk_करोne(&walk, SCATTERWALK_FROM_SG, 0);
		वापस 0;
	पूर्ण

	NX_CPB_FDM(csbcpb_aead) &= ~NX_FDM_CONTINUATION;

	/* page_limit: number of sg entries that fit on one page */
	max_sg_len = min_t(u64, nx_driver.of.max_sg_len/माप(काष्ठा nx_sg),
			   nx_ctx->ap->sglen);
	max_sg_len = min_t(u64, max_sg_len,
			   nx_ctx->ap->databytelen/NX_PAGE_SIZE);

	करो अणु
		/*
		 * to_process: the data chunk to process in this update.
		 * This value is bound by sg list limits.
		 */
		to_process = min_t(u64, nbytes - processed,
				   nx_ctx->ap->databytelen);
		to_process = min_t(u64, to_process,
				   NX_PAGE_SIZE * (max_sg_len - 1));

		nx_sg = nx_walk_and_build(nx_ctx->in_sg, max_sg_len,
					  req->src, processed, &to_process);

		अगर ((to_process + processed) < nbytes)
			NX_CPB_FDM(csbcpb_aead) |= NX_FDM_INTERMEDIATE;
		अन्यथा
			NX_CPB_FDM(csbcpb_aead) &= ~NX_FDM_INTERMEDIATE;

		nx_ctx->op_aead.inlen = (nx_ctx->in_sg - nx_sg)
					* माप(काष्ठा nx_sg);

		rc = nx_hcall_sync(nx_ctx, &nx_ctx->op_aead,
				req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP);
		अगर (rc)
			वापस rc;

		स_नकल(csbcpb_aead->cpb.aes_gca.in_pat,
				csbcpb_aead->cpb.aes_gca.out_pat,
				AES_BLOCK_SIZE);
		NX_CPB_FDM(csbcpb_aead) |= NX_FDM_CONTINUATION;

		atomic_inc(&(nx_ctx->stats->aes_ops));
		atomic64_add(assoclen, &(nx_ctx->stats->aes_bytes));

		processed += to_process;
	पूर्ण जबतक (processed < nbytes);

	स_नकल(out, csbcpb_aead->cpb.aes_gca.out_pat, AES_BLOCK_SIZE);

	वापस rc;
पूर्ण

अटल पूर्णांक gmac(काष्ठा aead_request *req, स्थिर u8 *iv, अचिन्हित पूर्णांक assoclen)
अणु
	पूर्णांक rc;
	काष्ठा nx_crypto_ctx *nx_ctx =
		crypto_aead_ctx(crypto_aead_reqtfm(req));
	काष्ठा nx_csbcpb *csbcpb = nx_ctx->csbcpb;
	काष्ठा nx_sg *nx_sg;
	अचिन्हित पूर्णांक nbytes = assoclen;
	अचिन्हित पूर्णांक processed = 0, to_process;
	अचिन्हित पूर्णांक max_sg_len;

	/* Set GMAC mode */
	csbcpb->cpb.hdr.mode = NX_MODE_AES_GMAC;

	NX_CPB_FDM(csbcpb) &= ~NX_FDM_CONTINUATION;

	/* page_limit: number of sg entries that fit on one page */
	max_sg_len = min_t(u64, nx_driver.of.max_sg_len/माप(काष्ठा nx_sg),
			   nx_ctx->ap->sglen);
	max_sg_len = min_t(u64, max_sg_len,
			   nx_ctx->ap->databytelen/NX_PAGE_SIZE);

	/* Copy IV */
	स_नकल(csbcpb->cpb.aes_gcm.iv_or_cnt, iv, AES_BLOCK_SIZE);

	करो अणु
		/*
		 * to_process: the data chunk to process in this update.
		 * This value is bound by sg list limits.
		 */
		to_process = min_t(u64, nbytes - processed,
				   nx_ctx->ap->databytelen);
		to_process = min_t(u64, to_process,
				   NX_PAGE_SIZE * (max_sg_len - 1));

		nx_sg = nx_walk_and_build(nx_ctx->in_sg, max_sg_len,
					  req->src, processed, &to_process);

		अगर ((to_process + processed) < nbytes)
			NX_CPB_FDM(csbcpb) |= NX_FDM_INTERMEDIATE;
		अन्यथा
			NX_CPB_FDM(csbcpb) &= ~NX_FDM_INTERMEDIATE;

		nx_ctx->op.inlen = (nx_ctx->in_sg - nx_sg)
					* माप(काष्ठा nx_sg);

		csbcpb->cpb.aes_gcm.bit_length_data = 0;
		csbcpb->cpb.aes_gcm.bit_length_aad = 8 * nbytes;

		rc = nx_hcall_sync(nx_ctx, &nx_ctx->op,
				req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP);
		अगर (rc)
			जाओ out;

		स_नकल(csbcpb->cpb.aes_gcm.in_pat_or_aad,
			csbcpb->cpb.aes_gcm.out_pat_or_mac, AES_BLOCK_SIZE);
		स_नकल(csbcpb->cpb.aes_gcm.in_s0,
			csbcpb->cpb.aes_gcm.out_s0, AES_BLOCK_SIZE);

		NX_CPB_FDM(csbcpb) |= NX_FDM_CONTINUATION;

		atomic_inc(&(nx_ctx->stats->aes_ops));
		atomic64_add(assoclen, &(nx_ctx->stats->aes_bytes));

		processed += to_process;
	पूर्ण जबतक (processed < nbytes);

out:
	/* Restore GCM mode */
	csbcpb->cpb.hdr.mode = NX_MODE_AES_GCM;
	वापस rc;
पूर्ण

अटल पूर्णांक gcm_empty(काष्ठा aead_request *req, स्थिर u8 *iv, पूर्णांक enc)
अणु
	पूर्णांक rc;
	काष्ठा nx_crypto_ctx *nx_ctx =
		crypto_aead_ctx(crypto_aead_reqtfm(req));
	काष्ठा nx_csbcpb *csbcpb = nx_ctx->csbcpb;
	अक्षर out[AES_BLOCK_SIZE];
	काष्ठा nx_sg *in_sg, *out_sg;
	पूर्णांक len;

	/* For scenarios where the input message is zero length, AES CTR mode
	 * may be used. Set the source data to be a single block (16B) of all
	 * zeros, and set the input IV value to be the same as the GMAC IV
	 * value. - nx_wb 4.8.1.3 */

	/* Change to ECB mode */
	csbcpb->cpb.hdr.mode = NX_MODE_AES_ECB;
	स_नकल(csbcpb->cpb.aes_ecb.key, csbcpb->cpb.aes_gcm.key,
			माप(csbcpb->cpb.aes_ecb.key));
	अगर (enc)
		NX_CPB_FDM(csbcpb) |= NX_FDM_ENDE_ENCRYPT;
	अन्यथा
		NX_CPB_FDM(csbcpb) &= ~NX_FDM_ENDE_ENCRYPT;

	len = AES_BLOCK_SIZE;

	/* Encrypt the counter/IV */
	in_sg = nx_build_sg_list(nx_ctx->in_sg, (u8 *) iv,
				 &len, nx_ctx->ap->sglen);

	अगर (len != AES_BLOCK_SIZE)
		वापस -EINVAL;

	len = माप(out);
	out_sg = nx_build_sg_list(nx_ctx->out_sg, (u8 *) out, &len,
				  nx_ctx->ap->sglen);

	अगर (len != माप(out))
		वापस -EINVAL;

	nx_ctx->op.inlen = (nx_ctx->in_sg - in_sg) * माप(काष्ठा nx_sg);
	nx_ctx->op.outlen = (nx_ctx->out_sg - out_sg) * माप(काष्ठा nx_sg);

	rc = nx_hcall_sync(nx_ctx, &nx_ctx->op,
			   req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP);
	अगर (rc)
		जाओ out;
	atomic_inc(&(nx_ctx->stats->aes_ops));

	/* Copy out the auth tag */
	स_नकल(csbcpb->cpb.aes_gcm.out_pat_or_mac, out,
			crypto_aead_authsize(crypto_aead_reqtfm(req)));
out:
	/* Restore XCBC mode */
	csbcpb->cpb.hdr.mode = NX_MODE_AES_GCM;

	/*
	 * ECB key uses the same region that GCM AAD and counter, so it's safe
	 * to just fill it with zeroes.
	 */
	स_रखो(csbcpb->cpb.aes_ecb.key, 0, माप(csbcpb->cpb.aes_ecb.key));

	वापस rc;
पूर्ण

अटल पूर्णांक gcm_aes_nx_crypt(काष्ठा aead_request *req, पूर्णांक enc,
			    अचिन्हित पूर्णांक assoclen)
अणु
	काष्ठा nx_crypto_ctx *nx_ctx =
		crypto_aead_ctx(crypto_aead_reqtfm(req));
	काष्ठा nx_gcm_rctx *rctx = aead_request_ctx(req);
	काष्ठा nx_csbcpb *csbcpb = nx_ctx->csbcpb;
	अचिन्हित पूर्णांक nbytes = req->cryptlen;
	अचिन्हित पूर्णांक processed = 0, to_process;
	अचिन्हित दीर्घ irq_flags;
	पूर्णांक rc = -EINVAL;

	spin_lock_irqsave(&nx_ctx->lock, irq_flags);

	/* initialize the counter */
	*(u32 *)&rctx->iv[NX_GCM_CTR_OFFSET] = 1;

	अगर (nbytes == 0) अणु
		अगर (assoclen == 0)
			rc = gcm_empty(req, rctx->iv, enc);
		अन्यथा
			rc = gmac(req, rctx->iv, assoclen);
		अगर (rc)
			जाओ out;
		अन्यथा
			जाओ mac;
	पूर्ण

	/* Process associated data */
	csbcpb->cpb.aes_gcm.bit_length_aad = assoclen * 8;
	अगर (assoclen) अणु
		rc = nx_gca(nx_ctx, req, csbcpb->cpb.aes_gcm.in_pat_or_aad,
			    assoclen);
		अगर (rc)
			जाओ out;
	पूर्ण

	/* Set flags क्रम encryption */
	NX_CPB_FDM(csbcpb) &= ~NX_FDM_CONTINUATION;
	अगर (enc) अणु
		NX_CPB_FDM(csbcpb) |= NX_FDM_ENDE_ENCRYPT;
	पूर्ण अन्यथा अणु
		NX_CPB_FDM(csbcpb) &= ~NX_FDM_ENDE_ENCRYPT;
		nbytes -= crypto_aead_authsize(crypto_aead_reqtfm(req));
	पूर्ण

	करो अणु
		to_process = nbytes - processed;

		csbcpb->cpb.aes_gcm.bit_length_data = nbytes * 8;
		rc = nx_build_sg_lists(nx_ctx, rctx->iv, req->dst,
				       req->src, &to_process,
				       processed + req->assoclen,
				       csbcpb->cpb.aes_gcm.iv_or_cnt);

		अगर (rc)
			जाओ out;

		अगर ((to_process + processed) < nbytes)
			NX_CPB_FDM(csbcpb) |= NX_FDM_INTERMEDIATE;
		अन्यथा
			NX_CPB_FDM(csbcpb) &= ~NX_FDM_INTERMEDIATE;


		rc = nx_hcall_sync(nx_ctx, &nx_ctx->op,
				   req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP);
		अगर (rc)
			जाओ out;

		स_नकल(rctx->iv, csbcpb->cpb.aes_gcm.out_cnt, AES_BLOCK_SIZE);
		स_नकल(csbcpb->cpb.aes_gcm.in_pat_or_aad,
			csbcpb->cpb.aes_gcm.out_pat_or_mac, AES_BLOCK_SIZE);
		स_नकल(csbcpb->cpb.aes_gcm.in_s0,
			csbcpb->cpb.aes_gcm.out_s0, AES_BLOCK_SIZE);

		NX_CPB_FDM(csbcpb) |= NX_FDM_CONTINUATION;

		atomic_inc(&(nx_ctx->stats->aes_ops));
		atomic64_add(csbcpb->csb.processed_byte_count,
			     &(nx_ctx->stats->aes_bytes));

		processed += to_process;
	पूर्ण जबतक (processed < nbytes);

mac:
	अगर (enc) अणु
		/* copy out the auth tag */
		scatterwalk_map_and_copy(
			csbcpb->cpb.aes_gcm.out_pat_or_mac,
			req->dst, req->assoclen + nbytes,
			crypto_aead_authsize(crypto_aead_reqtfm(req)),
			SCATTERWALK_TO_SG);
	पूर्ण अन्यथा अणु
		u8 *itag = nx_ctx->priv.gcm.iauth_tag;
		u8 *otag = csbcpb->cpb.aes_gcm.out_pat_or_mac;

		scatterwalk_map_and_copy(
			itag, req->src, req->assoclen + nbytes,
			crypto_aead_authsize(crypto_aead_reqtfm(req)),
			SCATTERWALK_FROM_SG);
		rc = crypto_memneq(itag, otag,
			    crypto_aead_authsize(crypto_aead_reqtfm(req))) ?
		     -EBADMSG : 0;
	पूर्ण
out:
	spin_unlock_irqrestore(&nx_ctx->lock, irq_flags);
	वापस rc;
पूर्ण

अटल पूर्णांक gcm_aes_nx_encrypt(काष्ठा aead_request *req)
अणु
	काष्ठा nx_gcm_rctx *rctx = aead_request_ctx(req);
	अक्षर *iv = rctx->iv;

	स_नकल(iv, req->iv, GCM_AES_IV_SIZE);

	वापस gcm_aes_nx_crypt(req, 1, req->assoclen);
पूर्ण

अटल पूर्णांक gcm_aes_nx_decrypt(काष्ठा aead_request *req)
अणु
	काष्ठा nx_gcm_rctx *rctx = aead_request_ctx(req);
	अक्षर *iv = rctx->iv;

	स_नकल(iv, req->iv, GCM_AES_IV_SIZE);

	वापस gcm_aes_nx_crypt(req, 0, req->assoclen);
पूर्ण

अटल पूर्णांक gcm4106_aes_nx_encrypt(काष्ठा aead_request *req)
अणु
	काष्ठा nx_crypto_ctx *nx_ctx =
		crypto_aead_ctx(crypto_aead_reqtfm(req));
	काष्ठा nx_gcm_rctx *rctx = aead_request_ctx(req);
	अक्षर *iv = rctx->iv;
	अक्षर *nonce = nx_ctx->priv.gcm.nonce;

	स_नकल(iv, nonce, NX_GCM4106_NONCE_LEN);
	स_नकल(iv + NX_GCM4106_NONCE_LEN, req->iv, 8);

	अगर (req->assoclen < 8)
		वापस -EINVAL;

	वापस gcm_aes_nx_crypt(req, 1, req->assoclen - 8);
पूर्ण

अटल पूर्णांक gcm4106_aes_nx_decrypt(काष्ठा aead_request *req)
अणु
	काष्ठा nx_crypto_ctx *nx_ctx =
		crypto_aead_ctx(crypto_aead_reqtfm(req));
	काष्ठा nx_gcm_rctx *rctx = aead_request_ctx(req);
	अक्षर *iv = rctx->iv;
	अक्षर *nonce = nx_ctx->priv.gcm.nonce;

	स_नकल(iv, nonce, NX_GCM4106_NONCE_LEN);
	स_नकल(iv + NX_GCM4106_NONCE_LEN, req->iv, 8);

	अगर (req->assoclen < 8)
		वापस -EINVAL;

	वापस gcm_aes_nx_crypt(req, 0, req->assoclen - 8);
पूर्ण

काष्ठा aead_alg nx_gcm_aes_alg = अणु
	.base = अणु
		.cra_name        = "gcm(aes)",
		.cra_driver_name = "gcm-aes-nx",
		.cra_priority    = 300,
		.cra_blocksize   = 1,
		.cra_ctxsize     = माप(काष्ठा nx_crypto_ctx),
		.cra_module      = THIS_MODULE,
	पूर्ण,
	.init        = nx_crypto_ctx_aes_gcm_init,
	.निकास        = nx_crypto_ctx_aead_निकास,
	.ivsize      = GCM_AES_IV_SIZE,
	.maxauthsize = AES_BLOCK_SIZE,
	.setkey      = gcm_aes_nx_set_key,
	.encrypt     = gcm_aes_nx_encrypt,
	.decrypt     = gcm_aes_nx_decrypt,
पूर्ण;

काष्ठा aead_alg nx_gcm4106_aes_alg = अणु
	.base = अणु
		.cra_name        = "rfc4106(gcm(aes))",
		.cra_driver_name = "rfc4106-gcm-aes-nx",
		.cra_priority    = 300,
		.cra_blocksize   = 1,
		.cra_ctxsize     = माप(काष्ठा nx_crypto_ctx),
		.cra_module      = THIS_MODULE,
	पूर्ण,
	.init        = nx_crypto_ctx_aes_gcm_init,
	.निकास        = nx_crypto_ctx_aead_निकास,
	.ivsize      = GCM_RFC4106_IV_SIZE,
	.maxauthsize = AES_BLOCK_SIZE,
	.setkey      = gcm4106_aes_nx_set_key,
	.setauthsize = gcm4106_aes_nx_setauthsize,
	.encrypt     = gcm4106_aes_nx_encrypt,
	.decrypt     = gcm4106_aes_nx_decrypt,
पूर्ण;
