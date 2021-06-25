<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AES ECB routines supporting the Power 7+ Nest Accelerators driver
 *
 * Copyright (C) 2011-2012 International Business Machines Inc.
 *
 * Author: Kent Yoder <yoder1@us.ibm.com>
 */

#समावेश <crypto/aes.h>
#समावेश <crypto/algapi.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/crypto.h>
#समावेश <यंत्र/vपन.स>

#समावेश "nx_csbcpb.h"
#समावेश "nx.h"


अटल पूर्णांक ecb_aes_nx_set_key(काष्ठा crypto_skcipher *tfm,
			      स्थिर u8               *in_key,
			      अचिन्हित पूर्णांक            key_len)
अणु
	काष्ठा nx_crypto_ctx *nx_ctx = crypto_skcipher_ctx(tfm);
	काष्ठा nx_csbcpb *csbcpb = (काष्ठा nx_csbcpb *)nx_ctx->csbcpb;

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

	csbcpb->cpb.hdr.mode = NX_MODE_AES_ECB;
	स_नकल(csbcpb->cpb.aes_ecb.key, in_key, key_len);

	वापस 0;
पूर्ण

अटल पूर्णांक ecb_aes_nx_crypt(काष्ठा skcipher_request *req,
			    पूर्णांक                      enc)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा nx_crypto_ctx *nx_ctx = crypto_skcipher_ctx(tfm);
	काष्ठा nx_csbcpb *csbcpb = nx_ctx->csbcpb;
	अचिन्हित दीर्घ irq_flags;
	अचिन्हित पूर्णांक processed = 0, to_process;
	पूर्णांक rc;

	spin_lock_irqsave(&nx_ctx->lock, irq_flags);

	अगर (enc)
		NX_CPB_FDM(csbcpb) |= NX_FDM_ENDE_ENCRYPT;
	अन्यथा
		NX_CPB_FDM(csbcpb) &= ~NX_FDM_ENDE_ENCRYPT;

	करो अणु
		to_process = req->cryptlen - processed;

		rc = nx_build_sg_lists(nx_ctx, शून्य, req->dst, req->src,
				       &to_process, processed, शून्य);
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

		atomic_inc(&(nx_ctx->stats->aes_ops));
		atomic64_add(csbcpb->csb.processed_byte_count,
			     &(nx_ctx->stats->aes_bytes));

		processed += to_process;
	पूर्ण जबतक (processed < req->cryptlen);

out:
	spin_unlock_irqrestore(&nx_ctx->lock, irq_flags);
	वापस rc;
पूर्ण

अटल पूर्णांक ecb_aes_nx_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस ecb_aes_nx_crypt(req, 1);
पूर्ण

अटल पूर्णांक ecb_aes_nx_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस ecb_aes_nx_crypt(req, 0);
पूर्ण

काष्ठा skcipher_alg nx_ecb_aes_alg = अणु
	.base.cra_name		= "ecb(aes)",
	.base.cra_driver_name	= "ecb-aes-nx",
	.base.cra_priority	= 300,
	.base.cra_blocksize	= AES_BLOCK_SIZE,
	.base.cra_alignmask	= 0xf,
	.base.cra_ctxsize	= माप(काष्ठा nx_crypto_ctx),
	.base.cra_module	= THIS_MODULE,
	.init			= nx_crypto_ctx_aes_ecb_init,
	.निकास			= nx_crypto_ctx_skcipher_निकास,
	.min_keysize		= AES_MIN_KEY_SIZE,
	.max_keysize		= AES_MAX_KEY_SIZE,
	.setkey			= ecb_aes_nx_set_key,
	.encrypt		= ecb_aes_nx_encrypt,
	.decrypt		= ecb_aes_nx_decrypt,
पूर्ण;
