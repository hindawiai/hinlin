<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AES CCM routines supporting the Power 7+ Nest Accelerators driver
 *
 * Copyright (C) 2012 International Business Machines Inc.
 *
 * Author: Kent Yoder <yoder1@us.ibm.com>
 */

#समावेश <crypto/पूर्णांकernal/aead.h>
#समावेश <crypto/aes.h>
#समावेश <crypto/algapi.h>
#समावेश <crypto/scatterwalk.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/crypto.h>
#समावेश <यंत्र/vपन.स>

#समावेश "nx_csbcpb.h"
#समावेश "nx.h"


अटल पूर्णांक ccm_aes_nx_set_key(काष्ठा crypto_aead *tfm,
			      स्थिर u8           *in_key,
			      अचिन्हित पूर्णांक        key_len)
अणु
	काष्ठा nx_crypto_ctx *nx_ctx = crypto_tfm_ctx(&tfm->base);
	काष्ठा nx_csbcpb *csbcpb = nx_ctx->csbcpb;
	काष्ठा nx_csbcpb *csbcpb_aead = nx_ctx->csbcpb_aead;

	nx_ctx_init(nx_ctx, HCOP_FC_AES);

	चयन (key_len) अणु
	हाल AES_KEYSIZE_128:
		NX_CPB_SET_KEY_SIZE(csbcpb, NX_KS_AES_128);
		NX_CPB_SET_KEY_SIZE(csbcpb_aead, NX_KS_AES_128);
		nx_ctx->ap = &nx_ctx->props[NX_PROPS_AES_128];
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	csbcpb->cpb.hdr.mode = NX_MODE_AES_CCM;
	स_नकल(csbcpb->cpb.aes_ccm.key, in_key, key_len);

	csbcpb_aead->cpb.hdr.mode = NX_MODE_AES_CCA;
	स_नकल(csbcpb_aead->cpb.aes_cca.key, in_key, key_len);

	वापस 0;

पूर्ण

अटल पूर्णांक ccm4309_aes_nx_set_key(काष्ठा crypto_aead *tfm,
				  स्थिर u8           *in_key,
				  अचिन्हित पूर्णांक        key_len)
अणु
	काष्ठा nx_crypto_ctx *nx_ctx = crypto_tfm_ctx(&tfm->base);

	अगर (key_len < 3)
		वापस -EINVAL;

	key_len -= 3;

	स_नकल(nx_ctx->priv.ccm.nonce, in_key + key_len, 3);

	वापस ccm_aes_nx_set_key(tfm, in_key, key_len);
पूर्ण

अटल पूर्णांक ccm_aes_nx_setauthsize(काष्ठा crypto_aead *tfm,
				  अचिन्हित पूर्णांक authsize)
अणु
	चयन (authsize) अणु
	हाल 4:
	हाल 6:
	हाल 8:
	हाल 10:
	हाल 12:
	हाल 14:
	हाल 16:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ccm4309_aes_nx_setauthsize(काष्ठा crypto_aead *tfm,
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

/* taken from crypto/ccm.c */
अटल पूर्णांक set_msg_len(u8 *block, अचिन्हित पूर्णांक msglen, पूर्णांक csize)
अणु
	__be32 data;

	स_रखो(block, 0, csize);
	block += csize;

	अगर (csize >= 4)
		csize = 4;
	अन्यथा अगर (msglen > (अचिन्हित पूर्णांक)(1 << (8 * csize)))
		वापस -EOVERFLOW;

	data = cpu_to_be32(msglen);
	स_नकल(block - csize, (u8 *)&data + 4 - csize, csize);

	वापस 0;
पूर्ण

/* taken from crypto/ccm.c */
अटल अंतरभूत पूर्णांक crypto_ccm_check_iv(स्थिर u8 *iv)
अणु
	/* 2 <= L <= 8, so 1 <= L' <= 7. */
	अगर (1 > iv[0] || iv[0] > 7)
		वापस -EINVAL;

	वापस 0;
पूर्ण

/* based on code from crypto/ccm.c */
अटल पूर्णांक generate_b0(u8 *iv, अचिन्हित पूर्णांक assoclen, अचिन्हित पूर्णांक authsize,
		       अचिन्हित पूर्णांक cryptlen, u8 *b0)
अणु
	अचिन्हित पूर्णांक l, lp, m = authsize;
	पूर्णांक rc;

	स_नकल(b0, iv, 16);

	lp = b0[0];
	l = lp + 1;

	/* set m, bits 3-5 */
	*b0 |= (8 * ((m - 2) / 2));

	/* set adata, bit 6, अगर associated data is used */
	अगर (assoclen)
		*b0 |= 64;

	rc = set_msg_len(b0 + 16 - l, cryptlen, l);

	वापस rc;
पूर्ण

अटल पूर्णांक generate_pat(u8                   *iv,
			काष्ठा aead_request  *req,
			काष्ठा nx_crypto_ctx *nx_ctx,
			अचिन्हित पूर्णांक          authsize,
			अचिन्हित पूर्णांक          nbytes,
			अचिन्हित पूर्णांक	      assoclen,
			u8                   *out)
अणु
	काष्ठा nx_sg *nx_insg = nx_ctx->in_sg;
	काष्ठा nx_sg *nx_outsg = nx_ctx->out_sg;
	अचिन्हित पूर्णांक iauth_len = 0;
	u8 पंचांगp[16], *b1 = शून्य, *b0 = शून्य, *result = शून्य;
	पूर्णांक rc;
	अचिन्हित पूर्णांक max_sg_len;

	/* zero the ctr value */
	स_रखो(iv + 15 - iv[0], 0, iv[0] + 1);

	/* page 78 of nx_wb.pdf has,
	 * Note: RFC3610 allows the AAD data to be up to 2^64 -1 bytes
	 * in length. If a full message is used, the AES CCA implementation
	 * restricts the maximum AAD length to 2^32 -1 bytes.
	 * If partial messages are used, the implementation supports
	 * 2^64 -1 bytes maximum AAD length.
	 *
	 * However, in the cryptoapi's aead_request काष्ठाure,
	 * assoclen is an अचिन्हित पूर्णांक, thus it cannot hold a length
	 * value greater than 2^32 - 1.
	 * Thus the AAD is further स्थिरrained by this and is never
	 * greater than 2^32.
	 */

	अगर (!assoclen) अणु
		b0 = nx_ctx->csbcpb->cpb.aes_ccm.in_pat_or_b0;
	पूर्ण अन्यथा अगर (assoclen <= 14) अणु
		/* अगर associated data is 14 bytes or less, we करो 1 GCM
		 * operation on 2 AES blocks, B0 (stored in the csbcpb) and B1,
		 * which is fed in through the source buffers here */
		b0 = nx_ctx->csbcpb->cpb.aes_ccm.in_pat_or_b0;
		b1 = nx_ctx->priv.ccm.iauth_tag;
		iauth_len = assoclen;
	पूर्ण अन्यथा अगर (assoclen <= 65280) अणु
		/* अगर associated data is less than (2^16 - 2^8), we स्थिरruct
		 * B1 dअगरferently and feed in the associated data to a CCA
		 * operation */
		b0 = nx_ctx->csbcpb_aead->cpb.aes_cca.b0;
		b1 = nx_ctx->csbcpb_aead->cpb.aes_cca.b1;
		iauth_len = 14;
	पूर्ण अन्यथा अणु
		b0 = nx_ctx->csbcpb_aead->cpb.aes_cca.b0;
		b1 = nx_ctx->csbcpb_aead->cpb.aes_cca.b1;
		iauth_len = 10;
	पूर्ण

	/* generate B0 */
	rc = generate_b0(iv, assoclen, authsize, nbytes, b0);
	अगर (rc)
		वापस rc;

	/* generate B1:
	 * add control info क्रम associated data
	 * RFC 3610 and NIST Special Publication 800-38C
	 */
	अगर (b1) अणु
		स_रखो(b1, 0, 16);
		अगर (assoclen <= 65280) अणु
			*(u16 *)b1 = assoclen;
			scatterwalk_map_and_copy(b1 + 2, req->src, 0,
					 iauth_len, SCATTERWALK_FROM_SG);
		पूर्ण अन्यथा अणु
			*(u16 *)b1 = (u16)(0xfffe);
			*(u32 *)&b1[2] = assoclen;
			scatterwalk_map_and_copy(b1 + 6, req->src, 0,
					 iauth_len, SCATTERWALK_FROM_SG);
		पूर्ण
	पूर्ण

	/* now copy any reमुख्यing AAD to scatterlist and call nx... */
	अगर (!assoclen) अणु
		वापस rc;
	पूर्ण अन्यथा अगर (assoclen <= 14) अणु
		अचिन्हित पूर्णांक len = 16;

		nx_insg = nx_build_sg_list(nx_insg, b1, &len, nx_ctx->ap->sglen);

		अगर (len != 16)
			वापस -EINVAL;

		nx_outsg = nx_build_sg_list(nx_outsg, पंचांगp, &len,
					    nx_ctx->ap->sglen);

		अगर (len != 16)
			वापस -EINVAL;

		/* inlen should be negative, indicating to phyp that its a
		 * poपूर्णांकer to an sg list */
		nx_ctx->op.inlen = (nx_ctx->in_sg - nx_insg) *
					माप(काष्ठा nx_sg);
		nx_ctx->op.outlen = (nx_ctx->out_sg - nx_outsg) *
					माप(काष्ठा nx_sg);

		NX_CPB_FDM(nx_ctx->csbcpb) |= NX_FDM_ENDE_ENCRYPT;
		NX_CPB_FDM(nx_ctx->csbcpb) |= NX_FDM_INTERMEDIATE;

		result = nx_ctx->csbcpb->cpb.aes_ccm.out_pat_or_mac;

		rc = nx_hcall_sync(nx_ctx, &nx_ctx->op,
				   req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP);
		अगर (rc)
			वापस rc;

		atomic_inc(&(nx_ctx->stats->aes_ops));
		atomic64_add(assoclen, &nx_ctx->stats->aes_bytes);

	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक processed = 0, to_process;

		processed += iauth_len;

		/* page_limit: number of sg entries that fit on one page */
		max_sg_len = min_t(u64, nx_ctx->ap->sglen,
				nx_driver.of.max_sg_len/माप(काष्ठा nx_sg));
		max_sg_len = min_t(u64, max_sg_len,
				nx_ctx->ap->databytelen/NX_PAGE_SIZE);

		करो अणु
			to_process = min_t(u32, assoclen - processed,
					   nx_ctx->ap->databytelen);

			nx_insg = nx_walk_and_build(nx_ctx->in_sg,
						    nx_ctx->ap->sglen,
						    req->src, processed,
						    &to_process);

			अगर ((to_process + processed) < assoclen) अणु
				NX_CPB_FDM(nx_ctx->csbcpb_aead) |=
					NX_FDM_INTERMEDIATE;
			पूर्ण अन्यथा अणु
				NX_CPB_FDM(nx_ctx->csbcpb_aead) &=
					~NX_FDM_INTERMEDIATE;
			पूर्ण


			nx_ctx->op_aead.inlen = (nx_ctx->in_sg - nx_insg) *
						माप(काष्ठा nx_sg);

			result = nx_ctx->csbcpb_aead->cpb.aes_cca.out_pat_or_b0;

			rc = nx_hcall_sync(nx_ctx, &nx_ctx->op_aead,
				   req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP);
			अगर (rc)
				वापस rc;

			स_नकल(nx_ctx->csbcpb_aead->cpb.aes_cca.b0,
				nx_ctx->csbcpb_aead->cpb.aes_cca.out_pat_or_b0,
				AES_BLOCK_SIZE);

			NX_CPB_FDM(nx_ctx->csbcpb_aead) |= NX_FDM_CONTINUATION;

			atomic_inc(&(nx_ctx->stats->aes_ops));
			atomic64_add(assoclen, &nx_ctx->stats->aes_bytes);

			processed += to_process;
		पूर्ण जबतक (processed < assoclen);

		result = nx_ctx->csbcpb_aead->cpb.aes_cca.out_pat_or_b0;
	पूर्ण

	स_नकल(out, result, AES_BLOCK_SIZE);

	वापस rc;
पूर्ण

अटल पूर्णांक ccm_nx_decrypt(काष्ठा aead_request   *req,
			  u8                    *iv,
			  अचिन्हित पूर्णांक assoclen)
अणु
	काष्ठा nx_crypto_ctx *nx_ctx = crypto_tfm_ctx(req->base.tfm);
	काष्ठा nx_csbcpb *csbcpb = nx_ctx->csbcpb;
	अचिन्हित पूर्णांक nbytes = req->cryptlen;
	अचिन्हित पूर्णांक authsize = crypto_aead_authsize(crypto_aead_reqtfm(req));
	काष्ठा nx_ccm_priv *priv = &nx_ctx->priv.ccm;
	अचिन्हित दीर्घ irq_flags;
	अचिन्हित पूर्णांक processed = 0, to_process;
	पूर्णांक rc = -1;

	spin_lock_irqsave(&nx_ctx->lock, irq_flags);

	nbytes -= authsize;

	/* copy out the auth tag to compare with later */
	scatterwalk_map_and_copy(priv->oauth_tag,
				 req->src, nbytes + req->assoclen, authsize,
				 SCATTERWALK_FROM_SG);

	rc = generate_pat(iv, req, nx_ctx, authsize, nbytes, assoclen,
			  csbcpb->cpb.aes_ccm.in_pat_or_b0);
	अगर (rc)
		जाओ out;

	करो अणु

		/* to_process: the AES_BLOCK_SIZE data chunk to process in this
		 * update. This value is bound by sg list limits.
		 */
		to_process = nbytes - processed;

		अगर ((to_process + processed) < nbytes)
			NX_CPB_FDM(csbcpb) |= NX_FDM_INTERMEDIATE;
		अन्यथा
			NX_CPB_FDM(csbcpb) &= ~NX_FDM_INTERMEDIATE;

		NX_CPB_FDM(nx_ctx->csbcpb) &= ~NX_FDM_ENDE_ENCRYPT;

		rc = nx_build_sg_lists(nx_ctx, iv, req->dst, req->src,
				       &to_process, processed + req->assoclen,
				       csbcpb->cpb.aes_ccm.iv_or_ctr);
		अगर (rc)
			जाओ out;

		rc = nx_hcall_sync(nx_ctx, &nx_ctx->op,
			   req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP);
		अगर (rc)
			जाओ out;

		/* क्रम partial completion, copy following क्रम next
		 * entry पूर्णांकo loop...
		 */
		स_नकल(iv, csbcpb->cpb.aes_ccm.out_ctr, AES_BLOCK_SIZE);
		स_नकल(csbcpb->cpb.aes_ccm.in_pat_or_b0,
			csbcpb->cpb.aes_ccm.out_pat_or_mac, AES_BLOCK_SIZE);
		स_नकल(csbcpb->cpb.aes_ccm.in_s0,
			csbcpb->cpb.aes_ccm.out_s0, AES_BLOCK_SIZE);

		NX_CPB_FDM(csbcpb) |= NX_FDM_CONTINUATION;

		/* update stats */
		atomic_inc(&(nx_ctx->stats->aes_ops));
		atomic64_add(csbcpb->csb.processed_byte_count,
			     &(nx_ctx->stats->aes_bytes));

		processed += to_process;
	पूर्ण जबतक (processed < nbytes);

	rc = crypto_memneq(csbcpb->cpb.aes_ccm.out_pat_or_mac, priv->oauth_tag,
		    authsize) ? -EBADMSG : 0;
out:
	spin_unlock_irqrestore(&nx_ctx->lock, irq_flags);
	वापस rc;
पूर्ण

अटल पूर्णांक ccm_nx_encrypt(काष्ठा aead_request   *req,
			  u8                    *iv,
			  अचिन्हित पूर्णांक assoclen)
अणु
	काष्ठा nx_crypto_ctx *nx_ctx = crypto_tfm_ctx(req->base.tfm);
	काष्ठा nx_csbcpb *csbcpb = nx_ctx->csbcpb;
	अचिन्हित पूर्णांक nbytes = req->cryptlen;
	अचिन्हित पूर्णांक authsize = crypto_aead_authsize(crypto_aead_reqtfm(req));
	अचिन्हित दीर्घ irq_flags;
	अचिन्हित पूर्णांक processed = 0, to_process;
	पूर्णांक rc = -1;

	spin_lock_irqsave(&nx_ctx->lock, irq_flags);

	rc = generate_pat(iv, req, nx_ctx, authsize, nbytes, assoclen,
			  csbcpb->cpb.aes_ccm.in_pat_or_b0);
	अगर (rc)
		जाओ out;

	करो अणु
		/* to process: the AES_BLOCK_SIZE data chunk to process in this
		 * update. This value is bound by sg list limits.
		 */
		to_process = nbytes - processed;

		अगर ((to_process + processed) < nbytes)
			NX_CPB_FDM(csbcpb) |= NX_FDM_INTERMEDIATE;
		अन्यथा
			NX_CPB_FDM(csbcpb) &= ~NX_FDM_INTERMEDIATE;

		NX_CPB_FDM(csbcpb) |= NX_FDM_ENDE_ENCRYPT;

		rc = nx_build_sg_lists(nx_ctx, iv, req->dst, req->src,
				       &to_process, processed + req->assoclen,
				       csbcpb->cpb.aes_ccm.iv_or_ctr);
		अगर (rc)
			जाओ out;

		rc = nx_hcall_sync(nx_ctx, &nx_ctx->op,
				   req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP);
		अगर (rc)
			जाओ out;

		/* क्रम partial completion, copy following क्रम next
		 * entry पूर्णांकo loop...
		 */
		स_नकल(iv, csbcpb->cpb.aes_ccm.out_ctr, AES_BLOCK_SIZE);
		स_नकल(csbcpb->cpb.aes_ccm.in_pat_or_b0,
			csbcpb->cpb.aes_ccm.out_pat_or_mac, AES_BLOCK_SIZE);
		स_नकल(csbcpb->cpb.aes_ccm.in_s0,
			csbcpb->cpb.aes_ccm.out_s0, AES_BLOCK_SIZE);

		NX_CPB_FDM(csbcpb) |= NX_FDM_CONTINUATION;

		/* update stats */
		atomic_inc(&(nx_ctx->stats->aes_ops));
		atomic64_add(csbcpb->csb.processed_byte_count,
			     &(nx_ctx->stats->aes_bytes));

		processed += to_process;

	पूर्ण जबतक (processed < nbytes);

	/* copy out the auth tag */
	scatterwalk_map_and_copy(csbcpb->cpb.aes_ccm.out_pat_or_mac,
				 req->dst, nbytes + req->assoclen, authsize,
				 SCATTERWALK_TO_SG);

out:
	spin_unlock_irqrestore(&nx_ctx->lock, irq_flags);
	वापस rc;
पूर्ण

अटल पूर्णांक ccm4309_aes_nx_encrypt(काष्ठा aead_request *req)
अणु
	काष्ठा nx_crypto_ctx *nx_ctx = crypto_tfm_ctx(req->base.tfm);
	काष्ठा nx_gcm_rctx *rctx = aead_request_ctx(req);
	u8 *iv = rctx->iv;

	iv[0] = 3;
	स_नकल(iv + 1, nx_ctx->priv.ccm.nonce, 3);
	स_नकल(iv + 4, req->iv, 8);

	वापस ccm_nx_encrypt(req, iv, req->assoclen - 8);
पूर्ण

अटल पूर्णांक ccm_aes_nx_encrypt(काष्ठा aead_request *req)
अणु
	पूर्णांक rc;

	rc = crypto_ccm_check_iv(req->iv);
	अगर (rc)
		वापस rc;

	वापस ccm_nx_encrypt(req, req->iv, req->assoclen);
पूर्ण

अटल पूर्णांक ccm4309_aes_nx_decrypt(काष्ठा aead_request *req)
अणु
	काष्ठा nx_crypto_ctx *nx_ctx = crypto_tfm_ctx(req->base.tfm);
	काष्ठा nx_gcm_rctx *rctx = aead_request_ctx(req);
	u8 *iv = rctx->iv;

	iv[0] = 3;
	स_नकल(iv + 1, nx_ctx->priv.ccm.nonce, 3);
	स_नकल(iv + 4, req->iv, 8);

	वापस ccm_nx_decrypt(req, iv, req->assoclen - 8);
पूर्ण

अटल पूर्णांक ccm_aes_nx_decrypt(काष्ठा aead_request *req)
अणु
	पूर्णांक rc;

	rc = crypto_ccm_check_iv(req->iv);
	अगर (rc)
		वापस rc;

	वापस ccm_nx_decrypt(req, req->iv, req->assoclen);
पूर्ण

काष्ठा aead_alg nx_ccm_aes_alg = अणु
	.base = अणु
		.cra_name        = "ccm(aes)",
		.cra_driver_name = "ccm-aes-nx",
		.cra_priority    = 300,
		.cra_flags       = CRYPTO_ALG_NEED_FALLBACK,
		.cra_blocksize   = 1,
		.cra_ctxsize     = माप(काष्ठा nx_crypto_ctx),
		.cra_module      = THIS_MODULE,
	पूर्ण,
	.init        = nx_crypto_ctx_aes_ccm_init,
	.निकास        = nx_crypto_ctx_aead_निकास,
	.ivsize      = AES_BLOCK_SIZE,
	.maxauthsize = AES_BLOCK_SIZE,
	.setkey      = ccm_aes_nx_set_key,
	.setauthsize = ccm_aes_nx_setauthsize,
	.encrypt     = ccm_aes_nx_encrypt,
	.decrypt     = ccm_aes_nx_decrypt,
पूर्ण;

काष्ठा aead_alg nx_ccm4309_aes_alg = अणु
	.base = अणु
		.cra_name        = "rfc4309(ccm(aes))",
		.cra_driver_name = "rfc4309-ccm-aes-nx",
		.cra_priority    = 300,
		.cra_flags       = CRYPTO_ALG_NEED_FALLBACK,
		.cra_blocksize   = 1,
		.cra_ctxsize     = माप(काष्ठा nx_crypto_ctx),
		.cra_module      = THIS_MODULE,
	पूर्ण,
	.init        = nx_crypto_ctx_aes_ccm_init,
	.निकास        = nx_crypto_ctx_aead_निकास,
	.ivsize      = 8,
	.maxauthsize = AES_BLOCK_SIZE,
	.setkey      = ccm4309_aes_nx_set_key,
	.setauthsize = ccm4309_aes_nx_setauthsize,
	.encrypt     = ccm4309_aes_nx_encrypt,
	.decrypt     = ccm4309_aes_nx_decrypt,
पूर्ण;
