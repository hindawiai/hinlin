<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AES CTR routines supporting the Power 7+ Nest Accelerators driver
 *
 * Copyright (C) 2011-2012 International Business Machines Inc.
 *
 * Author: Kent Yoder <yoder1@us.ibm.com>
 */

#समावेश <crypto/aes.h>
#समावेश <crypto/ctr.h>
#समावेश <crypto/algapi.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/crypto.h>
#समावेश <यंत्र/vपन.स>

#समावेश "nx_csbcpb.h"
#समावेश "nx.h"


अटल पूर्णांक ctr_aes_nx_set_key(काष्ठा crypto_skcipher *tfm,
			      स्थिर u8               *in_key,
			      अचिन्हित पूर्णांक            key_len)
अणु
	काष्ठा nx_crypto_ctx *nx_ctx = crypto_skcipher_ctx(tfm);
	काष्ठा nx_csbcpb *csbcpb = nx_ctx->csbcpb;

	nx_ctx_init(nx_ctx, HCOP_FC_AES);

	चयन (key_len) अणु
	हाल AES_KEYSIZE_128:
		NX_CPB_SET_KEY_SIZE(csbcpb, NX_KS_AES_128);
		nx_ctx->ap = &nx_ctx->props[NX_PROPS_AES_128];
		अवरोध;
	हाल AES_KEYSIZE_192:
		NX_CPB_SET_KEY_SIZE(csbcpb, NX_KS_AES_192);
		nx_ctx->ap = &nx_ctx->props[NX_PROPS_AES_192];
		अवरोध;
	हाल AES_KEYSIZE_256:
		NX_CPB_SET_KEY_SIZE(csbcpb, NX_KS_AES_256);
		nx_ctx->ap = &nx_ctx->props[NX_PROPS_AES_256];
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	csbcpb->cpb.hdr.mode = NX_MODE_AES_CTR;
	स_नकल(csbcpb->cpb.aes_ctr.key, in_key, key_len);

	वापस 0;
पूर्ण

अटल पूर्णांक ctr3686_aes_nx_set_key(काष्ठा crypto_skcipher *tfm,
				  स्थिर u8               *in_key,
				  अचिन्हित पूर्णांक            key_len)
अणु
	काष्ठा nx_crypto_ctx *nx_ctx = crypto_skcipher_ctx(tfm);

	अगर (key_len < CTR_RFC3686_NONCE_SIZE)
		वापस -EINVAL;

	स_नकल(nx_ctx->priv.ctr.nonce,
	       in_key + key_len - CTR_RFC3686_NONCE_SIZE,
	       CTR_RFC3686_NONCE_SIZE);

	key_len -= CTR_RFC3686_NONCE_SIZE;

	वापस ctr_aes_nx_set_key(tfm, in_key, key_len);
पूर्ण

अटल पूर्णांक ctr_aes_nx_crypt(काष्ठा skcipher_request *req, u8 *iv)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा nx_crypto_ctx *nx_ctx = crypto_skcipher_ctx(tfm);
	काष्ठा nx_csbcpb *csbcpb = nx_ctx->csbcpb;
	अचिन्हित दीर्घ irq_flags;
	अचिन्हित पूर्णांक processed = 0, to_process;
	पूर्णांक rc;

	spin_lock_irqsave(&nx_ctx->lock, irq_flags);

	करो अणु
		to_process = req->cryptlen - processed;

		rc = nx_build_sg_lists(nx_ctx, iv, req->dst, req->src,
				       &to_process, processed,
				       csbcpb->cpb.aes_ctr.iv);
		अगर (rc)
			जाओ out;

		अगर (!nx_ctx->op.inlen || !nx_ctx->op.outlen) अणु
			rc = -EINVAL;
			जाओ out;
		पूर्ण

		rc = nx_hcall_sync(nx_ctx, &nx_ctx->op,
				   req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP);
		अगर (rc)
			जाओ out;

		स_नकल(iv, csbcpb->cpb.aes_cbc.cv, AES_BLOCK_SIZE);

		atomic_inc(&(nx_ctx->stats->aes_ops));
		atomic64_add(csbcpb->csb.processed_byte_count,
			     &(nx_ctx->stats->aes_bytes));

		processed += to_process;
	पूर्ण जबतक (processed < req->cryptlen);
out:
	spin_unlock_irqrestore(&nx_ctx->lock, irq_flags);
	वापस rc;
पूर्ण

अटल पूर्णांक ctr3686_aes_nx_crypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा nx_crypto_ctx *nx_ctx = crypto_skcipher_ctx(tfm);
	u8 iv[16];

	स_नकल(iv, nx_ctx->priv.ctr.nonce, CTR_RFC3686_IV_SIZE);
	स_नकल(iv + CTR_RFC3686_NONCE_SIZE, req->iv, CTR_RFC3686_IV_SIZE);
	iv[12] = iv[13] = iv[14] = 0;
	iv[15] = 1;

	वापस ctr_aes_nx_crypt(req, iv);
पूर्ण

काष्ठा skcipher_alg nx_ctr3686_aes_alg = अणु
	.base.cra_name		= "rfc3686(ctr(aes))",
	.base.cra_driver_name	= "rfc3686-ctr-aes-nx",
	.base.cra_priority	= 300,
	.base.cra_blocksize	= 1,
	.base.cra_ctxsize	= माप(काष्ठा nx_crypto_ctx),
	.base.cra_module	= THIS_MODULE,
	.init			= nx_crypto_ctx_aes_ctr_init,
	.निकास			= nx_crypto_ctx_skcipher_निकास,
	.min_keysize		= AES_MIN_KEY_SIZE + CTR_RFC3686_NONCE_SIZE,
	.max_keysize		= AES_MAX_KEY_SIZE + CTR_RFC3686_NONCE_SIZE,
	.ivsize			= CTR_RFC3686_IV_SIZE,
	.setkey			= ctr3686_aes_nx_set_key,
	.encrypt		= ctr3686_aes_nx_crypt,
	.decrypt		= ctr3686_aes_nx_crypt,
	.chunksize		= AES_BLOCK_SIZE,
पूर्ण;
