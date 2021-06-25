<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AES XCBC routines supporting the Power 7+ Nest Accelerators driver
 *
 * Copyright (C) 2011-2012 International Business Machines Inc.
 *
 * Author: Kent Yoder <yoder1@us.ibm.com>
 */

#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/aes.h>
#समावेश <crypto/algapi.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/crypto.h>
#समावेश <यंत्र/vपन.स>

#समावेश "nx_csbcpb.h"
#समावेश "nx.h"


काष्ठा xcbc_state अणु
	u8 state[AES_BLOCK_SIZE];
	अचिन्हित पूर्णांक count;
	u8 buffer[AES_BLOCK_SIZE];
पूर्ण;

अटल पूर्णांक nx_xcbc_set_key(काष्ठा crypto_shash *desc,
			   स्थिर u8            *in_key,
			   अचिन्हित पूर्णांक         key_len)
अणु
	काष्ठा nx_crypto_ctx *nx_ctx = crypto_shash_ctx(desc);
	काष्ठा nx_csbcpb *csbcpb = nx_ctx->csbcpb;

	चयन (key_len) अणु
	हाल AES_KEYSIZE_128:
		nx_ctx->ap = &nx_ctx->props[NX_PROPS_AES_128];
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	स_नकल(csbcpb->cpb.aes_xcbc.key, in_key, key_len);

	वापस 0;
पूर्ण

/*
 * Based on RFC 3566, क्रम a zero-length message:
 *
 * n = 1
 * K1 = E(K, 0x01010101010101010101010101010101)
 * K3 = E(K, 0x03030303030303030303030303030303)
 * E[0] = 0x00000000000000000000000000000000
 * M[1] = 0x80000000000000000000000000000000 (0 length message with padding)
 * E[1] = (K1, M[1] ^ E[0] ^ K3)
 * Tag = M[1]
 */
अटल पूर्णांक nx_xcbc_empty(काष्ठा shash_desc *desc, u8 *out)
अणु
	काष्ठा nx_crypto_ctx *nx_ctx = crypto_tfm_ctx(&desc->tfm->base);
	काष्ठा nx_csbcpb *csbcpb = nx_ctx->csbcpb;
	काष्ठा nx_sg *in_sg, *out_sg;
	u8 keys[2][AES_BLOCK_SIZE];
	u8 key[32];
	पूर्णांक rc = 0;
	पूर्णांक len;

	/* Change to ECB mode */
	csbcpb->cpb.hdr.mode = NX_MODE_AES_ECB;
	स_नकल(key, csbcpb->cpb.aes_xcbc.key, AES_BLOCK_SIZE);
	स_नकल(csbcpb->cpb.aes_ecb.key, key, AES_BLOCK_SIZE);
	NX_CPB_FDM(csbcpb) |= NX_FDM_ENDE_ENCRYPT;

	/* K1 and K3 base patterns */
	स_रखो(keys[0], 0x01, माप(keys[0]));
	स_रखो(keys[1], 0x03, माप(keys[1]));

	len = माप(keys);
	/* Generate K1 and K3 encrypting the patterns */
	in_sg = nx_build_sg_list(nx_ctx->in_sg, (u8 *) keys, &len,
				 nx_ctx->ap->sglen);

	अगर (len != माप(keys))
		वापस -EINVAL;

	out_sg = nx_build_sg_list(nx_ctx->out_sg, (u8 *) keys, &len,
				  nx_ctx->ap->sglen);

	अगर (len != माप(keys))
		वापस -EINVAL;

	nx_ctx->op.inlen = (nx_ctx->in_sg - in_sg) * माप(काष्ठा nx_sg);
	nx_ctx->op.outlen = (nx_ctx->out_sg - out_sg) * माप(काष्ठा nx_sg);

	rc = nx_hcall_sync(nx_ctx, &nx_ctx->op, 0);
	अगर (rc)
		जाओ out;
	atomic_inc(&(nx_ctx->stats->aes_ops));

	/* XOr K3 with the padding क्रम a 0 length message */
	keys[1][0] ^= 0x80;

	len = माप(keys[1]);

	/* Encrypt the final result */
	स_नकल(csbcpb->cpb.aes_ecb.key, keys[0], AES_BLOCK_SIZE);
	in_sg = nx_build_sg_list(nx_ctx->in_sg, (u8 *) keys[1], &len,
				 nx_ctx->ap->sglen);

	अगर (len != माप(keys[1]))
		वापस -EINVAL;

	len = AES_BLOCK_SIZE;
	out_sg = nx_build_sg_list(nx_ctx->out_sg, out, &len,
				  nx_ctx->ap->sglen);

	अगर (len != AES_BLOCK_SIZE)
		वापस -EINVAL;

	nx_ctx->op.inlen = (nx_ctx->in_sg - in_sg) * माप(काष्ठा nx_sg);
	nx_ctx->op.outlen = (nx_ctx->out_sg - out_sg) * माप(काष्ठा nx_sg);

	rc = nx_hcall_sync(nx_ctx, &nx_ctx->op, 0);
	अगर (rc)
		जाओ out;
	atomic_inc(&(nx_ctx->stats->aes_ops));

out:
	/* Restore XCBC mode */
	csbcpb->cpb.hdr.mode = NX_MODE_AES_XCBC_MAC;
	स_नकल(csbcpb->cpb.aes_xcbc.key, key, AES_BLOCK_SIZE);
	NX_CPB_FDM(csbcpb) &= ~NX_FDM_ENDE_ENCRYPT;

	वापस rc;
पूर्ण

अटल पूर्णांक nx_crypto_ctx_aes_xcbc_init2(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा nx_crypto_ctx *nx_ctx = crypto_tfm_ctx(tfm);
	काष्ठा nx_csbcpb *csbcpb = nx_ctx->csbcpb;
	पूर्णांक err;

	err = nx_crypto_ctx_aes_xcbc_init(tfm);
	अगर (err)
		वापस err;

	nx_ctx_init(nx_ctx, HCOP_FC_AES);

	NX_CPB_SET_KEY_SIZE(csbcpb, NX_KS_AES_128);
	csbcpb->cpb.hdr.mode = NX_MODE_AES_XCBC_MAC;

	वापस 0;
पूर्ण

अटल पूर्णांक nx_xcbc_init(काष्ठा shash_desc *desc)
अणु
	काष्ठा xcbc_state *sctx = shash_desc_ctx(desc);

	स_रखो(sctx, 0, माप *sctx);

	वापस 0;
पूर्ण

अटल पूर्णांक nx_xcbc_update(काष्ठा shash_desc *desc,
			  स्थिर u8          *data,
			  अचिन्हित पूर्णांक       len)
अणु
	काष्ठा xcbc_state *sctx = shash_desc_ctx(desc);
	काष्ठा nx_crypto_ctx *nx_ctx = crypto_tfm_ctx(&desc->tfm->base);
	काष्ठा nx_csbcpb *csbcpb = nx_ctx->csbcpb;
	काष्ठा nx_sg *in_sg;
	काष्ठा nx_sg *out_sg;
	u32 to_process = 0, leftover, total;
	अचिन्हित पूर्णांक max_sg_len;
	अचिन्हित दीर्घ irq_flags;
	पूर्णांक rc = 0;
	पूर्णांक data_len;

	spin_lock_irqsave(&nx_ctx->lock, irq_flags);


	total = sctx->count + len;

	/* 2 हालs क्रम total data len:
	 *  1: <= AES_BLOCK_SIZE: copy पूर्णांकo state, वापस 0
	 *  2: > AES_BLOCK_SIZE: process X blocks, copy in leftover
	 */
	अगर (total <= AES_BLOCK_SIZE) अणु
		स_नकल(sctx->buffer + sctx->count, data, len);
		sctx->count += len;
		जाओ out;
	पूर्ण

	in_sg = nx_ctx->in_sg;
	max_sg_len = min_t(u64, nx_driver.of.max_sg_len/माप(काष्ठा nx_sg),
				nx_ctx->ap->sglen);
	max_sg_len = min_t(u64, max_sg_len,
				nx_ctx->ap->databytelen/NX_PAGE_SIZE);

	data_len = AES_BLOCK_SIZE;
	out_sg = nx_build_sg_list(nx_ctx->out_sg, (u8 *)sctx->state,
				  &len, nx_ctx->ap->sglen);

	अगर (data_len != AES_BLOCK_SIZE) अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	nx_ctx->op.outlen = (nx_ctx->out_sg - out_sg) * माप(काष्ठा nx_sg);

	करो अणु
		to_process = total - to_process;
		to_process = to_process & ~(AES_BLOCK_SIZE - 1);

		leftover = total - to_process;

		/* the hardware will not accept a 0 byte operation क्रम this
		 * algorithm and the operation MUST be finalized to be correct.
		 * So अगर we happen to get an update that falls on a block sized
		 * boundary, we must save off the last block to finalize with
		 * later. */
		अगर (!leftover) अणु
			to_process -= AES_BLOCK_SIZE;
			leftover = AES_BLOCK_SIZE;
		पूर्ण

		अगर (sctx->count) अणु
			data_len = sctx->count;
			in_sg = nx_build_sg_list(nx_ctx->in_sg,
						(u8 *) sctx->buffer,
						&data_len,
						max_sg_len);
			अगर (data_len != sctx->count) अणु
				rc = -EINVAL;
				जाओ out;
			पूर्ण
		पूर्ण

		data_len = to_process - sctx->count;
		in_sg = nx_build_sg_list(in_sg,
					(u8 *) data,
					&data_len,
					max_sg_len);

		अगर (data_len != to_process - sctx->count) अणु
			rc = -EINVAL;
			जाओ out;
		पूर्ण

		nx_ctx->op.inlen = (nx_ctx->in_sg - in_sg) *
					माप(काष्ठा nx_sg);

		/* we've hit the nx chip previously and we're updating again,
		 * so copy over the partial digest */
		अगर (NX_CPB_FDM(csbcpb) & NX_FDM_CONTINUATION) अणु
			स_नकल(csbcpb->cpb.aes_xcbc.cv,
				csbcpb->cpb.aes_xcbc.out_cv_mac,
				AES_BLOCK_SIZE);
		पूर्ण

		NX_CPB_FDM(csbcpb) |= NX_FDM_INTERMEDIATE;
		अगर (!nx_ctx->op.inlen || !nx_ctx->op.outlen) अणु
			rc = -EINVAL;
			जाओ out;
		पूर्ण

		rc = nx_hcall_sync(nx_ctx, &nx_ctx->op, 0);
		अगर (rc)
			जाओ out;

		atomic_inc(&(nx_ctx->stats->aes_ops));

		/* everything after the first update is continuation */
		NX_CPB_FDM(csbcpb) |= NX_FDM_CONTINUATION;

		total -= to_process;
		data += to_process - sctx->count;
		sctx->count = 0;
		in_sg = nx_ctx->in_sg;
	पूर्ण जबतक (leftover > AES_BLOCK_SIZE);

	/* copy the leftover back पूर्णांकo the state काष्ठा */
	स_नकल(sctx->buffer, data, leftover);
	sctx->count = leftover;

out:
	spin_unlock_irqrestore(&nx_ctx->lock, irq_flags);
	वापस rc;
पूर्ण

अटल पूर्णांक nx_xcbc_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	काष्ठा xcbc_state *sctx = shash_desc_ctx(desc);
	काष्ठा nx_crypto_ctx *nx_ctx = crypto_tfm_ctx(&desc->tfm->base);
	काष्ठा nx_csbcpb *csbcpb = nx_ctx->csbcpb;
	काष्ठा nx_sg *in_sg, *out_sg;
	अचिन्हित दीर्घ irq_flags;
	पूर्णांक rc = 0;
	पूर्णांक len;

	spin_lock_irqsave(&nx_ctx->lock, irq_flags);

	अगर (NX_CPB_FDM(csbcpb) & NX_FDM_CONTINUATION) अणु
		/* we've hit the nx chip previously, now we're finalizing,
		 * so copy over the partial digest */
		स_नकल(csbcpb->cpb.aes_xcbc.cv,
		       csbcpb->cpb.aes_xcbc.out_cv_mac, AES_BLOCK_SIZE);
	पूर्ण अन्यथा अगर (sctx->count == 0) अणु
		/*
		 * we've never seen an update, so this is a 0 byte op. The
		 * hardware cannot handle a 0 byte op, so just ECB to
		 * generate the hash.
		 */
		rc = nx_xcbc_empty(desc, out);
		जाओ out;
	पूर्ण

	/* final is represented by continuing the operation and indicating that
	 * this is not an पूर्णांकermediate operation */
	NX_CPB_FDM(csbcpb) &= ~NX_FDM_INTERMEDIATE;

	len = sctx->count;
	in_sg = nx_build_sg_list(nx_ctx->in_sg, (u8 *)sctx->buffer,
				 &len, nx_ctx->ap->sglen);

	अगर (len != sctx->count) अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	len = AES_BLOCK_SIZE;
	out_sg = nx_build_sg_list(nx_ctx->out_sg, out, &len,
				  nx_ctx->ap->sglen);

	अगर (len != AES_BLOCK_SIZE) अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	nx_ctx->op.inlen = (nx_ctx->in_sg - in_sg) * माप(काष्ठा nx_sg);
	nx_ctx->op.outlen = (nx_ctx->out_sg - out_sg) * माप(काष्ठा nx_sg);

	अगर (!nx_ctx->op.outlen) अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	rc = nx_hcall_sync(nx_ctx, &nx_ctx->op, 0);
	अगर (rc)
		जाओ out;

	atomic_inc(&(nx_ctx->stats->aes_ops));

	स_नकल(out, csbcpb->cpb.aes_xcbc.out_cv_mac, AES_BLOCK_SIZE);
out:
	spin_unlock_irqrestore(&nx_ctx->lock, irq_flags);
	वापस rc;
पूर्ण

काष्ठा shash_alg nx_shash_aes_xcbc_alg = अणु
	.digestsize = AES_BLOCK_SIZE,
	.init       = nx_xcbc_init,
	.update     = nx_xcbc_update,
	.final      = nx_xcbc_final,
	.setkey     = nx_xcbc_set_key,
	.descsize   = माप(काष्ठा xcbc_state),
	.statesize  = माप(काष्ठा xcbc_state),
	.base       = अणु
		.cra_name        = "xcbc(aes)",
		.cra_driver_name = "xcbc-aes-nx",
		.cra_priority    = 300,
		.cra_blocksize   = AES_BLOCK_SIZE,
		.cra_module      = THIS_MODULE,
		.cra_ctxsize     = माप(काष्ठा nx_crypto_ctx),
		.cra_init        = nx_crypto_ctx_aes_xcbc_init2,
		.cra_निकास        = nx_crypto_ctx_निकास,
	पूर्ण
पूर्ण;
